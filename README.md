# ESP32 Environmental Monitoring System

An IoT project that measures temperature and relative humidity using an ESP32 microcontroller and a DHT22 sensor. Sensor readings are sent to a locally hosted FastAPI, stored in a Postgre SQL database, and visualized in a Grafana dashboard.

The project combines embedded programming, API development, containerization, database management, and data visualization in a single end-to-end system.

## Project overview

The goal of this project was to build an environmental monitoring system that collects sensor data and makes it accessible through a dashboard.

The ESP32 periodically reads temperature and humidity values from the DHT22 sensor and transmits the readings over Wi-Fi to a FastAPI server running in Docker on a local machine. The API processes incoming data and stores the measurements in a PostgreSQL database. Grafana connects to the database to display real-time measurements and historical trends.

## Hardware setup

The hardware consists of an ESP32 development board connected to a DHT22 temperature and humidity sensor.

## Architecture

The system consists of four main components:

1. **ESP32 + DHT22:** Collects temperature and humidity measurements.

2. **FastAPI:** Receives sensor readings through HTTP requests.

3. **PostgreSQL:** Stores the collected measurements.

4. **Grafana:** Visualizes the stored data in a dashboard

```mermaid
flowchart TD
    A["ESP32 + DHT22<br/>Temperature & Humidity"]
    B["FastAPI<br/>Docker Container"]
    C[("PostgreSQL<br/>Database")]
    D["Grafana<br/>Dashboard"]

    A -->|"Wi-Fi / HTTP - JSON payload"| B
    B -->|"Store measurements"| C
    C -->|"Query data"| D 
   ```

## Dashboard preview

## Features

- Temperature and humidity monitoring using a DHT22 sensor.

- ESP32-based data collection and Wi-Fi connectivity.

- HTTP communication between the ESP32 and the API.

- FastAPI endpoint for receiving sensor readings.

- PostgreSQL database for persistent measurement storage.

- Docker-based deployment of backend services.

- Grafana dashboard for data visualization.

- Configuration separated from source code using environment variables and local secrets files.

## Technologies used 

| Technology  | Purpose |
| ------------- | ------------- |
| ESP32  | Microcontroller and sensor data collection  |
| DHT22  |  Temperature and humidity measurements  |
| C++ / Arduino IDE  | Embedded programming |
| Wi-Fi  |  Network connectivity  |
| HTTP (JSON) | Data transmission |
| Python / FastAPI | Backend API |
| Docker | Containerization and service deployment |
| PostgreSQL | Database and data storage |
| Grafana | Data visualization |

## Getting started

### Prerequisites

- Docker

- Arduino IDE

- ESP32 support library for Arduino IDE

- DHT sensor library by Adafruit

- ESP32 development board

- Breadboard & jumper wires

- 4.7kΩ resistor

- DHT22 sensor

- A local Wi-Fi network

### 1. Clone this repository

