#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ChainableLED.h>
#include <Wifi.h>

//*************** Coneción a ThinkSpeak *********
#include <ThingSpeak.h>

/////////// Información del Canal y Campos de ThingSpeak //////////////////
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 2014575;
char* readAPIKey = (char*)"MCVF18UY83B6ODE9"; //"70GGTLNT0EMFP0WO";
char* writeAPIKey = (char*)"CE9J7FJ9UB7CANQH"; //"7ZBZ9LU15LQRYKRF";
const unsigned long postingInterval = 20L * 1000L;
const unsigned long postingIntAlarma = 20L * 3250L;
unsigned int dataFieldOne = 1;                       
unsigned int dataFieldTwo = 2;                       
unsigned int dataFieldThree = 3;                     
unsigned int dataFieldFour = 4; 
// ************ Pines RFID **************+
#if defined(ESP32)
  #define SS_PIN 5
  #define RST_PIN 22
#elif defined(ESP8266)
  #define SS_PIN D8
  #define RST_PIN D0
#endif

///////////////////// Informacion RFID //////////////////
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

////////////// Variables globales RFID /////////////////////

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
// Init array that will store new NUID
byte nuidPICC[4];

String DatoHex;

String UserReg[] = {"F9049E2E", "22BE5B4H", "7762C83B"};

int Resultado = 0; //autorizado o no RFID

///////////////////// Variables globales vibrador /////////////////
int vb=12; // pin digital 12
int Avb=32; // pin analogico 32
int rfidon=26; // 26 pin
int rfidoff=13; // 13 pin
int Dig_out = 0; //variable
int Ana_out = 0; // variable
int B = 1; //boleado 1
int Buzer=14; // led verificacion 14
int maxVibra = 0;

/////////////////// Configuracion WIFI ///////////////////
char ssid[] = "FLIA MUCE"; //"EDWARD";//"Bravo";//"Piso 1";//"TP-Link_B520";
char password[] = "4fliamuce2001"; //"EDWARD12";//;//"9003407381"; //"67097135";
WiFiClient client;              //Cliente Wifi para ThingSpeaK

//////////////////************ FUNCIONES ***************/////////////////

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
    if(UserReg[i] == DatoHex)
    {
      String S1 = "USUARIO "+String(i+1)+" - PUEDE INGRESAR"; 
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
  int AnaV = Ana_out;
  int AnaV1 = (Ana_out- 4095)*-1;

  // guardar el dato mayor
  if(AnaV1 > maxVibra){
    maxVibra = AnaV1;
    //AnaV1 = maxVibra;
    //Serial.println("Entro");
  }
  //Serial.println(maxVibra);

  //Serial.print("     Anaolog : ");
  //Serial.print(AnaV1);
  //Serial.print("  -   Digital :");
  //Serial.println(Dig_out);
  return maxVibra;
}

// usa esta funcion siu solo quieres ecribir un solo campo
int writeTSData( long TSChannel, unsigned int TSField, float data ){
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess ){
    //lcd.setCursor(0, 1);
    //lcd.print("Send ThinkSpeak");
    Serial.println( String(data) + " written to Thingspeak." );
    }
    
    return writeSuccess;
}

//Usa esta funcion para escribir multiples campos
int write2TSData( long TSChannel, unsigned int TSField1, 
                  float field1Data,unsigned int TSField2, long field2Data,
                  unsigned int TSField3, long field3Data,
                  unsigned int TSField4, 
                  int field4Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3,  field3Data );
  ThingSpeak.setField( TSField4,  field4Data );

  int printSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  Serial.println("Subio datos");
  maxVibra = 0; // reinicia el maximo de vibracion
  return printSuccess;
}
void setup() 
{
  //Abrir el puerto de lectura en el PC para mensajes
  Serial.begin(115200);

  /////////////////// Conección WIFI /////////////////
  Serial.println("Conectandose a la WIFI!");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.println(WiFi.localIP());
  
  ///////////////////// setup RFID /////////////////
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

   ///////////////////// stupvibrador/////////////////
  pinMode(vb, INPUT);
  pinMode(Avb, INPUT);
  pinMode(rfidon, OUTPUT);
  pinMode(rfidoff, OUTPUT);
  pinMode(Buzer,OUTPUT);

  ///////////////// Conectar Cliente ThinkSpeak /////////////7
  ThingSpeak.begin( client ); 
}

//metodo repetitivo
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;
int vectorAlarma[] = {0,0,0,0,0,0};
int indice = 0;
unsigned long lastUpdateTimeAlarma = 0;
int alarma = 0;
int suma = 0;

