#ifndef FIFO_HPP
#define FIFO_HPP

#include <queue>
#include <vector>
#include "Tasks.hpp"

/**
 * @brief Class to implement the First-In-First-Out (FIFO) scheduling algorithm.
 * 
 * This scheduler processes tasks in the order they arrive, without 
 * preemption, ensuring that the first task to arrive is the first to be executed.
 */
class FIFOScheduler {
 public:
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
     * This method processes all tasks in the order they were added,
     * without preemption, until all tasks are completed.
     */
  void schedule();

  /**
     * @brief Retrieves the list of completed tasks.
     * @return A vector of completed tasks.
     */
  const std::vector<Task>& getCompletedTasks() const;

 private:
  std::queue<Task> taskQueue;  ///< Queue to hold the tasks in FIFO order.
  std::vector<Task>
      completedTasks;  ///< List of tasks that have been completed.
};

#endif  // FIFO_HPP
