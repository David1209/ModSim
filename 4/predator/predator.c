// PREDATOR.C
// BY DAVID VAN ERKELENS
// AND VICTOR DEN HAAN
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "predator.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

int predator_model(int x, int y, int preds, int preys, int pred_decr,
    int pred_inc, int pred_thres, int prey_thres)
{
    Field *f;
    Beast **b;
    if((x * y) < (preds + preys))
    {
        printf("The grid is too small for all beasts. The program will "
            "now terminate.\n");
        exit(0);
    }
    f = init_grid(x, y);
    fill_grid(f, x, y, b);
    print_grid(f);
    return 0;
}

Field* init_grid(int x, int y)
{
    Field *newfield;
    Beast ***content;
    int i;
    newfield = (Field *)malloc(sizeof(Field));
    content = (Beast ***)malloc(x * sizeof(Beast **));
    for(i = 0; i < x; i++)
    {
        int j;
        content[i] = (Beast **)malloc(y * sizeof(Beast *));
        for(j = 0; j < y; j++)
            content[i][j] = NULL;
    }
    newfield->x = x;
    newfield->y = y;
    newfield->grid = content;
    return newfield;
}

void fill_grid(Field *f, int preds, int preys, Beast **b)
{
    int i;
    f->preds = preds;
    f->preys = preys;
    b = (Beast **)calloc(preds + preys, sizeof(Beast *));
    for(i = 0; i < preys + preds; i++)
    {
        int x, y;
        Beast *newbeast;
        newbeast = (Beast *)malloc(sizeof(Beast));
        get_free_cell(f, &x, &y);
        newbeast->x = x;
        newbeast->y = y;
        if(i < preys)
        {
            newbeast->type = PREY;
            newbeast->energy = PREY_INIT;
        }
        else
        {
            newbeast->type = PREDATOR;
            newbeast->energy = PRED_INIT;
        }
        b[i] = newbeast;
        f->grid[x][y] = newbeast;
        printf("New beast (%d) inserted into cell %d:%d (health: %d)\n",
            newbeast->type, newbeast->x, b[i]->y, newbeast->energy);
    }
}

void get_free_cell(Field *f, int *x, int *y)
{
    int nx, ny;
    srand(time(NULL));
    nx = rand() % f->x;
    ny = rand() % f->y;
    while(f->grid[nx][ny] != NULL)
    {
        nx = rand() % f->x;
        ny = rand() % f->y;
    }
    *x = nx;
    *y = ny;
}

void print_grid(Field *f)
{
    int i, j;
    for(i = 0; i < f->x; i++)
    {
        for(j = 0; j < f->y; j++)
        {
            if(f->grid[i][j] == NULL)
                printf("0");
            else if(f->grid[i][j]->type == PREDATOR)
                printf(COLOR_RED"H"COLOR_RESET);
            else
                printf(COLOR_GREEN"P"COLOR_RESET);
        }
        printf("\n");
    }
}