void loop() {
  int maxVibraEnviado = LeerVibracion(vb, Avb);
  // Only update if posting time is exceeded
  if (millis() - lastUpdateTime >=  postingInterval) {
    lastUpdateTime = millis();
    

    /////////////////// Leer RFID 
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! rfid.PICC_IsNewCardPresent()){
      Serial.println("no hay ninguna tarjeta nueva presente en el sensor");

      int Resultado = 2;
      //int vibracion = LeerVibracion(vb, Avb);
      int vibracion = maxVibraEnviado;
      Serial.print("     Anaolog : ");
      Serial.println(vibracion);

    // Logica buzer
    if (vibracion > 1000){
      vectorAlarma[indice] = 1;
      indice = indice+1;
    }else{
      vectorAlarma[indice] = 0;
      indice = indice+1;
    }

    if (millis() - lastUpdateTimeAlarma >=  postingIntAlarma) {
      suma = vectorAlarma[0]+vectorAlarma[1]+vectorAlarma[2]+vectorAlarma[3]+vectorAlarma[4];

      if(suma >= 2){
        digitalWrite(Buzer,HIGH);
        alarma = 1;
        Serial.println("Se activo la alarma");
      }

      int vectorAlarma[] = {0,0,0,0,0,0};
      indice = 0;
      lastUpdateTimeAlarma = millis();
    }
    // Fin logica Buzer
      
      // Halt PICC
      rfid.PICC_HaltA();
      // Stop encryption on PCD
      rfid.PCD_StopCrypto1();

      write2TSData( channelID , 
                    dataFieldOne , vibracion, 
                    dataFieldTwo , Resultado,
                    dataFieldThree , millis(),
                    dataFieldFour , alarma);
      
      return;}
    
    // Verify if the NUID has been readed
    if ( ! rfid.PICC_ReadCardSerial()){
      Serial.println("Verificar si se ha leído la NUID");
      return;}
    
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    Serial.println(rfid.PICC_GetTypeName(piccType));
    // Check is the PICC of Classic MIFARE type
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K){
      Serial.println("Su Tarjeta no es del tipo MIFARE Classic.");
      return;
    }
    
    if (rfid.uid.uidByte[0] != nuidPICC[0] || rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[2] != nuidPICC[2] || rfid.uid.uidByte[3] != nuidPICC[3] ){
      Serial.println("Se ha detectado una nueva tarjeta.");
      
      // Store NUID into nuidPICC array
      for (byte i = 0; i < 4; i++) {nuidPICC[i] = rfid.uid.uidByte[i];}

      DatoHex = printHex(rfid.uid.uidByte, rfid.uid.size);
      Serial.print("Codigo Tarjeta: "); Serial.println(DatoHex);

      Resultado = verifivarRfid(UserReg, DatoHex);
      //Serial.println(Resultado);
    
    } else {
      Serial.println("Tarjeta leida previamente");
      Resultado = verifivarRfid(UserReg, DatoHex);
      Serial.println(Resultado);
    }

    if (Resultado == 1){
      if(alarma == 1){
        digitalWrite(Buzer,LOW);
        // Se reinician las variables de la alarma
        alarma = 0;
        int vectorAlarma[] = {0,0,0,0,0,0};
        indice = 0;
        lastUpdateTimeAlarma = millis();
      }
      digitalWrite(rfidon, HIGH);
      delay(1000);
      digitalWrite(rfidon, LOW);
    }else{
      digitalWrite(rfidoff, HIGH);
      delay(1000);
      digitalWrite(rfidoff, LOW);
    }

    //////// Leer sensor de vibracion
    //int vibracion = LeerVibracion(vb, Avb);
    int vibracion = maxVibraEnviado;
    Serial.print("     Anaolog : ");
    Serial.println(vibracion);

    // Logica buzer
    if (vibracion > 1000){
      vectorAlarma[indice] = 1;
      indice = indice+1;
    }else{
      vectorAlarma[indice] = 0;
      indice = indice+1;
    }

    if (millis() - lastUpdateTimeAlarma >=  postingIntAlarma) {
      suma = vectorAlarma[0]+vectorAlarma[1]+vectorAlarma[2]+vectorAlarma[3]+vectorAlarma[4];

      if(suma >= 2){
        digitalWrite(Buzer,HIGH);
        alarma = 1;
        Serial.println("Se activo la alarma");
      }

      int vectorAlarma[] = {0,0,0,0,0,0};
      indice = 0;
      lastUpdateTimeAlarma = millis();
    }
    // Fin logica Buzer

    // Halt PICC
    rfid.PICC_HaltA();
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();

    write2TSData( channelID , 
                  dataFieldOne , vibracion, 
                  dataFieldTwo , Resultado,
                  dataFieldThree , millis(),
                  dataFieldFour , alarma);
  }
}