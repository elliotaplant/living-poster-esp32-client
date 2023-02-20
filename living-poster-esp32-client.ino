#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <EEPROM.h>

WebServer server(80);
const int BUTTON_PIN = 15;
const int LED_PIN = 5;

struct Credentials
{
  String ssid;
  String password;
};

// Establishing Local server at port 80
int NUM_WIFI_ACCESS_POINT_ATTEMPTS = 10;
int EEPROM_SSID_SPACE = 32;

void setup()
{
  // Setup baud rate, pins
  Serial.begin(115200); // Initialize Serial monitor with baud rate
  EEPROM.begin(512);    // Initializing EEPROM with 512 bytes
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED off
}

// No looping here, just a single pass through
void loop()
{
  // Read WiFi credentials
  Credentials credentials = readCredentials();

  // Connect to wifi or make a server to get wifi credentials
  wifiConnectLoop(credentials);

  // Query conditions
  requestURL("living-poster.elliotaplant9602.workers.dev");

  // Interpret conditions to dial angle
  // Change the dial angles
  moveServos();

  // Find the number of ms until next switch (maybe get time from response?)
  // Hibernate that many ms
  hibernate();
}

// WiFi ----------------------------------------------------------

// Uses credentials to connect to WiFi or creates a server to get those credentials
void wifiConnectLoop(Credentials credentials)
{
  for (int i = 0; i < NUM_WIFI_ACCESS_POINT_ATTEMPTS; i++)
  {
    // Attempt to connect to wifi
    connectWifi(credentials);

    // If successful, exit
    if (testWifi())
      return;

    // If unsuccessful, create the configuration server
    setupAccessPoint();
  }
}

void connectWifi(Credentials credentials)
{
  WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
}

bool testWifi()
{
  Serial.print("Testing WiFi connection ");
  for (int i = 0; i < 30; i++)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi connection successful");
      return true;
    }
    delay(1000);
    Serial.print("*");
  }
  Serial.println();
  Serial.println("Failed to connect to WiFi");
  return false;
}

// Access point --------------------------------------------------

void setupAccessPoint()
{
  String ssidOptions = getSsidOptions();

  delay(100);
  Serial.println("Creating access point for WiFi credential modification");
  WiFi.softAP("Living Poster WiFi Setup", "");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");

  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());

  // Start the server
  createWebServer(ssidOptions);
  server.begin();
  Serial.println("Server started");

  // Handle clients
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    server.handleClient();
    delay(200);
  }
  delay(1000);
}

String getSsidOptions()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Scanning available WiFi networks");
  int n = WiFi.scanNetworks();
  Serial.print("Found ");
  Serial.print(n);
  Serial.println(" networks");

  String ssidOptions = "";
  for (int i = 0; i < n; ++i)
  {
    String ssid = WiFi.SSID(i);
    ssidOptions += "<option>" + ssid + "</option>";
  }
  return ssidOptions;
}

// Server --------------------------------------------------------------------
// Server to gather WiFi credentials

void createWebServer(String ssidOptions)
{
  // this is a capture?
  server.on("/", [ssidOptions]()
            {
    String content = "<!DOCTYPE html>"
                     "<html lang='en'>"
                     "  <head>"
                     "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                     "    <title>Living Poster WiFi Setup</title>"
                     "    <style>"
                     "      body {"
                     "        font-family: -apple-system, 'Roboto', 'Droid Sans', sans-serif;"
                     "        -webkit-font-smoothing: antialiased;"
                     "        -moz-osx-font-smoothing: grayscale;"
                     "        text-align: center;"
                     "        max-width: 800px;"
                     "        margin: 0 auto;"
                     "      }"
                     "      h1 { font-size: 4em; }"
                     "      label { display: block; font-size: 1.5em; }"
                     "      select, input, button { margin-top: 0.1em; font-size: 1.5em; padding: 0.25em 0.5em; width: 100%; max-width: 200px }"
                     "      .form-section { margin-bottom: 2em; }"
                     "    </style>"
                     "  </head>"
                     "  <body>"
                     "    <h1>WiFi Setup</h1>"
                     "    <form action='/save-credentials' method='POST'>"
                     "      <div class='form-section'>"
                     "        <label for='ssid'>Select your WiFi network</label>"
                     "        <select id='ssid' name='ssid' required>" +
                     ssidOptions +
                     "        </select>"
                     "      </div>"
                     "      <div class='form-section'>"
                     "        <label for='password'>Enter WiFi Password</label>"
                     "        <input id='password' name='password' placeholder='p@ssW0rd' required />"
                     "      </div>"
                     "      <button id='submit' type='submit'>Submit</button>"
                     "    </ form>"
                     "  </ body>"
                     "</ html>";

    server.send(200, "text/html", content); });

  server.on("/save-credentials", []()
            {
    Credentials credentials = {server.arg("ssid"), server.arg("password")};
    writeCredentials(credentials);

    String content = "<!DOCTYPE html>"
                     "<html lang='en'>"
                     "  <head>"
                     "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                     "    <title>Living Poster WiFi Setup</title>"
                     "    <style>"
                     "      body {"
                     "        font-family: -apple-system, 'Roboto', 'Droid Sans', sans-serif;"
                     "        -webkit-font-smoothing: antialiased;"
                     "        -moz-osx-font-smoothing: grayscale;"
                     "        text-align: center;"
                     "        max-width: 800px;"
                     "        margin: 0 auto;"
                     "      }"
                     "      h1 { font-size: 4em; }"
                     "      label { display: block; font-size: 1.5em; }"
                     "      select, input, button { margin-top: 0.1em; font-size: 1.5em; padding: 0.25em 0.5em; width: 100%; max-width: 200px }"
                     "      .form-section { margin-bottom: 2em; }"
                     "    </style>"
                     "  </head>"
                     "  <body>"
                     "    <h1>WiFi Setup</h1>"
                     "    <p>"
                     "      Your device will now reboot and should be connected to the WiFi in about 1 minute."
                     "    </p>"
                     "    <p>"
                     "      If it does not succeed, you can connect to this site again to reset the network and password."
                     "    </p>"
                     "    </p>"
                     "    <p>"
                     "      You can close this page and connect back to your regular WiFi network."
                     "    </p>"
                     "  </ body>"
                     "</ html>";

    server.send(201, "text/html", content);
    delay(1000);
    ESP.restart(); });
}

