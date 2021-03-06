#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
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

int forest_fire(int x, int y, double density)
{
    Forest *forest;
    printf(COLOR_YELLOW"\nForest Fire Simulation will be executed. "
        COLOR_RESET "Details:\n");
    printf("Gridsize: %d by %d\n", x, y);
    printf("Vegetation density: %g\n", density);
    forest = init_grid(x, y);
    fill_grid(forest, density);
    //print_grid(forest);
    //printf("\n");
    while(forest_fire_sim(forest))
    {
        //print_grid(forest);
        //printf("\n");
        //sleep(1);
    }
    if(forest->crossed > 0)
    {
        printf(COLOR_GREEN "Opposite side of the forest reached in %d "
            "steps.\n", forest->crossed);
        printf(COLOR_RESET);
        return forest->crossed;
    }
    printf(COLOR_RED "Couldn't reach the other side of the forest. "
        "Burning stopped after %d steps.\n", abs(forest->crossed));
    printf(COLOR_RESET);
    cleanup_grid(forest);
    free(forest);
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
    f->crossed = 0;
    for(i = 0; i < f->y; i++)
    {
        if(f->grid[0][i] == VEGETATION)
        {
            f->grid[0][i] = BURNING;
            f->burning[f->burns++] = i;
        }
    }
}

void print_grid(Forest *f)
{
    int i, j, veg = 0;
    for(i = 0; i < f->y; i++)
    {
        for(j = 0; j < f->x; j++)
        {
            if(f->grid[j][i] == 1)
                printf(COLOR_GREEN);
            if(f->grid[j][i] == 2)
                printf(COLOR_RED);
            if(f->grid[j][i] == 3)
                printf(COLOR_YELLOW);
            printf("%d", f->grid[j][i]);
            printf(COLOR_RESET);
            if(f->grid[j][i] == VEGETATION) veg++;
        }
        printf("\n");
    }
   // printf("Out of %d cells, %d are vegetated.\n", f->x*f->y, veg);
}

int forest_fire_sim(Forest *f)
{
    int *newburns = (int *)calloc(f->x*f->y, sizeof(int));
    int i, burn = 0;
    if(f->crossed < 1) f->crossed--;
    for(i = 0; i < f->burns; i++)
    {
        int x, y;
        x = f->burning[i] / f->y;
        y = f->burning[i] % f->y;
        //printf("BURNING: %d:%d (%d)\n", x, y, f->burning[i]);
        if(x > 0 && f->grid[x-1][y] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] - f->y;
            f->grid[x-1][y] = BURNING;
          //  printf("NEW BURN: %d:%d (%d)\n", x-1, y, f->burning[i] - f->x);
        }
        if(x < f->x-1 && f->grid[x+1][y] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] + f->y;
            f->grid[x+1][y] = BURNING;
            if(x == f->x-2 && f->crossed < 1)
            {
                f->crossed = abs(f->crossed);
            }
            //printf("NEW BURN: %d:%d (%d)\n", x+1, y, f->burning[i] + f->x);
        }
        if(y > 0 && f->grid[x][y-1] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] - 1;
            f->grid[x][y-1] = BURNING;
            //printf("NEW BURN: %d:%d (%d)\n", x, y-1, f->burning[i] - 1);
        }
        if(y < f->y-1 && f->grid[x][y+1] == VEGETATION)
        {
            newburns[burn++] = f->burning[i] + 1;
            f->grid[x][y+1] = BURNING;
            //printf("NEW BURN: %d:%d (%d)\n", x, y+1, f->burning[i] + 1);
        }
        f->grid[x][y] = BURNT;
    }
    f->burns = burn;
    f->burning = newburns;
    if(burn == 0) return 0;
    return 1;
}

void cleanup_grid(Forest *f)
{
    int i;
    for(i = 0; i < f->x; i++)
        free(f->grid[i]);
    free(f->grid);
    f->x = 0;
    f->y = 0;
    f->burns = 0;
    f->crossed = 0;
    free(f->burning);
}
