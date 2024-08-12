#ifndef FIFO_HPP
#define FIFO_HPP

#include "schedulers/BaseScheduler.hpp"

/**
 * @brief Class to implement the First-In-First-Out (FIFO) scheduling algorithm.
 * 
 * This scheduler processes tasks in the order they arrive, without 
 * preemption, ensuring that the first task to arrive is the first to be executed.
 */
class FIFOScheduler : public BaseScheduler {
 public:
  void schedule() override;
};

#endif  // FIFO_HPP
