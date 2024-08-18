#ifndef IO_UTILS_HPP
#define IO_UTILS_HPP

#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <vector>
#include "schedulers/BaseScheduler.hpp"
#include "utils/Tasks.hpp"

/**
 * @brief Loads tasks from a YAML file.
 * This function reads the tasks from the provided YAML file and creates 
 * a vector of Task objects. The YAML file should contain a "tasks" 
 * node where each task has attributes like id, burst_time, arrival_time, 
 * deadline, and optionally priority.
 * @param filename The path to the YAML file containing the tasks.
 * @return A vector of Task objects loaded from the YAML file.
 * @throw YAML::BadFile if the YAML file cannot be opened.
 */
std::vector<Task> loadTasksFromYAML(const std::string& filename);

/**
 * @brief Exports completed tasks to a YAML file.
 * This function writes the completed tasks to a YAML file with details 
 * like id, burst_time, arrival_time, deadline, priority, start_time, 
 * completion_time, waiting_time, and turnaround_time. The output file 
 * is saved in the "outputs" folder with the algorithm name as a prefix.
 * @param completedTasks A vector of Task objects representing completed tasks.
 * @param algorithmName The name of the scheduling algorithm used.
 */
void exportCompletedTasksToYAML(
    const std::vector<Task>& completedTasks,
    const std::vector<BaseScheduler::Interval>& intervals,
    const std::string& algorithmName, const std::string& outputFolderPath);

/**
 * @brief Prints a Gantt chart based on the provided tasks.
 * This function displays a simple Gantt chart on the console. 
 * The chart shows the completion times and corresponding task IDs 
 * in a formatted output.
 * @param tasks A vector of Task objects representing the scheduled tasks.
 */
void printGanttChart(const std::vector<Task>& tasks);

#endif  // IO_UTILS_HPP
