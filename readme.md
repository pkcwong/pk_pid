# pk_pid

release date - 2017/05/30

Log:
- added pid_output
- added pid_sampling
- added pid_init
- added pid_clock

---

## Brief

Generalized PID control system library.

## Terminology

### PID
The following shows a PID structure.
```c
struct PID
{
	double kp;
	double ki;
	double kd;
	int integral;
	Reading current;
	Reading prev;
};
```
Variables ```kp```, ```ki```, ```kd``` stores the PID constants.

## Method Summary

Method Declaration | Arguments | Method Description
--- | --- | ---
void pid_clock | int (\*ticks)(void) | initialize the function pointer to timer
void pid_init | PID* tracker, double p, double i, double d | initialize the PID tracker to specified configuration
void pid_sampling | PID* tracker, int reading | takes a reading for PID tracker
int pid_output | PID* tracker, int target | gives a correction output for PID control system

## Method Details

### void pid_clock

This method sets the timer function pointer for the PID library, which initializes the following variable. This is an initialization of the library and must be called on top of library usage.
```c
int (*pid_tick)(void);
```
The clock function will be used for time logging during PID output. Sample code as follows.
```c
#include "pk_pid.h"

#include <stdio.h>
#include <time.h>

int timer()
{
	return time(NULL);
}

int main()
{
	pid_clock(&timer);
}
```

### void pid_init

This method initializes the PID tracker according to specified constants. This is an initialization of the PID tracker and must be called on top of PID tracker usage. Sample code as follows.
```c
#include "pk_pid.h"

#include <stdio.h>
#include <time.h>

int timer()
{
	return time(NULL);
}

int main()
{
	PID pid;
	pid_clock(&timer);
	pid_init(&pid, 1, 0.1, 2);
}
```

### void pid_sampling

This method takes a reading for the PID tracker. The reading is stored in the PID tracker for future computations. Sample code as follows.
```c
#include "pk_pid.h"

#include <stdio.h>
#include <time.h>

int timer()
{
	return time(NULL);
}

int main()
{
	PID pid;
	pid_clock(&timer);
	pid_init(&pid, 1, 0, 0);
	// code below should be called in a loop
	pid_sampling(&pid, __reading__);
}
```

### int pid_output

This method gives a correction output for the PID control system. The return value of this function is a correction output, and should be added with the default power to produce the final PID corrected output. Sample code as follows.
```c
#include "pk_pid.h"

#include <stdio.h>
#include <time.h>

int timer()
{
	return time(NULL);
}

int main()
{
	PID pid;
	pid_clock(&timer);
	pid_init(&pid, 1, 0.1, 2);
	// code below should be called in a loop
	pid_sampling(&pid, __reading__);
	__power__ = __power__ + pid_output(&pid, __target__));
}
```
