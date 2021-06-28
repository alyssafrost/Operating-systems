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

    for (i = 0; i < N; i++)
    {
        char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
        printf("Please enter word %d of array: ", (i + 1));
        scanf("%s", buffer);
        arr[i] = buffer;
    }

    for (i = 0; i < N; i++)
    {
        printf("String #%d: %s\n", (i + 1), arr[i]);
    }

    for (i = 0; i < N; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

int old_main(int args, char **argv)
{
    int N, i;
    printf("Please enter number of elements in array: ");
    scanf("%d", &N);
    char **arr = (char **)malloc(sizeof(char *) * (N + 1)); // allocate array of N character pointers
    for (i = 0; i < N; i++)
    {
        char buffer[100];
        printf("Please enter word %d of array: ", (i + 1));
        arr[i] = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
        scanf("%s", buffer);
        strcpy(arr[i], buffer);
        /*
            Here is the problem. The array arr is an array of character pointers (i.e. strings), so what you really
            want to do here is have scanf() read in the string and store it at the memory location given by arr[i]. 
            By addressing arr[i] you're storing the string in the memory location of arr[i], not the memory location 
            that arr[i] points to. The reason why you're getting SegFault is that when you try to read in a string
            that's too long, it overflows the memory allocated for arr. For example, in the "sam is gay really gay xd" example
            you're trying to read in "really" and store it in an array that only has 5 character slots, hence SegFault.

            To fix this you need to remove the & operator so that the pointer given to scanf() points to the memory
            location you want to store the string at rather than at the array itself. You'll still run into SegFault issues
            because you have to pre-initialize each pointer at address arr[i] with malloc first

            char buffer[100];
            printf("Please enter word %d of array: ", (i+1));
            scanf("%s", buffer);

            arr[i] = *(malloc(sizeof(char) * strlen(buffer));
            strcpy(buffer, arr[i]); // Not sure if this is correct usage of strcpy but it is the function you want to use here
        */
    }
    printf("%s\n", *arr[i]);
    printf("%s\n", *arr[0]);
    printf("Given array is: ");
    printf("[");
    for (i = 0; i < N - 1; i++)
    {
        printf("%s, ", arr[i]);
    }
    printf("%s]\n", arr[N - 1]);
    char *temp; //
    int currLoc;
    for (i = 1; i < N; i++)
    {
        currLoc = i;
        while (currLoc > 0 && arr[currLoc - 1] > arr[currLoc])
        {
            temp = arr[currLoc];
            arr[currLoc] = arr[currLoc - 1];
            arr[currLoc - 1] = temp;
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
    return 0;
}