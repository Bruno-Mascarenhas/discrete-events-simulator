#include "schedulers/SJF.hpp"

void SJFScheduler::schedule() {
  sortTasksByArrivalTime();
  int currentTime = 0;

  while (!pendingTasks.empty() || !taskQueue.empty()) {
    // Add all tasks that have arrived by the current time to the priority queue
    while (!pendingTasks.empty() &&
           pendingTasks.front().getArrivalTime() <= currentTime) {
      taskQueue.push(pendingTasks.front());
      pendingTasks.pop();
    }

    if (!taskQueue.empty()) {
      Task currentTask = taskQueue.top();
      taskQueue.pop();

      if (currentTask.getStartTime() == -1) {
        currentTask.setStartTime(currentTime);
      }

      currentTime += currentTask.getBurstTime();
      currentTask.setRemainingTime(0);
      currentTask.setCompletionTime(currentTime);

      completedTasks.push_back(currentTask);

      std::cout << "Task " << currentTask.getId() << " completed at time "
                << currentTime << "\n";
    } else {
      // If no tasks are ready, advance time to the next task's arrival
      if (!pendingTasks.empty()) {
        currentTime = pendingTasks.front().getArrivalTime();
      }
    }
  }
}
