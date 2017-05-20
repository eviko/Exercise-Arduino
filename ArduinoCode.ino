// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
//int led = 13;

int New = 10;
int Done = 11;
int Reset = 12;
int FullLed =  13;
int NewLeds[] = {8,7,6,5,4,3,2};
int DoneLeds[] = {A0,A1,A2,A3,A4,A5,9};

int CurrentClient = 0;
int AllClients = 0;
int reset = 0;
bool NewHold = false;
bool DoneHold = false;
bool ResetHold = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  //input pins
  pinMode(New,INPUT);
  pinMode(Done,INPUT);
  pinMode(Reset,INPUT);

  //output pins
  pinMode(FullLed, OUTPUT);
  
  for(int i=0; i<=6; i++){
    pinMode(NewLeds[i], OUTPUT);
    pinMode(DoneLeds[i], OUTPUT);
  }
}
// the loop routine runs over and over again forever:
void loop() {

  //------New ----------
  
  if(digitalRead(New) == HIGH && AllClients<100){
    if(!NewHold){
      NewHold = true;
      AllClients++;
     
      for(int i=0;i<=6;i++){
        if( (AllClients & (1<<i)) == 0)
          digitalWrite(NewLeds[i],LOW);
        else
           digitalWrite(NewLeds[i],HIGH);        
      }
      
      if (AllClients == 100)
        digitalWrite(FullLed,HIGH); 
      
    }
  }else
  	NewHold = false;
  
    
    //------ Done ----------
   if(digitalRead(Done) == HIGH && CurrentClient < AllClients){
     if(!DoneHold){
       DoneHold = true;
       CurrentClient++;
       for(int i=0;i<=6;i++){
        if( (CurrentClient & (1<<i)) == 0)
          digitalWrite(DoneLeds[i],LOW);
        else
           digitalWrite(DoneLeds[i],HIGH);
       }
     }
   }else
   	DoneHold=false;
   
    //------ Reset ----------
    if(digitalRead(Reset) == HIGH){
    if(!ResetHold){
      ResetHold = true;
      CurrentClient =0;
      AllClients = 0;
      digitalWrite(FullLed, LOW);
      for(int i=0;i<6;i++){
      	digitalWrite(NewLeds[i],LOW);
      	digitalWrite(DoneLeds[i],LOW);
      }		  
    }
  }else
    ResetHold = false;
  
}   
