//#include <Arduino.h>
//#include <Wire.h>
//
//void K_4LD_init(void); // function prototype
//char* K_4LD_read(void); // function prototype
//
//void K_4LD_init(void); // function prototype
//
//
//const int ledPin =  18;    // Led Rojo
//const int ledPin2 =  19;  // Led Azul CAmbio a pin analogo_a3
//
//int EOC = 3;// corresponde al D3
//xzx
//void setup()
//{
//  // init Led's
//  pinMode(ledPin, OUTPUT);  // rojo
//  pinMode(ledPin2, OUTPUT); // azul 
//  digitalWrite(ledPin,LOW);   
//  digitalWrite(ledPin2,LOW); 
//  //pin available 4LD
//  pinMode(EOC, INPUT);      // sets the digital pin as output
//  /***********************************************************/
//  // Open serial communications and wait for port to open: 
//  Serial.begin(9600); //normal
//  /***********************************************************/
//  //init I2C 
//  K_4LD_init();// i2c init todo lo anterior
//  /***********************************************************/   
//}
//
//
///*************************--inicial loop---*******************************/  
//
//void loop()
//{
//
//while(1){
//         // K_4LD_init();
//          delay(1000);
//          Serial.println(K_4LD_read());
//          digitalWrite(ledPin, !digitalRead(ledPin));
//        }
//   
//}
//
////*******************************************************************************************************************************************////
// /*************************************************************/ 
// void K_4LD_init(void)
//{
//  Wire.begin();
// Wire.beginTransmission(0x40); // transmit to device #208 (0xD0)  //direccion del A/D conver
//  Wire.write(0x80);//HEX
//  Wire.write(0xAC);//HEX             // sends value byte 
//  //if(Wire.endTransmission(true)==0){Serial.print("success");}
//  //delay(8);//8mseg
//  Serial.println(String(Wire.endTransmission(true)));
//}
///***********************************/
//char* K_4LD_read(void)
//{
//  //Variables 
//  unsigned long Pressure=0,Temp=0;
//  unsigned char a,b,c,d,e;
//  int EOC = 7;// corresponde al A0 
//  int cont=0;
//  char box_4LD[40]="";
//  char box_PsrSea[10];
//  char box_TempSea[10];
//  char tab[]="\t";
//  char *pad;
//
//  K_4LD_init();
//  cont=0;
//  Pressure=0;
//  Temp=0;
//  
//  while(digitalRead(EOC)== LOW)
//    {
//    Wire.begin();
//    Wire.beginTransmission(0x40); //FUNCIONANDO
//    Wire.write(172); 
//    Wire.endTransmission(true);
//    digitalWrite(ledPin2, !digitalRead(ledPin2));
//    }
//
//  Wire.beginTransmission(0x40); // transmit to device #208 (0xD0)  //direccion del A/D conver
//  Wire.write(0x81);//HEX
//  Wire.endTransmission(false);
//  Wire.requestFrom(0x40, 5, true);
//  
//  while(Wire.available())    // slave may send less than requested
//     { 
//    a = Wire.read(); // receive a byte as character
//    b = Wire.read(); // receive a byte as character
//    c = Wire.read(); // receive a byte as character
//    d = Wire.read(); // receive a byte as character
//    e = Wire.read(); // receive a byte as character
//     }
//   Wire.endTransmission();
//
//     
//  //Calculo profundidad en Bares
//  Pressure=(Pressure|b)<<8;
//  Pressure=(Pressure|c);
//  unsigned long Psr_aux =(Pressure-16384)*3.0;//en long 32bits
//  float PsrSea=(Psr_aux/32768.0);// en float para coger las decimas
//  dtostrf(PsrSea,7,6,box_PsrSea);
//
//  //Calculo Temperatura
//  Temp=(Temp|d)<<8;
//  Temp=(Temp|e);
//  unsigned long  int Temp_aux=(Temp/16);// en float para coger las decimas
//  float TempSea=((Temp_aux-24)*0.05)-50;
//  dtostrf(TempSea,7,6,box_TempSea);
//  sprintf(box_4LD,box_TempSea);
//  strcat (box_4LD,tab);
//  strcat (box_4LD,box_PsrSea);
//
//
//  pad=&box_4LD[0];
//  return pad;
//}



