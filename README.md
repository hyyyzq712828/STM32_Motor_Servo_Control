# STM32-based High-Performance DC Motor Servo System



## 1. Project Overview

This project implements a high-performance closed-loop servo control system for a DC brushed motor based on the STM32F103C8T6 microcontroller. It features a cascaded PID control structure (Position Loop + Velocity Loop), modular software architecture, and real-time data visualization via a PC-based GUI (VOFA+).

The goal is to achieve fast, stable, and precise control of the motor's position and velocity, laying the groundwork for advanced robotics applications.

## 2. Hardware Components

| Component | Model | Description |
| :--- | :--- | :--- |
| Microcontroller | STM32F103C8T6 | ARM Cortex-M3 Core |
| Motor Driver | TB6612FNG | Dual-channel MOSFET H-bridge |
| DC Motor | MD520Z30_12V | Brushed DC motor with encoder |
| Encoder | 11-line Hall Encoder (1320 pulses/rev after reduction & 4x multiplication) |

**Wiring Diagram:**
(Here you can insert a simple wiring diagram image or text description)

## 3. Software Architecture

The software is designed with a layered and modular approach for better maintainability and scalability.

- **`main.c`**: Application layer, responsible for high-level logic and task scheduling (event-driven via timer interrupts).
- **`controller.c`**: Control layer, implements the core cascaded PID control loop.
- **`bsp.c`**: Board Support Package layer, responsible for initializing all hardware peripherals.
- **`motor.c`**: Driver for motor control (PWM, direction) and speed/position feedback.
- **`pid.c`**: A generic PID controller implementation.
- **`vofa.c`**: Communication protocol for sending data to the VOFA+ GUI.

## 4. Core Technical Details

### 4.1. Cascaded PID Control

The system employs a cascaded PID structure:
- **Outer Loop (Position Control):** A PD controller calculates a target velocity based on the position error.
- **Inner Loop (Velocity Control):** A high-performance PI controller with a low-pass filter on the derivative term tracks the target velocity and outputs the final PWM value.

### 4.2. PID Tuning Process

The PID parameters were meticulously tuned using the Ziegler-Nichols method and manual adjustments, with real-time feedback from VOFA+. 

*(Here you can insert your best VOFA+ waveform screenshots!)*

**Final Parameters:**
- **Velocity Loop:** Kp=8.5, Ki=0.75, Kd=0.01
- **Position Loop:** Kp=0.5, Ki=0.0, Kd=0.1

### 4.3. Real-time Control via Interrupts

The entire control loop is executed within a `TIM4` interrupt service routine with a precise period of **10ms**, ensuring stable and real-time performance, freeing up the main loop for other tasks.

## 5. How to Build & Run

1.  Clone the repository.
2.  Open the project in Keil MDK v5.
3.  Compile and download to the STM32 board.
4.  Connect to the serial port using VOFA+ (115200 baud rate) to visualize the data.

## 6. Problems & Solutions

- **Problem:** PWM changes did not affect motor speed.
  - **Reason:** The `STBY` pin of the TB6612 driver was not pulled high.
  - **Solution:** Connect the `STBY` pin to 3.3V.

- **Problem:** High-frequency oscillations in the velocity feedback when Kd was introduced.
  - **Reason:** The derivative term amplified sensor noise.
  - **Solution:** Implemented a first-order low-pass filter on the velocity measurement.

## 7. Future Work

- [ ] Implement an S-Curve trajectory planning module for smoother motion.
- [ ] Add a feedforward controller to the velocity loop to improve tracking performance.
- [ ] Explore advanced control algorithms such as ADRC.