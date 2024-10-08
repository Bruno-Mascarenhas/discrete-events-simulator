#include "schedulers/HPF.hpp"

void HPFScheduler::schedule() {
  sortTasksByArrivalTime();
  int currentTime = 0;
  int lastCurrentTime = 0;

  while (!pendingTasks.empty() || !taskQueue.empty()) {
    // Find the next event time
    int nextEventTime = std::numeric_limits<int>::max();

    if (!taskQueue.empty()) {
      nextEventTime =
          std::min(nextEventTime, taskQueue.front().getArrivalTime());
    }

    nextEventTime = std::min(nextEventTime, currentTime);

    // Advance time to the next event
    currentTime = nextEventTime;

    // Process arriving tasks
    while (!taskQueue.empty() &&
           taskQueue.front().getArrivalTime() <= currentTime) {
      pendingTasks.push(taskQueue.front());
      taskQueue.pop();
    }

    // Process tasks from the arrival time queue based on priority
    while (!pendingTasks.empty()) {
      Task currentTask = pendingTasks.top();
      pendingTasks.pop();

      // Set start time if not set
      if (currentTask.getStartTime() == -1) {
        currentTask.setStartTime(currentTime);
      }

      int executionTime = currentTask.getBurstTime();

      currentTask.setRemainingTime(currentTask.getRemainingTime() -
                                   executionTime);

      // Check if task finishes
      if (currentTask.getRemainingTime() == 0) {
        currentTask.setCompletionTime(currentTime);
        completedTasks.push_back(currentTask);
      } else {
        pendingTasks.push(currentTask);
      }

      intervals.push_back(
          {currentTime, currentTime + executionTime, currentTask.getId()});
      // Update the current time
      currentTime += executionTime;

      if (currentTime == lastCurrentTime) {
        // If no progress was made, move the task to the completed list
        Task currentTask = pendingTasks.top();
        currentTime += currentTask.getRemainingTime();
        currentTask.setCompletionTime(currentTime);
        completedTasks.push_back(currentTask);
        pendingTasks.pop();
      }

      //check if there new tasks arrived
      while (!taskQueue.empty() &&
             taskQueue.front().getArrivalTime() <= currentTime) {
        pendingTasks.push(taskQueue.front());
        taskQueue.pop();
      }

      lastCurrentTime = currentTime;
    }
  }
}