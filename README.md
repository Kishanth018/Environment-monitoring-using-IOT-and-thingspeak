Description

The IoT Environment Monitoring System is an embedded system designed to monitor environmental conditions such as temperature and gas concentration using sensors interfaced with the LPC2129 Microcontroller.

Analog sensor signals from the LM35 Temperature Sensor and MQ‑2 Gas Sensor are converted into digital values using the MCP3204 ADC through SPI communication. The processed data is then transmitted to an IoT cloud platform using the ESP‑01 Wi‑Fi Module, enabling remote monitoring of environmental parameters.

This project demonstrates sensor interfacing, SPI-based ADC communication, UART communication with Wi-Fi modules, and IoT data transmission in an embedded system.

Features

Real-time temperature monitoring

Gas leakage detection using MQ-2 sensor

High-resolution analog data conversion using MCP3204 ADC

SPI communication between microcontroller and ADC

UART communication with Wi-Fi module

Wireless IoT-based environmental monitoring

Continuous data transmission to cloud platform

Hardware Components

LPC2129 Microcontroller

MCP3204 ADC

LM35 Temperature Sensor

MQ‑2 Gas Sensor

ESP‑01 Wi‑Fi Module

Power Supply

Connecting wires

Working Principle

The LM35 sensor measures environmental temperature.

The MQ-2 sensor detects gas concentration in the environment.

Sensor analog signals are converted into digital values using the MCP3204 ADC through SPI communication.

The LPC2129 microcontroller processes the sensor data.

The processed data is transmitted via UART to the ESP-01 Wi-Fi module.

The Wi-Fi module sends the data to a cloud platform for remote environmental monitoring.
