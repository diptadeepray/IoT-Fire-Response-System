# IoT-Based Automated Fire Detection and Alert System  

## Overview  
This project automates fire detection and alert systems using IoT technology. It replaces traditional methods of fire reporting, ensuring quick and reliable emergency responses even in the absence of human intervention. The system leverages NodeMCU microcontrollers, environmental sensors, and the MQTT protocol to monitor conditions and trigger alarms in case of abnormalities.  

## Features  
- **Automated Fire Detection**: Monitors temperature and gas levels using DHT11 and gas sensors.  
- **Real-Time Alerts**: Sends location-based notifications to receivers for immediate action.  
- **Scalable MQTT Communication**: Efficient communication using a single MQTT topic for all nodes.  
- **Localized Alarm System**: Receiver nodes trigger buzzers for the corresponding locations.  

## System Architecture  
1. **Source Nodes**:  
   - NodeMCUs (`Source_Beleghata`, `Source_London`) equipped with:  
     - **DHT11 Sensor** for temperature monitoring.  
     - **Gas Sensor** for detecting smoke or hazardous gases.  
   - Publishes location-based messages upon detecting abnormal conditions.  

2. **Receiver Nodes**:  
   - NodeMCUs (`Receiver_Beleghata`, `Receiver_London`) equipped with buzzers.  
   - Subscribes to a shared MQTT topic and triggers the buzzer if the location matches incoming data.  

## Communication Protocol  
- **MQTT Protocol**:  
  - All nodes are connected to the internet for real-time communication.  
  - A shared MQTT topic ensures scalability and simplicity.  

## Demonstration Setup  
1. Nodes:  
   - `Source_Beleghata` (with sensors)  
   - `Receiver_Beleghata` (with buzzer)  
   - `Source_London` (with sensors)  
   - `Receiver_London` (with buzzer)  

2. Workflow:  
   - Source nodes detect abnormal conditions and publish the affected location (`"Beleghata"` or `"London"`) to the MQTT topic.  
   - Receiver nodes subscribe to the topic and trigger an alarm if the message matches their location.  

## Requirements  
- **Hardware**:  
  - 4 NodeMCU boards  
  - DHT11 sensors (2 units)  
  - Gas sensors (2 units)  
  - Buzzers (2 units)  

- **Software**:  
  - Arduino IDE  
  - MQTT broker (e.g., Mosquitto)  
  - Internet connection for NodeMCU devices  

## Installation and Usage  
1. **Hardware Setup**:  
   - Connect sensors to the Source NodeMCUs.  
   - Connect buzzers to the Receiver NodeMCUs.  

2. **Software Configuration**:  
   - Flash the provided code onto the NodeMCU devices using the Arduino IDE.  
   - Set up an MQTT broker and configure the nodes to publish/subscribe to the shared topic.  

3. **Testing**:  
   - Simulate abnormal conditions to test the system.  
   - Verify that alarms are triggered at the appropriate receiver nodes.  

## Future Enhancements  
- Integration with mobile applications for remote monitoring and alerts.  
- Expansion to support additional locations and sensors.  
- Advanced machine learning algorithms for anomaly detection.  
