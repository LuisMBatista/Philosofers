# Philosophers Project 🧘‍♂️🍽️

A fascinating concurrency exercise inspired by the famous **Dining Philosophers Problem**. In this project, each philosopher is represented as a thread, and the simulation ensures synchronization using mutexes to avoid race conditions. 

---

### The Scenario
- **Philosophers**: Thinkers who alternate between eating, sleeping and thinking.
- **Forks**: Shared resources that philosophers need to eat.
- **Table Rules**:
  1. A philosopher needs two forks to eat.
  2. A philosopher can only take the fork on their left and right.
  3. Philosophers alternate between eating, sleeping and thinking.

---

## 🛠️ Implementation

### Threads
- Each philosopher is represented by a separate thread, simulating their independent actions of **eating**, **sleeping** and **thinking**

### Mutexes
- Mutexes are used to control access to shared resources (forks) and ensure synchronization, preventing race conditions.

### Death Checker
- A separate thread monitors the state of all philosophers, checking if philosophers dies of starvation.

---

## 🚀 Features
- Accurate simulation of the dining philosophers problem.
- Thread-safe implementation using mutexes.
- Real-time monitoring of philosopher states.
- Prevention of deadlocks and starvation.

---

## 🖥️ How to Run

1. Clone the repository:
   ```sh
   git clone <https://github.com/LuisMBatista/philo>
   cd philo
   make && ./philo 2 450 200 200 5
   ```sh
