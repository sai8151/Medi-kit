# ESP8266 MAX30105 Sensor Project

This project utilizes an ESP8266 microcontroller along with the MAX30105 sensor for monitoring various physiological parameters.

## Installation

### Hardware Requirements
- ESP8266 microcontroller
- MAX30105 sensor

### Libraries
Ensure the following libraries are installed:
- ESP8266WiFi.h
- Wire.h
- MAX30105.h

To install libraries, follow the instructions provided by the respective libraries.

## Configuration

1. Connect the ESP8266 device to your Wi-Fi network by updating the following variables in the code:
   - `ssid`: Your Wi-Fi network's SSID
   - `password`: Your Wi-Fi network's password

2. Set up any additional pin initializations as required.

## Usage

The ESP8266 device provides the following functionalities:

- `/gpio2/0`: Turn off GPIO 2.
- `/sensor`: Retrieve sensor readings including red, IR, and green values, heart rate, and temperature.

## Dependencies

- ESP8266WiFi.h 
- Wire.h 
- MAX30105.h 

## Example

To turn off GPIO 2, send an HTTP request to `/gpio2/0`.

To retrieve sensor readings, send an HTTP request to `/sensor`.

## Scope

The project entails integrating machine learning (ML) into the ESP8266 MAX30105 Sensor system to analyze heart rate and related statistics. It involves collecting raw sensor data from the MAX30105 sensor, including red, IR, and green light intensity values, and preprocessing the data to handle missing values, outliers, and noise. Relevant features are then extracted, such as peak detection for heartbeats and statistical measures like mean and standard deviation, followed by model training using labeled datasets to discern heart rate patterns. Model performance is evaluated using metrics like mean absolute error and correlation coefficient.

# If you're interested in contributing, feel free to reach out to me.
