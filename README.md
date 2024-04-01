# DeafAlDer

![Project Photos](imagesAndPhotos/project_photos.JPG)

## Introduction

DeafAIDer system is a home signaling and alarm system designed specifically for people who are deaf. The idea was born as a project for the XLV Innovation and Invention Olympics at the Electrical and Electronic Schools in Szczecin, Poland, under the guidance of Dr. Dariusz Mostowski. Our goal was to create an affordable and scalable solution to alert deaf individuals to everyday events and emergencies through predefined light signals, vibrations, and low-frequency sound waves. It's user-friendly, integrates easily with existing home systems, and can work with both custom and commercial sensors.

![DeafAlDer Logo](imagesAndPhotos/Defaider_Logo_new.png)


## Functional assumptions

The DeafAIDer system is designed to be modular and scalable, seamlessly integrating with both custom-made and third-party detectors and actuators through software modifications. It's capable of alerting users to both everyday events (like waking up, kitchen timers, and doorbells) and emergency situations (like fire, carbon monoxide poisoning, and flooding) through optical signals using household lighting, specialized flashing modules, and vibration alerts. This flexible system ensures that deaf individuals can be promptly informed about important events in their environment.


## Hardware - electronics

### PLC control 

The DeafAIDer system's heart, a Siemens PLC controller LOGO! 12/24 RCE, orchestrates event detection and signaling, integrating seamlessly with both custom and commercial modules via digital inputs and controlling outputs for various alert types, all while offering extensive programmability and remote management features.

![PLC Wired Up](imagesAndPhotos/PLC_wired_up.JPG)
![PLC Programming](imagesAndPhotos/PLC_programming.JPG)
![PLC Connections Diagram](imagesAndPhotos/PLC_connections_diagram.png)

### Flood Sensor Module

The flood sensor module in the DeafAIDer® system detects water leaks or pipe bursts by utilizing the electrical conductivity of water to change the state of a MOSFET transistor, triggering an alert and activating programmed responses such as strobe lighting and display notifications.

- Altium Designs for Flood Sensor:
    - ![Flood Sensor Schematic](imagesAndPhotos/altium/floodSensor_sch.JPG)
    - ![Flood Sensor PCB](imagesAndPhotos/altium/floodSensor_pcb.JPG)
    - ![Flood Sensor Top View](imagesAndPhotos/altium/floodSensor_top.JPG)

### Kitchen Timer Module

The kitchen timer module, designed for simplicity and functionality, uses a single encoder with a button for setting and adjusting countdown times for cooking tasks. Upon time expiration, it triggers an alarm and a visual signal on the display, also notifying the DeafAIDer system to activate kitchen lights for an intuitive and accessible alert.

- Altium Designs for Kitchen Timer:
    - ![Timer Schematic](imagesAndPhotos/altium/timer_sch.JPG)
    - ![Timer PCB](imagesAndPhotos/altium/timer_pcb.JPG)
    - ![Timer Top View](imagesAndPhotos/altium/timer_top.JPG)


### Smoke and carbon monoxide

To seamlessly incorporate commercial smoke and carbon monoxide detectors into the DeafAIDer system, custom boards were developed. These boards adapt the sensors to the system's 12V power supply and convert alarm signals into digital outputs compatible with the central control unit. This ensures that the system can directly power the sensors and correctly interpret their alerts, enabling effective visual warnings for users.

- Altium Designs for Smoke and CO Detector:
    - ![Smoke Detector PCB](imagesAndPhotos/altium/smokeDetector_pcb.JPG)
    - ![Smoke Detector Schematic](imagesAndPhotos/altium/smokeDetector_sch.JPG)
    - ![Smoke Detector Bottom](imagesAndPhotos/altium/smokeDetector_bottom.JPG)
    - ![Smoke Detector Top](imagesAndPhotos/altium/smokeDetector_top.JPG)

### Alarm Clock Module with Vibration Signal

Built on an ATmega8 microcontroller, this module offers multiple input methods including an encoder, proximity sensors, and a capacitive button, with feedback displayed on a quadruple 7-segment display, enhanced by an RGB LED for color-coded alerts. It uniquely controls a vibration pad for waking up, integrating several functional blocks like power supply adaptation, signal processing, and RTC module for timekeeping. Customization ensures direct connection to the central unit via logic level conversion, making it a vital component for the visually and auditorily accessible DeafAIDer system.

