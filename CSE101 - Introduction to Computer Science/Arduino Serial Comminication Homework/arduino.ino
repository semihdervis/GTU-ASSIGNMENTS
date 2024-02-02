#define ledPin 13
#define buttonPin 4
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
void loop() {
    char selection;              
    if( Serial.available()){
        selection=Serial.read();    
    }
    if(selection == '1'){
        digitalWrite(ledPin,HIGH);      
    }
    else if(selection == '2'){
        digitalWrite(ledPin,LOW);      
    }
    else if(selection == '3'){
        led_Blink();      
    }
    else if(selection == '4'){
        square_func();
    }       
}
void led_Blink(){
          digitalWrite(ledPin,HIGH);
          delay(1000);

          digitalWrite(ledPin,LOW);
          delay(1000);

          digitalWrite(ledPin,HIGH);
          delay(1000);

          digitalWrite(ledPin,LOW);
          delay(1000);

          digitalWrite(ledPin,HIGH);
          delay(1000);

          digitalWrite(ledPin,LOW);
          delay(1000);
}
void square_func(){
    int Number=0;
    int k=1;  

  while(true){    
     if(Serial.available()){                               
        String Data = Serial.readString();              
        delay(150);                   
        Number = Data.toInt();       
        Number=Number*Number; 
        delay(150);           
        Serial.println(Number);

        if(Number>0 || k+Number == 1){   
           break;
        }        
     }
  }
}


