#include "error.h"
#include "fractol.h"
#include "libft_adv.h"
#include "thread.h"

int		threads_stop(pthread_t thread[NUM_THREAD], int n_thread)
{
	int		err;
	int		res;

	err = 0;
	res = 0;
	while (n_thread-- > 0)
		if ((err = pthread_join(thread[n_thread], NULL)))
		{
			ft_putstr_fd(ERR_THREAD_CLOSE, STDERR_FILENO);
			ft_putendl_fd(strerror(err), STDERR_FILENO);
			res = res | err;
		}
	return (res);
}

int		threads_start(pthread_t thread[NUM_THREAD], t_args thr_arg[NUM_THREAD]
		, void *fun(void *))
{
	int		n_thread;
	int		err;

	n_thread = -1;
	err = 0;
	while (++n_thread < NUM_THREAD && !err)
		err = pthread_create(&thread[n_thread], NULL, fun, &thr_arg[n_thread]);
	if (err)
	{
		ft_putstr_fd(ERR_THREAD_OPEN, STDERR_FILENO);
		ft_putendl_fd(strerror(err), STDERR_FILENO);
		threads_stop(thread, n_thread - 1);
		return (1);
	}
	return (0);
}
