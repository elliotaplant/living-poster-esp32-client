// Hibernate ---------------------------------------------------

void hibernateUntilNextCycle(uint64_t serverTimeMs)
{
  uint64_t msLeftInCycle = CYCLE_TIME_MS - (serverTimeMs % CYCLE_TIME_MS);

  // If <20% of the cycle time is left, skip this cycle and go to the next one
  float fractionRemaining = (float)msLeftInCycle / (float)CYCLE_TIME_MS;
  if (fractionRemaining < 0.2)
  {
    msLeftInCycle += CYCLE_TIME_MS;
  }

  uint64_t usLeftInCycle = msLeftInCycle * 1000;

  Serial.printf("Total time: %dms\n", millis());
  Serial.printf("Hibernating for %d seconds\n", msLeftInCycle / 1000);
  hibernateMs(msLeftInCycle);
}

void hibernateMs(uint64_t millisToSleep)
{
  uint64_t microsToSleep = millisToSleep * 1000;
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF);
  esp_sleep_enable_timer_wakeup(microsToSleep);
  esp_deep_sleep_start();
}
