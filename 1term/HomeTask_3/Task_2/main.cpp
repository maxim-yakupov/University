#include "stdio.h"
#include "stdlib.h"
#include "time.h"

using namespace std;

void printArray(int n, int *array[]);

int main()
{
    srand(time(NULL));
    printf("Array have size N*N. Type N: ");
    int n = 1;
    scanf("%d", &n);
    int** array = new int* [n];
    for (int i = 0; i < n; i++)
    {
        array[i] = new int [n];
    };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            array[i][j] = rand()%100;
        };
    };
    printArray(n, array);

    int x = n / 2;
    int y = x;
    int counterOfChangesDirections = 0;
    int counterOfSteps = 0;
    while (counterOfSteps != n*n)
    {
        printf("%d ", array[x][y]);
        int direction = counterOfChangesDirections % 4;
        switch (direction)
        {
            case 0://go left
            {
                y--;
                if (x - 1 == y)
                {
                    counterOfChangesDirections++;
                };
                break;
            };
            case 1://go down
            {
                x++;
                if (n - x - 1 == y)
                {
                    counterOfChangesDirections++;
                };
                break;
            };
            case 2://go right
            {
                y++;
                if (x == y)
                {
                    counterOfChangesDirections++;
                };
                break;
            };
            default://go up
            {
                x--;
                if (n - x - 1 == y)
                {
                    counterOfChangesDirections++;
                };
                break;
            };
        };
        counterOfSteps++;
    };

    for (int i = 0; i < n; i++)
    {
        delete [] array[i];
    };
    delete [] array;

    return 0;
}

void printArray(int n, int* array[])
{
    printf("=======array======\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ",array[i][j]);
        };
        printf("\n");
    };
    printf("==================\n");
}
