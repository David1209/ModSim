#ifndef FORESTH
#define FORESTH

typedef struct {
    char **grid;
    signed int *burning;
    int x, y, burns;
} Forest;

int forest_fire(int x, int y, double density);
Forest* init_grid(int x, int y);
void fill_grid(Forest *f, double density);
void print_grid(Forest *f);
void forest_fire_sim(Forest *f);

#endif
