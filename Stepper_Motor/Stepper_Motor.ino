#include <Servo.h>
#include <Stepper.h>

const int stepsPerRevolution = 360;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

Servo myServo;
int currentAngle = 35;
int servoPin = 6;

const int angleThreshold = 3;

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(10);
  myServo.attach(servoPin);
  myServo.write(currentAngle);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("MOVE"))
    {
      int pressure = command.substring(5).toInt();
      int targetAngle = map(pressure, 0, 800, 35, 60);

      if (abs(targetAngle - currentAngle) >= angleThreshold)
      {
        moveServoSmoothly(targetAngle);
      }

      myStepper.step(2);
    }
  }
}

void moveServoSmoothly(int targetAngle)
{
  int step = (targetAngle > currentAngle) ? 1 : -1;
  while (currentAngle != targetAngle)
  {
    currentAngle += step;
    myServo.write(currentAngle);
    delay(15);
  }
}
