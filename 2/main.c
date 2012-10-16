/*******************************************
 *               ModSim 2012               *
 *            Assignment nr. 2             *
 *           September 18, 2012            *
 *                                         *
 *           David van Erkelens            *
 *            Victor den Haan              *
 *                                         *
 *          University of Amsterdam        *
 *       Department of Computer Science    *
 *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"
#include "part1.h"
#include "part2.h"
#include "part3.h"
#include "part4.h"
#include "part5.h"

int main(int argc, char** argv) 
{
    printf("ModSim 2012 - Assignment 2. By David van Erkelens and "
            "Victor den Haan.\n");
    execute_part_one();
    execute_part_two();
    execute_part_three();
    execute_part_four();
    execute_part_five();
    return 0;
}