//
//#define I2C_DEV_ADDR 0x55
//
//uint32_t i = 0;
//
//void onRequest(){
//  Wire.print(i++);
//  Wire.print(" Packets.");
//  Serial.println("onRequest");
//}
//
//void onReceive(int len){
//  Serial.printf("onReceive[%d]: ", len);
//  while(Wire.available()){
//    Serial.write(Wire.read());
//  }
//  Serial.println();
//}
//
//void setup() {
//  Serial.begin(115200);
//  Serial.setDebugOutput(true);
//  Wire.onReceive(onReceive);
//  Wire.onRequest(onRequest);
//  Wire.begin((uint8_t)I2C_DEV_ADDR);
//
//#if CONFIG_IDF_TARGET_ESP32
//  char message[64];
//  snprintf(message, 64, "%u Packets.", i++);
//  Wire.slaveWrite((uint8_t *)message, strlen(message));
//#endif
//}
//
//void loop() {
//
//}

// Lectura adresss
//#include <Wire.h>
// 
//void setup() {
//  Wire.begin();
//  Serial.begin(115200);
//  Serial.println("\nI2C Scanner");
//}
// 
//void loop() {
//  byte error, address;
//  int nDevices;
//  Serial.println("Scanning...");
//  nDevices = 0;
//  for(address = 1; address < 127; address++ ) {
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
//    if (error == 0) {
//      Serial.print("I2C device found at address 0x");
//      if (address<16) {
//        Serial.print("0");
//      }
//      Serial.println(address,HEX);
//      nDevices++;
//    }
//    else if (error==4) {
//      Serial.print("Unknow error at address 0x");
//      if (address<16) {
//        Serial.print("0");
//      }
//      Serial.println(address,HEX);
//    }    
//  }
//  if (nDevices == 0) {
//    Serial.println("No I2C devices found\n");
//  }
//  else {
//    Serial.println("done\n");
//  }
//  delay(5000);          
//}


// Código ultimo funcionando con SD y RTC
#include <Wire.h>
#include <math.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "time.h"
#include <RTClib.h> // incluye libreria para el manejo del modulo RTC

RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

const int Sensor_Address = 0x77; // Dirección I2C del sensor
int EOC = 3;//



// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

String dataMessage;


// Initialize SD card
void initSDCard(){
   if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }
  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

// Write to the SD card
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

// Append data to the SD card
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}



void setup() {
  Wire.begin(); // Iniciar la comunicación I2C
  Serial.begin(115200);
  
   if (! rtc.begin()) {       // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
 while (1);         // bucle infinito que detiene ejecucion del programa
 }
 //rtc.adjust(DateTime(__DATE__, __TIME__)); // funcion que permite establecer fecha y horario


  initSDCard();
   // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.txt");
  if(!file) {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "Epoch Time, Temperature, Pressure \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close(); // arreglar
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
  // Iniciar la comunicación con el sensor Keller PA-4LD 
  Wire.beginTransmission(Sensor_Address);
  Wire.write(0xAC); // Comando para iniciar la lectura de presión
  Wire.endTransmission();

  delay(8); // Esperar el tiempo de conversión (8 ms para modo estándar según hoja de datos)

  Wire.beginTransmission(Sensor_Address);
  Wire.write(0x81);//HEX
  Wire.endTransmission(false);
  Wire.requestFrom(Sensor_Address, 5);

  if (Wire.available() == 5) {
    unsigned int STATUS_BYTE = Wire.read();
    unsigned int P_MSB = Wire.read();
    unsigned int P_MLB = Wire.read();
    unsigned int T_MSB = Wire.read();
    unsigned int T_MLB = Wire.read();

    
    unsigned long Pb = ((P_MSB << 8) | P_MLB);
    unsigned long Tb = ((T_MSB << 8) | T_MLB);
    
    // Conversión decimal a variable de medida
    float PsrSea = ((Pb-16384)*3.0/32768.000);
    float TempSea = ((Tb/16-24)*0.05)-50;
    
  // Mostrar las variables en el puerto serie

 DateTime fecha = rtc.now();        // funcion que devuelve fecha y horario en formato
              // DateTime y asigna a variable fecha
  
   //Concatenate all info separated by commas
  dataMessage = String(fecha.day()) + "/" + String(fecha.month()) + "/" + String(fecha.year()) + "/" + String(fecha.hour()) +  ":" + String(fecha.minute()) + ":" + String(fecha.second()) + "," + String(TempSea) +  "," + String(PsrSea)+ "\r\n";
  Serial.print("Saving data: ");
  Serial.println(dataMessage);

  //Append the data to file
  appendFile(SD, "/data.txt", dataMessage.c_str());
  lastTime = millis(); 
  }
 }
}