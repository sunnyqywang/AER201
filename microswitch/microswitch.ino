void setup() {
  
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  Serial.begin(9600);
}
int left;
int right;

void loop() {
   
   left = analogRead(A0);
   right = analogRead(A1);
   if (left>0) 
     Serial.println("left pressed");
   if (right>0)
     Serial.println("right pressed");
     
}

