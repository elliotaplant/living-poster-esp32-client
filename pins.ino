void pinsSetup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED off
}

void blink(bool success)
{
  if (success) {
    for (int i = 0; i < 5; i++) 
    {
      digitalWrite(LED_PIN, HIGH); // LED on
      delay(200);
      digitalWrite(LED_PIN, LOW); // LED off
      delay(200);
    }
  } else {
    digitalWrite(LED_PIN, HIGH); // LED on
    delay(2000);
    digitalWrite(LED_PIN, LOW); // LED off
  }
}