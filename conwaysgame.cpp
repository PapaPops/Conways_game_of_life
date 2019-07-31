#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cstdlib>
#include<chrono>
#include<thread>


#define width 40
#define height 40

int **grid;

void initialize(int **arr)
{
    for(int i = 0; i< width; i++)
        {
            for(int j = 0; j<height; j++)
            {
                if(rand()%3 == 0)
                {
                    arr[i][j] = 1;
                }
                else
                {
                    arr[i][j] = 0;
                }
                
            }
        }
}

void draw_grid(int **arr)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j<height;j++)
            {

                std::cout<<((arr[i][j] == 0) ? " " : "■");
                std::cout<<" ";
            }
        std::cout<<"\n";
    }
}

int count_neighbors(int (&arr)[width][height],int x_width,int y_height)
{
    int neighbors = 0;
    for(int i = -1; i <=1; i++)
    {
        for(int j = -1; j<=1;j++)
        {
            if(arr[x_width+i][y_height+j]==1)
                {
                    neighbors++;
                }
        }
    }

    if(arr[x_width][y_height] == 1)
        neighbors--;

    return neighbors;
}

void update(int **arr)
{

int previous_arr[width][height];

for(int i = 0; i < width; i++)
{
    for(int j = 0; j<height; j++)
        previous_arr[i][j] = arr[i][j];
}

for(int i = 1; i<width-1;i++)
{

    for(int j = 1; j<height-1;j++)
    {
        int neighbors = count_neighbors(previous_arr,i,j);

        if(previous_arr[i][j] == 0 && neighbors == 3)
            arr[i][j] = 1;
        else if(previous_arr[i][j] == 1 && neighbors <= 1)
            arr[i][j] = 0;
        else if(previous_arr[i][j] == 1 && neighbors >= 4)
            arr[i][j] = 0;
        else if(previous_arr[i][j] == 1 && (neighbors == 2 || neighbors == 3))
            arr[i][j] = 1;

    }

}

}

int main()
{
    srand(time(NULL));
    grid = new int *[width];
    for(int i = 0; i < width; i++)
    {
        grid[i] = new int[height];
    }


    initialize(grid);
    std::cout<<"sleep time? (seconds) ";
    float sleeptime;
    std::cin>>sleeptime;

    sleeptime *= 1000;
    


    while(true)
    {
        system("clear");
        update(grid);
        draw_grid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)sleeptime));
    }

    return 0;
}