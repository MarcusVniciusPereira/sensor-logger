#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
String inData;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("failed.");
    while (1);
  }
  Serial.println("initialized.");
  if(SD.exists("datalog.csv")){
    SD.remove("datalog.csv");
  }
}

void loop() {
    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 
        if (recieved == '\n')
        {
            File dataFile = SD.open("datalog.csv", FILE_WRITE);
            if (dataFile) {
              if(inData == '\n'){
               } else {
                dataFile.print(inData);
                dataFile.close();
               }
            }
            else {
              Serial.println("error opening datalog.csv");
            }
            inData = "";
        }
    }
}
