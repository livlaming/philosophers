# philosophers

Introduction to multithreading with the dining philosophers problem. Discovering mutex, semaphore and shared memory. https://en.wikipedia.org/wiki/Dining_philosophers_problem

## Installation and usage: 

### Build
Run ```make```

### Run

Run ```./philo [num_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [(optional)num_of_times_each_philosopher_must_eat]```


### Example

```./philo 2 380 800 900```

```./philo 2 380 800 900 10```


### Tests
you'll find different types of testing in the TESTS folder.
