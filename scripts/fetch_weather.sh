#!/bin/bash

# Prompt user for city name
read -p "Enter city name: " city

# Fetch weather data using the API key
curl -s "http://api.openweathermap.org/data/2.5/weather?q=$city&appid=2e308f9c7894051f674a6fe4cf0db9f4" > ./data/weather.json

echo "Weather data saved to data/weather.json"

