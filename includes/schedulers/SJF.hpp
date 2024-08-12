#ifndef SJF_HPP
#define SJF_HPP

#include <queue>
#include <vector>
#include "Tasks.hpp"

/**
 * @brief Class to implement the Shortest Job First (SJF) scheduling algorithm.
 * 
 * This scheduler processes tasks based on their burst time, with shorter tasks
 * being given priority, handling tasks with different arrival times.
 */
class SJFScheduler {
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
     * This method processes tasks based on their burst time, handling 
     * different arrival times and ensuring that shorter tasks are given 
     * priority.
     */
  void schedule();

  /**
     * @brief Retrieves the list of completed tasks.
     * @return A vector of completed tasks.
     */
  const std::vector<Task>& getCompletedTasks() const;

 private:
  /**
     * @brief Comparator to compare tasks based on burst time, 
     * with shorter tasks first
     */
  struct CompareBurstTime {
    bool operator()(const Task& t1, const Task& t2) const {
      return t1.getBurstTime() > t2.getBurstTime();
    }
  };

  std::priority_queue<Task, std::vector<Task>, CompareBurstTime> taskQueue;
  std::vector<Task> completedTasks;
  std::queue<Task> pendingTasks;
};

#endif  // SJF_HPP
