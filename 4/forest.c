#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "forest.h"

/* Settings for the wind */
#define WIND 0
#define WINDX -1
#define WINDY 1

/* Defining the states in which the cells can be */
#define BARREN 0
#define VEGETATION 1
#define BURNING 2
#define BURNT 3

/*
 * TODO FOR FOREST FIRE:
 * 1. Implement the grid (multi dimensional array)
 * 2. Write some simple loops to emulate the forest fire
 * 3. Output some images show the simulation
 * 4. Think about optimisation. (only looking at the burning trees?)
 */

int forest_fire(int x, int y, double density)
{
    int i, j;
    Forest forest;
    printf("Forest Fire Simulation will be executed. Details:\n");
    printf("Gridsize: %d by %d\n", x, y);
    printf("Vegetation density: %g\n", density);
    forest = init_grid(x, y);
    fill_grid(&forest, density);
}

Forest init_grid(int x, int y)
{
    Forest newgrid;
    char **content;
    int i;
    newgrid = (Forest *)malloc(sizeof(Forest));
    content = (char **)calloc(x, sizeof(char *));
    for(i = 0; i < x; i++)
        content[i] = (char *)calloc(y, sizeof(char));
    newgrid->x = x;
    newgrid->y = y;
    newgrid->grid = content;
    newgrid->burning = (int *)calloc(x*y, sizeof(int));
    for(i = 0; i < x*y; i++)
        newgrid->burning[i] = -1;
    return newgrid;
}

void fill_grid(Forest *f, double density)
{
    int i, j;
    srand(time(NULL));
    for(i = 0; i < f->x; i++)
    {
        for(j = 0; j < f->y; j++)
        {
            double number = (rand() % 1000) / 1000.0;
            if(number <= density)
                f->grid[i][j] = VEGETATION;
            else
                f->grid[i][j] = BARREN;
        }
    }
}

void print_grid(Forest *f)
{

}
