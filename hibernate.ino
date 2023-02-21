// Hibernate ---------------------------------------------------
// const int HOUR_IN_MS = 60 * 60 * 1000; // ms
const int HOUR_IN_MS = 60 * 1000; // fake 10s hour

void hibernateUntilNextHour(uint64_t serverTimeMs)
{
  uint64_t msLeftInHour = HOUR_IN_MS - (serverTimeMs % HOUR_IN_MS);
  uint64_t usLeftInHour = msLeftInHour * 1000;

  Serial.printf("Hibernating for %d seconds\n", msLeftInHour / 1000);
  hibernateMs(msLeftInHour);
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
