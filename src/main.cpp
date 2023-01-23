
///////////////////// vibrador /////////////////
int vb=34; // pin digital
int Avb=4; // pin analogico
int Dig_out = 0; //variable
int Ana_out = 0; // variable

int B = 1;
///////////////////// RFID //////////////////
// LISTA DE REPRODUCCION - ESP32 - ESP8266
// https://www.youtube.com/playlist?list=PLZHVfZzF2DYID9jGK8EpcMni-U2CSTrw3

// LISTA DE REPRODCUION DEL CURSO DE ARDUINO DESDE CERO
// https://www.youtube.com/playlist?list=PLZHVfZzF2DYJeLXXxz6YtpBj4u7FoGPWN
/* ESP 32 NODE MCU
  Vcc <-> 3V3 (o Vin(5V) según la versión del módulo)
  RST (Reset) <-> D22
  GND (Masse) <-> GND
  MISO (Master Input Slave Output) <-> 19
  MOSI (Master Output Slave Input) <-> 23
  SCK (Serial Clock) <-> 18
  SS/SDA (Slave select) <-> 5
*/
/* ESP 8266 NODE MCU
  Vcc <-> 3V3 (o Vin(5V) según la versión del módulo)
  RST (Reset) <-> D0
  GND (Tierra) <-> GND
  MISO (Master Input Slave Output) <-> D6
  MOSI (Master Output Slave Input) <-> D7
  SCK (Serial Clock) <-> D5
  SS/SDA (Slave select) <-> D8
*/

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#if defined(ESP32)
  #define SS_PIN 5
  #define RST_PIN 22
#elif defined(ESP8266)
  #define SS_PIN D8
  #define RST_PIN D0
#endif

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
// Init array that will store new NUID
byte nuidPICC[4];

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
String DatoHex;
/*const String UserReg_1 = "F9049E2E";
const String UserReg_2 = "B33786A3";
const String UserReg_3 = "7762C83B";*/

String UserReg[] = {"F9049E2E", "B33786A3", "7762C83B"};
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
String printHex(byte *buffer, byte bufferSize)
{  
   String DatoHexAux = "";
   for (byte i = 0; i < bufferSize; i++) 
   {
       if (buffer[i] < 0x10)
       {
        DatoHexAux = DatoHexAux + "0";
        DatoHexAux = DatoHexAux + String(buffer[i], HEX);  
       }
       else { DatoHexAux = DatoHexAux + String(buffer[i], HEX); }
   }
   
   for (int i = 0; i < DatoHexAux.length(); i++) {DatoHexAux[i] = toupper(DatoHexAux[i]);}
   return DatoHexAux;
}

int verifivarRfid( String UserRegisters[], String Dato){
  int a = 2;
  for (int i = 0; i < sizeof(UserRegisters) ; i++)
  {
    Serial.println(sizeof(UserRegisters));
    Serial.println(UserReg[i]);
    if(UserReg[i] == DatoHex)
    {
      String S1 = "USUARIO "+String(i)+" - PUEDE INGRESAR"; 
      Serial.println(S1);
      return a = 1;    
    }else{
      String S2 = "NO ESTA REGISTRADO - PROHIBIDO EL INGRESO"; 
      Serial.println(S2);
      return a = 0;  
    }
  }
  return a;
}

int LeerVibracion(int vb, int Avb){
  Dig_out = digitalRead(vb);
  Ana_out = analogRead(Avb);
  Serial.print("Anaolog : ");
  int AnaV = Ana_out;//(Ana_out- 4095)*-1;
  Serial.println(AnaV);
  int AnaV1 = (Ana_out- 4095)*-1;
  Serial.println(AnaV1);
  Serial.print("          Digital :");
  Serial.println(Dig_out);
  return AnaV1;
}

int led=2; // pin Led de verificacion
void setup() 
{

  ///////////////////// rfid/////////////////
   Serial.begin(9600);
   SPI.begin(); // Init SPI bus
   rfid.PCD_Init(); // Init MFRC522
   Serial.println();
   Serial.print(F("Reader :"));
   rfid.PCD_DumpVersionToSerial();
   for (byte i = 0; i < 6; i++) {
     key.keyByte[i] = 0xFF;
   } 
   DatoHex = printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
   Serial.println();
   Serial.println();
   Serial.println("Iniciando el Programa");

   ///////////////////// vibrador/////////////////
  pinMode(vb, INPUT);
  pinMode(Avb, INPUT);
  pinMode(led,OUTPUT);
  
}

void loop() 
{
  ///////////////////// vibrador/////////////////
  /*Dig_out = digitalRead(vb);
  Ana_out = analogRead(Avb);
  Serial.print("Anaolog : ");
  int AnaV = Ana_out;//(Ana_out- 4095)*-1;
  Serial.println(AnaV);
  int AnaV1 = (Ana_out- 4095)*-1;
  Serial.println(AnaV1);
  Serial.print("          Digital :");
  Serial.println(Dig_out);*/
  
  int vibracion = LeerVibracion(vb, Avb);
  if (vibracion > 1000 and B==1){
    digitalWrite(led,HIGH);
    B = 0;
    delay(500);
  }else if (vibracion > 1000 and B==0){
    digitalWrite(led,LOW);
    B = 1;
    delay(500);
  }
  
  delay(100);

  /////////////////// rfid /////////////////
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
     if ( ! rfid.PICC_IsNewCardPresent()){return;}
     
     // Verify if the NUID has been readed
     if ( ! rfid.PICC_ReadCardSerial()){return;}
     
     Serial.print(F("PICC type: "));
     MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
     Serial.println(rfid.PICC_GetTypeName(piccType));
     // Check is the PICC of Classic MIFARE type
     if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
     {
       Serial.println("Su Tarjeta no es del tipo MIFARE Classic.");
       return;
     }
     
     if (rfid.uid.uidByte[0] != nuidPICC[0] || rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[2] != nuidPICC[2] || rfid.uid.uidByte[3] != nuidPICC[3] )
     {
       Serial.println("Se ha detectado una nueva tarjeta.");
       
       // Store NUID into nuidPICC array
       for (byte i = 0; i < 4; i++) {nuidPICC[i] = rfid.uid.uidByte[i];}
    
       DatoHex = printHex(rfid.uid.uidByte, rfid.uid.size);
       Serial.print("Codigo Tarjeta: "); Serial.println(DatoHex);

      int Resultado = verifivarRfid(UserReg, DatoHex);
      Serial.println(Resultado);
      ///
       /*if(UserReg_1 == DatoHex)
       {
        Serial.println("USUARIO 1 - PUEDE INGRESAR");     
       }
       else if(UserReg_2 == DatoHex)
       {
        Serial.println("USUARIO 2 - PUEDE INGRESAR");
       }
       else if(UserReg_3 == DatoHex)
       {
        Serial.println("USUARIO 3 - PUEDE INGRESAR");
       }
       else
       {
        Serial.println("NO ESTA REGISTRADO - PROHIBIDO EL INGRESO");
       }  
       Serial.println();*/
       ///
     }
     else 
     {
      Serial.println("Tarjeta leida previamente");
      int Resultado = verifivarRfid(UserReg, DatoHex);
      Serial.println(Resultado);
     }
     // Halt PICC
     rfid.PICC_HaltA();
     // Stop encryption on PCD
     rfid.PCD_StopCrypto1();
    delay(1000);
}