- Altium Designs for Alarm Clock:
    - ![Alarm Clock PCB](imagesAndPhotos/altium/alarmClock_pcb.JPG)
    - ![Alarm Clock Schematic](imagesAndPhotos/altium/alarmClock_sch.JPG)
    - ![Alarm Clock Bottom View](imagesAndPhotos/altium/alarmClock_bottom.JPG)
    - ![Alarm Clock Top View](imagesAndPhotos/altium/alarmClock_top.JPG)
    - ![Alarm Clock Screen PCB](imagesAndPhotos/altium/alarmClockScreen_pcb.JPG)
    - ![Alarm Clock Screen Schematic](imagesAndPhotos/altium/alarmClockScreen_sch.JPG)
    - ![Alarm Clock Screen Bottom](imagesAndPhotos/altium/alarmClockScreen_bottom.JPG)
    - ![Alarm Clock Screen Top](imagesAndPhotos/altium/alarmClockScreen_top.JPG)
    - ![Alarm Clock Vibrating Pillow PCB](imagesAndPhotos/altium/alarmClockVibratingPillow_pcb.JPG)
    - ![Alarm Clock Vibrating Pillow Schematic](imagesAndPhotos/altium/alarmClockVibratingPillow_sch.JPG)
    - ![Alarm Clock Vibrating Pillow Bottom](imagesAndPhotos/altium/alarmClockVibratingPillow_bottom.JPG)
    - ![Alarm Clock Vibrating Pillow Top](imagesAndPhotos/altium/alarmClockVibratingPillow_top.JPG)


### Doorbell Module

The doorbell module features an encapsulated momentary button with LED indicators, interfacing with an acoustic signaler within the distribution board. It comprises a power supply block for system integration, a button control with debouncing circuitry, and an LED lighting section that alternates between blue for standby and red when activated, ensuring efficient power use and clear visual feedback.

- Altium Designs for Doorbell:
    - ![Doorbell PCB](imagesAndPhotos/altium/doorbell_pcb.JPG)
    - ![Doorbell Schematic](imagesAndPhotos/altium/doorbell_sch.JPG)
    - ![Doorbell Bottom View](imagesAndPhotos/altium/doorbell_bottom.JPG)
    - ![Doorbell Top View](imagesAndPhotos/altium/doorbell_top.JPG)

## Hardware - mechanical

All these custom-designed enclosures, detailed in Autodesk Inventor 2014 and realized through 3D printing, were efficiently accommodated within a presentation case. This meticulous organization not only ensured the portability of the DeafAIDer® system's components like the alarm clock module, kitchen timer, and various sensors but also highlighted the system's modular design and the practical application of 3D printing in creating tailored electronics enclosures for a cohesive and professional demonstration setup.

![Inventor](imagesAndPhotos/inventor.png)

![3D Printing](imagesAndPhotos/3d_printing.JPG)

## Software

The DeafAIDer system's software is developed across two main platforms. 

The PLC components are programmed using Logo Soft Comfort, a user-friendly software tailored for configuring Siemens LOGO! PLCs, enabling intuitive logic creation for the system's core functionalities. 

For the ATmega microcontroller modules, including the alarm clock and kitchen timer, the Eclipse IDE is utilized alongside the C programming language, offering a robust environment for developing and debugging the microcontroller's firmware.


## System enchancement and debugging

The development journey of the DeafAIDer® system involved iterative programming, thorough testing, and subsequent enhancements to ensure reliability and efficiency. Initial coding in Siemens Soft Comfort and Eclipse IDE for PLC and ATmega microcontroller modules laid the foundation. Debugging was integral, with a notable instance being a minor yet crucial bug fix in the alarm clock's code, illustrating the importance of exhaustive testing. Enhancements focused on optimizing user interaction and expanding functionalities, like improving gesture sensor performance under varying light conditions. Future directions include broadening the system's module range, integrating with commercial automation networks for increased versatility, and enhancing user interface components for more intuitive control. Implementing a unified communication protocol across modules could streamline system scalability and maintenance, marking a significant step towards a more sophisticated and user-friendly system.



## Conclusions and Future Work

The DeafAIDer® system performs exceptionally well, meeting all design specifications with stable and efficient operation. A minor bug discovered in the alarm clock module during extensive testing was promptly fixed, showcasing the system's overall reliability and the effectiveness of thorough testing procedures. The system provides a comprehensive solution at a reasonable cost, with all devices functioning correctly under typical home conditions.

However, some limitations were identified, such as the gesture sensor's reduced effectiveness under intense lighting, suggesting potential improvements in sensor technology or methodology. Future enhancements could include adding more modules, like gas sensors or flame detectors, and expanding compatibility with commercial building automation systems, particularly KNX networks. This would necessitate additional hardware and software modifications but could significantly increase the system's versatility and application scope.

Integrating a LOGO! TDE display module for convenient monitoring and control directly from the distribution board or a central location in the home would enhance user interaction and accessibility. Ensuring a stable and constant internet connection, possibly through a wired network setup, would improve remote accessibility and control, vital for system management outside the home environment. Implementing a UPS power supply for the LOGO! controller could safeguard against power outages, maintaining system functionality and security.

Considering system expansion, transitioning from digital voltage outputs in modules to a unified data bus system could streamline installation and facilitate scalability. Incorporating microcontrollers in individual sensors for direct communication with the central unit could reduce wiring complexity and improve system adaptability for extensive installations.

Overall, the DeafAIDer® system's success opens avenues for further development, aiming for greater integration, user-friendliness, and a wider range of functionalities to better serve the needs of the deaf and hard-of-hearing community.









