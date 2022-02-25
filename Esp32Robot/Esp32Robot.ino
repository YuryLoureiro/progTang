#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define FRENTE 45
#define TRAS 65

// Valores aleatórios para as portas onde ligaremos os motores das rodas, só modificar na hora que montarmos o robô, já coloquei o sentido de giro de cada variável
int S_A = 30;  //speed motor a
int M_A1 = 26; //motor a = +
int M_A2 = 25; //motor a = -
int M_B1 = 33; //motor b = -
int M_B2 = 32; //motor b = +
int S_B = 30;  //speed motor b

BluetoothSerial SerialBT;

void robot_frente() 
{
  Serial.println("Frente\n");
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW); 
}

void robot_tras() 
{
  Serial.println("Tras\n");
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, HIGH); 
}

void robot_parar() 
{
  Serial.println("Tras\n");
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW); 
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Robot"); //Nome do dispositivo
  Serial.println("O dispositivo foi iniciado!");
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    int action = SerialBT.parseInt();
    switch (action)
    {
      case FRENTE:
        robot_frente();
        delay(200);
        robot_parar();
        break;
    
      case TRAS:
        robot_tras();
        delay(200);
        robot_parar();
        break;

      default:
        break;
    }
  }
  delay(20);
}
