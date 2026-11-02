# ESP32 Environmental Monitoring System

An IoT project that measures temperature and relative humidity using an ESP32 microcontroller and a DHT22 sensor. Sensor readings are sent to a locally hosted FastAPI, stored in a Postgre SQL database, and visualized in a Grafana dashboard.

The project combines embedded programming, API development, containerization, database management, and data visualization in a single end-to-end system.

## Project overview

The goal of this project was to build an environmental monitoring system that collects sensor data and makes it accessible through a dashboard.

The ESP32 periodically reads temperature and humidity values from the DHT22 sensor and transmits the readings over Wi-Fi to a FastAPI server running in Docker on a local machine. The API processes incoming data and stores the measurements in a PostgreSQL database. Grafana connects to the database to display real-time measurements and historical trends.

## Hardware setup

The hardware consists of an ESP32 development board connected to a DHT22 temperature and humidity sensor.

The DHT22 sensor is connected to the ESP32 using the following pin configuration:

| DHT22 Pin | ESP32 Pin |
|-----------|-----------|
| VCC       | 3.3V      |
| DATA      | GPIO 27    |
| NC        | Not connected |
| GND       | GND       |

A 4.7kΩ pull-up resistor is connected between VCC and DATA to ensure stable communication.

![ESP32 connected to DHT22](images/hardware_setup.jpg)

*ESP32 connected to the DHT22 sensor.*

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

![Grafana dashboard](images/dashboard_preview.png)

*Grafana dashboard displaying temperature and humidity measurements.*

## Features

- Temperature and humidity monitoring using a DHT22 sensor.

- ESP32-based data collection and Wi-Fi connectivity.

- HTTP communication between the ESP32 and the API.

- FastAPI endpoint for receiving sensor readings.

- PostgreSQL database for persistent measurement storage.

- Docker-based deployment of backend services.

- Grafana dashboard for data visualization.

- Configuration separated from source code using environment variables and local secrets files.

- Over-The-Air (OTA) firmware updates, allowing wireless ESP32 programming

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
```
git clone https://github.com/leorydingit/dht22-esp32-iot.git
cd ESP32_DHT22.ino
```
### 2. Configure environment variables

Create a local .env file in the project root directory and add the required backend configuration.

Use .env.example as a template

Do not commit real passwords, API keys, or other sensitive configuration values.

### 3. Configure the ESP32

Configure the local secrets header file with:

- Wi-Fi SSID

- Wi-Fi password

- API server address & port

- OTA password

Make sure the ESP32 uses the host machine's local IP address rather than localhost when communicating with the API.

### 4. Start the backend

From the project root directory, start the Docker services:

```docker compose up --build -d```

Check the service status:

```docker compose ps```

### 5. Upload the firmware code

1. Connect the DHT22 sensor to the ESP32 according to the hardware wiring diagram.

2. Make sure a 4.7kΩ pull-up resistor is connected between 3.3V and the DATA pin.

3. Open the Arduino sketch in Arduino IDE.

4. Select the correct ESP32 board and serial port.

5. Upload the sketch.

6. Open Serial Monitor to check data transmission.

Once the initial firmware has been uploaded via USB, future firmware updates can be performed wirelessly using OTA.

### 6. Access Grafana dashboard

Once the Docker services are running, open Grafana in a web browser.

Default example:

```http://localhost:3000```

The actual address and port depend on the Docker Compose configuration.

Ensure that Grafana is connected to the PostgreSQL database and that the dashboard is configured correctly.

## Security & Configuration

Sensitive configuration is kept separate from the main source code.

- Wi-Fi credentials are stored in a local secrets header file.

- Database credentials and backend settings are managed through environment variables.

- Local secrets files are excluded from version control.

- Python virtual environments are excluded from version control.

Never commit passwords, API keys, or other sensitive information to a public repository.

## What I learned

This project provided practical experience with:

- Embedded programming and sensor integration.

- Reading and transmitting sensor data over Wi-Fi.

- HTTP requests, JSON format, and API communication.

- Using FastAPI.

- Running containerized services with Docker.

- Storing and querying structured data using PostgreSQL.

- Connecting Grafana to a database for data visualization.

- Managing configuration and separating secrets from source code.

- Integrating multiple technologies into a complete IoT system.

## Author

Built as a personal learning project to explore IoT development, backend services, containerization, databases, and data visualization.

