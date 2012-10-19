// PREDATOR.H
//

typedef struct Beast {
    int type, energy, x, y;
} Beast;

typedef struct Field {
    int x, y, preds, preys, incr, decr, prey_thres, pred_thres;
    Beast ***grid;
} Field;

#define PREDATOR 0
#define PREY 1

#define PRED_INIT 50
#define PREY_INIT 50

Field* init_grid(int x, int y);
void fill_grid(Field *f, int preds, int preys, Beast **b);

int predator_model(int x, int y, int preds, int preys, int pred_decr,
    int prey_inc, int pred_thres, int prey_thres);
void get_adj_free_cell(int x, int y, int *nx, int *ny);
int pred_prey_sim(Field *f, Beast **b);
void get_free_cell(Field *f, int *x, int *y);
void print_grid(Field *f);