String ipToString(IPAddress ipAddress)
{
  return String(ipAddress[0]) + '.' +
         String(ipAddress[1]) + '.' +
         String(ipAddress[2]) + '.' +
         String(ipAddress[3]);
}

// EEPROM ----------------------------------------------------
Credentials readCredentials()
{
  Serial.println("Reading EEPROM SSID");
  String ssid = readEEPROM(0, EEPROM_SSID_SPACE);
  Serial.println("SSID:");
  Serial.println(ssid);

  Serial.println("Reading EEPROM password");
  String password = readEEPROM(EEPROM_SSID_SPACE, 96);
  Serial.println("PASSWORD:");
  Serial.println(password);
  Credentials credentials = {ssid, password};
  return credentials;
}

void writeCredentials(Credentials credentials)
{

  clearEEPROM(96);

  Serial.println("Writing SSID");
  Serial.println(credentials.ssid);
  writeEEPROM(0, credentials.ssid);

  Serial.println("Writing Password");
  Serial.println(credentials.password);
  writeEEPROM(EEPROM_SSID_SPACE, credentials.password);

  EEPROM.commit();
}

String readEEPROM(int start, int end)
{
  String content = "";
  for (int i = start; i < end; i++)
  {
    content += char(EEPROM.read(i));
  }
  return content;
}

void clearEEPROM(int length)
{
  Serial.println("Clearing EEPROM");
  for (int i = 0; i < length; ++i)
  {
    EEPROM.write(i, 0);
  }
}

void writeEEPROM(int start, String content)
{
  for (int i = 0; i < content.length(); i++)
  {
    EEPROM.write(i + start, content[i]);
  }
}

// Hibernate ---------------------------------------------------
const uint32_t SLEEP_DURATION = 4 * 1000000; // µs

void hibernate()
{
  Serial.print("Hibernating for ");
  Serial.print(SLEEP_DURATION);
  Serial.println(" us");
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF);

  esp_sleep_enable_timer_wakeup(SLEEP_DURATION);
  esp_deep_sleep_start();
}

// Request -------------------------------------------------
void requestURL(const char *host)
{
  Serial.println("Connecting to domain: " + String(host));

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, 443)) // Using port 443 for https
  {
    Serial.println("connection failed");
    return;
  }

  Serial.println("Connected!");

  // Why does this need to have the (String) prefix?
  String request = (String) "GET / HTTP/1.1\r\n" +
                   "Host: " + String(host) + "\r\n" +
                   "Connection: close\r\n\r\n";

  // This will send the request to the server
  client.print(request);

  unsigned long timeout = millis();
  while (client.available() == 0) // should this be 'false'?
  {
    // if we don't get a response in 5s, timeout
    if (millis() - timeout > 5000)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_PIN, 1);
    delay(100);
    digitalWrite(LED_PIN, 0);
    delay(100);
  }

  Serial.println("Closing connection");
  client.stop();
}

// Servos -----------------------------------------------
void moveServos()
{
  Serial.println("Moving servos (or I would be, if I had them)");
}