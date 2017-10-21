# Neutron Sensors Documentation 

* (Novice) Explain how to use this project's libraries in your code
* (Novice) How to use the particle cloud and webhooks to scale your sensors to IoT devices.
* (Intermediate) How to program your own Neutron Sensors
* (Advanced) Full in depth tutorial of how the innerworkings of the code works 

**Tip:** If you just want to get some code working, follow the first part of the paper. 

---

## Part 1: How to use library in your code

```c++

//1
NeutronTemperatureSensor tempSensor = NeutronTemperatureSensor("Best Sensor", D2);

//2
void setup() { 
	Serial.begin(9600);
}


void loop() {

	//3
	String sensorName;
	double sensorReading;
	
	//4	
	sensorReading = tempSensor.readSensor();
	sensorName = tempSensor.getName(); 
	
	//5
	Serial.print(sensorName);
	Serial.print(" is reading ");
	Serial.println(sensorReading);
}

```

1. Declare the temperature sensor, naming it "Best Sensor" and attaching it to pin D2
2. Begin serial monitor to debug output
3. Declare one `String` and one `double`
4. Call functions to get specific values of the sensor device
5. Print out the values captured to the serial monitor 


