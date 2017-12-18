int switchL = 2;
int switchLC = 3;
//int switchR = 12;
int switchRC = 13;

int wBtn1 = 8;
int wBtn2 = 9;
int wBtn3 = 10;

int sliderRR = A2;
int sliderRL = A3;
int sliderLR = A4;
int sliderLL = A5;

int mappedSliderRR, mappedSliderRL, mappedSliderLR, mappedSliderLL;

void setup() {
  Serial.begin(9600);
  pinMode(switchL, INPUT);
  pinMode(switchLC, INPUT);
  //pinMode(switchR, INPUT);
  pinMode(switchRC, INPUT);
  pinMode(wBtn1, INPUT_PULLUP);
  pinMode(wBtn2, INPUT_PULLUP);
  pinMode(wBtn3, INPUT_PULLUP);
  pinMode(sliderRR, INPUT);
  pinMode(sliderRL, INPUT);
  pinMode(sliderLR, INPUT);
  pinMode(sliderLL, INPUT);

}

void loop() {

  mappedSliderRR = map(analogRead(sliderRR), 0, 1024, 0, 1000);
  mappedSliderRL = map(analogRead(sliderRL), 0, 1024, 1001, 2000);
  mappedSliderLR = map(analogRead(sliderLR), 0, 1024, 2001, 3000);
  mappedSliderLL = map(analogRead(sliderLL), 0, 1024, 3001, 4000);
    
    //Serial.print ("sliderRR: ");
  Serial.println (mappedSliderRR);
  delay(25);
    //Serial.print ("sliderRL: ");
  Serial.println (mappedSliderRL);
  delay(25);
    //Serial.print ("sliderLR: ");
  Serial.println (mappedSliderLR);
  delay(25);
    //Serial.print ("sliderLL ");
  Serial.println (mappedSliderLL);
  delay(25);

  int b = digitalRead(switchL);
  if (b == 1) {
    Serial.println(4001);
  } else {
    Serial.println(4002);
  }

  delay(25);

  int c = digitalRead(switchLC);
  if (c == 1) {
    Serial.println(4003);
  } else {
    Serial.println(4004);
  }

  delay(25);
  
  /*int d = digtitalRead(switchR);
  if (d == 1) {
    Serial.println(4005);
  } else {
    Serial.println(4006);
  }

  delay(25);
*/

  int e = digitalRead(switchRC);
  if (e == 1) {
    Serial.println(4007);
  } else {
    Serial.println(4008);
  }

  delay(25);

  int f = digitalRead(wBtn1);
  if (f == 1) {
    Serial.println(4009);
  } else {
    Serial.println(4010);
  }

  delay(25);

  int g = digitalRead(wBtn2);
  if (g == 1) {
    Serial.println(4011);
  } else {
    Serial.println(4012);
  }

  delay(25);

  int h = digitalRead(wBtn3);
  if (h == 1) {
    Serial.println(4013);
  } else {
    Serial.println(4014);
  }

  delay(100);
}
