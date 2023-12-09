#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BOARD_SIZE 9

int sudokuPuzzle[BOARD_SIZE][BOARD_SIZE] = {
    {6, 1, 9, 5, 7, 4, 3, 8, 2},
    {5, 4, 3, 8, 2, 9, 1, 7, 6},
    {7, 8, 2, 6, 1, 3, 9, 5, 4},
    {1, 9, 8, 4, 6, 7, 5, 2, 3},
    {3, 6, 5, 9, 8, 2, 4, 1, 7},
    {4, 2, 7, 1, 3, 5, 8, 6, 9},
    {9, 5, 6, 7, 4, 8, 2, 3, 1},
    {8, 3, 1, 2, 9, 6, 7, 4, 5},
    {2, 7, 4, 3, 5, 1, 6, 9, 8},
};

bool rowValidation[BOARD_SIZE];
bool colValidation[BOARD_SIZE];
bool boxValidation[BOARD_SIZE];

void printSudokuPuzzle(int sudokuPuzzle[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%5d", sudokuPuzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *checkRow(void *args)
{
    int occurrences[BOARD_SIZE];
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        occurrences[i] = 0;
    }
    int row = *((int *)args);

    for (i = 0; i < BOARD_SIZE; i++)
    {
        occurrences[sudokuPuzzle[i][row] - 1] += 1;
    }

    rowValidation[row] = true;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (occurrences[i] != 1)
        {
            rowValidation[row] = false;
        }
    }
}

void *checkCol(void *args)
{
    int occurrences[BOARD_SIZE];
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        occurrences[i] = 0;
    }
    int col = *((int *)args);

    for (i = 0; i < BOARD_SIZE; i++)
    {
        occurrences[sudokuPuzzle[col][i] - 1] += 1;
    }

    colValidation[col] = true;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (occurrences[i] != 1)
        {
            colValidation[col] = false;
        }
    }
}

void *checkBox(void *args)
{
    int occurrences[BOARD_SIZE];
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        occurrences[i] = 0;
    }
    int box = *((int *)args);
    int j = 0;
    int x = (box / 3) * 3;
    int y = (box % 3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            occurrences[sudokuPuzzle[i + x][j + y] - 1] += 1;
        }
    }

    boxValidation[box] = true;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (occurrences[i] != 1)
        {
            boxValidation[box] = false;
        }
    }
}

int main()
{
    printf("Sudoku Puzzle:\n");
    printSudokuPuzzle(sudokuPuzzle);

    pthread_t rowThreads[BOARD_SIZE];
    pthread_t colThreads[BOARD_SIZE];
    pthread_t boxThreads[BOARD_SIZE];
    int i = 0;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        int *a = malloc(sizeof(int));
        int *b = malloc(sizeof(int));
        int *c = malloc(sizeof(int));
        *a = i;
        *b = i;
        *c = i;
        pthread_create(&rowThreads[i], NULL, checkRow, a);
        pthread_create(&colThreads[i], NULL, checkCol, b);
        pthread_create(&boxThreads[i], NULL, checkBox, c);
    }
    for (i = 0; i < BOARD_SIZE; i++)
    {
        pthread_join(rowThreads[i], NULL);
        pthread_join(colThreads[i], NULL);
        pthread_join(boxThreads[i], NULL);
    }

    printf("Validation Results:\n");
    bool allRowsPassed = true;
    printf("Rows:\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (!rowValidation[i])
        {
            printf("Row %i did not pass\n", i);
            allRowsPassed = false;
        }
    }
    if (allRowsPassed)
    {
        printf("All rows passed!\n");
    }

    bool allColsPassed = true;
    printf("Cols:\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (!colValidation[i])
        {
            printf("Col %i did not pass\n", i);
            allColsPassed = false;
        }
    }
    if (allColsPassed)
    {
        printf("All cols passed!\n");
    }

    bool allBoxesPassed = true;
    printf("Boxes:\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (!boxValidation[i])
        {
            printf("Box %i did not pass\n", i);
            allBoxesPassed = false;
        }
    }
    if (allBoxesPassed)
    {
        printf("All boxes passed!\n");
    }

    return 0;
}