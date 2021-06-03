#include "../headers.h"

long	get_time_milisecond(long sec, long usec)
{
	long	time;

	time = (sec * 1000) + (usec / 1000);
	return (time);
}

long	get_duration(struct timeval start_tp)
{
	struct timeval	tp;
	long			end;
	long			start;
	long			duration;

	gettimeofday(&tp, NULL);
	start = get_time_milisecond(start_tp.tv_sec, start_tp.tv_usec);
	end = get_time_milisecond(tp.tv_sec, tp.tv_usec);
	duration = end - start;
	return (duration);
}
