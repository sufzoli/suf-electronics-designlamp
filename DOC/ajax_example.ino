#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 pressure;
double baseline; // baseline pressure

WiFiServer server(80);
WiFiClient client;
String HTTP_req;

void setup() {
      Serial.begin(115200);
    WiFi.begin("your-SSID", "your-WiFi-Password"); 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

if (pressure.begin())
       {
       }
       else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }
   baseline = getPressure();
}

void loop() {
    WiFiClient client = server.available();
    if (client) { 
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) { 
                char c = client.read();
                HTTP_req += c;
                if (c == '\n' && currentLineIsBlank) {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: keep-alive");
                    client.println();
                    if (HTTP_req.indexOf("ajax_switch") > -1) {
                        getTemperature(client);
                    } else {
                        client.println("<!DOCTYPE html>");
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<title>ESP BMP180 web display</title>");
                        client.println("<script>");
                        client.println("function getTemperature() {");
                        client.println("nocache = \"&nocache=\"+ Math.random() * 1000000;");
                        client.println("var request = new XMLHttpRequest();");
                        client.println("request.onreadystatechange = function() {");
                        client.println("if (this.readyState == 4) {");
                        client.println("if (this.status == 200) {");
                        client.println("if (this.responseText != null) {");
                        client.println("document.getElementById(\"switch_txt\").innerHTML = this.responseText;");
                        client.println("}}}}");
                        client.println("request.open(\"GET\", \"ajax_switch\" + nocache, true);");
                        client.println("request.send(null);");
                        client.println("setTimeout('getTemperature()', 1000);");
                        client.println("}");
                        client.println("</script>");
                        client.println("</head>");
                        client.println("<body onload=\"getTemperature()\">");
                        client.println("<h1>ESP8266 BMP180 web server</h1>");
                        client.println("<font color=\"#6a5acd\"><body bgcolor=\"#a0dFfe\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\n</div>\n<div style=\"clear:both;\"></div><p>");                                               
                        client.println("<p id=\"switch_txt\">BMPSTATUS/p>");
                        client.println("<p>Example Display of BMP data</p>");
                        client.println("<p><a href=\"http://www.esp8266.com\">ESP8266 Support Forum</a></p>");
                        client.println("</body>");
                        client.println("</html>");
                    }
                //    Serial.print(HTTP_req);
                    HTTP_req = "";
                    break;
                }
            }
        }
        delay(1);
        client.stop();
    }
}
double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

void getTemperature(WiFiClient cl) {
    char status;
    double T,a,P;
    P = getPressure();
    a = pressure.altitude(P,baseline);
    pressure.getTemperature(T);
      status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.
  }
    status = pressure.getTemperature(T);  
    cl.print("Temperature: ");
    cl.print(T);
    cl.print(" C");
    cl.print("<BR>Absolute Pressure: ");
    cl.print(P,2);
    cl.print(" mb");
    cl.print("   -  ");
    cl.print(P*0.0295333727,2);
    cl.print(" inHg");    
    cl.print("<BR>Relative Altitude: ");
    cl.print(a,0);
    cl.print(" meters above Start Position ( ");
    cl.print(a*3.28084,0);
    cl.print(" Feet for OLD Git's)");    
}

 
   
