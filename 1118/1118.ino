#include <LWiFi.h>
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)

#define fsr_pin 14
#define NOTE_C5  523
#define NOTE_C6  1047

DHT dht(DHTPIN, DHTTYPE);

int melody1[] = { NOTE_C5 };
int melody2[] = { NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6};
int duration = 1000;  // 500 miliseconds

char ssid[] = "Ninenight999";      // your network SSID (name)
char pass[] = "nine99nin";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


void loop() {
  // listen for incoming clients
  int fsr_value = analogRead(fsr_pin);
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
        // send a standard http response header
          if (fsr_value <= 500) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");  // the connection will be closed after completion of the response
              client.println("Refresh: 5");  // refresh the page automatically every 5 sec
              Serial.print(fsr_value);
              client.println();
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              // output the value of each analog input pin
              client.print("<p><font size='10'> HAPPY DAY ^_^");
              client.println("</font></p>");
              client.println("</html>");
          }
          else if (fsr_value > 500 && fsr_value <= 2000) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");  // the connection will be closed after completion of the response
              client.println("Refresh: 5");  // refresh the page automatically every 5 sec
              Serial.print(fsr_value);
              client.println();
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              // output the value of each analog input pin
              client.print("<p><font size='10'> I need some help~ ");
              client.println("</font></p>");
              client.println("<p> Pressure value:");
              client.print(fsr_value);
              client.println("</p>");
              client.println("</html>");
          }
          else if (fsr_value > 2150 && fsr_value <= 3400) {
              for (int thisNote = 0; thisNote < 1; thisNote++) {
              // 在 pin8 上輸出聲音&#65292;每個音階響 0.5 秒
              tone(8, melody1[thisNote], duration);
              }
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");  // the connection will be closed after completion of the response
              client.println("Refresh: 5");  // refresh the page automatically every 5 sec
              Serial.print(fsr_value);
              client.println();
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              // output the value of each analog input pin
              client.print("<p><b><font size='10'><font color='purple'> OH NO! COME HERE! ");
              client.println("</font></font></b></p>");
              client.println("<p> Pressure value:");
              client.print(fsr_value);
              client.println("</p>");
              client.println("</html>");
          }
          else {
              for (int thisNote = 0; thisNote < 4; thisNote++) {
              // 在 pin8 上輸出聲音&#65292;每個音階響 0.5 秒
              tone(8, melody2[thisNote], duration);
              }
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");  // the connection will be closed after completion of the response
              client.println("Refresh: 5");  // refresh the page automatically every 5 sec
              Serial.print(fsr_value);
              client.println();
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              // output the value of each analog input pin
              client.print("<p><b><font size='10'><font color='red'> GOD!!! WARNING!!!!");
              client.println("</font></font></b></p>");
              client.print("<p><b><font size='10'><font color='red'> GOD!!! WARNING!!!!");
              client.println("</font></font></b></p>");
              client.print("<p><b><font size='10'><font color='red'> GOD!!! WARNING!!!!");
              client.println("</font></font></b></p>");
              client.println("<p> Pressure value:");
              client.print(fsr_value);
              client.println("</p>");
              client.println("</html>");
          }
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
