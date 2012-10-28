// PREDATOR.H
//

typedef struct Beast {
    int type, energy, x, y;
} Beast;

typedef struct Field {
    int x, y, preds, preys, incr, decr, prey_thres, pred_thres;
    int **grid;
    Beast **list;
} Field;

#define PREDATOR 0
#define PREY 1

#define PRED_INIT 50
#define PREY_INIT 50

Field* init_grid(int x, int y);
void fill_grid(Field *f, int preds, int preys, Beast **b);

int predator_model(int x, int y, int preds, int preys, int pred_decr,
    int prey_inc, int pred_thres, int prey_thres);
int get_free_adj_cell(Field *f, Beast *b, int *nx, int *ny);
int pred_prey_sim(Field *f, Beast **b, int msteps);
void get_free_cell(Field *f, int *x, int *y);
void print_grid(Field *f);
void eat_beast(Field *f, Beast *prey, Beast *pred);
void kill_beast(Field *f, Beast *b);
int move_beast(Field *f, Beast *b, int ox, int oy, int nx, int ny);
void procreate_beast(Field *f, Beast *b, Beast **list);
void create_beast(Field *f, Beast **b, int x, int y, int type, int energy);
int get_free_slot(Field *f, Beast **list);
