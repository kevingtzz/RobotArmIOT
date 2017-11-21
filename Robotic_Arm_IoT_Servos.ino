#include <ArduinoJson.h>
#include <Servo.h>
#include <ThingworxWiFi101.h>



//Name: getThingWorx
//Author: David Velasquez, Juan Gonzalo Quiroz, Daniel Lopez, Kevin Gutierrez
//Date: 13/11/2017
//Description: This program gets Thingworx Server variables using REST GET request through ThingworxWiFi101 library

//Libraries
//#include <ThingworxWiFi101.h>


//Server Constants
const unsigned long TPOST = 1000;  //Time between requests to TWX server (every 1/2 secs)
const unsigned int motorsCount = 5;  //Number of sensor vars to send to TWX server (2)
char* ssid = "HUAWEI_ALE-L23_7331"; //WiFi SSID
char* password = "c6cdb13d"; //WiFi Pass
char* host = "iot.dis.eafit.edu.co";  //TWX Host example: myhost.edu.co (without http at beginning)
unsigned int port = 80; //TWX host port
  
int initial = 50;
//Potenciometro var declaration

float A_Pot_Base, A_Pot_Brazo, A_Pot_Codo , A_Pot_Muneca ,
      A_Pot_Pinza , A_status;

String testing = "";

String inputJson = "";


//Pin declaration.
int spinP = 0;  
int arm1P = 1;
int arm2P = 2;
int arm3P = 3;
int gripP = 5;
int conexionLocal = 6;
bool internet = false;

//Servo objects.
Servo spin, arm1, arm2, arm3, grip;
 
//->TWX Vars

char appKey[] = "0f2f3131-8220-4020-9893-847c08e53f05"; //API Key from TWX
char thingName[] = "Robotic_Arm_V2";  //Thing name from TWX
char serviceName[] = "Robotic_Cast";  //Thing service name from TWX

char* propertyNames[] = {"Pot_Base", "Pot_Brazo", "Pot_Codo", "Pot_Muneca",
                          "Pot_Pinza"};  //Input names vector created on service from TWX (check names on TWX service)                         
float propertyValues[motorsCount]; //Vector to store sensor vars to be sent to TWX

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

  propertyValues[0] = A_Pot_Base;
  propertyValues[1] = A_Pot_Brazo;
  propertyValues[2] = A_Pot_Codo;
  propertyValues[3] = A_Pot_Muneca;
  propertyValues[4] = A_Pot_Pinza;

  
  myThing.post(motorsCount, propertyNames, propertyValues);
}

void assingValues(){
  DynamicJsonBuffer jsonBuffer;
  inputJson = myThing.getjson(); //Get all properties from server platform
  
  JsonObject& root = jsonBuffer.parseObject(inputJson);
  A_Pot_Base   = root["rows"][0][propertyNames[0]];
  A_Pot_Brazo  = root["rows"][0][propertyNames[1]];
  A_Pot_Codo     = root["rows"][0][propertyNames[2]];
  A_Pot_Muneca   = root["rows"][0][propertyNames[3]];
  A_Pot_Pinza     = root["rows"][0][propertyNames[4]];
  
  Serial.println(A_Pot_Base);
  
}


void readStatus(){
  
  DynamicJsonBuffer jsonBuffer;
  
  inputJson = myThing.getjson("status"); //Get all properties from server platform
  JsonObject& root = jsonBuffer.parseObject(inputJson);
  A_status = root["rows"][0]["status"] ;
  Serial.println("***************");
  Serial.println(A_status);
  Serial.println("***************");
  
  }
void assingValuesUnitary(){
  DynamicJsonBuffer jsonBuffer;
  
  inputJson = myThing.getjson(propertyNames[0]); //Get all properties from server platform
  JsonObject& root = jsonBuffer.parseObject(inputJson);
  A_Pot_Base   = root["rows"][0][propertyNames[0]];

  inputJson = myThing.getjson(propertyNames[1]); //Get all properties from server platform
  JsonObject& root2 = jsonBuffer.parseObject(inputJson);
  A_Pot_Brazo  = root2["rows"][0][propertyNames[1]];

  inputJson = myThing.getjson(propertyNames[2]); //Get all properties from server platform
  JsonObject& root3 = jsonBuffer.parseObject(inputJson);
  A_Pot_Codo     = root3["rows"][0][propertyNames[2]];
  
  inputJson = myThing.getjson(propertyNames[3]); //Get all properties from server platform
  JsonObject& root4 = jsonBuffer.parseObject(inputJson);
  A_Pot_Muneca   = root4["rows"][0][propertyNames[3]];
  
  
  inputJson = myThing.getjson(propertyNames[4]); //Get all properties from server platform
  JsonObject& root5 = jsonBuffer.parseObject(inputJson);
  A_Pot_Pinza     = root5["rows"][0][propertyNames[4]];

  Serial.println("*****************");
  Serial.println(A_Pot_Base);
  Serial.println(A_Pot_Brazo);
  Serial.println(A_Pot_Codo);
  Serial.println(A_Pot_Muneca);
  Serial.println(A_Pot_Pinza);
  Serial.println("*****************");
  
  }


