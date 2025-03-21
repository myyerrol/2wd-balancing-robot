#include "driver_wifi.hpp"

const char *g_wifi_ssid = "Yuyang的iPhone";
const char *g_wifi_pass = "193728465";

NetworkServer g_wifi_server(80);

void initWIFI() {
    Serial.print("[wifi] connecting to ");
    Serial.println(g_wifi_ssid);

    WiFi.begin(g_wifi_ssid, g_wifi_pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    Serial.println("");
    Serial.print("[wifi] connected\n");
    Serial.print("[wifi] ip address: ");
    Serial.print(WiFi.localIP());

    g_wifi_server.begin();
}

typedef struct MainStruct {
    float pid[3];
    float imu[3];
} MainStruct;

void sendDataToWIFI(NetworkClient *p_client, MainStruct *p_main) {
    p_client->println("HTTP/1.1 200 OK");
    p_client->println("Content-type:text/html");
    p_client->println();

    p_client->print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
    p_client->print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

    p_client->print("P: ");
    p_client->print(p_main->pid[0]);
    p_client->print("I: ");
    p_client->print(p_main->pid[1]);
    p_client->print("D: ");
    p_client->print(p_main->pid[2]);

    p_client->println();
}

void recvDataFrWIFI(NetworkClient *p_client) {

}

void testWIFI() {
    NetworkClient t_wifi_client = g_wifi_server.accept();

    if (t_wifi_client) {
        Serial.println("[wifi] create client");
        String t_wifi_recv_data = "";
        while (t_wifi_client.connected()) {
            if (t_wifi_client.available()) {
                char c = t_wifi_client.read();
                // Serial.write(c);
                if (c == '\n') {
                    if (t_wifi_recv_data.length() == 0) {
                        t_wifi_client.println("HTTP/1.1 200 OK");
                        t_wifi_client.println("Content-type:text/html");
                        t_wifi_client.println();

                        t_wifi_client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
                        t_wifi_client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

                        t_wifi_client.println();
                        break;
                    }
                    else {
                        t_wifi_recv_data = "";
                    }
                }
                else if (c != '\r') {
                    t_wifi_recv_data += c;
                }
            }
        }
        t_wifi_client.stop();
        Serial.println("[wifi] close client");
    }
}
