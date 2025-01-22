#include <stdio.h>
#include <jansson.h>
#include<string.h>

int main() {
    // Open the weather.json file
    FILE *file = fopen("data/weather.json", "r");  
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    json_error_t error;
    json_t *root = json_loadf(file, 0, &error);  // Load the JSON from the file

    if (!root) { 
        // If loading failed, print the error details
        fprintf(stderr, "Error loading JSON: %s\n", error.text);
        fclose(file);
        return 1;
    }

    // Successfully loaded JSON, you can now work with 'root'
    printf("JSON loaded successfully!\n");

    // Extract specific fields from the JSON
    json_t *weather = json_object_get(root, "weather");  // Get the "weather" array
    json_t *weather_0 = json_array_get(weather, 0);      // Get the first element in the "weather" array
    const char *description = json_string_value(json_object_get(weather_0, "description"));  // Extract description

    json_t *main = json_object_get(root, "main");  // Get the "main" object
    double temp_kelvin = json_real_value(json_object_get(main, "temp"));  // Extract temperature
    const char *city = json_string_value(json_object_get(root, "name"));  // Extract city name
  double temp_celsius = temp_kelvin - 273.15;
    // Check if the data was extracted successfully
    if (description && city && temp_kelvin) {
        // Print the extracted data
        printf("Weather in %s:\n", city);
        printf("Description: %s\n", description);
        printf("Temperature: %.2f C\n", temp_celsius);
    } else {
       
        const char *cod = json_string_value(json_object_get(root, "cod"));
    if (cod && strcmp(cod, "404") == 0) {
        // Extract the "message" field
        const char *message = json_string_value(json_object_get(root, "message"));
        if (message) {
            printf("Error: %s\n", message);
        } else {
            printf("Error: Unknown error occurred.\n");
        }
    } else {
        printf("No error. Weather data loaded successfully!\n");
    }
    }

    // Clean up
    json_decref(root);  // Free the memory used by the JSON object
    fclose(file);  // Close the file

    return 0;
}
