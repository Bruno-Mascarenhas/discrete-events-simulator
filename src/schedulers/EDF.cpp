#include "schedulers/EDF.hpp"

void EDFScheduler::schedule() {
  sortTasksByArrivalTime();
  int currentTime = 0;

  while (!pendingTasks.empty() || !taskQueue.empty()) {
    // Find the next event time
    int nextEventTime = std::numeric_limits<int>::max();
    if (!taskQueue.empty()) {
      nextEventTime = std::min(nextEventTime, taskQueue.top().getDeadline());
    }
    if (!pendingTasks.empty()) {
      nextEventTime =
          std::min(nextEventTime, pendingTasks.front().getArrivalTime());
    }

    // Advance time to the next event
    currentTime = nextEventTime;

    // Process arriving tasks
    while (!pendingTasks.empty() &&
           pendingTasks.front().getArrivalTime() <= currentTime) {
      taskQueue.push(pendingTasks.front());
      pendingTasks.pop();
    }

    // Process tasks
    while (!taskQueue.empty()) {
      Task currentTask = taskQueue.top();
      taskQueue.pop();

      // Set start time if not set
      if (currentTask.getStartTime() == -1) {
        currentTask.setStartTime(currentTime);
      }

      // Calculate execution time
      int executionTime =
          std::min(currentTask.getRemainingTime(),
                   currentTime + 1 - currentTask.getStartTime());
      currentTask.setRemainingTime(currentTask.getRemainingTime() -
                                   executionTime);

      // If task finishes
      if (currentTask.getRemainingTime() == 0) {
        currentTask.setCompletionTime(currentTime + executionTime);
        completedTasks.push_back(currentTask);
      } else {
        // Re-enqueue the task
        taskQueue.push(currentTask);
      }
    }
  }
}
