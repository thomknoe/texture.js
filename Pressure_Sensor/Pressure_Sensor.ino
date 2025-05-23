const int pressurePin = A0;
const int buttonPin = 2;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int pressureValue = analogRead(pressurePin);

  int buttonState = digitalRead(buttonPin);

  Serial.print(pressureValue);
  Serial.print(",");
  Serial.println(buttonState);

  delay(100);
}
