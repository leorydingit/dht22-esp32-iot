# ESP32 Environmental Monitoring System

An IoT project that measures temperature and relative humidity using an ESP32 microcontroller and a DHT22 sensor. Sensor readings are sent to a locally hosted API, stored in a SQL database, and visualized in a Grafana dashboard.

The project combines embedded programming, API development, containerization, database management, and data visualization in a single end-to-end system.

## Dashboard preview

## Hardware setup

The hardware consists of an ESP32 microcontroller connected to a DHT22 temperature and humidity sensor. The ESP32 periodically collects measurements and sends them to the backend over Wi-Fi.

## Architecture
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
