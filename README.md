<h1 align="center">
	philosophers
</h1>

*<p align="center">Eat, Sleep, Spaghetti, repeat.<br>
This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.</p>*

## Description:
Simulation of the famous [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).  
In `philo` implementation, philosophers are represented as **threads**, forks as **mutexes**.  
In `philo_bonus` implementation, philosophers are represented as **processes**, forks as **semphores**.  

The actions of the philosophers are shown in a log with timestamps.  
If a philosopher dies, the program terminates after printing the death log.  
The "number of times each philosopher must eat" can be specified optionally.  
In that case, the program terminates after each philosopher eats at least that many times.  

> Philosophers sit around a circular table with a fork in between each philosopher.  
> Philosophers will eat, sleep, and think.  
> A philosopher must eat periodically to stay alive.  
> A philosopher dies when the time they haven't eaten reaches the time it takes for them to die.  
> A philosopher must use two forks in order to eat.  
> Since there aren't enough forks for all philosophers to eat at once, they must take turns.  

## Set-up:
First, enter directory of choice with `cd philosophers/philo` or `cd philosophers/philo_bonus`.  
Then use any makefile command.

#### Makefile Commands:
```C
make        //compile executable (./philo)
make clean  //delete .o
make fclean //delete .o and executable
make re     //delete .o and executable, then recompile
```

## Usage:  
```Java
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
//unit for time is ms
```
