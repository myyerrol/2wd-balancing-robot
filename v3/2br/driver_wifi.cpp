#include "driver_wifi.hpp"

const char *ssid = "Yuyang的iPhone";
const char *password = "193728465";

NetworkServer server(80);

void initWIFI() {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void testWIFI() {
    NetworkClient client = server.accept();

    if (client) {
        Serial.println("New Client.");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                if (currentLine.length() == 0) {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println();

                    client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
                    client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

                    client.println();
                    break;
                }
                else {
                    currentLine = "";
                }
                }
                else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H")) {
                    Serial.print("H\n");
                }
                if (currentLine.endsWith("GET /L")) {
                    Serial.print("L\n");
                }
            }
        }
        client.stop();
        Serial.println("Client Disconnected.");
    }
}
