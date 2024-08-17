#include <iostream>
#include <unordered_set>
#include "schedulers/BaseScheduler.hpp"
#include "schedulers/EDF.hpp"
#include "schedulers/FIFO.hpp"
#include "schedulers/HPF.hpp"
#include "schedulers/RoundRobin.hpp"
#include "schedulers/SJF.hpp"
#include "utils/ioutils.hpp"

void runScheduler(BaseScheduler& scheduler, const std::vector<Task>& tasks) {
  scheduler.addTasks(tasks);
  scheduler.schedule();
  printGanttChart(scheduler.getCompletedTasks());
}

int main(int argc, char* argv[]) {
  // Load tasks from YAML file
  std::vector<Task> tasks = loadTasksFromYAML("../examples/tasks.yml");

  if (argc < 2) {
    std::cerr << "Please specify an algorithm: fifo, sjf, edf, robin, or all"
              << std::endl;
    return 1;
  }

  std::string algorithm = argv[1];

  if (algorithm == "fifo" || algorithm == "all") {
    std::cout << "\nFIFO Scheduler:\n";
    FIFOScheduler fifoScheduler;
    runScheduler(fifoScheduler, tasks);
  }

  if (algorithm == "sjf" || algorithm == "all") {
    std::cout << "\nSJF Scheduler:\n";
    SJFScheduler sjfScheduler;
    runScheduler(sjfScheduler, tasks);
  }

  if (algorithm == "edf" || algorithm == "all") {
    std::cout << "\nEDF Scheduler:\n";
    EDFScheduler edfScheduler;
    runScheduler(edfScheduler, tasks);
  }

  if (algorithm == "robin" || algorithm == "all") {
    std::cout << "\nRound Robin Scheduler:\n";
    RoundRobinScheduler roundRobinScheduler(2);  // Quantum = 2
    runScheduler(roundRobinScheduler, tasks);
  }

  if (algorithm == "hpf" || algorithm == "all") {
    std::cout << "\nHPF Scheduler:\n";
    HPFScheduler hpfScheduler;
    runScheduler(hpfScheduler, tasks);
  }

  std::unordered_set<std::string> validAlgorithms = {"fifo",  "sjf", "edf",
                                                     "robin", "hpf", "all"};

  if (validAlgorithms.find(algorithm) == validAlgorithms.end()) {
    std::cout << "Invalid algorithm specified\n";
  }

  return 0;
}
