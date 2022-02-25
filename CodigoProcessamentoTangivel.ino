#include <TangibleProcessTag.h>

#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

#include <Arduino.h>

#include <map>
#include <vector>

#define READERS 4 // Numero de READERS da matriz de Leitura

String multiarray[100][4];
String column;

ProcessTag Project;

int currentRow = 1;
int count = 0;

void processMatrix(String matrix[][4])
{
  int totalRows = currentRow;
  int a[totalRows][READERS];

  Serial.println("Início do processamento");
  Serial.println("Matriz para ser processada:");
  for (int i = 0; i < currentRow; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      Serial.print(i);
      Serial.print(",");
      Serial.print(j);
      Serial.print(":");
      Serial.println(multiarray[i][j]);
      
      String aux = multiarray[i][j];
      aux.remove(aux.length() - 2);
      a[i][j] = aux.toInt();
    }
  }
  Serial.println("Espere 4 segundos");
  delay(4000);
  Serial.println("Execução do Código:");

  Project.runCode(a, 1, totalRows);
}

PN532_SPI pn532spi(SPI, 32);
NfcAdapter nfc = NfcAdapter(pn532spi);

void setup(void)
{
  Project.setupLCD();

  Serial.begin(9600);
  Serial.println("* Verificação Modulos PN532 NFC RFID *");
  nfc.begin();
}

void loop(void)
{
  column = "";

  delay(400);

  Serial.println("\nScan row of NFC tags\n");

  if (nfc.tagPresent(200))
  {
    NfcTag tag = nfc.read();
    //tagA.print();

    if (tag.hasNdefMessage())
    {
      NdefMessage message = tag.getNdefMessage();
      NdefRecord record = message.getRecord(0);

      int payloadLength = record.getPayloadLength();
      byte payload[payloadLength];
      record.getPayload(payload);

      String payloadAsString = "";
      for (int c = 0; c < payloadLength; c++)
      {
        payloadAsString += String((char)payload[c]);
      }
      Serial.println(payloadAsString);
      column = payloadAsString;
    }
  }
  delay(200);
  
  if (column != "")
  {
    // Se o primeiro termo da currentRow analisado for diferente do primeiro termo da proxima currentRow analisada
    if (column == "00100")
    {
      count = 0;
      currentRow++;
      delay(100);
      Serial.println("Row scanned!");
      // Se for a tag de FIM, finaliza o programa
    }
    else
    { // Se ainda estiver lendo a mesma currentRow, capture a column B e C.
      multiarray[currentRow][count] = column;
      count++;
    }
    if (column == "99900")
    {
      Serial.println("Scanning finished! Compiling tangible code!");
      processMatrix(multiarray);
      currentRow = 1;
    }
  }

  delay(1000);
}
