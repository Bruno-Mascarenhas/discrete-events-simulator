#ifndef SJF_HPP
#define SJF_HPP

#include <schedulers/BaseScheduler.hpp>

/**
 * @brief Class to implement the Shortest Job First (SJF) scheduling algorithm.
 * 
 * This scheduler processes tasks based on their burst time, with shorter tasks
 * being given priority, handling tasks with different arrival times.
 */
class SJFScheduler : public BaseScheduler {
 public:
  void schedule() override;

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
  std::queue<Task> pendingTasks;
};

#endif  // SJF_HPP
