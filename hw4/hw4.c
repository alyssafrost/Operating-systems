/*
Name(s): 
- Alyssa Frost
- Mallory Merkel
---
BlazerId(s): 
- frost7
- mmerkel
---
Project #: 4
---
To compile: 
To run: 
*/

#include <stdio.h>
#include <stdlib.h>
#include "job.h"
#include "queue.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

/*
Objective:
To implement a simple job scheduler that executes non-interactive jobs 
(e.g., jobs that do not have direct user interaction,jobs that can run in the background).
*/
queue *job_queue;
void *run_job_thread(void *vargp)
{
    // todo
}

void REPL()
{
    int job_id = 0;
    while (true)
    {
        printf("Enter a command> ");
        char *command = NULL;
        size_t size = 0;
        getline(&command, &size, stdin);
        int token_index = 0;
        char *args[100];

        char *token = strtok(command, " ");

        while (token != NULL)
        {
            args[token_index] = token;
            token = strtok(NULL, " ");
            token_index++;
        }
        args[token_index] = NULL;
        if (strcmp(args[0], "submit") == 0)
        {
            job *j = init_job(&args[1], job_id);
            queue_insert(job_queue, *j);
            printf("\nJob %d was added to the queue.\n", job_id);
            job_id++;
        }
        else if ("showjobs")
        {
            // display_job
        }
    }
}

int main(int argc, char **argv)
{
    int P = atoi(argv[1]);
    job_queue = queue_init(100);
    pthread_t *job_thread_ids = (pthread_t *)malloc(sizeof(pthread_t));
    int i;
    for (i = 0; i < P; i++)
        pthread_create(&job_thread_ids[i], NULL, run_job_thread, NULL);
    REPL();
    for (i = 0; i < P; i++)
        pthread_join(job_thread_ids[i], NULL);
    return 0;
}

// https://www.geeksforgeeks.org/multithreading-c-2/