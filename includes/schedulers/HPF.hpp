#ifndef HPF_HPP
#define HPF_HPP

#include <schedulers/BaseScheduler.hpp>

/**
 * @brief Class to implement the Highest Priority First (HPF) scheduling algorithm.
 * 
 * This scheduler processes tasks based on their priority, with higher priority tasks
 * being given precedence, handling tasks with different arrival times.
 */
class HPFScheduler : public BaseScheduler {
 public:
  void schedule() override;

 private:
  /**
   * @brief Comparator to compare tasks based on priority, 
   * with higher priority tasks first.
   */
  struct ComparePriority {
    bool operator()(const Task& t1, const Task& t2) const {
      return t1.getPriority() < t2.getPriority();
    }
  };

  std::priority_queue<Task, std::vector<Task>, ComparePriority> pendingTasks;
};

#endif  // HPF_HPP
