/*
 * Syringe Pump Program
 * By: Tutla Ayatullah
 */
#define en_pin  2 /*1 = disable; 0 = enable*/
#define dir_pin 3 /*1 = CW; 0 = CCW*/
#define pul_pin 5
#define startPin 6
#define stopPin 7
#define fwdPin 8
#define revPin 9

#define enable_motor digitalWrite(en_pin,0)
#define disable_motor digitalWrite(en_pin,1)

#define stepsPerRevolution 1600
#define rotation  5

bool dir = 1, stat = 1, maju = 0, mundur = 0;
bool startBtn = 0, stopBtn = 0, fwdBtn = 0, revBtn = 0;
int step_del = 400, pos = 50;
char incByte = 0;

void setup() {
  /*Output PIN*/
  pinMode(en_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(pul_pin, OUTPUT);
  
  /*Input PIN*/
  pinMode(startBtn, INPUT);
  pinMode(stopBtn, INPUT);
  pinMode(fwdBtn, INPUT);
  pinMode(revBtn, INPUT);

  /*Configure Stepper Motor*/
  enable_motor;
  digitalWrite(dir_pin,dir);
}

void loop() {
//  startBtn = digitalRead(startPin);
  fwdBtn = digitalRead(fwdPin);
  revBtn = digitalRead(revPin);

  if(startBtn){
    stat = 1;
  }
  if(stat&&fwdBtn){
    maju = 1;
    mundur = 0;
  }
  else if(stat&&revBtn){
    maju = 0;
    mundur = 1;
  }
  
  if(stat){
    if(maju){
      enable_motor;
      for(int i = 0;i<pos;i++){
        step_fwd();
      }
      maju = 0;
    }
    else if(mundur){
      enable_motor;
      for(int i = 0;i<pos;i++){
        step_bwd();
      }
      mundur = 0;      
    }
    else{
      disable_motor;/* Idle Condition*/
    }
  }
}

void step_fwd(){
  digitalWrite(dir_pin, 1);
  digitalWrite(pul_pin, HIGH);
  delayMicroseconds(step_del);
  digitalWrite(pul_pin, LOW);
  delayMicroseconds(step_del);
}

void step_bwd(){
  digitalWrite(dir_pin, 0);
  digitalWrite(pul_pin, HIGH);
  delayMicroseconds(step_del);
  digitalWrite(pul_pin, LOW);
  delayMicroseconds(step_del);
}
