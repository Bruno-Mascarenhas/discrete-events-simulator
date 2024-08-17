#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>
#include "schedulers/EDF.hpp"
#include "schedulers/FIFO.hpp"
#include "schedulers/HPF.hpp"
#include "schedulers/RoundRobin.hpp"
#include "schedulers/SJF.hpp"
#include "utils/Tasks.hpp"
#include "utils/ioutils.hpp"

class SchedulerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    tasks = loadTasksFromYAML("../tests/tasks/tasks.yml");
  }

  void TearDown() override { tasks.clear(); }

  std::vector<Task> tasks;
};

TEST_F(SchedulerTest, FIFOSchedulerTest) {
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
  EDFScheduler edfScheduler;
  edfScheduler.addTasks(tasks);
  edfScheduler.schedule();

  const auto& completedTasks = edfScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check if tasks were scheduled based on their deadlines
  for (int i = 1; i < completedTasks.size(); ++i) {
    EXPECT_GE(completedTasks[i].getDeadline(),
              completedTasks[i - 1].getDeadline());
  }
}

TEST_F(SchedulerTest, SJFSchedulerTest) {
  SJFScheduler sjfScheduler;
  sjfScheduler.addTasks(tasks);
  sjfScheduler.schedule();

  const auto& completedTasks = sjfScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check if tasks were scheduled based on their shortest burst times
  for (int i = 1; i < completedTasks.size(); ++i) {
    EXPECT_GE(completedTasks[i].getBurstTime(),
              completedTasks[i - 1].getBurstTime());
  }
}

TEST_F(SchedulerTest, RoundRobinSchedulerTest) {
  RoundRobinScheduler roundRobinScheduler(2);  // Quantum = 2
  roundRobinScheduler.addTasks(tasks);
  roundRobinScheduler.schedule();

  const auto& completedTasks = roundRobinScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check order and timing based on expected results

  // Check if tasks were preempted after their quantum
}

TEST_F(SchedulerTest, HPFSchedulerTest) {
  HPFScheduler hpfScheduler;
  hpfScheduler.addTasks(tasks);
  hpfScheduler.schedule();

  const auto& completedTasks = hpfScheduler.getCompletedTasks();

  ASSERT_EQ(completedTasks.size(), tasks.size());

  // Check if tasks were scheduled based on their priorities
  for (int i = 1; i < completedTasks.size(); ++i) {
    EXPECT_LE(completedTasks[i].getPriority(),
              completedTasks[i - 1].getPriority());
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}