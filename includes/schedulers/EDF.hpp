#ifndef EDF_HPP
#define EDF_HPP

#include <schedulers/BaseScheduler.hpp>

/**
 * @brief Class to implement the Earliest Deadline First (EDF) scheduling algorithm.
 * 
 * This scheduler processes tasks based on their deadlines, with tasks having 
 * earlier deadlines being given priority. It handles preemption and tasks 
 * with different arrival times.
 */
class EDFScheduler : public BaseScheduler {
 public:
  void schedule() override;

 private:
  /**
   * @brief Comparator to compare tasks based on deadline, 
   * with earlier deadlines first
   */
  struct CompareDeadline {
    bool operator()(const Task& t1, const Task& t2) const {
      return t1.getDeadline() > t2.getDeadline();
    }
  };

  std::priority_queue<Task, std::vector<Task>, CompareDeadline> pendingTasks;
};

#endif  // EDF_HPP
