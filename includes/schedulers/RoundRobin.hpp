#ifndef SCHEDULERS_HPP
#define SCHEDULERS_HPP

#include <queue>
#include <vector>
#include "Tasks.hpp"

/**
 * @class RoundRobinScheduler
 * @brief Implements the Round Robin Scheduling algorithm.
 * 
 * This class manages a queue of tasks and schedules them according to the 
 * Round Robin Scheduling algorithm, where each task is given a fixed time slice (quantum).
 */
class RoundRobinScheduler {
 public:
  /**
     * @brief Constructs a RoundRobinScheduler object.
     * @param quantum Time slice allocated to each task.
     */
  RoundRobinScheduler(int quantum);

  /**
     * @brief Adds a task to the scheduler.
     * @param task The task to be added to the scheduling queue.
     */
  void addTask(const Task& task);

  /**
   * @brief Adds miltiple tasks to the scheduler.
   * @param tasks The tasks to be added to the scheduling queue.
   */
  void addTasks(const std::vector<Task>& tasks);

  /**
     * @brief Executes the scheduling of tasks.
     * 
     * This function processes the tasks in the queue, giving each task 
     * a time slice according to the Round Robin algorithm. It handles 
     * tasks with different arrival times, ensuring tasks are only executed 
     * once they have arrived.
     */
  void schedule();

  /**
    * @brief Returns the list of completed tasks.
    * @return A vector containing the completed tasks.
    */
  const std::vector<Task>& getCompletedTasks() const;

 private:
  int quantum;                       ///< Time slice for each task
  std::queue<Task> taskQueue;        ///< Queue of tasks to be scheduled
  std::vector<Task> completedTasks;  ///< List of finished tasks
};

#endif  // SCHEDULERS_HPP
