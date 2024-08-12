#include "schedulers/RoundRobin.hpp"
#include <iostream>
#include <queue>

RoundRobinScheduler::RoundRobinScheduler(int quantum) : quantum(quantum) {}

void RoundRobinScheduler::addTask(const Task& task) {
  taskQueue.push(task);
}

void RoundRobinScheduler::addTasks(const std::vector<Task>& tasks) {
  for (const Task& task : tasks) {
    taskQueue.push(task);
  }
}

void RoundRobinScheduler::schedule() {
  int currentTime = 0;

  // A queue to temporarily hold tasks that have arrived but are not yet ready to execute
  std::queue<Task> waitingQueue;

  while (!taskQueue.empty() || !waitingQueue.empty()) {
    // Move tasks from taskQueue to waitingQueue based on current time
    while (!taskQueue.empty() &&
           taskQueue.front().getArrivalTime() <= currentTime) {
      waitingQueue.push(taskQueue.front());
      taskQueue.pop();
    }

    // If there are tasks ready to execute
    if (!waitingQueue.empty()) {
      Task currentTask = waitingQueue.front();
      waitingQueue.pop();

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
        // If the task is not completed, push it back into the waitingQueue
        waitingQueue.push(currentTask);
      }
    } else {
      // If no tasks are ready, advance time to the next task's arrival
      if (!taskQueue.empty()) {
        currentTime = taskQueue.front().getArrivalTime();
      }
    }
  }
}

const std::vector<Task>& RoundRobinScheduler::getCompletedTasks() const {
  return completedTasks;
}