#ifndef _PK_PID
#define _PK_PID

struct Reading
{	
	int value;
	int ticks;
};
typedef struct Reading Reading;

struct PID
{
	double kp;
	double ki;
	double kd;
	int integral;
	Reading current;
	Reading prev;
};
typedef struct PID PID;

void pid_clock(int (*ticks)(void));
void pid_init(PID* tracker, double p, double i, double d);
void pid_sampling(PID* tracker, int reading);
int pid_output(PID* tracker, int target);

#endif

