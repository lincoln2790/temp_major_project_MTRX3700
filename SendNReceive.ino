void setup() {
  // put your setup code here, to run once:
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  Serial1.print('A');
  Serial.print('A');
  Serial.print('\n');
  delay(1000);
  Serial1.print('B');
  Serial.print('B');
  delay(100);
  while (Serial1.available() > 0) {
    int SW_val = Serial1.read();          
    Serial.print(SW_val);
  }
  delay(1000);
  Serial.print('\n');

}
