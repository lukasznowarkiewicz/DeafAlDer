# DeafAlDer

## Introduction

DeafAIDer system is a home signaling and alarm system designed specifically for people who are deaf. The idea was born as a project for the XLV Innovation and Invention Olympics at the Electrical and Electronic Schools in Szczecin, Poland, under the guidance of Dr. Dariusz Mostowski. Our goal was to create an affordable and scalable solution to alert deaf individuals to everyday events and emergencies through predefined light signals, vibrations, and low-frequency sound waves. It's user-friendly, integrates easily with existing home systems, and can work with both custom and commercial sensors.



## Functional assumptions

The DeafAIDer system is designed to be modular and scalable, seamlessly integrating with both custom-made and third-party detectors and actuators through software modifications. It's capable of alerting users to both everyday events (like waking up, kitchen timers, and doorbells) and emergency situations (like fire, carbon monoxide poisoning, and flooding) through optical signals using household lighting, specialized flashing modules, and vibration alerts. This flexible system ensures that deaf individuals can be promptly informed about important events in their environment.


## Hardware - electronics

### PLC control 

The DeafAIDer system's heart, a Siemens PLC controller LOGO! 12/24 RCE, orchestrates event detection and signaling, integrating seamlessly with both custom and commercial modules via digital inputs and controlling outputs for various alert types, all while offering extensive programmability and remote management features.

### Flood Sensor Module

The flood sensor module in the DeafAIDer® system detects water leaks or pipe bursts by utilizing the electrical conductivity of water to change the state of a MOSFET transistor, triggering an alert and activating programmed responses such as strobe lighting and display notifications.


### Kitchen Timer Module

The kitchen timer module, designed for simplicity and functionality, uses a single encoder with a button for setting and adjusting countdown times for cooking tasks. Upon time expiration, it triggers an alarm and a visual signal on the display, also notifying the DeafAIDer system to activate kitchen lights for an intuitive and accessible alert.

### Smoke and carbon monoxide

To seamlessly incorporate commercial smoke and carbon monoxide detectors into the DeafAIDer system, custom boards were developed. These boards adapt the sensors to the system's 12V power supply and convert alarm signals into digital outputs compatible with the central control unit. This ensures that the system can directly power the sensors and correctly interpret their alerts, enabling effective visual warnings for users.


### Alarm Clock Module with Vibration Signal

Built on an ATmega8 microcontroller, this module offers multiple input methods including an encoder, proximity sensors, and a capacitive button, with feedback displayed on a quadruple 7-segment display, enhanced by an RGB LED for color-coded alerts. It uniquely controls a vibration pad for waking up, integrating several functional blocks like power supply adaptation, signal processing, and RTC module for timekeeping. Customization ensures direct connection to the central unit via logic level conversion, making it a vital component for the visually and auditorily accessible DeafAIDer system.

### Doorbell Module

The doorbell module features an encapsulated momentary button with LED indicators, interfacing with an acoustic signaler within the distribution board. It comprises a power supply block for system integration, a button control with debouncing circuitry, and an LED lighting section that alternates between blue for standby and red when activated, ensuring efficient power use and clear visual feedback.

## Hardware - mechanical

All these custom-designed enclosures, detailed in Autodesk Inventor 2014 and realized through 3D printing, were efficiently accommodated within a presentation case. This meticulous organization not only ensured the portability of the DeafAIDer® system's components like the alarm clock module, kitchen timer, and various sensors but also highlighted the system's modular design and the practical application of 3D printing in creating tailored electronics enclosures for a cohesive and professional demonstration setup.


## Software

The DeafAIDer system's software is developed across two main platforms. 

The PLC components are programmed using Logo Soft Comfort, a user-friendly software tailored for configuring Siemens LOGO! PLCs, enabling intuitive logic creation for the system's core functionalities. 

For the ATmega microcontroller modules, including the alarm clock and kitchen timer, the Eclipse IDE is utilized alongside the C programming language, offering a robust environment for developing and debugging the microcontroller's firmware.








