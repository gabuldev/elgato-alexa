#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Espalexa.h>
#include <ESP8266mDNS.h> // Biblioteca mDNS

// Wi-Fi settings
const char* wifi_ssid = "YOUR WIFI";
const char* wifi_password = "YOUPASSWORD";

Espalexa espalexa;
EspalexaDevice* elgatoKeylight;

HTTPClient http;
WiFiClient client;

String url;
String keylight_ip;
int led = 2;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  
  // Conectando ao WiFi
  while(!connectWifi()) {
    Serial.println("Retrying in 5 seconds...");
    delay(5000);
  }

  // Iniciando mDNS para resolver o IP da KeyLight
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    return;
  }
  Serial.println("mDNS responder started");

  // Resolvendo o IP da KeyLight via mDNS usando o service string específico
  keylight_ip = resolveKeylightIP();
  if (keylight_ip == "") {
    Serial.println("Não foi possível resolver o IP da KeyLight.");
    return;
  }
  Serial.println("IP da KeyLight: " + keylight_ip);

  // Iniciando Espalexa e definindo a URL para controle da KeyLight
  elgatoKeylight = new EspalexaDevice("Elgato Keylight", keyligtCallback);
  espalexa.addDevice(elgatoKeylight);
  espalexa.begin();
  
  url = "http://" + keylight_ip + ":9123/elgato/lights";
  client.connect(keylight_ip.c_str(), 9123);
}

String resolveKeylightIP() {
  IPAddress ip;
  
  // Buscando dispositivos Elgato via mDNS (_elg._tcp.local)
  int n = MDNS.queryService("_elg", "tcp");  // Envia uma busca mDNS pelo serviço Elgato
  if (n == 0) {
    Serial.println("Nenhum dispositivo Elgato encontrado.");
    return "";
  } else {
    for (int i = 0; i < n; ++i) {
      // Procura por qualquer dispositivo cujo hostname contenha "key-light"
      if (MDNS.hostname(i).indexOf("key-light") >= 0) {
        ip = MDNS.IP(i);
        Serial.print("Hostname encontrado: ");
        Serial.println(MDNS.hostname(i));  // Mostra o hostname
        return ip.toString();
      }
    }
    Serial.println("KeyLight não encontrado.");
    return "";
  }
}

void ledsBlink() {
  digitalWrite(led, HIGH);   
  delay(1000);               
  digitalWrite(led, LOW);    
  delay(1000);             
}

void wifiConnecting() {
  digitalWrite(led, HIGH);   
  delay(500);              
  digitalWrite(led, LOW);    
  delay(500);               
}

void wifiConnected(){
  digitalWrite(led, HIGH);  
}
void wifiOff(){
    digitalWrite(led, LOW); 
}

String command = "";
void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi got disconnected!");
    while(!connectWifi()) {
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
    }
  }

  espalexa.loop();

  if(command != "") {
    if(!http.begin(client, url)) {
      Serial.println("Couldn't connect to Elgato Keylight");
      return;  
    }

    http.addHeader("Content-Type", "application/json");
    Serial.println(url + " - " + http.PUT(command));
    Serial.println("Response: " + http.getString());
    http.end();

    Serial.println(command);
    command = "";
  }
  delay(1);
}

void keyligtCallback(uint8_t brightness) {
  String setting = "";

  String to_add = "";
  if (brightness == 0) {
    to_add = "{\"on\": 0}";
  } else {
    to_add = "{\"on\": 1, \"brightness\":" + String(map(brightness, 0, 255, 0, 100)) + "}";
  }

  setting = to_add;

  command = "{\"lights\":[" + setting + "],\"numberOfLights\":1}";
}

boolean connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  Serial.println("Connecting...");

  for (int i = 0; i < 20; i++) {
    wifiConnecting();
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  }

  Serial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected();
    Serial.print("Connected to ");
    Serial.println(wifi_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    wifiOff();
    Serial.println("Connection failed");
    return false;
  }
}
