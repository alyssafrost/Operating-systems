/* Implementation of a simple circular queue using a static array */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* create the queue data structure and initialize it */
queue *queue_init(int n)
{
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = n;
	q->buffer = malloc(sizeof(job) * n);
	q->start = 0;
	q->end = 0;
	q->count = 0;

	return q;
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, job item)
{ // modify to accept "job" struct
	pthread_mutex_lock(&mutex);
	if ((q == NULL) || (q->count == q->size))
	{
		pthread_mutex_unlock(&mutex);
		return -1;
	}

	q->buffer[q->end % q->size] = item;
	q->end = (q->end + 1) % q->size;
	q->count++;

	pthread_mutex_unlock(&mutex);
	return q->count;
}

/* delete an item from the queue, update the pointers and count, and 
   return the item deleted (-1 if queue is null or empty) */

job *queue_delete(queue *q)
{
	pthread_mutex_lock(&mutex);
	if ((q == NULL) || (q->count == 0))
	{
		pthread_mutex_unlock(&mutex);
		return init_job(NULL, -1);
	}

	job *j = &q->buffer[q->start];
	q->start = (q->start + 1) % q->size;
	q->count--;

	pthread_mutex_unlock(&mutex);
	return j;
}

/* display the contents of the queue data structure */
void queue_display(queue *q) // displays QUEUED jobs
{
	pthread_mutex_lock(&mutex);
	int i;
	if (q != NULL && q->count != 0)
	{
		for (i = 0; i < q->count; i++)
			display_job(&q->buffer[(q->start + i) % q->size]);
	}
	pthread_mutex_unlock(&mutex);
}

/* delete the queue data structure */
void queue_destroy(queue *q)
{
	pthread_mutex_lock(&mutex);
	free(q->buffer);
	free(q);
	pthread_mutex_unlock(&mutex);
}
