#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

/* main method */

int main(void)
{
    int N, i;
    printf("Please enter number of elements in array: ");
    scanf("%d", &N);

    char **arr = malloc(sizeof(char *) * N);

    char buffer[BUFFER_SIZE];
    for (i = 0; i < N; i++)
    {
        printf("Please enter word %d of array: ", (i + 1));
        scanf("%s", buffer);

        arr[i] = malloc(sizeof(char *) * (strlen(buffer) + 1));
        strcpy(arr[i], buffer);
    }

    //Sorting
    printf("Given array is: ");
    printf("[");
    for (i = 0; i < N - 1; i++)
    {
        printf("%s, ", arr[i]);
    }
    printf("%s]\n", arr[N - 1]);
    char temp[BUFFER_SIZE];
    int currLoc;
    for (i = 1; i < N; i++)
    {
        currLoc = i;
        // int k = ;
        // printf("%d\n", k);
        while (currLoc > 0 && strcmp(arr[currLoc], arr[currLoc - 1]) < 0)
        {
            strcpy(temp, arr[currLoc]);
            strcpy(arr[currLoc], arr[currLoc - 1]);
            strcpy(arr[currLoc - 1], temp);
            currLoc--;
        }
    }
    printf("Sorted array is: ");
    printf("[");
    for (i = 0; i < N - 1; i++)
    {
        printf("%s, ", arr[i]);
    }
    printf("%s]\n", arr[N - 1]);

    // Free mallocd memory
    for (i = 0; i < N; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
