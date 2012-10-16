#ifndef FORESTH
#define FORESTH

typedef struct {
    char **grid;
    signed int *burning;
} forest;

int forest_fire(int x, int y, double density);

#endif
