# CPS-Arduino

This is a simple Arduino project for a CPS course at the University of Tehran. The project consists of two main parts:

- Main board: This part includes one Arduino Uno board that controls and applies logic in the circuit. It receives data from the TH board (explained later), checks conditions, and computes signals to send back to the TH board via Bluetooth.

- TH board: This part includes one Arduino Uno that connects temperature and humidity sensors and sends this information via Bluetooth to the main board. After receiving data (motor speed), it runs the motor.

## Parts

- Main board:
    - One Arduino Uno
    - One Bluetooth module
    - One LCD (LM041L) [to display information]

- TH board:
    - One Arduino Uno
    - One Bluetooth module
    - One DC-MOTOR
    - SHT25 (temperature and humidity sensor)

This project is a great example of using Arduino in a practical application for a CPS course.
