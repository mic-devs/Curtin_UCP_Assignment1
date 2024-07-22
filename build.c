#include <stdio.h>
#include <stdlib.h>
#include "build.h"

char** build(int row, int column)
{
    int i, j; 
    char** area; /* the play map*/

/* Creating the 2D Array */
    area = (char**)malloc(row * sizeof(int*)); /* Sets the rows */
    for (i = 0; i < row; i++) /* Sets the columns */
    { 
        area[i] = (char*)malloc(column * sizeof(int));
    }
/* Creating the 2D Array */

/* Fill the area with space */
    for (i = 0; i < row; i++) /* Cycle through the rows */
    { 
        for (j = 0; j < column; j++) /* Cycle through the columns */
        {
            area[i][j] = ' ';
        }
    }
/* Fill the area with space */

/* Making the borders */
    for (i = 0; i < column; i++) /* Set top & bottom borders */
    { 
        area[0][i] = '*';
        area[row-1][i]= '*';
    }

    for (i = 1; i < row-1; i++) /* Set left & right borders */
    {
        area[i][0] = '*';
        area[i][column-1] = '*';
    }

/* Making the borders */

/* Cementing the roads */
    for (i = 2; i < row-1; i++)
    {
        for (j = 1; j < column-1; j++)
        {
            area[i][j] = '.';
        }
        i++;
    }
/* Cementing the roads */

    area[1][1] = 'P'; /* Initialise player */
    area[row-2][column-2] = 'G'; /* Initialise goal */

    return area;

    for(i = 0; i < row; i++) /* free the area */
    {
        free(area[i]);
        area[i] = NULL;
    }
    free(area);
    area = NULL;
}