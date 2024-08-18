#include "schedulers/SJF.hpp"

void SJFScheduler::schedule() {
  sortTasksByArrivalTime();
  int currentTime = 0;

  while (!pendingTasks.empty() || !taskQueue.empty()) {
    // Add all tasks that have arrived by the current time to the priority queue
    while (!taskQueue.empty() &&
           taskQueue.front().getArrivalTime() <= currentTime) {
      pendingTasks.push(taskQueue.front());
      taskQueue.pop();
    }

    if (!pendingTasks.empty()) {
      Task currentTask = pendingTasks.top();
      pendingTasks.pop();

      if (currentTask.getStartTime() == -1) {
        currentTask.setStartTime(currentTime);
      }

      intervals.push_back({currentTime,
                           currentTime + currentTask.getBurstTime(),
                           currentTask.getId()});

      currentTime += currentTask.getBurstTime();
      currentTask.setRemainingTime(0);
      currentTask.setCompletionTime(currentTime);

      completedTasks.push_back(currentTask);
    } else {
      // If no tasks are ready, advance time to the next task's arrival
      if (!taskQueue.empty()) {
        currentTime = taskQueue.front().getArrivalTime();
      }
    }
  }
}
