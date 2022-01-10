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
String columnA, columnB, columnC;

ProcessTag Project;

int currentRow = 1;

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
  Serial.println("Execução do Código:");

  Project.runCode(a, 1, totalRows);
}

PN532_SPI pn532spiA(SPI, 9);
NfcAdapter nfcA = NfcAdapter(pn532spiA);

PN532_SPI pn532spiB(SPI, 10);
NfcAdapter nfcB = NfcAdapter(pn532spiB);

PN532_SPI pn532spiC(SPI, 12);
NfcAdapter nfcC = NfcAdapter(pn532spiC);

void setup(void)
{
  Project.setupLCD();

  Serial.begin(9600);
  Serial.println("* Verificação Modulos PN532 NFC RFID *");
  nfcA.begin();
  nfcB.begin();
  nfcC.begin();
}

void loop(void)
{
  columnA = "";
  columnB = "";
  columnC = "";

  delay(400);

  Serial.println("\nScan row of NFC tags\n");

  if (nfcA.tagPresent(200))
  {
    NfcTag tagA = nfcA.read();
    //tagA.print();

    if (tagA.hasNdefMessage())
    {
      NdefMessage messageA = tagA.getNdefMessage();
      NdefRecord recordA = messageA.getRecord(0);

      int payloadLengthA = recordA.getPayloadLength();
      byte payloadA[payloadLengthA];
      recordA.getPayload(payloadA);

      String payloadAsStringA = "";
      for (int c = 0; c < payloadLengthA; c++)
      {
        payloadAsStringA += String((char)payloadA[c]);
      }
      Serial.println(payloadAsStringA);
      columnA = payloadAsStringA;
    }
  }
  delay(200);

  if (nfcB.tagPresent(200))
  {
    NfcTag tagB = nfcB.read();
    //tagB.print();

    if (tagB.hasNdefMessage())
    {
      NdefMessage messageB = tagB.getNdefMessage();
      NdefRecord recordB = messageB.getRecord(0);

      int payloadLengthB = recordB.getPayloadLength();
      byte payloadB[payloadLengthB];
      recordB.getPayload(payloadB);

      String payloadAsStringB = "";
      for (int c = 0; c < payloadLengthB; c++)
      {
        payloadAsStringB += String((char)payloadB[c]);
      }
      Serial.println(payloadAsStringB);
      columnB = payloadAsStringB;
    }
    delay(200);
  }

  if (nfcC.tagPresent(200))
  {
    NfcTag tagC = nfcC.read();
    //tagB.print();
    if (tagC.hasNdefMessage())
    {
      NdefMessage messageC = tagC.getNdefMessage();
      NdefRecord recordC = messageC.getRecord(0);

      int payloadLengthC = recordC.getPayloadLength();
      byte payloadC[payloadLengthC];
      recordC.getPayload(payloadC);

      String payloadAsStringC = "";
      for (int c = 0; c < payloadLengthC; c++)
      {
        payloadAsStringC += String((char)payloadC[c]);
      }
      Serial.println(payloadAsStringC);
      columnC = payloadAsStringC;
    }
    delay(200);
  }

  if (columnA != "")
  {
    multiarray[currentRow][0] = columnA;
    if (columnB != "")
    {
      multiarray[currentRow][1] = columnB;
      if (columnC != "")
      {
        multiarray[currentRow][2] = columnC;
      }
    }

    // Se o primeiro termo da currentRow analisado for diferente do primeiro termo da proxima currentRow analisada
    if (multiarray[currentRow][0] != multiarray[currentRow - 1][0])
    {
      currentRow++;
      delay(100);
      Serial.println("Row scanned!");
      // Se for a tag de FIM, finaliza o programa
      if (columnA == "99900")
      {
        Serial.println("Scanning finished! Compiling tangible code!");
        processMatrix(multiarray);
      }
    }
    else
    { // Se ainda estiver lendo a mesma currentRow, capture a column B e C.
      if (columnB != "")
      {
        multiarray[currentRow - 1][1] = columnB;
      }

      if (columnC != "")
      {
        multiarray[currentRow - 1][2] = columnC;
      }

      Serial.println("New row not detected");
    }
  }

  delay(1000);
}
