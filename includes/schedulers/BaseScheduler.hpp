#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include "utils/Tasks.hpp"

/**
 * @brief Abstract base class for different scheduling algorithms.
 * 
 * This interface defines the common methods that all schedulers must implement.
 */
class BaseScheduler {
 public:
  virtual ~BaseScheduler() = default;

  /**
   * @brief Adds a task to the scheduler.
   * @param task The task to be added to the scheduling queue.
   */
  void addTask(const Task& task);

  /**
   * @brief Adds multiple tasks to the scheduler.
   * @param tasks The tasks to be added to the scheduling queue.
   */
  void addTasks(const std::vector<Task>& tasks);

  /**
   * @brief Executes the scheduling of tasks.
   * 
   * This method must be implemented by the derived classes.
   */
  virtual void schedule() = 0;

  /**
   * @brief Retrieves the list of completed tasks.
   * @return A vector of completed tasks.
   */
  const std::vector<Task>& getCompletedTasks();

  /**
   * @brief Calculates the average turnaround time of the completed tasks.
   * @return The average turnaround time.
   */
  double getAverageTurnaroundTime();

 protected:
  std::vector<Task> completedTasks;
  std::queue<Task> taskQueue;

  /**
   * @brief Sort the taskQueue based on the arrival time of the tasks.
   *     This should be used before scheduling the tasks.
   */
  void sortTasksByArrivalTime();
};

#endif  // SCHEDULER_HPP
