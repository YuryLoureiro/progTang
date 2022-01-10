#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Robot"); //Bluetooth device name // <------- set this to be the same as the name you chose above!!!!!
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    int action = SerialBT.parseInt();
    if (action == 45){
      Serial.write("Frente");
    }
    if (action == 65){
      Serial.write("Tras");
    }
  }
  delay(20);
}
