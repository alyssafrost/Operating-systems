#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

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
        int fdout, fderr;                                  // file descriptor
        char *std_out = (char *)malloc(sizeof(char) * 50); // filename
        char *err_out = (char *)malloc(sizeof(char) * 50); // filename
        char buffer[50];

        snprintf(std_out, 50, "%d.out", j->job_id); // convert into to string
        snprintf(err_out, 50, "%d.err", j->job_id); // convert into to string

        if ((fdout = open(std_out, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1)
        {
            printf("Error opening file stdout.txt for output\n");
            exit(-1);
        }
        // open file to write error output in append mode
        if ((fderr = open(err_out, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1)
        {
            printf("Error opening file error.txt for error\n");
            exit(-1);
        }

        dup2(fdout, 1); // replace standard output stream with file stdout.txt
        dup2(fderr, 2); // replace error output stream with file stdout.err

        execvp(j->command[0], j->command);

        close(fdout);
        close(fderr);
    }
    else
    {
        int status;
        waitpid(0, &status, 0);
    }
}
