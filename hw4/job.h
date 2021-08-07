#ifndef __JOB_H__
#define __JOB_H__

typedef struct _job
{
    char **command;
    int job_id;
    char *status;

} job;

job *init_job(char **command, int job_id);
void display_job(job *j);
void run_job(job *j);

#endif
