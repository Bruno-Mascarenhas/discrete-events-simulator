import matplotlib.pyplot as plt
import yaml
import os
import sys
from datetime import datetime, timedelta


def create_gantt_chart(yaml_file, output_folder):
    with open(yaml_file, "r") as file:
        data = yaml.safe_load(file)

    algorithm_name = data["algorithmName"]
    intervals = data["intervals"]
    completed_tasks = data["completed_tasks"]

    # Calculate average turnaround and waiting times
    total_turnaround_time = sum(task["turnaround_time"] for task in completed_tasks)
    total_waiting_time = sum(task["waiting_time"] for task in completed_tasks)
    average_turnaround_time = total_turnaround_time / len(completed_tasks)
    average_waiting_time = total_waiting_time / len(completed_tasks)

    fig, ax = plt.subplots()

    # Plot intervals
    for interval in intervals:
        start_time = interval["start_time"]
        end_time = interval["end_time"]
        task_id = interval["task_id"]

        ax.barh(
            task_id,
            end_time - start_time,
            left=start_time,
            color="b",
            align="center",
            alpha=0.5,
        )

    plt.xlabel("Time")
    plt.ylabel("Task Id")
    plt.title(f"Gantt Chart for {algorithm_name} Scheduling")

    # Display average turnaround and waiting times on the graph
    text_str = f"Avg Turnaround Time: {average_turnaround_time:.2f}\nAvg Waiting Time: {average_waiting_time:.2f}"
    plt.text(
        0.95,
        0.05,
        text_str,
        transform=ax.transAxes,
        fontsize=10,
        verticalalignment="bottom",
        horizontalalignment="right",
        bbox=dict(facecolor="white", alpha=0.5),
    )

    # Set x-axis and y-axis to grid lines each unit
    ax.xaxis.set_major_locator(plt.MultipleLocator(1))
    ax.yaxis.set_major_locator(plt.MultipleLocator(1))
    plt.grid(True, which="both", axis="both", linestyle="--", linewidth=0.5)
    plt.tight_layout()

    # Save the chart in the same directory as the YAML file
    output_file = os.path.join(
        output_folder, os.path.basename(yaml_file).replace(".yaml", ".png")
    )
    plt.savefig(output_file)
    plt.close()


def main(input_folder):
    for filename in os.listdir(input_folder):
        if filename.endswith(".yaml"):
            yaml_file = os.path.join(input_folder, filename)
            create_gantt_chart(yaml_file, input_folder)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 generate_gantt_charts.py <input_folder>")
        sys.exit(1)

    input_folder = sys.argv[1]
    main(input_folder)
