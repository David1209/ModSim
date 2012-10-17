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

#include "forest.h"

#define X 0
#define Y 1

#define SMALL 0
#define MEDIUM 1
#define LARGE 2

int main()
{
    int dim[3][2] = {{10,10}, {50,40}, {250,250}};
    double densities[] = {0.5, 0.6, 0.7, 0.8};
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 4; j++)
        {
            forest_fire(dim[i][X], dim[i][Y], densities[j]);
        }
    }
    return 0;
}