void writeServos(){


    spin.write(A_Pot_Base);
    Serial.println(A_Pot_Base);
    delay(1000);
    Serial.println("TERMINE DE MOVER BASE");

    arm1.write(A_Pot_Brazo);
    delay(1000);
    Serial.println("TERMINE DE MOVER BRAZO1");

    arm2.write(A_Pot_Codo);
    delay(1000);
    Serial.println("TERMINE DE MOVER BRAZO2");
   
    arm3.write(A_Pot_Muneca);
    delay(1000);
    Serial.println("TERMINE DE MOVER BRAZO3");

    grip.write(A_Pot_Pinza);
    delay(1000);
    Serial.println("TERMINE DE MOVER PINZA");
  
}

void writeServosLog(){

    long base = 0;
    long brazo1 = 0;
    long brazo2 = 0;
    long brazo3 = 0;
    long pinza = 0;
    
    delay(1);
    base = map(A_Pot_Base,0,1023,0,180);
    //Serial.println(base);
    spin.write(base);
    Serial.println(base);
    //delay(1000);
    Serial.println("TERMINE DE MOVER BASE");
    
    //Serial.println("spin: " + spinV);

    delay(1);
    brazo1 = map(A_Pot_Brazo,0,1023,0,180);
    arm1.write(brazo1);
    //delay(5000);
    Serial.println("TERMINE DE MOVER BRAZO1");
    //Serial.println("arm1: " + arm1V);

    delay(1);
    brazo2 = map(A_Pot_Codo,0,1023,0,180);
    arm2.write(brazo2);
    //delay(5000);
    Serial.println("TERMINE DE MOVER BRAZO2");
    //Serial.println("arm2: " + arm2V);

    delay(1);
    brazo3 = map(A_Pot_Muneca,0,1023,0,180);
    arm3.write(brazo3);
    //delay(5000);
    Serial.println("TERMINE DE MOVER BRAZO3");
    //Serial.println("arm3: " + arm3V);
    
    delay(1);
    pinza = map(A_Pot_Pinza,0,1023,25,75);
    grip.write(pinza);
    //delay(5000);
    Serial.println("TERMINE DE MOVER PINZA");
  
}
void setup() {

  //Physical outputs initialization
  spin.attach(5);   //D0
  arm1.attach(4);   //D1
  arm2.attach(3);  //D2
  arm3.attach(2);   //D3
  grip.attach(1); //D4
  digitalWrite(conexionLocal, LOW);
  //grip.write(25);
  //Communications
  
  Serial.begin(9600); //Serial communications with computer at 9600 bauds for debug purposes
  WiFiInit(); //WiFi communications initialization
}


void loop() {
  
  
  if(digitalRead(conexionLocal) == HIGH) internet = true;
  else internet = false;
  
  if(internet){
    readStatus();

    if(A_status == 0){
    A_Pot_Base = analogRead(spinP);     
    A_Pot_Brazo = analogRead(arm1P);
    A_Pot_Codo = analogRead(arm2P);    
    A_Pot_Muneca = analogRead(arm3P);
    A_Pot_Pinza = analogRead(gripP);
    writeServosLog();
  }else{
    if (millis() - lastConnectionTime > TPOST) {  //Send request to server every TPOST seconds
      assingValuesUnitary(); 
      writeServos();
      lastConnectionTime = millis();  //Refresh last connection time
    }
  }
  //Send Post.
  if (millis() - lastConnectionTime > TPOST && internet == HIGH) {  //Send request to server every TPOST seconds
    makePost(); //Send values to server platform
    lastConnectionTime = millis();  //Refresh last connection time
  }
}else{
  
    A_Pot_Base = analogRead(spinP);     
    A_Pot_Brazo = analogRead(arm1P);
    A_Pot_Codo = analogRead(arm2P);    
    A_Pot_Muneca = analogRead(arm3P);
    A_Pot_Pinza = analogRead(gripP);
    writeServosLog();
  }
  
  

}
