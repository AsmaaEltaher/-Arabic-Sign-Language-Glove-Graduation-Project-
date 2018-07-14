
const int THUMB_FLEX_PIN = A3;
const int INDEX_FLEX_PIN = A2;
const int MIDDLE_FLEX_PIN = A0;
const int RING_FLEX_PIN = A1;
const int PINKY_FLEX_PIN = A4;

const int xPin = 3;
const int yPin = 2;

//int x = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(THUMB_FLEX_PIN, INPUT);
  pinMode(INDEX_FLEX_PIN, INPUT);
  pinMode(MIDDLE_FLEX_PIN, INPUT);
  pinMode(RING_FLEX_PIN, INPUT);
  pinMode(PINKY_FLEX_PIN, INPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
}

void loop()
{
  //x++;
  while(Serial.available()){
    char pyData=Serial.read();
    
     float thumb_angle = thumb_bend();
     float index_angle = index_bend();
     float middle_angle = middle_bend();
     float ring_angle = ring_bend();
     float pinky_angle = pinky_bend();

     int xAcceleration = x_acceleration();
     int yAcceleration = y_acceleration();

     String orientation = orientation_acceleration(xAcceleration, yAcceleration);
     
     Serial.print(thumb_angle); Serial.print("\t");
     Serial.print(index_angle); Serial.print( "\t");
     Serial.print(middle_angle); Serial.print("\t");
     Serial.print(ring_angle); Serial.print("\t");
     Serial.print(pinky_angle); Serial.print("\t");
     Serial.print(xAcceleration); Serial.print("\t");
     Serial.print(yAcceleration); //Serial.print("\t");
     //Serial.print(orientation); Serial.print("\t");
     Serial.print("\n");
     
  }
  delay(100);
  //if(x%500==0)delay(500000);
}

float thumb_bend() {
  float angle = -1;
  while (angle < 0)angle = map(analogRead(THUMB_FLEX_PIN), 530.0, 190.0, 0.0, 180.0);
  return angle;
}

float index_bend() {
  float angle = -1;
  while (angle < 0)angle = map(analogRead(INDEX_FLEX_PIN), 300.0, 80.0, 0.0, 180.0);
  return angle;
}

float middle_bend() {
  float angle = -1;
  while (angle < 0)angle = map(analogRead(MIDDLE_FLEX_PIN), 555.0, 195.0, 0.0, 180.0);
  return angle;
}

float ring_bend() {
  float angle = -1;
  while (angle < 0)angle = map(analogRead(RING_FLEX_PIN), 580.0, 300, 0.0, 180.0);
  return angle;
}

float pinky_bend() {
  float angle = -1;
  while (angle < 0)angle = map(analogRead(PINKY_FLEX_PIN), 140, 60, 0.0, 180.0);
  return angle;
}

int x_acceleration() {
  int xPulse, xAcceleration;

  xPulse = pulseIn(xPin, HIGH);

  xAcceleration = ((xPulse / 10) - 500) * 8;
  return xAcceleration;
}

int y_acceleration() {
  int yPulse, yAcceleration;

  yPulse = pulseIn(yPin, HIGH);

  yAcceleration = ((yPulse / 10) - 500) * 8;
  return yAcceleration;
}

String orientation_acceleration(int xAcceleration, int yAcceleration) {
  String orientation;
  if (xAcceleration > 300)orientation = "Landscape Down";
  else if (xAcceleration < -300)orientation = "Landscape Up";
  else if (yAcceleration > -700)orientation = "Protirate Down";
  else if (yAcceleration < -1200)orientation = "Protirate Up";
  else orientation = "Flat";

  return orientation;
}
