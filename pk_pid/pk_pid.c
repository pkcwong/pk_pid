#include "pk_pid.h"

int (*pid_tick)(void);

void pid_clock(int (*ticks)(void))
{
	pid_tick = ticks;
}

void pid_init(PID* tracker, double p, double i, double d)
{
	tracker->kp = p;
	tracker->ki = i;
	tracker->kd = d;
	tracker->integral = 0;
	tracker->current.ticks = 0;
	tracker->current.value = 0;
	tracker->prev.ticks = 0;
	tracker->prev.value = 0;
}

void pid_sampling(PID* tracker, int reading)
{
	int ticks = pid_tick();
	tracker->prev = tracker->current;
	tracker->current.value = reading;
	tracker->current.ticks = ticks;
}

int pid_output(PID* tracker, int target)
{
	int ticks = pid_tick();
	if(tracker->prev.ticks == 0 || tracker->current.ticks == 0)
	{
		return 0;
	}
	else
	{
		int proportion;
		int derivative;
		proportion = target - tracker->current.value;
		tracker->integral += (target - tracker->current.value) * (ticks - tracker->current.ticks + 1);
		derivative = (float)(tracker->prev.value - tracker->current.value) / (float)(tracker->prev.ticks - tracker->current.ticks + 1);
		return proportion * tracker->kp + tracker->integral * tracker->ki + derivative * tracker->kd;
	}
}

