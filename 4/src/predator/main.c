// MAIN.C

#include <stdio.h>
#include "predator.h"

int main()
{
    FILE *data, *gp;
    int i, j;
    data = fopen("data.dat", "w+");
    fprintf(data, "# DATA FILE CREATED BY PREDATOR PREY SIMULATION\n");
    for(i = 0; i <= 10; i++)
    {
        fprintf(data, "%d %d %d %d %d %d\n", i*5, 20, 10, 10, 250,
            predator_model(15, 15, i*5, 20, 5, 5, 250));
    }
    fclose(data);
    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set title \"Number of predators vs extinction\"\n");
    fprintf(gp, "set pointsize 2 \n");
    fprintf(gp, "set xlabel \"Number of predators\"\n");
    fprintf(gp, "set ylabel \"Steps to extinction\"\n");
    fprintf(gp, "plot \"data.dat\" using 1:6 notitle with line\n");
    fprintf(gp, "set terminal png \n");
    fprintf(gp, "set output \"pred_vs_exinc.png\"\n");
    fprintf(gp, "replot\n");
    fclose(gp);
    data = fopen("data.dat", "w+");
    fprintf(data, "# DATA FILE CREATED BY PREDATOR PREY SIMULATION\n");
    for(i = 0; i <= 10; i++)
    {
        fprintf(data, "%d %d %d %d %d %d\n", 20, i*5, 10, 10, 250,
            predator_model(15, 15, 20, i*5, 5, 5, 250));
    }
    fclose(data);
    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set title \"Number of preys vs extinction\"\n");
    fprintf(gp, "set pointsize 2 \n");
    fprintf(gp, "set xlabel \"Number of preys\"\n");
    fprintf(gp, "set ylabel \"Steps to extinction\"\n");
    fprintf(gp, "plot \"data.dat\" using 2:6 notitle with line\n");
    fprintf(gp, "set terminal png \n");
    fprintf(gp, "set output \"prey_vs_exinc.png\"\n");
    fprintf(gp, "replot\n");
    fclose(gp);
}
