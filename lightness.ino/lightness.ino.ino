
#include <aREST.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>

aREST rest = aREST();

const char* ssid = "wifi";
const char* password = "hunter2";

#define LISTEN_PORT           80

IRsend irsend(4);
WiFiServer server(LISTEN_PORT);

int increaseBrightness(String unused);
int decreaseBrightness(String unused);
int white(String unused);
int blue(String unused);
int on(String unused);
int off(String unused);
int user(String code);

void setup(void)
{
  Serial.begin(115200);
  irsend.begin();
  rest.function("increase", increaseBrightness);
  rest.function("decrease", decreaseBrightness);
  rest.function("white", white);
  rest.function("blue", blue);
  rest.function("on", on);
  rest.function("off", off);
  rest.function("user", user);

  rest.set_id("1");
  rest.set_name("esp8266");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

int increaseBrightness(String unused) {
  irsend.sendNEC(0xF700FF, 32);
  return 1;
}

int decreaseBrightness(String unused) {
  irsend.sendNEC(0xF7807F, 32);
  return 1;
}

int white(String unused) {
  irsend.sendNEC(0xF7E01F, 32);
  return 1;
}

int blue(String unused) {
  irsend.sendNEC(0xF7609F, 32);
  return 1;
}

int on(String unused) {
  irsend.sendNEC(0xF7C03F, 32);
  return 1;
}

int off(String unused) {
  irsend.sendNEC(0xF740BF, 32);
  return 1;
}

int user(String code) {
  irsend.sendNEC(0xFF3AC5, 32);
  return 1;
}

