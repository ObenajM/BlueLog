#include <Arduino.h>
#include <Wire.h>

void K_4LD_init(void); // function prototype
char* K_4LD_read(void); // function prototype

void K_4LD_init(void); // function prototype


const int ledPin =  18;    // Led Rojo
const int ledPin2 =  19;  // Led Azul CAmbio a pin analogo_a3

int EOC = 3;// corresponde al D3

void setup()
{
  // init Led's
  pinMode(ledPin, OUTPUT);  // rojo
  pinMode(ledPin2, OUTPUT); // azul 
  digitalWrite(ledPin,LOW);   
  digitalWrite(ledPin2,LOW); 
  //pin available 4LD
  pinMode(EOC, INPUT);      // sets the digital pin as output
  /***********************************************************/
  // Open serial communications and wait for port to open: 
  Serial.begin(9600); //normal
  /***********************************************************/
  //init I2C 
  K_4LD_init();// i2c init todo lo anterior
  /***********************************************************/   
}


/*************************--inicial loop---*******************************/  

void loop()
{

while(1){
         // K_4LD_init();
          delay(1000);
          Serial.println(K_4LD_read());
          digitalWrite(ledPin, !digitalRead(ledPin));
        }
   
}

//*******************************************************************************************************************************************////
 /*************************************************************/ 
 void K_4LD_init(void)
{
  Wire.begin();
 Wire.beginTransmission(0x40); // transmit to device #208 (0xD0)  //direccion del A/D conver
  Wire.write(0x80);//HEX
  Wire.write(0xAC);//HEX             // sends value byte 
  //if(Wire.endTransmission(true)==0){Serial.print("success");}
  //delay(8);//8mseg
  Serial.println(String(Wire.endTransmission(true)));
}
/***********************************/
char* K_4LD_read(void)
{
  //Variables 
  unsigned long Pressure=0,Temp=0;
  unsigned char a,b,c,d,e;
  int EOC = 7;// corresponde al A0 
  int cont=0;
  char box_4LD[40]="";
  char box_PsrSea[10];
  char box_TempSea[10];
  char tab[]="\t";
  char *pad;

  K_4LD_init();
  cont=0;
  Pressure=0;
  Temp=0;
  
  while(digitalRead(EOC)== LOW)
    {
    Wire.begin();
    Wire.beginTransmission(0x40); //FUNCIONANDO
    Wire.write(172); 
    Wire.endTransmission(true);
    digitalWrite(ledPin2, !digitalRead(ledPin2));
    }

  Wire.beginTransmission(0x40); // transmit to device #208 (0xD0)  //direccion del A/D conver
  Wire.write(0x81);//HEX
  Wire.endTransmission(false);
  Wire.requestFrom(0x40, 5, true);
  
  while(Wire.available())    // slave may send less than requested
     { 
    a = Wire.read(); // receive a byte as character
    b = Wire.read(); // receive a byte as character
    c = Wire.read(); // receive a byte as character
    d = Wire.read(); // receive a byte as character
    e = Wire.read(); // receive a byte as character
     }
   Wire.endTransmission();

     
  //Calculo profundidad en Bares
  Pressure=(Pressure|b)<<8;
  Pressure=(Pressure|c);
  unsigned long Psr_aux =(Pressure-16384)*3.0;//en long 32bits
  float PsrSea=(Psr_aux/32768.0);// en float para coger las decimas
  dtostrf(PsrSea,7,6,box_PsrSea);

  //Calculo Temperatura
  Temp=(Temp|d)<<8;
  Temp=(Temp|e);
  unsigned long  int Temp_aux=(Temp/16);// en float para coger las decimas
  float TempSea=((Temp_aux-24)*0.05)-50;
  dtostrf(TempSea,7,6,box_TempSea);
  sprintf(box_4LD,box_TempSea);
  strcat (box_4LD,tab);
  strcat (box_4LD,box_PsrSea);


  pad=&box_4LD[0];
  return pad;
}



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