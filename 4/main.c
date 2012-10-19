/*
 *  Assignment 4 - Modelating & Simulating Course
 *  By David van Erkelens <David.vanErkelens@student.uva.nl>
 *  And Victor den Haan <Victor.denHaan@student.uva.nl>
 *
 *  Department of Computer Science
 *  University of Amsterdam
 *  October 2012
 *
 *  This program describes two cellular automata: Forest Fire Propagation and
 *  The Spread of Malaria/Predator-Prey Model. The first will be implemented
 *  anyway, and one (or two, if there is enough time) of the last two.
 */

#include <stdio.h>
#include "forest.h"

#define X 0
#define Y 1

#define SMALL 0
#define MEDIUM 1
#define LARGE 2

#define GRIDS 4
#define DENSITIES 15

int main()
{
    int dim[GRIDS][2] = {{10,20}, {40,40}, {50,40}, {75,75}};
    double densities[DENSITIES] = {0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};
    int steps[GRIDS][DENSITIES];
    int i, j;
    FILE *data;
    data = fopen("data.dat", "w+");
    fprintf(data, "# DATA FILE CREATED BY FOREST FIRE SIMULATION\n");
    for(i = 0; i < GRIDS; i++)
    {
        for(j = 0; j < DENSITIES; j++)
        {
            steps[i][j] = forest_fire(dim[i][X], dim[i][Y], densities[j]);
            printf("For gridsize %d:%d with density %f the other end of the "
                "forest is reached in %d steps.\n", dim[i][X], dim[i][Y],
                densities[j], steps[i][j]);
            fprintf(data, "%d %d %d %f %d\n", dim[i][X], dim[i][Y],
                dim[i][X]*dim[i][Y], densities[j], steps[i][j]);
        }
    }
    fclose(data);
    FILE *gp;
    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set title \"Density vs. steps\"\n");
    fprintf(gp, "set pointsize 2 \n");
    fprintf(gp, "set xlabel \"Number of steps required\\n(0 = not reached)\"\n");
    fprintf(gp, "set ylabel \"Forest Density\"\n");
    fprintf(gp, "set cblabel \"Forest width\"\n");
    fprintf(gp, "plot \"data.dat\" using 5:4:1 notitle with points lt palette pt 13\n");
    fprintf(gp, "set terminal png \n");
    fprintf(gp, "set output \"test.png\"\n");
    fprintf(gp, "replot\n");
    fclose(gp);
    return 0;
}
