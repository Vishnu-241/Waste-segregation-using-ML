const int trigPin1=8;// for 1st ultra sonic sensor
const int echoPin1=4;
float duration1;
int distance1;

const int trigPin2=7;// for 2nd ultrasonic sensor
const int echoPin2=6;
float duration2;
int distance2;

const int trigPin3=2;// for 3rd utrasonci senor
const int echoPin3=5;
float duration3;
int distance3;

const int msensor=A0;// for mositure sensor
int msvalue=0;

const int irsensor=3;// for ir sensor
int irvalue=0;

const int dc1_positive=10;// for dc gear motors
const int dc1_negative=11;
const int dc2_positive=9;
const int dc2_negative=12;

String inputString = "";
bool dataCom = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
Serial.setTimeout(1);
pinMode(trigPin1,OUTPUT);
pinMode(echoPin1,INPUT);

pinMode(trigPin2,OUTPUT);
pinMode(echoPin2,INPUT); 

pinMode(trigPin3,OUTPUT);
pinMode(echoPin3,INPUT);

pinMode(msensor,INPUT);

pinMode(irsensor,INPUT);

pinMode(dc1_positive,OUTPUT);
pinMode(dc1_negative,OUTPUT);

pinMode(dc2_positive,OUTPUT);
pinMode(dc2_negative,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin1,LOW);// calculating 1st ultrasonic sensor distance
  delayMicroseconds(2);
  digitalWrite(trigPin1,HIGH);
  delayMicroseconds(10);
  duration1=pulseIn(echoPin1,HIGH);
  distance1=duration1*0.34/2;

  digitalWrite(trigPin2,LOW);//calculating 2nd ultrasonic sensor distance
  delayMicroseconds(2);
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(10);
  duration2=pulseIn(echoPin2,HIGH);
  distance2=duration2*0.34/2;

  digitalWrite(trigPin3,LOW);// calculating 3rd ultrasonic sensor distance
  delayMicroseconds(2);
  digitalWrite(trigPin3,HIGH);
  delayMicroseconds(10);
  duration3=pulseIn(echoPin3,HIGH);
  distance3=duration3*0.34/2;

  msvalue=analogRead(msensor);
  irvalue=digitalRead(irsensor);
  


  /*Serial.print(" Distance1 is :");
  Serial.println(distance1);

  Serial.print(" Distance2 is :");
  Serial.println(distance2);

  Serial.print(" Distance3 is :");
  Serial.println(distance3);

  Serial.print("moisture value is: ");
  Serial.println(msvalue);

  Serial.println(irvalue);*/

  if((distance1<=50)||(distance2<=50)||(distance3<=50) ){
    digitalWrite(dc1_positive,LOW);
    digitalWrite(dc1_negative,LOW);
    digitalWrite(13,HIGH);
    delay(2000);
    digitalWrite(13,LOW);
  }
  else if ((msvalue>=1000)&&(irvalue==LOW)&&((distance2>50)||(distance3>50)))
  {
    digitalWrite(dc1_positive,LOW); 
    digitalWrite(dc1_negative,HIGH);
    delay(200);
    digitalWrite(dc1_negative,LOW);
    digitalWrite(dc1_positive,HIGH);
    delay(200);
    digitalWrite(dc1_positive,LOW);
    digitalWrite(dc1_negative,LOW);
    
  }
  else if((msvalue<1000)&&(irvalue==LOW)&&(distance1>50))
  {
    digitalWrite(dc1_positive,HIGH);
    digitalWrite(dc1_negative,LOW);
    delay(200);
    digitalWrite(dc1_negative,HIGH);
    digitalWrite(dc1_positive,LOW);
    delay(200);
    digitalWrite(dc1_positive,LOW);
    digitalWrite(dc1_negative,LOW);
    
  }
}

void serialEvent() {
char inChar = (char)Serial.read();
inputString += inChar;
if (inChar == '\n'){
  dataCom = true;
 digitalWrite(13,HIGH);  
 Serial.println(inputString);
 delay(2000);
 digitalWrite(13,LOW);    
}

if (dataCom){
//change H for value of waste
if(inputString == "H\n"){ // convyor rotaion for e waste 
 // Serial.println(inputString);
  // conveyor motor foraward rotation
 digitalWrite(13,HIGH);
digitalWrite(dc2_positive,LOW);
digitalWrite(dc2_negative,HIGH);
 delay(10000);// change time delay as per requirement
  Serial.println("drywaste");
  digitalWrite(13,LOW);
  digitalWrite(dc2_positive,LOW);
  digitalWrite(dc2_negative,LOW);
  
}
// change L value for diff waste
else if(inputString == "L\n"){ // convyor rotaion for e waste 
  //Serial.println(inputString);// conveyor motor foraward rotation
  digitalWrite(13,HIGH);
  digitalWrite(dc2_positive,HIGH);
  digitalWrite(dc2_negative,LOW);
  delay(10000); // time delay as per requiremnt
  Serial.println("ewaste");
  digitalWrite(13,LOW);
  digitalWrite(dc2_positive,LOW);
 digitalWrite(dc2_negative,LOW);
  
}

inputString = "";
dataCom = false;
  }
}

