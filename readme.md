# Smart Vehicle Emission Monitoring Device 🚗💨

An IoT-based embedded system built to measure, monitor, and protect the environment by tracking vehicle pollution levels in real-time. Unlike traditional 6-month PUC checks, this system continuously monitors exhaust emissions to instantly detect hazardous spikes using an ESP32 and an MQ-2 gas sensor.

## 🚀 Features
* **Real-Time Monitoring:** Continuous PPM tracking rather than periodic manual checks.
* **Intelligent Data Smoothing:** Employs a software-based smoothing algorithm to filter out sensor noise.
* **Peak & Spike Tracking:** Automatically captures and holds the highest PPM level and alerts on sudden emission spikes.
* **Hardware Display:** 16x2 LCD integration for live parameter viewing.
* **Web Integration:** Simulates real-time telemetry data with a live waveform graph on the VAHANSETU platform.
* **Low Cost & Portable:** Fully operational offline prototype built under ₹700.

---

## 🛠️ Hardware Requirements & Wiring

### Components Used
* **Microcontroller:** ESP32 Development Board
* **Sensor:** MQ-2 Gas Sensor
* **Display:** 16x2 Character LCD
* **PCB/Design:** Custom Board Layout (`.brd` file included)

### LCD Connections (Parallel Interface)
| LCD Pin | ESP32 GPIO |
| :--- | :--- |
| **RS** | GPIO 19 |
| **E** | GPIO 18 |
| **D4** | GPIO 5 |
| **D5** | GPIO 23 |
| **D6** | GPIO 22 |
| **D7** | GPIO 21 |

> ⚠️ *Note: The MQ-2 Analog Output pin is mapped to **GPIO 35** on the ESP32.*

---

## 💻 Software Implementation

The firmware includes analog attenuation configuration for the ESP32's 12-bit ADC to ensure accurate voltage readouts from the MQ sensor, alongside exponential moving average smoothing:

```cpp
// Smoothing calculation snippet
smoothPPM = (0.3 * ppm) + (0.7 * smoothPPM);