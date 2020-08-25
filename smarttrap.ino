#include <Wire.h>

/////i2c btw arduino & pi
/////end

/////RTC
#include <TimeLib.h>
#include <DS1307RTC.h>
/////end

/////ina219
#include <Adafruit_INA219.h>
/////end

/////am2315
#include <Adafruit_AM2315.h>
/////end

/////SSR
/////end

/////tcs34725
#include "Adafruit_TCS34725.h"
/////end

/////sd
#include <SPI.h>
#include <SD.h>
/////end
//////////////////////////////////////////////////////////////////////////////////

/////i2c btw arduino & pi
#define SLAVE_ADDRESS 0x04
#define FLOATS_SENT 8
float data[FLOATS_SENT];
/////end

/////Real time clock
//set time before read
/////Real time clock end

/////ina219
Adafruit_INA219 ina219_a;
Adafruit_INA219 ina219_b(0x41);
/////end

/////am2315
Adafruit_AM2315 am2315;
/////end

/////ssr
int Base = 8;
int Collector = 7;
/////end

/////tcs34725
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
/////end

/////sd
File myFile;
const int chipSelect = 10;
/////end
//////////////////////////////////////////////////////////////////////////////////
void setup() {
  /////serial
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  /////end
  
  /////i2c btw arduino & pi
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onRequest(sendData);
  /////end

  /////RTC
  Serial.println("-DS1307RTC Read Test");
  /////end

  /////INA219
  uint32_t currentFrequency;  
  Serial.println("-INA219 Hello!");
  ina219_a.begin();
  ina219_b.begin();
  Serial.println("        Measuring voltage and current with INA219 ...");
  /////INA219 end

  /////am2315
  Serial.println("-AM2315 Test!");
  if (! am2315.begin()) {
     Serial.println("-Sensor not found, check wiring & pullups!");
     //while (1);
  }
  /////end

  /////ssr
  pinMode(Base, OUTPUT);
  pinMode(Collector, OUTPUT);
  /////end

  /////tcs34725
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
  /////end

  /////sd
  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  /////end

}
//////////////////////////////////////////////////////////////////////////////////
void loop() {
/*
  /////RTC
  tmElements_t tm;
  
  if (RTC.read(tm)) { //RTC.read(tm) is needed to start reading RTC
    Serial.println("-------------------------------------------------");
    Serial.print("Ok, Time = ");
    //Serial.print(tm.Hour);
    //Serial.print(':');
    //Serial.print(tm.Minute);
    //Serial.print(':');
    //Serial.println(tm.Second);
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
    }
    delay(9000);
  }
  /////end

  /////ina219
  float shuntvoltage_a = 0;
  float busvoltage_a = 0;
  float loadvoltage_a = 0;

  shuntvoltage_a = ina219_a.getShuntVoltage_mV();
  busvoltage_a = ina219_a.getBusVoltage_V();
  loadvoltage_a = busvoltage_a + (shuntvoltage_a / 1000);
  
  Serial.print("Load Voltage a:  "); Serial.print(loadvoltage_a); Serial.println(" V");
  Serial.println("");

  float current_mA_b = 0;
  
  current_mA_b = ina219_b.getCurrent_mA();
    
  Serial.print("Current b:       "); Serial.print(current_mA_b); Serial.println(" mA");
  Serial.println("");
  /////end

  /////AM2315
  float temperature, humidity;
  delay(2000);//AM2315 need time to start up
  if (! am2315.readTemperatureAndHumidity(&temperature, &humidity)) {
    Serial.println("Failed to read data from AM2315");
    //return;//infinite loop if having return
  }
  Serial.print("Temp *C: "); Serial.println(temperature);
  Serial.print("Hum %: "); Serial.println(humidity);
  Serial.println();
  /////end

  /////ssr
  digitalWrite(Base,1);
  digitalWrite(Collector,1);
  //delay(3000);
  //digitalWrite(Base,0);
  //digitalWrite(Collector,0);
  /////end

  /////tcs34725
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.println("");
  //Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //Serial.print("C: "); Serial.print(c, DEC); Serial.println(" ");
  /////end
*/
////////////reduce the used storage space
  /////RTC
  tmElements_t tm;
  RTC.read(tm);
  /////end
  /////ina219
  float shuntvoltage_a = 0;
  float busvoltage_a = 0;
  float loadvoltage_a = 0;
  shuntvoltage_a = ina219_a.getShuntVoltage_mV();
  busvoltage_a = ina219_a.getBusVoltage_V();
  loadvoltage_a = busvoltage_a + (shuntvoltage_a / 1000);
  float current_mA_b = 0;
  current_mA_b = ina219_b.getCurrent_mA();
  /////end
  /////am2315
  float temperature, humidity;
  delay(2000);//AM2315 need time to start up
  am2315.readTemperatureAndHumidity(&temperature, &humidity);
  /////end
  /////tcs34725
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  /////end
////////////end

/*
  /////turn on pi
  if ((tm.Minute >= 0 & tm.Minute < 7)||
  (tm.Minute >= 20 & tm.Minute < 27)||
  (tm.Minute >= 40 & tm.Minute < 47)& 
  loadvoltage_a > 11){
  digitalWrite(Base,1);
  digitalWrite(Collector,1);
  }
  /////end

  /////turn off pi
  if ((tm.Minute >= 7 & tm.Minute < 20) || 
  (tm.Minute >= 27 & tm.Minute < 40) || 
  tm.Minute >= 47 & tm.Minute <= 59){
  digitalWrite(Base,0);
  digitalWrite(Collector,0);
  }
  /////end
*/

  digitalWrite(Base,1);
  digitalWrite(Collector,1);
  /////sd
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    //myFile.println(1);
    myFile.print(tm.Day);myFile.print("/");myFile.print(tm.Month);
    myFile.print("\t");
    myFile.print(tm.Hour);myFile.print(":");myFile.print(tm.Minute);
    myFile.print(":");myFile.print(tm.Second);
    myFile.print("\t");
    myFile.print(temperature);
    myFile.print("\t");
    myFile.print(humidity);
    myFile.print("\t");
    myFile.print(loadvoltage_a);
    myFile.print("\t");
    myFile.print(current_mA_b);
    myFile.print("\t");
    myFile.print(colorTemp, DEC);
    myFile.print("\t");
    myFile.println(lux, DEC);
    
  // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Inside the test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  SD.remove("test.txt");
  /////end*/
  
  /////i2c btw arduino & pi
  data[0] = tm.Hour;
  data[1] = tm.Minute;
  data[2] = colorTemp;
  data[3] = lux;
  data[4] = loadvoltage_a;
  data[5] = current_mA_b;
  data[6] = temperature;
  data[7] = humidity;
  //data[8] = lux;
  /////end
  
  delay(10000);
}
//////////////////////////////////////////////////////////////////////////////////
/////i2c btw arduino & pi
void sendData(){
  Wire.write((byte*) &data, FLOATS_SENT*sizeof(float));
}
/////end
/*
/////RTC
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}*/
/////end
