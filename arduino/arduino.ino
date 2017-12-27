const int trigger1 = 2; //Trigger pin of 1st Sesnor
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor
long time_taken;
int dist, distL, distR;

void setup() {
  Serial.begin(9600);

  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
}
/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
  {
  Serial.println("hello");
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  time_taken = pulseIn(echo, HIGH);
  dist = time_taken * 0.034 / 2;
  if (dist > 50){
    Serial.println("in if statement");
  dist = 50;
  }
  Serial.println(dist);
  }
  float speedOfSound=776.5;
/*void calculate_distance(int trigPin, int echoPin) {
  Serial.println("in function");
  float pingTime; float targetDistance;
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state

  pingTime = pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
  pingTime = pingTime / 1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime = pingTime / 3600; //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  dist = speedOfSound * pingTime; //This will be in miles, since speed of sound was miles per hour
  dist = dist / 2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  dist = dist * 63360; //Convert miles to inches by multipling by 63360 (inches per mile));
  dist/=2.54;
  if(dist > 50){
    dist = 50;
  }
  Serial.println(dist);
}*/
void loop() { //infinite loopy
  calculate_distance(trigger1, echo1);
  distL = dist; //get distance of left sensor
  calculate_distance(trigger2, echo2);
  distR = dist; //get distance of right sensor
  //Uncomment for debudding
  /*Serial.print("L=");
    Serial.println(distL);
    Serial.print("R=");
    Serial.println(distR);
  */
  //Pause Modes -Hold
  if ((distL > 40 && distR > 40) && (distL < 50 && distR < 50)) //Detect both hands
  {
    Serial.println("Play/Pause");
    delay (500);
  }
  calculate_distance(trigger1, echo1);
  distL = dist;
  calculate_distance(trigger2, echo2);
  distR = dist;

  //Control Modes
  //Lock Left - Control Mode
  if (distL >= 13 && distL <= 17)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger1, echo1);
    distL = dist;
    if (distL >= 13 && distL <= 17)
    {
      Serial.println("Left Locked");
      while (distL <= 40)
      {
        calculate_distance(trigger1, echo1);
        distL = dist;
        if (distL < 10) //Hand pushed in
        {
          Serial.println ("Vup");
          delay (300);
        }
        if (distL > 20) //Hand pulled out
        {
          Serial.println ("Vdown");
          delay (300);
        }
      }
    }
  }
  //Lock Right - Control Mode
  if (distR >= 13 && distR <= 17)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger2, echo2);
    distR = dist;
    if (distR >= 13 && distR <= 17)
    {
      Serial.println("Right Locked");
      while (distR <= 40)
      {
        calculate_distance(trigger2, echo2);
        distR = dist;
        if (distR < 10) //Right hand pushed in
        {
          Serial.println ("Rewind");
          delay (300);
        }
        if (distR > 20) //Right hand pulled out
        {
          Serial.println ("Forward");
          delay (300);
        }
      }
    }
  }
  delay(200);
}
