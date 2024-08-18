#include <filesystem>
#include <iostream>
#include <unordered_set>
#include "schedulers/BaseScheduler.hpp"
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
  if (argc < 2) {
    std::cerr << "Please specify an algorithm: fifo, sjf, robin, or all"
              << std::endl;
    return 1;
  }

  // Documentation to argument == help
  if (argc == 2 && std::string(argv[1]) == "help") {
    std::cout << "Usage: ./discrete-events-simulator <algorithm> <input_path> "
                 "<output_path>"
              << std::endl
              << "Algorithms: fifo, sjf, edf, robin, hpf, all" << std::endl
              << "Default input_path: ../examples/tasks.yml" << std::endl
              << "Default output_path: ../outputs" << std::endl;
    return 0;
  }

  std::string algorithm = argv[1];
  std::unordered_set<std::string> validAlgorithms = {"fifo",  "sjf", "edf",
                                                     "robin", "hpf", "all"};

  if (validAlgorithms.find(algorithm) == validAlgorithms.end()) {
    std::cerr << "Invalid algorithm specified" << std::endl;
    return 1;
  }

  std::vector<Task> tasks;
  std::filesystem::path input_path = "../examples/tasks.yml";
  std::filesystem::path output_path = "../outputs/";

  if (argc == 4) {
    input_path = argv[2];
    output_path = argv[3];
    tasks = loadTasksFromYAML(input_path / "tasks.yml");
  } else {
    tasks = loadTasksFromYAML("../examples/tasks.yml");
  }

  if (algorithm == "fifo" || algorithm == "all") {
    std::cout << "\nFIFO Scheduler:\n";
    FIFOScheduler fifoScheduler;
    runScheduler(fifoScheduler, tasks);
    exportCompletedTasksToYAML(fifoScheduler.getCompletedTasks(),
                               fifoScheduler.getIntervals(), "FIFO",
                               output_path);
  }

  if (algorithm == "sjf" || algorithm == "all") {
    std::cout << "\nSJF Scheduler:\n";
    SJFScheduler sjfScheduler;
    runScheduler(sjfScheduler, tasks);
    exportCompletedTasksToYAML(sjfScheduler.getCompletedTasks(),
                               sjfScheduler.getIntervals(), "SJF", output_path);
  }

  if (algorithm == "robin" || algorithm == "all") {
    std::cout << "\nRound Robin Scheduler:\n";
    RoundRobinScheduler roundRobinScheduler(2);  // Quantum = 2
    runScheduler(roundRobinScheduler, tasks);
    exportCompletedTasksToYAML(roundRobinScheduler.getCompletedTasks(),
                               roundRobinScheduler.getIntervals(), "RoundRobin",
                               output_path);
  }

  if (algorithm == "hpf" || algorithm == "all") {
    std::cout << "\nHPF Scheduler:\n";
    HPFScheduler hpfScheduler;
    runScheduler(hpfScheduler, tasks);
    exportCompletedTasksToYAML(hpfScheduler.getCompletedTasks(),
                               hpfScheduler.getIntervals(), "HPF", output_path);
  }

  return 0;
}
