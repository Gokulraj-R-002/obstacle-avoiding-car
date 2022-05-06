int trig_pin = 13;
int echo_pin = 12;
int buzzer_pin = 7;

int turn = 0;

int turn_time = 800; // time taken to rotate 90 degree
int threshold_dist = 30; // cm

//int Lf = 11, Lb = 10, Rf = 9, Rb = 8;
int Lf = 8, Lb = 10, Rf = 9, Rb = 11;

int duration;
int distance;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  
  pinMode(Lf, OUTPUT);
  pinMode(Lb, OUTPUT);
  pinMode(Rf, OUTPUT);
  pinMode(Rb, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  if (distance > threshold_dist) {
    turn = 0;
    
    digitalWrite(Lf, HIGH);
    digitalWrite(Lb, LOW);
    digitalWrite(Rf, HIGH);
    digitalWrite(Rb, LOW);
    
//    digitalWrite(buzzer_pin, LOW);
  }
  
  else if (distance <= threshold_dist) {
//    digitalWrite(buzzer_pin, HIGH);

    // turning left when obstacle is present
    if(turn == 0)
    {
      turn = 1;
      digitalWrite(Lf, LOW);
      digitalWrite(Lb, LOW);
      digitalWrite(Rf, HIGH);
      digitalWrite(Rb, LOW);
      delay(turn_time);
    }
    else if(turn==1)// taking u turn if an obstacle is present after first turn
    {
      turn = 2;

      // go back to the original position
      digitalWrite(Lf, LOW);
      digitalWrite(Lb, LOW);
      digitalWrite(Rf, LOW);
      digitalWrite(Rb, HIGH);
      delay(turn_time);
      
      // turn right
      digitalWrite(Lf, HIGH);
      digitalWrite(Lb, LOW);
      digitalWrite(Rf, LOW);
      digitalWrite(Rb, LOW);
      delay(turn_time);
    }
    else if(turn==2) // turning right when obstacle is present after turn 2
    {
//      turn = 3;
      turn = 0;

      digitalWrite(Lf, LOW);
      digitalWrite(Lb, LOW);
      digitalWrite(Rf, LOW);
      digitalWrite(Rb, HIGH);
      delay(turn_time);
    }
  }
}
