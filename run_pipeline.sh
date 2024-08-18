#!/bin/bash

# Ensure the output directory exists
mkdir -p outputs

# Run the C++ executable to generate YAML files in the input directory
./build/discrete-events-simulator all examples outputs

# Run the Python script to generate Gantt charts in the same directory
python3 src/gui/gantt_chat.py outputs