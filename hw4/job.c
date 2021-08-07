#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "job.h"

job *init_job(char **command, int job_id)
{
    job *j = (job *)malloc(sizeof(job));
    j->command = command;
    j->job_id = job_id;
    j->status = "Waiting";

    return j;
}

void display_job(job *j)
{
    int i = 0; //test 1 if sucks
    printf("%d\t", j->job_id);
    while (j->command[i] != NULL)
    {
        printf("%s ", j->command[i]);
        i++;
    }
    printf("\t%s\n", j->status);
}

void run_job(job *j)
{

    int pid = fork();
    if (pid == 0)
    {

        execvp(j->command[0], j->command);
    }
    else
    {
        int status;
        waitpid(0, &status, 0);
    }
}
