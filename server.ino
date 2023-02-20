#include <WebServer.h>

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
