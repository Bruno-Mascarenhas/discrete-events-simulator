#include "schedulers/RoundRobin.hpp"

RoundRobinScheduler::RoundRobinScheduler(int quantum) : quantum(quantum) {}

void RoundRobinScheduler::schedule() {
  sortTasksByArrivalTime();
  int currentTime = 0;

  while (!taskQueue.empty() || !pendingTasks.empty()) {
    // Move tasks from taskQueue to pendingTasks based on current time
    while (!taskQueue.empty() &&
           taskQueue.front().getArrivalTime() <= currentTime) {
      pendingTasks.push(taskQueue.front());
      taskQueue.pop();
    }

    // If there are tasks ready to execute
    if (!pendingTasks.empty()) {
      Task currentTask = pendingTasks.front();
      pendingTasks.pop();

      if (currentTask.getStartTime() == -1) {
        currentTask.setStartTime(currentTime);
      }

      // Execute the task for the time slice or remaining time, whichever is smaller
      int timeSlice = std::min(quantum, currentTask.getRemainingTime());
      currentTask.setRemainingTime(currentTask.getRemainingTime() - timeSlice);
      currentTime += timeSlice;

      // If the task is completed
      if (currentTask.getRemainingTime() == 0) {
        currentTask.setCompletionTime(currentTime);
        completedTasks.push_back(currentTask);

        std::cout << "Task " << currentTask.getId() << " completed at time "
                  << currentTime << "\n";
      } else {
        // If the task is not completed, push it back into the pendingTasks
        pendingTasks.push(currentTask);
      }
    } else {
      // If no tasks are ready, advance time to the next task's arrival
      if (!taskQueue.empty()) {
        currentTime = taskQueue.front().getArrivalTime();
      }
    }
  }
}
