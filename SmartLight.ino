#include <ESP8266WiFi.h>         
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);   

const char* ssid = "jummamia";
const char* passw = "12345678";

int r,g,b;

void handleGenericArgs() { 
    String message = "R,    G,   B\n";
    message += server.arg(0);
    message += "  ";
    message += server.arg(1);
    message += "  ";
    message += server.arg(2);
    r = server.arg(0).toInt();
    g = server.arg(1).toInt();
    b = server.arg(2).toInt();
    server.send(200, "text/plain", message);          //Response to the HTTP request
}

void setup() {
    Serial.begin(115200);
    
    pinMode(LED_BUILTIN,OUTPUT);
    
    WiFi.begin( ssid , passw ); //Connect to the WiFi network
    
    while (WiFi.status() != WL_CONNECTED) {           //Wait for connection
        delay(500);
        Serial.println("Waiting to connect…");
    }
    
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());                   //Print the local IP to access the server
    
    server.on("/genericArgs", handleGenericArgs);     //Associate the handler function to the path
    
    server.begin();                                   //Start the server
    
    Serial.println("Server listening");  
    
    pinMode(D4,OUTPUT);
    pinMode(D5,OUTPUT); 
    pinMode(D6,OUTPUT); 
     
    delay(5000);
}

void loop() {
    server.handleClient();   

    analogWrite(D4,g);      //analogWrite writes a PWM digital signal instead of an analog signal
    analogWrite(D5,r);
    analogWrite(D6,b);
    
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.println(b);
}
