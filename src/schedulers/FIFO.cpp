#include "schedulers/FIFO.hpp"
#include <iostream>

void FIFOScheduler::addTask(const Task& task) {
  taskQueue.push(task);
}

void FIFOScheduler::addTasks(const std::vector<Task>& tasks) {
  for (const Task& task : tasks) {
    taskQueue.push(task);
  }
}

void FIFOScheduler::schedule() {
  int currentTime = 0;

  while (!taskQueue.empty()) {
    Task currentTask = taskQueue.front();

    if (currentTask.getArrivalTime() > currentTime) {
      currentTime = currentTask.getArrivalTime();
    }

    taskQueue.pop();

    if (currentTask.getStartTime() == -1) {
      currentTask.setStartTime(currentTime);
    }

    // Execute the task (FIFO assumes full execution without time slices)
    currentTime += currentTask.getBurstTime();
    currentTask.setRemainingTime(0);
    currentTask.setCompletionTime(currentTime);

    completedTasks.push_back(currentTask);

    std::cout << "Task " << currentTask.getId() << " completed at time "
              << currentTime << "\n";
  }
}

const std::vector<Task>& FIFOScheduler::getCompletedTasks() const {
  return completedTasks;
}
