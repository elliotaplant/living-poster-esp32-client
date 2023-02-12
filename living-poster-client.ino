#include <EEPROM.h>

struct Credentials
{
  String ssid;
  String password;
};

void setup()
{
  // Setup baud rate, pins
  Serial.begin(115200); // Initialize Serial monitor with baud rate
  EEPROM.begin(512);    // Initializing EEPROM with 512 bytes
}

void loop()
{
  // No looping here, just a single pass through
  // Wake up
  // Read WiFi credentials
  wifiSetup();
  // Connect to wifi or make a server to get wifi credentials
  wifiConnectLoop();
  // query conditions
  requestURL("example.com");

  // interpret conditions to dial angle
  // change the dial angles
  // find the number of ms until next switch (maybe get time from response?)
  // Hibernate that many ms
  hibernate();
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
    delay(100);
    server.handleClient();
  }
  delay(1000); // why?
}

String getSsidOptions()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Scanning available WiFi networks");
  int n = WiFi.scanNetworks();
  Serial.println("Found " + n + " networks");

  String ssidOptions = "";
  for (int i = 0; i < n; ++i)
  {
    String ssid = WiFI.SSID(i);
    ssidOptions += "<option>" + ssid + "</option>";
  }
  return ssidOptions;
}

// Server --------------------------------------------------------------------
// Server to gather WiFi credentials
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

WebServer server(80);

void createWebServer(String ssidOptions)
{
  server.on("/", []()
            {
    String ipStr = ipToString(WiFi.softAPIP());
    String content = "<!DOCTYPE html>"
"<html lang='en'>"
"  <head>"
"    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"    <title>Living Poster WiFi Setup</title>"
"    <style>"
"      body {"
"    font - family : -apple - system, 'Roboto', 'Droid Sans', sans - serif;"
"    -webkit - font - smoothing : antialiased;"
"    -moz - osx - font - smoothing : grayscale;"
"    text - align : center;"
"      }"
"      h1 {"
"    font - size : 4em; }"
"      label {"
"  display:"
"    block;"
"    font - size : 1.5em; }"
"      select, input, button {"
"    margin - top : 0.1em;"
"    font - size : 1.5em; }"
"      .form-section {"
"    margin - bottom : 2em; }"
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
"      }"
"      h1 { font-size: 4em; }"
"      label { display: block; font-size: 1.5em; }"
"      select, input, button { margin-top: 0.1em; font-size: 1.5em; }"
"      .form-section { margin-bottom: 2em; }"
"    </style>"
"  </head>"
"  <body>"
"    <h1>WiFi Setup</h1>"
"    <h3>Replace this with SSID?</h3>"
"    <p>"
"      Your device will now reboot and should be connected to the WiFi in about 1 minute."
"      <br>"
"      If it does not succeed, you can connect to this site again to reset the network and password."
"      <br>"
"      You can close this page and connect back to your regular WiFi network."
"    </p>"
"  </ body>"
"</ html>";

    ESP.restart(); // Really?
    server.send(201, "text/html", content); });
}

String ipToString(IPAddress ipAddress)
{
  return String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
}

String getSsidOptions()
{
  String ssidOptions = "";
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Scanning available WiFi networks");
  int n = WiFi.scanNetworks();
  Serial.print("Found ");
  Serial.print(n);
  Serial.print(" networks");

  for (int i = 0; i < n; ++i)
  {
    String ssid = WiFI.SSID(i);
    ssidOptions += "<option>" + ssid + "</option>";
  }
  return ssidOptions;
}

// EEPROM ----------------------------------------------------
Credentials readCredentials()
{
  Serial.println("Reading EEPROM SSID");
  String ssid = readEEPROM(0, 32);
  Serial.println("SSID:");
  Serial.println(ssid);

  Serial.println("Reading EEPROM password");
  String password = readEEPROM(32, 96);
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
  writeEEPROM(32, credentials.password);
  EEPROM.commit();
}

String readEEPROM(int start, int end)
{
  String content = "";
  for (int i = start; i < end; i++)
  {
    content += char(EEPROM.read(i));
  }
  return content
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
  for (int i = start; i < start + content.length(); ++i)
  {
    EEPROM.write(i, content[i]);
  }
}