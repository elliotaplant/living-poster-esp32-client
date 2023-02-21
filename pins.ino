void pinsSetup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED off
}

void blink()
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_PIN, HIGH); // LED on
    delay(200);
    digitalWrite(LED_PIN, LOW); // LED off
    delay(200);
  }
}