
## routine.c

**1. Memory Management:**

- **`t_data`:** This data structure is allocated on the heap using `malloc` in the `main` function. It stores pointers to various other data structures, like philosophers (`philos`), forks (`forks`), control mutex (`control`), and threads (`threads`).
- **`t_params`:** This structure is also allocated on the heap within `t_data`. It stores parameters like the number of philosophers, their lifetimes, etc.
- **`t_philos`:** Each philosopher is represented by a dynamically allocated structure on the heap. It contains information like the philosopher's ID, last meal time, meal count, state (alive/dead), and pointers to its left and right forks, control mutex, and parameters.
- **`forks`:** An array of `pthread_mutex_t` objects is dynamically allocated to represent the forks. Each element acts as a mutex protecting access to a specific fork.
- **`control`:** A single `pthread_mutex_t` object is allocated to control access to the `last_meal` and `meal_times` information within a philosopher.
- **`threads`:** An array of `pthread_t` object is dynamically allocated to manage the philosopher threads.

**2. Data Structure Access:**

- Each philosopher accesses its own `t_philos` structure through the `ptr` argument passed to the `routine` function.
- Within `t_philos`, other data structures are accessed through pointers like `left_fork`, `right_fork`, `pcontrol`, and `params`.
- The `actions` function takes a philosopher and an action function as arguments, allowing it to dynamically choose between different behavior like taking forks, eating, sleeping, or thinking.

**3. Routine Function:**

- The `routine` function is the main loop executed by each philosopher thread.
- It continuously checks if the philosopher is alive (using `is_alive`).
- If alive, it performs actions in a specific order:
    - `take_shopstick`: Attempts to acquire both left and right forks in a specific order (avoiding deadlock).
    - `eat`: Prints a message and updates internal state like `last_meal` and `meal_times`.
    - Unlocks both forks.
    - `sleep_and_think`: Prints a message and sleeps for a period of time.
    - Checks again if the philosopher is alive.
    - Prints a "thinking" message and delays for a short time.

**4. Additional Points:**

- The program uses mutexes to ensure thread safety and prevent deadlock when accessing shared resources like forks and the control mutex.
- The `get_time` function helps track the timing of various actions for each philosopher.
- The `usleeep` function is a custom sleep function that takes a philosopher and a sleep duration as arguments, allowing for potential future modifications to individual philosopher behavior.

I hope this breakdown provides a clearer understanding of the memory management and data structure interactions in my program.
