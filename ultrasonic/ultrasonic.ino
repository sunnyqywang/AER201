int duration;
  const int UltrasonicechoPin = 31;
  const int UltrasonictrigPin = 30;
void setup() {
  
  Serial.begin(9600);
  
}

void loop() {
        
  pinMode(UltrasonictrigPin, OUTPUT);
  digitalWrite(UltrasonictrigPin,LOW);
  delay(2);
  digitalWrite(UltrasonictrigPin,HIGH);
  delay(5);
  digitalWrite(UltrasonictrigPin,LOW);
  
  pinMode(UltrasonicechoPin, INPUT);
  digitalWrite(UltrasonicechoPin, HIGH);
  duration = pulseIn(UltrasonicechoPin,HIGH);
  
  Serial.println(duration);
  
  delay(5);
    
}
