#include <WiFi.h>
#include <WebServer.h>

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
  WebServer *server = createWebServer(ssidOptions);
  server->begin();
  Serial.println("Server started");

  // Handle clients
  bool ledState = false;
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    server->handleClient();
    if (ledState)
    {
      digitalWrite(LED_PIN, HIGH); // LED on
    }
    else
    {
      digitalWrite(LED_PIN, LOW); // LED on
    }
    ledState = !ledState;
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
