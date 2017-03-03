int counter = 0;
int subcounter = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if(Serial.available()) {
    char inByte = Serial.read();
    String str = "";
    str += (int) inByte;
    str += " ";

    if (inByte == 'a') {
      int adc0 = analogRead(A0);
      int adc1 = analogRead(A1);

      // construct string from values
      str += adc0;
      str += " ";
      str += adc1;
    }

    if (inByte == 'b') {
      int adc0 = analogRead(A0);

      // construct string from values
      str += adc0;
      str += " ";
      str += counter;
      str += " ";
      str += subcounter;

      counter++;
      if(counter > 255) {
        counter = 0;
        subcounter++;
      }
      if(subcounter > 255) {
        subcounter = 0;
      }
    }

    Serial.println(str);
  }
}
