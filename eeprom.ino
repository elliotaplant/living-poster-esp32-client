#include <EEPROM.h>

void eepromSetup()
{
  EEPROM.begin(512); // Initializing EEPROM with 512 bytes
}

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