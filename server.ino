#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RECEIVED_SIGNAL_PIN D0
#define SERVER_READY_PIN D1

const char *ssid = "";
const char *password = "";

ESP8266WebServer server(80);

void setup() {
  // initialize serial communication
  Serial.begin(115200);

  // define pin as output
  pinMode(RECEIVED_SIGNAL_PIN, OUTPUT);
  pinMode(SERVER_READY_PIN, OUTPUT);
  digitalWrite(SERVER_READY_PIN, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/signal", handleSignalFromApp);

  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(SERVER_READY_PIN, LOW);
}

void handleRoot() {
  server.send(200, "text/plain", "Hello world!");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleSignalFromApp() {
  server.send(200, "text/plain", "done");
  
  // Turn on the LED
  digitalWrite(RECEIVED_SIGNAL_PIN, HIGH);
  Serial.println("LED turned on");
  delay(1000); // Wait for 1 second

  // Turn off the LED
  digitalWrite(RECEIVED_SIGNAL_PIN, LOW);
  Serial.println("LED turned off");
  delay(1000); // Wait for 1 second
}

void loop() {
  // Handle client requests
  server.handleClient();
}
