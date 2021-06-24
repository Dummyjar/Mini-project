int tr = 8; // tr = transfer rate
#define clk 2 // clock
#define data 13 // transmission data
const char *message = "it works!!!";
void setup() {
 Serial.begin(9600);
 pinMode(clk, OUTPUT);
 pinMode(data, OUTPUT);
 for (int j = 0; j < strlen(message); j++) {
 char byte = message[j];
 for (int i = 0; i < 8; i++) {
 bool bit = byte & (0x80 >> i); // reading each bit of a letter
// right shift operator
 digitalWrite(data, bit); // data led
 Serial.print(bit);

 delay((1000 / tr) / 2);
 // clock pulse
 digitalWrite(clk, HIGH);
 delay((1000 / tr) / 2);
 digitalWrite(clk, LOW);
 }Serial.println();

 }

 digitalWrite(data, LOW);
}
void loop(){}