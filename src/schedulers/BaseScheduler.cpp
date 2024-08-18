#include "schedulers/BaseScheduler.hpp"

void BaseScheduler::addTask(const Task& task) {
  taskQueue.push(task);
}

void BaseScheduler::addTasks(const std::vector<Task>& tasks) {
  for (const Task& task : tasks) {
    taskQueue.push(task);
  }
}

const std::vector<Task>& BaseScheduler::getCompletedTasks() {
  return completedTasks;
}

double BaseScheduler::getAverageTurnaroundTime() {
  if (completedTasks.size() == 0)
    return -1;

  double totalTurnaroundTime = 0.0;
  for (const Task& task : completedTasks) {
    totalTurnaroundTime += task.getTurnaroundTime();
  }
  return totalTurnaroundTime / completedTasks.size();
}

double BaseScheduler::getAverageWaitingTime() {
  if (completedTasks.size() == 0)
    return -1;

  double totalWaitingTime = 0.0;
  for (const Task& task : completedTasks) {
    totalWaitingTime += task.getWaitingTime();
  }
  return totalWaitingTime / completedTasks.size();
}

std::vector<BaseScheduler::Interval> BaseScheduler::getIntervals() {
  return intervals;
}

void BaseScheduler::sortTasksByArrivalTime() {
  std::vector<Task> tasks;
  while (!taskQueue.empty()) {
    tasks.push_back(taskQueue.front());
    taskQueue.pop();
  }

  std::sort(tasks.begin(), tasks.end(), [](const Task& t1, const Task& t2) {
    return t1.getArrivalTime() < t2.getArrivalTime();
  });

  for (const Task& task : tasks) {
    taskQueue.push(task);
  }
}
