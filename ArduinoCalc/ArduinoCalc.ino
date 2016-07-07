#include <Wire.h>

// the setup function runs once when you press reset or power the board
void setup() {
  Wire.onReceive(receiveEvent); //Zgłaszane przy wysyłaniu (nadawca: Write)
  Wire.onRequest(requestEvent); //Zgłaszane przy żądaniu odczytu (nadawca: Read)
  Wire.begin(18); //Jesteśmy slave numer 18
}

// the loop function runs over and over again until power down or reset
void loop() { }


/*
 * Sprawdzać kabelki
 * RPI2: 3.3V (tu nie jest konieczne)
 * RPI2: SDA1 -> Uno: A4 (zielony)
 * RPI2: SCL1 -> Uno: A5 (biały)
 * GND (czarny)
 * Leonardo:
 */
 
byte arr[2];
int sum=0;
void receiveEvent(int howMany) {  //Odebranie I2C, howMany - ile bajtów
    sum = 0;
    while (Wire.available() > 0){
        byte b = Wire.read();
        sum+=b;
    }
}

void requestEvent() {
    arr[0] = sum & 0xFF;
    arr[1] = (sum>>8)& 0xFF; 
    Wire.write(arr,sizeof(arr));
}


