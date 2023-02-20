#include <WiFi.h>
#include <EEPROM.h>

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
