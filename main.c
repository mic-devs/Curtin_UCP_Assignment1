#include <stdio.h>
#include <stdlib.h>
#include "build.h"
#include "game.h"

int main(int argc, char* argv[])
{
    char** map;
    int row, column, status;
    row = atoi(argv[1]);
    column = atoi(argv[2]);

/* Checking Arguments */
    if (argc != 3)
    {
        printf("Error: Pass 3 arguments only!\n");
        return 1;
    }
    if (row < 3)
    {
        printf("Error: At least 3 rows required!\n");
        return 1;
    }
    if ((row % 2)!=1)
    {
        printf("Error: Number of rows must be an odd number!\n");
        return 1;
    }
    if (column < 5)
    {
        printf("Error: At least 5 rows required!\n");
        return 1;
    }
/* Checking Arguments */

    row += 2; /* Add rows for borders */
    column += 2; /* Add columns for borders */

    map = build(row, column); /* Build the play area map */

    status = play(map, row, column); /* Run game and receive win/lose result */

    if (status == 1)
    {
        printf("You win!\n");
    }
    else
    {
        printf("You lose!\n");
    }

    return 0;
}