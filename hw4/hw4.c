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
    while (true)
    {
        job *j = queue_delete(job_queue);
        if (j->job_id == -1)
        {
            sleep(1);
            continue;
        }
        run_job(j);
    }
}

void REPL()
{

    int job_id = 0;
    while (true)
    {
        printf("Enter a command> ");
        char *command = NULL;
        size_t size;
        getline(&command, &size, stdin);
        command[strlen(command) - 1] = '\0'; //null byte char

        int token_index = 0;
        char **args = malloc(sizeof(char *) * 100);

        char *token = strtok(command, " ");

        while (token != NULL)
        {
            if (token != NULL)
            {
                args[token_index] = strdup(token);
            }
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
        else if (strcmp(args[0], "showjobs") == 0)
        {
            printf("JobID\t Command\t Status\n");
            queue_display(job_queue);
        }
        else
        {
            printf("Invalid command: '%s'\n", args[0]);
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