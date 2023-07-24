#define potentiometer A0
#define stop_button  11
#define start_button 10
#define pwm  9
#define motorackapa 2
#define Led_On  4
#define Led_Off 7
#define Start 5
#define Stop 6


int analog_value = 0;
int output_value= 0;

//start buton 
int lastButtonState; 
int currentButtonState;
bool Test_State;

//stop buton
int lastButtonState1;
int currentButtonState1;

//Raspberry Start

int Start_Rasp;
int Stop_Rasp;
int Motor_Test;



void setup()
 {
   Serial.begin(9600);
   pinMode(Led_Off, OUTPUT);
   pinMode(Led_On,OUTPUT);
   pinMode(motorackapa, INPUT);
   pinMode(potentiometer, INPUT);
   pinMode(pwm, OUTPUT);
   pinMode(start_button, INPUT_PULLUP);
   pinMode(stop_button, INPUT_PULLUP);
   pinMode(Start, INPUT);
   pinMode(Stop, INPUT);
   currentButtonState = digitalRead(start_button);
   currentButtonState1 = digitalRead(stop_button);  
}

void loop()
 {

  lastButtonState    = currentButtonState;     
  currentButtonState = digitalRead(start_button);
  Start_Rasp= digitalRead(Start);
  Motor_Test =digitalRead(motorackapa);   // Start Buton with external buton 
  if((lastButtonState ==1 && currentButtonState ==0) ||Start_Rasp==1 )
       
      { 
         Test_State = true;
         Serial.println("Start butona basıldı");
      }
  if(Motor_Test ==1)
  {
    Donanim_Testi();
    Test_State = false;
  }

  else
     analogWrite(pwm,0);
     digitalWrite(Led_On,LOW);
     digitalWrite(Led_Off,HIGH);
     Serial.println("Motor OFF KONUMUNDA");
    
  while(Test_State == true)
     {
        Motor();
        Serial.println("While Döngüsüne girildi");
        lastButtonState1  = currentButtonState1;    
        currentButtonState1 = digitalRead(stop_button);
        Stop_Rasp =  digitalRead(Stop);
        Motor_Test =digitalRead(motorackapa);
       if((lastButtonState1 == 0 && currentButtonState1 ==1)|| Stop_Rasp ==1)    
     {
          Test_State =false;
          digitalWrite(Led_On, LOW);
          digitalWrite(Led_Off,HIGH);
     }

        if(Motor_Test ==1)
        {
            Donanim_Testi();
            Test_State=false;
        }
     }
}

void Motor()
{
    analog_value = analogRead(potentiometer);
    output_value = map (analog_value, 0,1023,0,255);
        if (analog_value < 200)
         {
           analogWrite(pwm, 0);
          }
        else
         analogWrite(pwm, output_value); 
         digitalWrite(Led_On, HIGH);
         digitalWrite(Led_Off,LOW);
}

void Donanim_Testi()
{
    for(int i =100; i<=250 ; i+=5)
          { 
             analogWrite(pwm,i);
             digitalWrite(Led_On,HIGH);
             delay(200);
             digitalWrite(Led_On,LOW);
             Serial.println("Donanım Testi ");
          }
}

