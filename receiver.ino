#include <LiquidCrystal.h>
// Pin assignments
#define RX_CLOCK 3
#define RX_DATA A5
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define RS 8
#define EN 9
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
char message[16];
volatile byte rx_byte = 0;
volatile int bit_position = 0;
volatile bool update_lcd = true;
void setup() {
 pinMode(RX_DATA, INPUT);
 strcpy(message, "");
 lcd.begin(16, 2);
 attachInterrupt(digitalPinToInterrupt(RX_CLOCK), onClockPulse, RISING);
}
void onClockPulse() {
 bool rx_bit = analogRead(RX_DATA)>150? true : false;
if (bit_position == 8) {
 rx_byte = 0;
 bit_position = 0;
 }

 if (rx_bit) {
 rx_byte |= (0x80 >> bit_position);
 }
 bit_position += 1;
 if (bit_position == 8) {
 strncat(message, (const char *)&rx_byte, 1);
 }

 update_lcd = true;
}

void loop() {
 if (update_lcd) {
 update_lcd = false;

 lcd.noCursor();
 lcd.setCursor(0, 0);
 lcd.print(message);
 lcd.setCursor(0, 1);
 for (int i = 0; i < 8; i += 1) {
 if (i < bit_position) {
 lcd.print(rx_byte & (0x80 >> i) ? "1" : "0");
 } else {
 lcd.print(" ");
 }
 }
 lcd.setCursor(strlen(message), 0);
 lcd.cursor();
 }
}