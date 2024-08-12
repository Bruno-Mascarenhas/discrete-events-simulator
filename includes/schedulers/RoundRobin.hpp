#ifndef SCHEDULERS_HPP
#define SCHEDULERS_HPP

#include <schedulers/BaseScheduler.hpp>

/**
 * @class RoundRobinScheduler
 * @brief Implements the Round Robin Scheduling algorithm.
 * 
 * This class manages a queue of tasks and schedules them according to the 
 * Round Robin Scheduling algorithm, where each task is given a fixed time slice (quantum).
 */
class RoundRobinScheduler : public BaseScheduler {
 public:
  /**
     * @brief Constructs a RoundRobinScheduler object.
     * @param quantum Time slice allocated to each task.
     */
  RoundRobinScheduler(int quantum);

  void schedule() override;

 private:
  int quantum;  ///< Time slice for each task
  std::queue<Task>
      pendingTasks;  ///< Queue to hold tasks that are not yet ready to execute
};

#endif  // SCHEDULERS_HPP
