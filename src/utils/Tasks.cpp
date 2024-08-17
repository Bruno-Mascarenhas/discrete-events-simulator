#include "utils/Tasks.hpp"

Task::Task(int id, int burst_time, int arrival_time, int deadline)
    : id(id),
      burst_time(burst_time),
      remaining_time(burst_time),
      arrival_time(arrival_time),
      deadline(deadline),
      start_time(
          -1),  // Start time is initialized to -1, indicating it hasn't started yet
      completion_time(
          -1),  // Completion time is initialized to -1, indicating it's not completed yet
      waiting_time(0),
      turnaround_time(0) {}

Task::Task(int id, int burst_time, int arrival_time, int deadline, int priority)
    : id(id),
      burst_time(burst_time),
      remaining_time(burst_time),
      arrival_time(arrival_time),
      deadline(deadline),
      priority(priority),
      start_time(
          -1),  // Start time is initialized to -1, indicating it hasn't started yet
      completion_time(
          -1),  // Completion time is initialized to -1, indicating it's not completed yet
      waiting_time(0),
      turnaround_time(0) {}

// Getters
int Task::getId() const {
  return id;
}

int Task::getBurstTime() const {
  return burst_time;
}

int Task::getRemainingTime() const {
  return remaining_time;
}

int Task::getDeadline() const {
  return deadline;
}

int Task::getArrivalTime() const {
  return arrival_time;
}

int Task::getStartTime() const {
  return start_time;
}

int Task::getCompletionTime() const {
  return completion_time;
}

int Task::getWaitingTime() const {
  return waiting_time;
}

int Task::getTurnaroundTime() const {
  return turnaround_time;
}

int Task::getPriority() const {
  return priority;
}

// Setters
void Task::setRemainingTime(int time) {
  remaining_time = time;
}

void Task::setStartTime(int time) {
  start_time = time;
}

void Task::setCompletionTime(int time) {
  completion_time = time;

  // Calculate turnaround time and waiting time
  if (!setTurnaroundTime() || !setWaitingTime())
    std::cerr << "Error calculating turnaround/waiting time for task " << id
              << std::endl;
}

bool Task::setWaitingTime() {
  if (turnaround_time == -1 || burst_time == -1) {
    return false;
  }

  waiting_time = turnaround_time - burst_time;
  return true;
}

bool Task::setTurnaroundTime() {
  if (completion_time == -1 || arrival_time == -1) {
    return false;
  }

  turnaround_time = completion_time - arrival_time;
  return true;
}
