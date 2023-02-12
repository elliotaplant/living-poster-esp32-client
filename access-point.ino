
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
