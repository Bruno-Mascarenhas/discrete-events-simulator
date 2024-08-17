#include "schedulers/FIFO.hpp"

void FIFOScheduler::schedule() {
  sortTasksByArrivalTime();
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
  }
}
