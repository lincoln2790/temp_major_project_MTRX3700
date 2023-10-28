/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will create a new access point (with no password).
  It will then launch a new server and print out the IP address
  to the Serial Monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 13.

  If the IP address of your board is yourAddress:
    http://yourAddress/H turns the LED on
    http://yourAddress/L turns it off

  created 25 Nov 2012
  by Tom Igoe
  adapted to WiFi AP by Adafruit
 */

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key index number (needed only for WEP)

int led =  LED_BUILTIN;

// int tx =  1;
// int rx = 2;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  pinMode(led, OUTPUT);      // set the LED pin mode
  digitalWrite(led, HIGH);
  //Initialize serial and wait for port to open:
  // delay(5000);

  // delay(10000);
  Serial.begin(9600);
  Serial1.begin(9600);
  //Serial1.begin(9600);
  delay(4000);
  // while (!Serial ) {
  //   // Serial.end();
  //   // Serial.begin(9600);
  //   // delay(5000);
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }
  digitalWrite(led, LOW);
  // //Serial1.println("Access Point Web Server");


  // pinMode(tx, OUTPUT);      // set the RX pin mode
  // pinMode(rx, INPUT);      // set the TX pin mode
  
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    //Serial1.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    //Serial1.println("Please upgrade the firmware");
  }
  
  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));

  // print the network name (SSID);
  //Serial1.print("Creating access point named: ");
  //Serial1.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    //Serial1.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  // printWiFiStatus();
}


void loop() {
  // compare the previous status to the current status
  // Serial1.print('A');
  // Serial.print('A');
  // Serial.print('\n');
  // delay(1000);
  // Serial1.print('B');
  // Serial.print('B');
  // delay(100);
  // while (Serial1.available() > 0) {
  //   int SW_val = Serial1.read();          
  //   Serial.print(SW_val);
  // }
  // delay(1000);
  // Serial.print('\n');
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      //Serial1.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      //Serial1.println("Device disconnected from AP");
    }
  }
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    //Serial1.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      delayMicroseconds(10);                // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial1.write(c);                    // print it out to the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            // client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            // client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

            client.print("Click <a href=\"/B1\">here</a> to search for bird sample stored in template slot 1.<br>");
            // client.println();
            client.print("Click <a href=\"/B2\">here</a> to search for bird sample stored in template slot 2.<br>");
            // client.println();
            client.print("Click <a href=\"/B3\">here</a> to search for bird sample stored in template slot 3.<br>");
            // client.println();
            client.print("Click <a href=\"/B4\">here</a> to search for bird sample stored in template slot 4.<br>");
            // client.println();
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        // if (currentLine.endsWith("GET /H")) {
        //   digitalWrite(led, HIGH);               // GET /H turns the LED on
        //   digitalWrite(tx, HIGH);               // GET /H turns the LED on
        // }
        // if (currentLine.endsWith("GET /L")) {
        //   digitalWrite(led, LOW);  
        //   digitalWrite(tx, LOW);                // GET /L turns the LED off
        // }
        if (currentLine.endsWith("GET /B1")) {
          Serial.print('1');
          Serial.print('\n');
          Serial1.print('1');
          // Serial1.print('\n');
          // delay(1000);
          
        }
        else if (currentLine.endsWith("GET /B2")) {
          Serial.print('2');
          Serial.print('\n');
          Serial1.print('2');
          // Serial1.print('\n');
          // delay(1000);
        }
        else if (currentLine.endsWith("GET /B3")) {
          Serial.print('3');
          Serial.print('\n');
          Serial1.print('3');
          // Serial1.print('\n');
          // delay(1000);
        }
        else if (currentLine.endsWith("GET /B4")) {
          Serial.print('4');
          Serial.print('\n');
          Serial1.print('4');
          // Serial1.print('\n');
          // delay(1000);
        }

      }
    }
    // close the connection:
    client.stop();
    //Serial1.println("client disconnected");
    // printf("%c", digitalRead(tx));
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}
