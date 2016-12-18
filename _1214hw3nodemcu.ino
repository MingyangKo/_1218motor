//mcu
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>


const char* ssid = "yang";
const char* password = "00000000";

ESP8266WebServer server(80);

//int Motar1=;

char led_status[25];
String webSite;

void buildWeb() {
  webSite += "<html>";
  webSite+="<head>\n";
  webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>Form Control Motar</title>\n";
  webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
  webSite+="<script>";
  webSite+="$(document).ready(function(){";
  webSite+="$(\"[type = range]\").change(function(){";

  webSite+="var motarval = $(\"#motar\").val();";
  webSite+="$(\"#motar-text\").text(motarval);";
  webSite+="});";
  webSite+="});";
  webSite+="</script>";
  webSite+="</head>\n";
  
  webSite += "<body>";
  webSite += "<h1>Motar Control form</h1>";
  webSite += "<form action=\"/form1\">";
  webSite += "<p>Angle : <span id = \"motar-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"motar\" name=\"Motar\" min=\"0\" max=\"179\" value=\"0\" ><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</body></html>";
   
}

void handleRoot() {
  server.send ( 200, "text/html", webSite ); //send back client a HTML file
}

void ColorPicker(){
  int mot = server.arg("Motar").toInt();
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(mot);  // sends one byte
  Wire.endTransmission();    // stop transmitting
  
  //analogWrite(Motar1,mot);

  server.send(200,"text/html",webSite);
}

void handleNotFound() {
  server.send ( 404, "text/html", "404 Error!" );  
}


void setup(void){
  buildWeb();

  //pinMode(Motar1, OUTPUT);
  //digitalWrite(Motar1, 0);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());



  server.on("/", handleRoot);
  server.on("/form1",ColorPicker);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  Wire.begin(4,5);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

