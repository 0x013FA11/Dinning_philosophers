## death.c
**kill_philo:**

* Takes a `philo` pointer as input, representing a philosopher.
* Uses a mutex lock on the philosopher's control mutex (`pcontrol`).
* Sets the philosopher's state to `false`, indicating it's dead.
* Releases the lock on the control mutex.

**died:**

* Takes two arguments:
    * `philo`: A pointer to the philosopher array.
    * `i`: The index of the philosopher who died.
* Sets the state of the specified philosopher to `false`.
* Prints a message using `get_time` and the philosopher's ID, stating it has died.
* Loops through all other philosophers (except the one who died).
    * Uses `kill_philo` to mark each remaining philosopher as dead.

**death_controler:**

* Takes a `data` pointer as input, containing information about all philosophers.
* Runs in a loop until the number of dead philosophers (`flag`) matches the total number of philosophers.
* Within the loop:
    * Resets `flag` to 0.
    * Iterates through all philosophers:
        * Locks the philosopher's control mutex.
        * If the philosopher's state is already `false`, increments `flag`.
        * Otherwise, checks if the time since the philosopher's last meal exceeds the `time_to_die` parameter.
            * If so, calls `died` on that philosopher, effectively killing it and marking all others as dead.
        * Releases the lock on the control mutex.

**Safety Considerations:**

* This code uses mutexes to ensure thread safety when accessing and modifying shared data like philosopher states.
* The code avoids printing explicit details about the cause of death, focusing on the event itself.

**Overall, this code implements a simple and efficient mechanism for detecting and handling philosopher deaths in my program. It ensures all philosophers are notified of a death and become inactive, preventing further dining attempts and potential deadlock issues.**
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
## Makefile

This Makefile defines the build process for your Dining Philosophers program named "philo". Here's a breakdown of its contents:

**Variables:**

* `NAME`: Set to "philo", which is the final executable name.
* `SRCS`: A list of source files (C files) used in the program.
* `OBJS`: A list of generated object files compiled from the source files (calculated using `patsubst`).
* `CC`: The compiler command to use (defaults to `cc`).
* `CFLAGS`: Compilation flags used with the compiler. They include:
    * `-pthread`: Enables pthread support for thread creation and synchronization.
    * `-Wall`: Enables most compiler warnings.
    * `-Wextra`: Enables additional, stricter warnings.
    * `-Werror`: Treats all warnings as errors, causing the build to fail if any warnings are present.
    * `-g`: Enables debug information generation in the compiled object files.
    * `# -fsanitize=address,undefined`: Commented out line for potential future use with Address Sanitizer and Undefined Behavior Sanitizer (comment removal may require additional library installations).

**Targets:**

* `all`: Default target that builds the program.
    * It first invokes the `$(OBJS)` target to ensure all object files are compiled.
    * Then, it uses the compiled object files and the specified CFLAGS to link the final executable named "philo".
* `%.o`: This is a pattern rule for compiling object files.
    * It defines how to compile each source file (`%.c`) into an object file (`%.o`) using the `CC` and `CFLAGS` variables.
    * The philosophers.h header file is also included during compilation.
* `clean`: Removes all generated object files.
* `fclean`: Performs a more thorough cleanup, removing both object and executable files.
* `re`: Runs `fclean` followed by `all` to effectively rebuild the program from scratch.

**Overall, this Makefile provides a clear and concise way to build and clean your Dining Philosophers program. It utilizes variables and pattern rules to automate the compilation and linking process, making it easier to maintain and update your project.**

## utils2.c utils.c

**Memory Management:**

* This file dynamically allocates memory using `malloc` for various data structures:
    * `t_data`: Stores pointers to other data structures and parameters.
    * `t_params`: Holds program parameters like number of philosophers and timeouts.
    * `t_philos`: Individual philosopher data, including ID, forks, control mutex, and state.
    * `forks`: Array of mutexes representing individual forks.
    * `control`: Array of mutexes for controlling access to philosopher data.
* It's crucial to free allocated resources using functions like `clean` in the Makefile to avoid memory leaks.

**Data Structure Access:**

* `parse_arguments` accesses command line arguments and populates the `t_data` and `t_params` structures.
* Individual philosopher data is accessed through pointer arithmetic within functions like `initialize`.
* Mutexes are used to control access to shared resources like forks and control data.

**Function Breakdown:**

* **ft_atoi:** Converts a string to an integer, used for parsing arguments.
* **check_params:** Validates program parameters, ensuring proper values.
* **parse_arguments:** Parses command line arguments and initializes the program.
    * Extracts parameter values using `ft_atoi` and checks validity with `check_params`.
    * Sets up philosopher data structures and resources using `initialize`.
* **init_locks:** Allocates and initializes mutexes for forks and control access.
    * Uses `malloc` for memory allocation and `pthread_mutex_init` for initialization.
* **initialize:** Sets up individual philosophers with IDs, forks, mutexes, and state.
    * Relies on `init_locks` for resource allocation and `check_params` for valid parameters.

**Interaction with other parts:**

* `parse_arguments` is called by the `main` function to initialize the program.
* Allocated resources like threads and mutexes are used by other functions like `routine` for philosopher behavior.
* Initial philosopher state is set up here and accessed by functions like `death_controler` for monitoring and death detection.

**Overall, `utils.c` plays a crucial role in setting up the program's foundation by:**

* Managing memory allocation and deallocation.
* Parsing user-provided parameters.
* Initializing philosopher data structures and resources.
* Providing thread-safe access to shared resources through mutexes.
* Interacting with other parts of the program for proper execution.


