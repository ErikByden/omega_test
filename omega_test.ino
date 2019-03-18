#include <SoftwareSerial.h>
#include "WiFiEsp.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>

  const char serverJson[] = "api.openweathermap.org";
const String email = "eri_byd@hotmail.com";
const String xid = "dicegame24";
String data = "P1,4,2,1";
const String hostname = "primat.se";
String countryCode = "se";
const String APIKey = "0c6c77820236b1a47e8ac996c35c21c8";
//const String uri = "/services/data/" + email + "-" + xid + ".csv";
const String senduri = "/services/sendform.aspx?xdata=" + email + "|" + xid;
const int port = 80;
String line;
// Create module object on GPIO pin

// wifi 6 (RX) and 7 (TX)
SoftwareSerial mySerial1(10, 11);

// Declare and initialise global arrays for WiFi settings
const char ssid[] =  "AndroidAP"; //"Telia5GHz-2C424D";
const char pass[] = "nevc6096"; //"internet" ;


  WiFiEspClient clientJson;
int testVar = 0;
int switchNumber=0;
char ALLDATA[100];
int x  =0;
int i = 0;
String change;

// Declare and initialise variable for radio status
int status = WL_IDLE_STATUS;
WiFiEspServer server(80);
RingBuffer buf(8);
WiFiEspClient client;
void setup()
{
    // Initialize serial for debugging
    Serial.begin(115200);
    // Initialize serial
   mySerial1.begin(9600);
    wifiInit();
}

void loop()
{
    //jSon();
    //delay(1000); 
    //printWifiStatus();
   // delay(5000);
client = server.available();
if(client) {
buf.init(); 
    Serial.println(F("New client"));
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       // Serial.write(c);
        buf.push(c);

        //for(int i=0;i>6;i++)
        if(i<6)
        {
          
         
           Serial.print(c);
                     

          if(i==5 ) //c!='H' && c!='f' && c!='a' && c!=' '
          {
            
                                    Serial.print("näst innersta loopen");
                                               Serial.print(c);

            if(c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7')
            {
              change = c;
              switchNumber = change.toInt();
                        Serial.print("innersta loopen");
                       Serial.print(c);
              Serial.print(switchNumber);
               }
          

            }
          }
          i++;

          


          
      
         


        if (c == '\n' && currentLineIsBlank) 
        {
          Serial.println(F("Sending response"));
          i=0;
                  Serial.println(switchNumber);

          // Send a standard HTTP response header
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n");

String html ="<!DOCTYPE html> <html> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel= \"stylesheet\" href=\"https://zztorp.github.io/WeatherDataHtmlCss/main.css\"> </head> <body> <h1 align=\"center\">Mathilda & Eriks IoT-Projekt</h1> <h1 align=\"center\">Weather Data</h1> <div class=\"row\"> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Stockholm.jpg\"  style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/2'\"> Stockholm</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Tokyo.jpg\" style=\"width:100%\" alt=\"centered image\"/> <button class=\"btn\" onclick=\"window.location.href='/1'\">Tokyo</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Paris.jpg\" alt=\"Paris\" style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/5'\">Paris</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Amsterdam.jpg\" alt=\"Amsterdam\" style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/3'\">Amsterdam</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/London.jpg\" alt=\"London\" style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/6'\">London</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Barcelona.jpg\" alt=\"Barcelona\" style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/4'\">Barcelona</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/SanFrancisco.jpg\" alt=\"SanFrancisco\" style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/7'\">San Francisco</button> </div> </div> </body> </html>";
client.print(html);
            
         
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }

      }
    }
    delay(3000);
        Serial.println(switchNumber);

    client.stop();

    Serial.println(F("Client disconnected"));
        Serial.println(switchNumber);

   if(!switchNumber == 0){jSon();}
  }
  

}


void jSon()
{

client.flush();
client.stop();
clientJson.flush();
clientJson.stop();
  String city;
 

switch(switchNumber)
{
  case 1:
  city = "tokyo";
  break;
  case 2:
  city = "Stockholm";
  break;
  case 3:
  city = "Amsterdam";
  break;
  case 4:
  city = "Barcelona";
  break;
  case 5:
  city = "Paris";
  break;
  case 6:
  city = "London";
  break;
  case 7:
  city =  "Dubai";// "SanFrancisco";
  break;
 
  }

  String uri = "/data/2.5/weather?q=" + city + "&APPID=" + APIKey;//"/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + APIKey;
delay(1000);
   // Serial.println();
   // Serial.println(F("Reading from server..."));
    // if you get a connection, report back via serial
    if (clientJson.connect(serverJson, port))
    {
        Serial.println(F("Connected to server"));
        // Make a HTTP request
        clientJson.println("GET " + uri + " HTTP/1.1");
        clientJson.println("Host: " + hostname);
        clientJson.println("Connection: close");
        clientJson.println();
    }

    /* if there are incoming bytes available
     * from the server, read them and print them */
    while (clientJson.available() == 0)
    {
        delay(5);
        Serial.print(F("newhurrdirr"));
    }

      
Serial.print(F("sistatest"));
   char endOfHeaders[] = "\r\n\r\n";
   if (!clientJson.find(endOfHeaders)) {
   Serial.println(F("Invalid response"));
    Serial.print(F("innan buff"));

   return;
  }
 
Serial.print(F("innan parce"));


 // const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2)
//+ JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12)+ 368;
//const size_t bufferSize = 500;
//DynamicJsonBuffer jsonBuffer(bufferSize);

      

      
StaticJsonBuffer <2000> jsonBuffer;

JsonObject& root = jsonBuffer.parseObject(clientJson);
Serial.print(F("efter parce"));

if(!root.success()) {
  Serial.println(F("parseObject() failed"));
}

JsonObject& weather_0 = root["weather"][0];

//double longitude = root ["weather"][0];
const char* weather = weather_0 ["main"];
const char* CITY = root["name"];
//Serial.print(longitude);
Serial.print(weather);
Serial.print(CITY);


delay(3000);
  switchNumber = 0;
  clientJson.stop();
  }

  
void wifiInit()
{
    // Initialize ESP module
    WiFi.init(&mySerial1);
    // Check for the presence of the shield
    if (WiFi.status() == WL_NO_SHIELD)
    {
        Serial.println(F("WiFi shield not present"));
        // Don't continue
        while (true)
        {
        
        }       
    }

    // Attempt to connect to WiFi network
    while (status != WL_CONNECTED)
    {
        Serial.print(F("Attempting to connect to SSID: "));
        Serial.println(ssid);
        // Connect to WPA/WPA2 network
        status = WiFi.begin(ssid, pass);
    }

    server.begin();
    IPAddress ip = WiFi.localIP();
    Serial.print(F("IP Address: "));
    Serial.println(ip);

    Serial.println(F("You're connected to the network"));
    printWifiStatus();
    Serial.println();

}





void printWifiStatus()
{
    // print the SSID of the network you're attached to
    Serial.print(F("SSID: "));
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address
    //IPAddress ip = WiFi.localIP();
    //Serial.print("IP Address: ");
    //Serial.println(ip);

    // print the received signal strength
    long rssi = WiFi.RSSI();
    Serial.print(F("Signal strength (RSSI):"));
    Serial.print(rssi);
    Serial.println(F(" dBm"));

}
