//Name: getThingWorx
//Author: David Velasquez, Juan Gonzalo Quiroz, Daniel Lopez, Kevin Gutierrez
//Date: 13/11/2017
//Description: This program gets Thingworx Server variables using REST GET request through ThingworxWiFi101 library

#include <ThingworxWiFi101.h>
#include <Servo.h>

Servo spin, arm1, arm2, arm3, grip; //Servo objects.

int Pspin = A0;  //Potentiometer pin declaration.
int Parm1 = 1;
int Parm2 = 2;
int Parm3 = 3;
int Pgrip = 4;

int Vspin;  //Potentiometer var declaration.
int Varm1;
int Varm2;
int Varm3;
int Vgrip;

String inputJson = "";

//Server Constants
const unsigned long TPOST = 500;  //Time between requests to TWX server (every 1/2 secs)
const unsigned int motorsCount = 5;  //Number of sensor vars to send to TWX server (2)
char* ssid = "ConectatePerra"; //WiFi SSID
char* password = "43453892linuX"; //WiFi Pass
char* host = "iot.dis.eafit.edu.co";  //TWX Host example: myhost.edu.co (without http at beginning)
unsigned int port = 80; //TWX host port


//->TWX Vars

char appKey[] = "0f2f3131-8220-4020-9893-847c08e53f05"; //API Key from TWX
char thingName[] = "Robotic_Arm";  //Thing name from TWX
char serviceName[] = "Robotic_Arm_Cast";  //Thing service name from TWX

char* propertyNames[] = {"Vspin", "Varm1", "Varm2", "Varm3", "Vgrip"};  //Input names vector created on service from TWX (check names on TWX service)

int propertyValues[motorsCount]; //Vector to store sensor vars to be sent to 

//->Timing Vars
unsigned long lastConnectionTime = 0; //Last connection ms time between server requests

//->ThingworxWiFi101 Vars
ThingWorx myThing(host, port, appKey, thingName, serviceName);  //Declare the TWX object with his corresponding properties

//Subroutines & functions
void printWifiStatus() {
  //Print SSID name
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  //Print ipv4 assigned to WiFi101 module
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  //Print signal strength for WiFi101 module
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void WiFiInit() {
  delay(1000);  //Wait 1 sec for module initialization

  //Check if WiFi Shield is connected to Arduino
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    //Infinite loop if shield is not detected
    while (true);
  }

    //Attempt a WiFi connection to desired access point at ssid, password
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, password);
    delay(10000); //Wait 10 secs for establishing connection
  }
  //Print WiFi status
  printWifiStatus();
}

void makePost(){
  
  propertyValues[0] = Vspin;
  propertyValues[1] = Varm1;
  propertyValues[2] = Varm2;
  propertyValues[3] = Varm3;
  propertyValues[4] = Vgrip;
  
  myThing.post(motorsCount, propertyNames, propertyValues);
}

void assingValues(){
  DynamicJsonBuffer jsonBuffer;
  inputJson = myThing.getjson(); //Get all properties from server platform
  
  JsonObject& root = jsonBuffer.parseObject(inputJson);
    
  Vspin = root["rows"][0][writeNames[0]];
  Varm1 = root["rows"][0][writeNames[1]];
  Varm2 = root["rows"][0][writeNames[2]];
  Varm3 = root["rows"][0][writeNames[3]];
  Vgrip = root["rows"][0][writeNames[4]];
}

void setup() {

  spin.attach(16); //D0
  arm1.attach(5);  //D1
  arm2.attach(4);  //D2
  arm3.attach(0);  //D3
  grip.attach(2);  //D4

  delay(100);
  spin.write(90);
  delay(100);
  arm1.write(90);
  delay(100);
  arm2.write(90);
  delay(100);
  arm3.write(90);
  delay(100);
  grip.write(70);
  delay(100);

  Vspin = analogRead(Pspin);
  Varm1 = analogRead(Parm1);
  Varm2 = analogRead(Parm2);
  Varm3 = analogRead(Parm3);
  Vgrip = analogRead(Pgrip);

    //Communications
  Serial.begin(9600); //Serial communications with computer at 9600 bauds for debug purposes
  WiFiInit(); //WiFi communications initialization
  
}

void loop() {

  
      val = analogRead(pot);
      val = map(val,0,1023,0,180);
      grip.write(val);
      //delay(1000);

        //Send Post.
  if (millis() - lastConnectionTime > TPOST) {  //Send request to server every TPOST seconds
    makePost(); //Send values to server platform
    lastConnectionTime = millis();  //Refresh last connection time
  }

    //Recive 
  if (millis() - lastConnectionTime > TPOST) {  //Send request to server every TPOST seconds
    assingValues();
    lastConnectionTime = millis();  //Refresh last connection time   
  }
}
