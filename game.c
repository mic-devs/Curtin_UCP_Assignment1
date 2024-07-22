#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "terminal.h"
#include "random.h"

int play(char** map, int row, int column)
{
    int status = 0; /* 0 for in-game, 1 for win, 2 for lose */
    int i, j, carStart, carDirection, carFound, jump;
    char move, temp;
    int player[2] = {1,1}; /* Player coordinates */

    initRandom();

/* Set the cars */
    for (i = 2; i < row-1; i++) /* Go through every road (even) row */
    { 
        carStart = randomUCP(1, column-2); /* Assign random car start location */
        carDirection = randomUCP(0,1); /* Assign random direction, 0 for left, 1 for right */

        if (carStart == 1)
        { /* if car on left-end, face car to right */
            map[i][carStart] = '>'; 
        }
        else if (carStart == (column-2) )
        { /* if car on right-end, face car to left */
            map[i][carStart] = '<';
        }
        else
        { /* if car mid-road, face to respective direction */
            if (carDirection == 0)
            {
                map[i][carStart] = '<';
            }
            else
            {
                map[i][carStart] = '>';
            }
        }
        i++;
    }   
    
/* Set the cars */

    while (status == 0)
    {   
        system("clear"); /* clears the terminal screen */
        for (i = 0; i < row; i++) /* Prints the play area map */
        { 
            for (j = 0; j < column; j++) 
            {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        printf("Press w to move up\n");
        printf("Press s to move down\n");
        printf("Press a to move left\n");
        printf("Press d to move right\n");

        disableBuffer();
        scanf("%c", &move); /* take player movement */
        enableBuffer();

/* Player Movement */
        jump = 0; /* keep track if player jumps over car */
        if (move == 's') /* move down */
        {
            if ( (player[0]+1) != (row-1) ) /* ensure player doesn't pass border */
            {
                temp = map[ player[0]+1 ][ player[1] ]; /* destination */
                
                if (temp == '.')
                { /* if destination is road, origin must be blank */
                    map[ player[0] ][ player[1] ] = ' '; /* mark origin with blank*/
                    map[ player[0]+1 ][ player[1] ] = 'P'; /* mark destination with P */
                }
                else if ((temp == '<') || (temp == '>'))
                { /* player jumps over car */
                    map[ player[0] ][ player[1] ] = ' '; /* mark origin with blank*/
                    jump = 1; /* reinstate 'P' later after cars have moved */
                }
                else
                { /* if destination is blank, origin must be road */
                    map[ player[0] ][ player[1] ] = '.'; /* mark origin with road*/
                    map[ player[0]+1 ][ player[1] ] = 'P'; /* mark destination with P */
                }
                
                player[0] = player[0] + 1; /* Update player coordinates */
            }
        }
        else if (move == 'w') /* move up */
        {
            if ( (player[0]-1) != 0 ) /* ensure player doesn't pass border */
            {
                temp = map[ player[0]-1 ][ player[1] ]; /* destination */
                
                if (temp == '.')
                { /* if destination is road, origin must be blank */
                    map[ player[0] ][ player[1] ] = ' '; /* mark origin with blank*/
                    map[ player[0]-1 ][ player[1] ] = 'P'; /* mark destination with P */
                }
                else if ((temp == '<') || (temp == '>'))
                { /* player jumps over car */
                    map[ player[0] ][ player[1] ] = ' '; /* mark origin with blank*/
                    jump = 1; /* reinstate 'P' later after cars have moved */
                }
                else
                { /* if destination is blank, origin must be road */
                    map[ player[0] ][ player[1] ] = '.'; /* mark origin with road*/
                    map[ player[0]-1 ][ player[1] ] = 'P'; /* mark destination with P */
                }
                
                player[0] = player[0] - 1; /* Update player coordinates */
            }
        }
        else if (move == 'a') /* move left */
        {
            if ( (player[1]-1) != 0 ) /* ensure player doesn't pass border */
            {
                temp = map[ player[0] ][ player[1]-1 ]; /* destination */
                
                if (temp == '.')
                { /* if destination is road, origin must be road */
                    map[ player[0] ][ player[1] ] = '.'; /* mark origin with road*/
                    map[ player[0] ][ player[1]-1 ] = 'P'; /* mark destination with P */
                }
                else if ((temp == '<') || (temp == '>'))
                { /* player jumps over car */
                    map[ player[0] ][ player[1] ] = '.'; /* mark origin with blank*/
                    jump = 1; /* reinstate 'P' later after cars have moved */
                }
                else
                { /* if destination is blank, origin must be blank */
                    map[ player[0] ][ player[1] ] = ' '; /* mark origin with blank*/
                    map[ player[0] ][ player[1]-1 ] = 'P'; /* mark destination with P */
                }
                
                player[1] = player[1] - 1; /* Update player coordinates */
            }
        }
        else if (move == 'd') /* move right */
        {
            if ( (player[1]+1) != column-1 ) /* ensure player doesn't pass border */
            {
                temp = map[ player[0] ][ player[1]+1 ]; /* destination */
                
                if (temp == '.')
                { /* if destination is road, origin must be road */
                    map[ player[0] ][ player[1] ] = '.'; /* mark origin with road*/
                    map[ player[0] ][ player[1]+1 ] = 'P'; /* mark destination with P */
                }
                else if ((temp == '<') || (temp == '>'))
                { /* player jumps over car */
                    map[ player[0] ][ player[1] ] = '.'; /* mark origin with blank*/
                    jump = 1; /* reinstate 'P' later after cars have moved */
                }
                else
                { /* if destination is blank, origin must be blank */
                    map[ player[0] ][ player[1] ] = ' '; /* mark origin with blank*/
                    map[ player[0] ][ player[1]+1 ] = 'P'; /* mark destination with P */
                }
                
                player[1] = player[1] + 1; /* Update player coordinates */
            }
        }
        else
        {
            /* nothing happens if user enters invalid input */
        }
/* Player Movement */

/* Car Movement */
        for (i = 2; i < row-1; i++) /* Go through every even row to find car */
        {
            carFound = 0;

            for (j = 2; j < column-1; j++) /* go through the row from right to left */
            {
                if (map[i][j] == '<') /* find left-facing car */
                {
                    carFound = 1;
                    if (map[i][j-1] == 'P') /* check if car will crash into player */
                    {
                        map[i][j] = '.'; /* re-initialise car origin to road */
                        status = 2;
                    }
                    else if (map[i][j-1] == '.') /* check if destination is road */
                    {
                        map[i][j] = '.'; /* re-initialise car origin to road */
                        if ( (j-1) == 1) /* if destination is on left-end */
                        {
                            map[i][1] = '>'; /* turn car to face right */
                        }
                        else
                        {
                            map[i][j-1] = '<'; /* shift car left */
                        }
                    }
                }
            }
           
            if (carFound == 0) /* if no left-facing car found, search for right-facing car */
            {
                for (j = column-3; j > 0; j--) /* go through the row from left to right */
                {
                    if (map[i][j] == '>') /* find right-facing car */
                    {
                        carFound = 1;
                        if (map[i][j+1] == 'P') /* check if car will crash into player */
                        {
                            map[i][j] = '.'; /* re-initialise car origin to road */
                            status = 2;
                        }
                        else if (map[i][j+1] == '.') /* check if destination is road */
                        {
                            map[i][j] = '.'; /* re-initialise car origin to road */
                            if ( (j+1) == column-2) /* if destination is on right-end */
                            {
                                map[i][column-2] = '<'; /* turn car to face left */
                            }
                            else
                            {
                                map[i][j+1] = '>'; /* shift car right */
                            }
                        }
                    }
                }
            }

            i++;
        }
/* Car Movement */

/* Jump Check */
        if (jump == 1)
        { /* After the cars have moved, 'P' is reinstated based on its saved coordinates,
             this gives the 'jumping' effect */
            map[player[0]][player[1]] = 'P';
            jump = 0;
        }
/* Jump Check */

        if ( (player[0] == row-2) && (player[1] == column-2) ) 
        { /* Check if player has reached goal */
            system("clear");
            for (i = 0; i < row; i++) /* Prints the play area map */
            { 
                for (j = 0; j < column; j++) 
                {
                    printf("%c", map[i][j]);
                }
                printf("\n");
            }
            status = 1;
        }
        else if (status == 2)
        { /* Check if player lost*/
            system("clear");
            for (i = 0; i < row; i++) /* Prints the play area map */
            { 
                for (j = 0; j < column; j++) 
                {
                    printf("%c", map[i][j]);
                }
                printf("\n");
            }
        }
    }

    return status;
}