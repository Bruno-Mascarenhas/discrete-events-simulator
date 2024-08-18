#include "utils/ioutils.hpp"

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

void exportCompletedTasksToYAML(
    const std::vector<Task>& completedTasks,
    const std::vector<BaseScheduler::Interval>& intervals,
    const std::string& algorithmName, const std::string& outputFolderPath) {

  std::filesystem::path path = outputFolderPath;
  std::filesystem::path outputfile =
      path / (algorithmName + "_completed_tasks.yaml");

  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "algorithmName";
  emitter << YAML::Value << algorithmName;
  emitter << YAML::Key << "completed_tasks";
  emitter << YAML::Value << YAML::BeginSeq;

  for (const auto& task : completedTasks) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "id" << YAML::Value << task.getId();
    emitter << YAML::Key << "burst_time" << YAML::Value << task.getBurstTime();
    emitter << YAML::Key << "arrival_time" << YAML::Value
            << task.getArrivalTime();
    emitter << YAML::Key << "deadline" << YAML::Value << task.getDeadline();
    emitter << YAML::Key << "priority" << YAML::Value << task.getPriority();
    emitter << YAML::Key << "start_time" << YAML::Value << task.getStartTime();
    emitter << YAML::Key << "completion_time" << YAML::Value
            << task.getCompletionTime();
    emitter << YAML::Key << "waiting_time" << YAML::Value
            << task.getWaitingTime();
    emitter << YAML::Key << "turnaround_time" << YAML::Value
            << task.getTurnaroundTime();
    emitter << YAML::EndMap;
  }

  emitter << YAML::EndSeq;

  emitter << YAML::Key << "intervals";
  emitter << YAML::Value << YAML::BeginSeq;

  for (const auto& interval : intervals) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "start_time" << YAML::Value << interval.start;
    emitter << YAML::Key << "end_time" << YAML::Value << interval.end;
    emitter << YAML::Key << "task_id" << YAML::Value << interval.taskId;
    emitter << YAML::EndMap;
  }

  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;

  // Create the output folder if it doesn't exist
  if (!std::filesystem::exists(outputFolderPath)) {
    std::filesystem::create_directory(outputFolderPath);
  }

  // Save the YAML data to the file
  std::ofstream outfile(outputfile);
  if (outfile.is_open()) {
    outfile << emitter.c_str();
    outfile.close();
    std::cout << "Completed tasks exported successfully to: " << outputfile
              << std::endl;
  } else {
    std::cerr << "Failed to open output file: " << outputfile << std::endl;
  }
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