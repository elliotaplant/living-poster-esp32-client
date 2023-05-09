FQBN='esp32:esp32:esp32'
echo 'Compiling';
arduino-cli compile --fqbn $FQBN .;
echo 'Uploading';
arduino-cli upload -p /dev/cu.usbserial-D30DOR0H --fqbn $FQBN .;
