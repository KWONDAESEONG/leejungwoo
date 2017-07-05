
const int analogInPin = A0;
int cnt = 0;
int k = 0;
int k2 = 0;
char s[100];
char s2[100];

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // read from port 1, send to port 0:

  cnt++;
  int inAno = analogRead(analogInPin);
  int compareValue = 1;
  int posCnt = 0;
  if(cnt>10000){
    Serial1.write("A");
    for(int i=0; i<5; i++){
      compareValue *= 10;
      if(inAno < compareValue){
        posCnt = i+1;
        break;
      }
    }
    Serial1.print(posCnt);
    Serial1.print(":");
    Serial1.println(inAno);
    cnt=0;
  }
  
  if (Serial1.available()) {
    char inByte = Serial1.read();
    
    if(inByte == '\n') {
      s[k]= 0 ;
      if(s[0]=='C'){
        int a =0;
        for(int i=0; i<strlen(s); i++){
          if(s[i]==':'){
            a=i;
          }
        }
        Serial.println(s);
        Serial.println("Type - Chat");
        Serial.print("Size - ");
        for(int i=1; i<a; i++){
          Serial.print(s[i]);
        }
        Serial.println();
        Serial.print("Data - ");

        for(int i=a+1; i<k-1; i++){          
            
            if('0' <= s[i] && s[i] <= '9'){
              s[i] = s[i] - (k-(a+2));  
            }else{
              s[i] = s[i] - (k-(a+2));
              if(s[i]<97){
                s[i] = s[i] + 26;
              }
            }
        }
        
        Serial.println(&s[a+1]);
        Serial.println("-----------------------");
      }

      if(s[0]=='A'){
        int a =0;
        for(int i=0; i<strlen(s); i++){
          if(s[i]==':'){
            a=i;
          }
        }
        Serial.println(s);
        Serial.println("Type - Analog");
        Serial.print("Size - ");
        for(int i=1; i<a; i++){
          Serial.print(s[i]);
        }
        Serial.println();
        Serial.print("Data - ");
        int sa = s[(a+1)] - 48;
        int i = a+2;
        while(i!=k){
          if('0' <= s[i] && s[i] <= '9'){
            sa = sa*10 + (s[i]-48);
          }
          i++;
        }
        sa = sa*2;
        Serial.println(&s[a+1]);
        Serial.print("Data*2 - ");
        Serial.println(sa);
        Serial.println("-----------------------");
      }
      k=0;
    }else {
      s[k]  = inByte;
      k++;
    }
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
      char inByte = Serial.read();
      
          
      if(inByte == '\n') {
        s2[k2]= 0 ;
  
        Serial1.write("C");
        Serial1.print(strlen(s2));
        Serial1.print(":");

        for(int i=0; i<k2; i++){          
            s2[i]+=k2;
            if(s2[i]>122){
              s2[i] = s2[i] - 26;
            }
        }
        
        Serial1.println(s2);
        k2=0;
      }else {
        s2[k2]  = inByte;
        k2++;
      }
      
    }
    
  
}
