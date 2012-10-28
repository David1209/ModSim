// PREDATOR.C
// BY DAVID VAN ERKELENS
// AND VICTOR DEN HAANi
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "predator.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

int predator_model(int x, int y, int preds, int preys, int pred_decr,
    int prey_inc, int pred_thres, int prey_thres)
{
    Field *f;
    Beast *b[x*y];
    if((x * y) < (preds + preys))
    {
        printf("The grid is too small for all beasts. The program will "
            "now terminate.\n");
        exit(0);
    }
    f = init_grid(x, y);
    f->list = (Beast **)b;
    f->prey_thres = prey_thres;
    f->pred_thres = pred_thres;
    f->incr = prey_inc;
    f->decr = pred_decr;
    //b = (Beast **)malloc(preds + preys * sizeof(Beast *));
    fill_grid(f, preds, preys, b);
    printf("%d\n", b[0]->energy);
    print_grid(f);
    printf("%d\n", pred_prey_sim(f, b, 50));
    return 0;
}

Field* init_grid(int x, int y)
{
    Field *newfield;
    int **content;
    int i;
    newfield = (Field *)malloc(sizeof(Field));
    content = (int **)malloc(x * sizeof(int *));
    for(i = 0; i < x; i++)
    {
        int j;
        content[i] = (int *)malloc(y * sizeof(int));
        for(j = 0; j < y; j++)
            content[i][j] = -1;
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
        f->grid[x][y] = i;
        printf("New beast (%d) inserted into cell %d:%d (health: %d)\n",
            newbeast->type, newbeast->x, b[i]->y, newbeast->energy);
    }
    for(i = preds + preys; i < f->x * f->y; i++)
    {
        b[i] = NULL;
    }
}

void get_free_cell(Field *f, int *x, int *y)
{
    int nx, ny;
    srand(time(NULL));
    nx = rand() % f->x;
    ny = rand() % f->y;
    while(f->grid[nx][ny] != -1)
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
            if(f->grid[i][j] == -1)
                printf("0");
            else if(f->list[f->grid[i][j]]->type == PREDATOR)
                printf(COLOR_RED"H"COLOR_RESET);
            else
                printf(COLOR_GREEN"P"COLOR_RESET);
        }
        printf("\n");
    }
}

int pred_prey_sim(Field *f, Beast **b, int msteps)
{
    int beasts = f->x * f->y, steps = 0, ret;
    while(1)
    {
        int i;
        steps++;
        printf("Predators: %d, Preys: %d\n", f->preds, f->preys);
        for(i = 0; i < beasts; i++)
        {
            int nx, ny, x, y;
            if(b[i] == NULL) continue;
            x = b[i]->x;
            y = b[i]->y;
            ret = get_free_adj_cell(f, b[i], &nx, &ny);
            if(ret)
            {
                //printf("test\n");
                if(ret == 2)
                {
                    //printf("%d:%d eats %d:%d\n", x, y, nx, ny);
                    eat_beast(f, b[f->grid[nx][ny]], b[i]);
                }
                else if(move_beast(f, b[i], x, y, nx, ny))
                {
                    char *names[2] = {"Predator", "Prey"};
                    //printf("%s %d:%d moves to %d:%d\n", names[b[i]->type], x, y, nx, ny);
                    //procreate_beast(f, b[i], b);
                }
            }
            procreate_beast(f, b[i], b);
        }
        //print_grid(f);
        //printf("\n");
        //sleep(1);
        if(f->preds == 0)
        {
            printf("The predators went extinct.\n");
            return steps;
        }
        if(f->preys == 0)
        {
            printf("The preys went extinct.\n");
            return -1 * steps;
        }
        if(steps == msteps)
            break;
    }
    return 0;
}

int get_free_adj_cell(Field *f, Beast *b, int *nx, int *ny)
{
    int dir, tx, ty, i, x, y;
    srand(time(NULL)+b->x+b->y);
    dir = rand() % 4;
    x = b->x;
    y = b->y;
    tx = x;
    ty = y;
    //printf("xy %d:%d\n", x, y);
    for(i = 0; i < 4; i++)
    {
        //printf("1\n");
        tx = x;
        ty = y;
        if(dir == 0 && x > 0) tx --;
        if(dir == 1 && y < f->y - 1) ty ++;
        if(dir == 2 && x < f->x - 1) tx ++;
        if(dir == 3 && y > 0) ty --;
        //printf("2\n");
        //printf("%d:%d\n", tx, ty);
        if(f->grid[tx][ty] == -1)
        {
            *nx = tx;
            *ny = ty;
            return 1;
        }
        //printf("2.4\n");
        if(b->type == PREDATOR && f->list[f->grid[tx][ty]]->type == PREY)
        {
            *nx = tx;
            *ny = ty;
            return 2;
        }
        //printf("3\n");
        dir++;
        dir %= 4;
    }
    return 0;
}

void eat_beast(Field *f, Beast *prey, Beast *pred)
{
    pred->energy += prey->energy;
    kill_beast(f, prey);
}

void kill_beast(Field *f, Beast *b)
{
    if(b->type == PREDATOR)
        f->preds--;
    else
        f->preys--;
    //free(f->grid[b->x][b->y]);
    f->grid[b->x][b->y] = -1;
}

int move_beast(Field *f, Beast *b, int ox, int oy, int nx, int ny)
{
    if(b->type == PREDATOR)
    {
        if(b->energy - f->decr <= 0)
        {
            kill_beast(f, b);
            return 0;
        }
        b->energy -= f->decr;
    }
    else
    {
        b->energy += f->incr;
    }
    //printf("Moving beast to %d:%d, clearing %d:%d\n", nx, ny, ox, oy);
    f->grid[nx][ny] = f->grid[ox][oy];
    f->grid[ox][oy] = -1;
    b->x = nx;
    b->y = ny;
    return 1;
}

void procreate_beast(Field *f, Beast *b, Beast **list)
{
    /*if(b->type == PREDATOR && b->energy >= f->pred_thres)
    {
        Beast dummy;
        int x, y;
        dummy.x = b->x;
        dummy.y = b->y;
        dummy.type = PREY;
        if(get_free_adj_cell(f, &dummy, &x, &y))
        {
            int newhealth = b->energy / 2;
            b->energy = newhealth;
            create_beast(f, list, x, y, PREDATOR, newhealth);
        }
    }*/
    if(b->type == PREY && b->energy >= f->prey_thres)
    {
        int x, y;
        if(get_free_adj_cell(f, b, &x, &y))
        {
            int newhealth = b->energy / 2;
            b->energy = newhealth;
            create_beast(f, list, x, y, PREY, newhealth);
        }
        f->preys ++;
    }
}

void create_beast(Field *f, Beast **b, int x, int y, int type, int energy)
{
    Beast *newbeast;
    int i;
    newbeast = (Beast *)malloc(sizeof(Beast));
    get_free_cell(f, &x, &y);
    newbeast->x = x;
    newbeast->y = y;
    newbeast->type = type;
    newbeast->energy = energy;
    i = get_free_slot(f, b);
    b[i] = newbeast;
    f->grid[x][y] = i;
}

int get_free_slot(Field *f, Beast **list)
{
    int i;
    Beast **list2;
    for(i = 0; i < f->preds + f-> preys; i++)
    {
        if(list[i] == NULL) return i;
    }
    list2 = (Beast **)calloc(f->preds + f->preys + 10, sizeof(Beast *));
    for(i = 0; i < f->preds + f-> preys; i++)
        list2[i] = list[i];
    list = list2;
    return i;
}
