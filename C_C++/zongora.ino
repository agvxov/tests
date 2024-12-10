// C++ code
//

const int buzzerPin = 3;

int notes[] = {200, 294, 330, 349};
int threashold_values[]  = {190, 280, 570};

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(A0, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  int keyVal = analogRead(A0);
  
  if (keyVal != 0){
    Serial.println(keyVal);
  } else {
    noTone(buzzerPin);
    return;
  }
  
  if(keyVal <= threashold_values[0]){
     tone(buzzerPin, notes[3]);
  }
  else if(keyVal <= threashold_values[1]){
     tone(buzzerPin, notes[2]);
  }
  else if(keyVal <= threashold_values[2]){
     tone(buzzerPin, notes[1]);
  } else {
    tone(buzzerPin, notes[0]);
  } 
}
