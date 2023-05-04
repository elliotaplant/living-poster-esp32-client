void pinsSetup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BATTERY_VOLTAGE_PIN, INPUT);
  digitalWrite(LED_PIN, LOW); // LED off
}

void blink()
{
  digitalWrite(LED_PIN, HIGH); // LED on
  delay(2000);
  digitalWrite(LED_PIN, LOW); // LED off
}