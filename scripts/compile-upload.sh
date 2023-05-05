FQBN='esp32:esp32:esp32'
arduino-cli compile --fqbn $FQBN .;
arduino-cli upload -p <REPLACE_WITH_REAL_PORT> --fqbn $FQBN .;
