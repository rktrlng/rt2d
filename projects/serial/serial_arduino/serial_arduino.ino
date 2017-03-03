int counter = -32768; // 16 bit signed int (to 32767)

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
    }

    Serial.println(str);

    counter++;
    if(counter == 32767) {
      counter = -32768;
    }
  }
}
