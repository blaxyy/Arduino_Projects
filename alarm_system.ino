#include <Keypad.h>

int strom = 0;
char pin[] = "1234";
char pin_input[5] = "";
char new_pin[5] = "";
int pin_index = 0;
bool setting_new_pin = false;
bool alarm_active = false;

byte Pins_Rows[] = {13, 12, 11, 10};
byte Pins_Columns[] = {9, 8, 7, 6};
char keys[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
Keypad Keyboard = Keypad(makeKeymap(keys), Pins_Rows, Pins_Columns, 4, 4);

void setup() {
    Serial.begin(115200);
    pinMode(2, INPUT_PULLUP);
    pinMode(5, OUTPUT);
}

void loop() {
    char key = Keyboard.getKey();
    if (key) {
        Serial.println(key);
        if (key >= '0' && key <= '9') {
            if (pin_index < 4) {
                if (setting_new_pin) {
                    new_pin[pin_index] = key;
                    pin_index++;
                    new_pin[pin_index] = '\0';
                } else {
                    pin_input[pin_index] = key;
                    pin_index++;
                    pin_input[pin_index] = '\0';
                }
            }
        } else if (key == '*') {
            if (setting_new_pin) {
                if (pin_index == 4) {
                    strcpy(pin, new_pin);
                    setting_new_pin = false;
                    Serial.println("Neuer PIN gespeichert!");
                } else {
                    Serial.println("Neuer PIN muss 4 Stellen haben.");
                }
            } else {
                if (strcmp(pin, pin_input) == 0) {
                    strom = !strom;
                    if (strom == 1) {
                        Serial.println("An");
                    } else {
                        Serial.println("Aus");
                        noTone(5);
                        alarm_active = false;
                    }
                } else {
                    Serial.println("Falscher PIN");
                }
            }
            pin_index = 0;
            memset(pin_input, '\0', sizeof(pin_input));
            memset(new_pin, '\0', sizeof(new_pin));
        } else if (key == '#') {
            if (pin_index > 0) {
                pin_index--;
                if (setting_new_pin) {
                    new_pin[pin_index] = '\0';  
                } else {
                    pin_input[pin_index] = '\0';
                }
            }
        } else if (key == 'A') {
            if (strcmp(pin, pin_input) == 0) {
                setting_new_pin = true;
                Serial.println("Geben Sie neuen PIN ein:");
                pin_index = 0;
                memset(new_pin, '\0', sizeof(new_pin));
            } else {
                Serial.println("Falscher PIN");
                pin_index = 0;
                memset(pin_input, '\0', sizeof(pin_input));
            }
        } else if (key == 'B') {
            setting_new_pin = false;
            pin_index = 0;
            memset(pin_input, '\0', sizeof(pin_input));
            Serial.println("Neuen PIN speichern abgebrochen");
        }
    }

    if (strom == 1 && !alarm_active) {
        if (digitalRead(2) == HIGH) {
            alarm_active = true;
            for (int count = 0; count < 6; count++) {
                if (strom == 0) break;
                tone(5, 200, 500);
                delay(500);
                noTone(5);
                delay(1000);
            }
            alarm_active = false;
        }
    }
}