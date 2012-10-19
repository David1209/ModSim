// PREDATOR.H
//

typedef struct Field {
    int x, y, preds, preys;
    char **grid;
} Field;

typedef struct Beast {
    int type, energy, x, y;
} Beast;

#define PREDATOR 0
#define PREY 1

#define PRED_INT 50
#define PREY_INT 50

int predator_model(int x, int y, int preds, int preys, int pred_decr,
    int prey_inc, int pred_thres, int prey_thres);
void get_adj_cell(int x, int y, int *nx, int *ny);
int pred_prey_sim(Field *f, Beast b[]);
void get_rand_free_cell(int *x, int *y);
