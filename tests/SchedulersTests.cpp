#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>
#include "Tasks.hpp"
#include "schedulers/EDF.hpp"
#include "schedulers/FIFO.hpp"
#include "schedulers/RoundRobin.hpp"
#include "schedulers/SJF.hpp"

class SchedulerTest : public ::testing::Test {
 protected:
  std::vector<Task> loadTasksFromYAML(const std::string& filename) {
    std::vector<Task> tasks;

    YAML::Node config = YAML::LoadFile(filename);
    for (const YAML::Node& task_node : config["tasks"]) {
      int id = task_node["id"].as<int>();
      int burst_time = task_node["burst_time"].as<int>();
      int arrival_time = task_node["arrival_time"].as<int>();
      int deadline = task_node["deadline"].as<int>();
      int priority = task_node["priority"].as<int>();  // Optional

      tasks.emplace_back(id, burst_time, arrival_time, deadline, priority);
    }

    return tasks;
  }
};

TEST_F(SchedulerTest, FIFOSchedulerTest) {
  std::string yamlFilePath = "../tests/tasks/tasks.yml";
  std::vector<Task> tasks = loadTasksFromYAML(yamlFilePath);

  FIFOScheduler fifoScheduler;
  fifoScheduler.addTasks(tasks);
  fifoScheduler.schedule();

  const auto& completedTasks = fifoScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check order and timing based on expected results
  EXPECT_EQ(completedTasks[0].getId(), 1);
  EXPECT_EQ(completedTasks[1].getId(), 2);
}

TEST_F(SchedulerTest, EDFSchedulerTest) {
  std::string yamlFilePath = "tests/tasks/tasks.yml";
  std::vector<Task> tasks = loadTasksFromYAML(yamlFilePath);

  EDFScheduler edfScheduler;
  edfScheduler.addTasks(tasks);
  edfScheduler.schedule();

  const auto& completedTasks = edfScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check order and timing based on expected results
  EXPECT_EQ(completedTasks[0].getId(), 2);
  EXPECT_EQ(completedTasks[1].getId(), 1);
}

TEST_F(SchedulerTest, SJFSchedulerTest) {
  std::string yamlFilePath = "tests/tasks/tasks.yml";
  std::vector<Task> tasks = loadTasksFromYAML(yamlFilePath);

  SJFScheduler sjfScheduler;
  sjfScheduler.addTasks(tasks);
  sjfScheduler.schedule();

  const auto& completedTasks = sjfScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check order and timing based on expected results
  EXPECT_EQ(completedTasks[0].getId(), 3);
  EXPECT_EQ(completedTasks[1].getId(), 1);
}

TEST_F(SchedulerTest, RoundRobinSchedulerTest) {
  std::string yamlFilePath = "tests/tasks/tasks.yml";
  std::vector<Task> tasks = loadTasksFromYAML(yamlFilePath);

  RoundRobinScheduler roundRobinScheduler(2);  // Quantum = 2
  roundRobinScheduler.addTasks(tasks);
  roundRobinScheduler.schedule();

  const auto& completedTasks = roundRobinScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check order and timing based on expected results
  EXPECT_EQ(completedTasks[0].getId(), 1);
  EXPECT_EQ(completedTasks[1].getId(), 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}