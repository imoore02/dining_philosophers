# dining_philosophers
The Dining Philosophers Problem is a classic concurrency problem in computer science, originally formulated by Edsger Dijkstra in 1965. It illustrates the challenges of resource allocation and synchronization in a multi-threaded environment. It demonstrates the basics of process threading, and how work on the same memory space.

## Problem
Imagine five philosophers sitting around a circular table. Each philosopher spends his life alternately thinking and eating. However, to eat, a philosopher needs two forks—one on his left and one on his right. There is a single fork placed between each pair of adjacent philosophers.

The problem arises when every philosopher picks up one fork simultaneously, leading to a deadlock situation where no philosopher can eat, despite having a fork in hand.

## Solutions
Various synchronization techniques can be employed to solve the Dining Philosophers Problem, ensuring that philosophers can eat without causing conflicts with neighboring philosophers. This solution uses mutexes as a resource allocation strategies to prevent deadlock and starvation.

## Usage
Clone the repository and 'make'.
You can then test the project using the executable in the format: 
  ```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
./philo 4 500 200 250
  ```
The inputs represent:
* Number of Philosophers: Specifies the total number of philosophers sitting around the table.
* Time to Die: Represents the maximum time a philosopher can spend without eating before they "die." This helps simulate the possibility of a philosopher not being able to acquire the necessary forks to eat.
* Time to Eat: Specifies the time it takes for a philosopher to finish eating once they have acquired both forks.
* Time to Sleep: Represents the time a philosopher spends sleeping or thinking after finishing a meal before they start another meal.


Naturally not all inputs will work as time_to_die must be at least time_to_eat + time_to_sleep. If your inputs are correct the philosophers will live forever!
