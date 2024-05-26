int strom = 0;
char pin = '1234';
char pin_input = '0000';

#include <Keypad.h>
byte Pins_Rows[]={13,12,11,10};
byte Pins_Columns[]={9,8,7,6};
char keys[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
Keypad Keyboard= Keypad(makeKeymap(keys),Pins_Rows,Pins_Columns,4,4);


void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, OUTPUT);

}

void loop() {
    pin_input = Keyboard.getKey();
    Serial.println(pin_input);
    delay(200);
    if (pin_input == pin && strom == 0) {
      strom = 1;
    } else if (pin_input == pin && strom == 1) {
      strom = 0;
    }
    if (strom == 0) {
      Serial.println("Aus");
    } else if (strom == 1) {
      Serial.println("An");
      if (digitalRead(2) == true) {
        for (int count = 0; count < 6; count++) {
          tone(5,200,500);
           delay(500);
          delay(1000);
        }
      }
    }

}
