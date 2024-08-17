#ifndef TASKS_HPP
#define TASKS_HPP

#include <iostream>

/**
 * @class Task
 * @brief Represents a task abstraction.
 * 
 * This class contains the essential attributes needed to simulate 
 * the execution of tasks using the Round Robin Scheduling algorithm.
 */
class Task {
 public:
  /**
     * @brief Constructs a Task object.
     * @param id Unique identifier for the task.
     * @param burst_time Total CPU burst time required by the task.
     * @param arrival_time Time at which the task arrives.
     * @param deadline Time by which the task must complete.
     * @param priority Priority of the task.
     */
  Task(int id, int burst_time, int arrival_time, int deadline);

  Task(int id, int burst_time, int arrival_time, int deadline, int priority);

  // Getters and setters
  int getId() const;
  int getBurstTime() const;
  int getRemainingTime() const;
  int getDeadline() const;
  int getPriority() const;
  void setRemainingTime(int time);
  int getArrivalTime() const;
  int getStartTime() const;
  void setStartTime(int time);
  int getCompletionTime() const;
  void setCompletionTime(int time);
  int getWaitingTime() const;
  int getTurnaroundTime() const;

 private:
  int id;               ///< Unique identifier for the task
  int burst_time;       ///< Total CPU burst time required by the task
  int remaining_time;   ///< Remaining burst time for the task
  int arrival_time;     ///< Time at which the task arrives
  int start_time;       ///< Time at which the task starts execution
  int completion_time;  ///< Time at which the task completes execution
  int waiting_time;     ///< Time the task has been waiting in the ready queue
  int turnaround_time;  ///< Total time taken from arrival to completion
  int deadline;         ///< Time by which the task must complete
  int priority;         ///< Priority of the task
  bool setTurnaroundTime();  ///< Calculate turnaround time
  bool setWaitingTime();     ///< Calculate waiting time
};

#endif  // TASKS_HPP
