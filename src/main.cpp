#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "schedulers/EDF.hpp"
#include "schedulers/FIFO.hpp"
#include "schedulers/RoundRobin.hpp"
#include "schedulers/SJF.hpp"

std::vector<Task> loadTasksFromYAML(const std::string& filename) {
  std::vector<Task> tasks;

  try {
    YAML::Node config = YAML::LoadFile(filename);
    for (const YAML::Node& task_node : config["tasks"]) {
      int id = task_node["id"].as<int>();
      int burst_time = task_node["burst_time"].as<int>();
      int arrival_time = task_node["arrival_time"].as<int>();
      int deadline = task_node["deadline"].as<int>();
      int priority = task_node["priority"].as<int>();  // Optional

      tasks.emplace_back(id, burst_time, arrival_time, deadline, priority);
    }
  } catch (const YAML::BadFile& e) {
    std::cerr << "Failed to open YAML file: " << filename << std::endl;
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return tasks;
}

void printGanttChart(const std::vector<Task>& tasks) {
  std::cout << "Gantt Chart:\n";
  std::cout << "Time: ";
  for (const auto& task : tasks) {
    std::cout << std::setw(5) << task.getCompletionTime();
  }
  std::cout << "\nTasks: ";
  for (const auto& task : tasks) {
    std::cout << std::setw(5) << task.getId();
  }
  std::cout << "\n";
}

int main() {
  // Load tasks from YAML file
  std::vector<Task> tasks = loadTasksFromYAML("../examples/tasks.yml");

  // EDF Scheduler
  std::cout << "EDF Scheduler:\n";
  EDFScheduler edfScheduler;
  edfScheduler.addTasks(tasks);
  edfScheduler.schedule();
  printGanttChart(edfScheduler.getCompletedTasks());

  // FIFO Scheduler
  std::cout << "\nFIFO Scheduler:\n";
  FIFOScheduler fifoScheduler;
  fifoScheduler.addTasks(tasks);
  fifoScheduler.schedule();
  printGanttChart(fifoScheduler.getCompletedTasks());

  // SJF Scheduler
  std::cout << "\nSJF Scheduler:\n";
  SJFScheduler sjfScheduler;
  sjfScheduler.addTasks(tasks);
  sjfScheduler.schedule();
  printGanttChart(sjfScheduler.getCompletedTasks());

  // Round Robin Scheduler
  std::cout << "\nRound Robin Scheduler:\n";
  RoundRobinScheduler roundRobinScheduler(2);  // Quantum = 2
  roundRobinScheduler.addTasks(tasks);
  roundRobinScheduler.schedule();
  printGanttChart(roundRobinScheduler.getCompletedTasks());

  return 0;
}
