#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>
# include <unistd.h>

# define NUM_THREAD 16

typedef struct	s_args
{
	int				nb_iter;
	unsigned int	*pixel;
	int				index;
	double			zoom;
	double			offset_x;
	double			offset_y;
	double			mouse_x;
	double			mouse_y;
}				t_args;

int				threads_stop(pthread_t thread[NUM_THREAD], int n_thread);
int				threads_start(pthread_t thread[NUM_THREAD]
		, t_args thr_arg[NUM_THREAD], void *fun(void *));

#endif
