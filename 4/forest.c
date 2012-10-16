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

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

/*
 * TODO FOR FOREST FIRE:
 * 1. Implement the grid (multi dimensional array)
 * 2. Write some simple loops to emulate the forest fire
 * 3. Output some images show the simulation
 * 4. Think about optimisation. (only looking at the burning trees?)
 */

int forest_fire(int x, int y, double density)
{
    Forest *forest;
    printf("Forest Fire Simulation will be executed. Details:\n");
    printf("Gridsize: %d by %d\n", x, y);
    printf("Vegetation density: %g\n", density);
    forest = init_grid(x, y);
    fill_grid(forest, density);
    int i = 0;
    print_grid(forest);
    while(i < 10)
    {
        forest_fire_sim(forest);
        print_grid(forest);
        i++;
        printf("\n");
    }
    return 0;
}

Forest* init_grid(int x, int y)
{
    Forest *newgrid;
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
    f->burning[0] = 5;
    f->burns = 1;
    f->grid[0][5] = BURNING;
}

void print_grid(Forest *f)
{
    int i, j, veg = 0;
    for(i = 0; i < f->x; i++)
    {
        for(j = 0; j < f->y; j++)
        {
            if(f->grid[i][j] == 1)
                printf(COLOR_GREEN);
            if(f->grid[i][j] == 2)
                printf(COLOR_RED);
            if(f->grid[i][j] == 3)
                printf(COLOR_YELLOW);
            printf("%d", f->grid[i][j]);
            printf(COLOR_RESET);
            if(f->grid[i][j] == VEGETATION) veg++;
        }
        printf("\n");
    }
   // printf("Out of %d cells, %d are vegetated.\n", f->x*f->y, veg);
}

void forest_fire_sim(Forest *f)
{
    int *newburns = (int *)calloc(f->x*f->y, sizeof(int));
    int i, burn = 0;
    for(i = 0; i < f->burns; i++)
    {
        int x, y;
        if(f->burning[i] < 0) break;
        x = f->burning[i] / f->x;
        y = f->burning[i] % f->x;
        //printf("BURNING: %d:%d\n", x, y);
        if(x > 0 && f->grid[x-1][y] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] - f->x;
            f->grid[x-1][y] = BURNING;
            //printf("NEW BURN: %d:%d (%d)\n", x-1, y, f->burning[i] - f->x);
        }
        if(x < f->x && f->grid[x+1][y] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] + f->x;
            f->grid[x+1][y] = BURNING;
            //printf("NEW BURN: %d:%d (%d)\n", x+1, y, f->burning[i] + f->x);
        }
        if(y > 0 && f->grid[x][y-1] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] - 1;
            f->grid[x][y-1] = BURNING;
            //printf("NEW BURN: %d:%d (%d)\n", x, y-1, f->burning[i] - 1);
        }
        if(y < f->y && f->grid[x][y+1] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] + 1;
            f->grid[x][y+1] = BURNING;
            //printf("NEW BURN: %d:%d (%d)\n", x, y+1, f->burning[i] + 1);
        }
        f->grid[x][y] = BURNT;
    }
    f->burns = burn;
    f->burning = newburns;
}
