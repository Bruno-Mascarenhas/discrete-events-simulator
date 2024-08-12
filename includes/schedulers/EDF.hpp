#ifndef EDF_HPP
#define EDF_HPP

#include <limits>
#include <queue>
#include <vector>
#include "Tasks.hpp"

/**
 * @brief Class to implement the Earliest Deadline First (EDF) scheduling algorithm.
 * 
 * This scheduler processes tasks based on their deadlines, with tasks having 
 * earlier deadlines being given priority. It handles preemption and tasks 
 * with different arrival times.
 */
class EDFScheduler {
 public:
  /**
   * @brief Adds a task to the scheduler.
   * @param task The task to be added to the scheduling queue.
   */
  void addTask(const Task& task);

  /**
   * @brief Adds a vector of tasks to the scheduler.
   * @param tasks The vector of tasks to be added to the scheduling queue.
   */
  void addTasks(const std::vector<Task>& tasks);

  /**
     * @brief Executes the scheduling of tasks.
     * 
     * This method processes tasks based on their deadlines, handling 
     * different arrival times and ensuring that tasks with earlier deadlines 
     * are given priority. It supports preemption.
     */
  void schedule();

  /**
     * @brief Retrieves the list of completed tasks.
     * @return A vector of completed tasks.
     */
  const std::vector<Task>& getCompletedTasks() const;

 private:
  /**
     * @brief Comparator to compare tasks based on their deadlines.
     * less deadline means higher priority
     */
  struct CompareDeadline {
    bool operator()(const Task& t1, const Task& t2) const {
      return t1.getDeadline() > t2.getDeadline();
    }
  };

  std::priority_queue<Task, std::vector<Task>, CompareDeadline> taskQueue;
  std::vector<Task> completedTasks;
  std::queue<Task>
      pendingTasks;  // Tasks that have arrived but not yet processed
};

#endif  // EDF_HPP
