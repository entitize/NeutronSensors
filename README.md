# Project Neutron Sensors

### Send sensor data to the cloud!  

## Features:
* Currently supports both Dallas Temperature Sensors and YL-69 Moisture Sensors
* All sensors connected to one photon device will only publish one event rather than having each sensor making seperate requests.
* Devices will dynamically get configuration updates from online Firebase database which the user can control via an iPhone App.
* Data is logged to:
	* Firebase for dynamic updates on iPhone App
	* Google Sheets for viewing temperature data over a long period of time

