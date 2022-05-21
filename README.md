# Organic Gardner esp32 Station

This is the esp32 _collection and control_ station code for the
_Organic Gardner_ project. This code runs on an esp32 development
board with the following features:

- DHT22 Temperature sensor with the signal connected pin P5.
- Wifi is configured with an SSID and Password
- MQTT broker is configured and connected to
- MQTT publishes sensor data to iote/data/<stationid>/{humidity,tempf}

## How to use example

### Hardware Required

- esp32 development board
- dht22 sensor with pin connected to P5

### Configure the project

```
idf.py menuconfig
```

- set the wifi SSID/Passwd
- set the MQTT server address

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(Replace PORT with the name of the serial port to use.)

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use
ESP-IDF to build projects.

## Example Output

The following log output should appear when the example runs (note that the bootloader log has been omitted).

```
TBD
```
