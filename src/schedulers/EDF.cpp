#include "schedulers/EDF.hpp"

void EDFScheduler::schedule() {
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
    if (!pendingTasks.empty()) {
      nextEventTime = std::min(nextEventTime, pendingTasks.top().getDeadline());
    }

    // Advance time to the next event
    currentTime = nextEventTime;

    // Process arriving tasks
    while (!taskQueue.empty() &&
           taskQueue.front().getArrivalTime() <= currentTime) {
      pendingTasks.push(taskQueue.front());
      taskQueue.pop();
    }

    if (pendingTasks.empty()) {
      // If no tasks to process, continue to the next event time
      continue;
    }

    // Process tasks with the earliest deadlines
    Task currentTask = pendingTasks.top();
    pendingTasks.pop();

    // Set start time if not set
    if (currentTask.getStartTime() == -1) {
      currentTask.setStartTime(currentTime);
    }

    // Determine the execution time
    int deadlineOfNextTask = (pendingTasks.empty())
                                 ? std::numeric_limits<int>::max()
                                 : pendingTasks.top().getDeadline();
    int executionTime = std::min(currentTask.getRemainingTime(),
                                 deadlineOfNextTask - currentTime);

    // Update the current time and remaining time of the task
    currentTask.setRemainingTime(currentTask.getRemainingTime() -
                                 executionTime);
    currentTime += executionTime;

    // Check if the task is finished
    if (currentTask.getRemainingTime() == 0) {
      currentTask.setCompletionTime(currentTime);
      completedTasks.push_back(currentTask);
    } else {
      // Re-enqueue the task if not finished
      pendingTasks.push(currentTask);
    }

    if (currentTime == lastCurrentTime) {
      // If no progress was made, move the task to the completed list
      Task currentTask = pendingTasks.top();
      currentTime += currentTask.getRemainingTime();
      currentTask.setCompletionTime(currentTime);
      completedTasks.push_back(currentTask);
      pendingTasks.pop();
    }

    lastCurrentTime = currentTime;
  }
}
