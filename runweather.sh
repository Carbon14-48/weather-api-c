#!/bin/bash

# Step 1: Run the fetcher script to fetch weather data
echo "Fetching weather data..."
./scripts/fetch_weather.sh

# Step 2: Check if the fetcher script ran successfully
if [ $? -eq 0 ]; then
    echo "Weather data fetched successfully!"
else
    echo "Failed to fetch weather data."
    exit 1
fi

# Step 3: Compile the C program if it hasn't been compiled yet
echo "Compiling the C program..."
gcc ./c/main.c -o ./bin/weather_program -ljansson

# Step 4: Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Failed to compile the C program."
    exit 1
fi

# Step 5: Run the compiled C program to process and display the weather data
echo "Running the C program..."
./bin/weather_program

