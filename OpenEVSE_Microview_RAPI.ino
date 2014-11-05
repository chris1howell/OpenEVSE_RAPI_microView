
#include <MicroView.h>

#define RAPI_BUFLEN 13


int EVSE_STATE = 0;
int EVSE_LAST_STATE = 1;


class RAPI {
  int m_RAPIinByte; // RAPI byte being read in
  char m_RAPIinstr[RAPI_BUFLEN]; // RAPI byte being read in
  int m_RAPIstrCount; //RAPI string counter

public:
  RAPI();
  void Init();
  
  void flush() { 
    Serial.flush(); 
  }
  void getInput();
  uint8_t getInt();
};

RAPI g_RAPI;

RAPI::RAPI()
{
  m_RAPIstrCount = 0; 
}

void RAPI::Init()
{
 g_RAPI.flush();

}

uint8_t RAPI::getInt()
{
  uint8_t c;
  uint8_t num = 0;

  do {
    c = Serial.read(); // read the byte
    if ((c >= '0') && (c <= '9')) {
      num = (num * 10) + c - '0';
    }
  } while (c != 13);
  return num;
}

void RAPI::getInput()
{
  if(Serial.available()) { // if byte(s) are available to be read
    m_RAPIinByte = Serial.read(); // read the byte
    Serial.print(char(m_RAPIinByte));
    digitalWrite(13, HIGH);
    if(m_RAPIinByte != 13) {
      m_RAPIinstr[m_RAPIstrCount] = char(m_RAPIinByte);
      m_RAPIstrCount++;
    }
    if(m_RAPIinByte == 13) {
      if (strcmp(m_RAPIinstr, "$ST 1") == 0){ //if match 
        EVSE_STATE = 1;
           
      } 
      else if (strcmp(m_RAPIinstr, "$ST 2") == 0) { // string compare
        EVSE_STATE = 2;
      } 
      else if (strcmp(m_RAPIinstr, "$ST 3") == 0) { // string compare
        EVSE_STATE = 3;
      }
      else if (strcmp(m_RAPIinstr, "$ST 4") == 0) { // string compare
        EVSE_STATE = 4;
      }
      else if (strcmp(m_RAPIinstr, "$ST 5") == 0) { // string compare
        EVSE_STATE = 5;
      }
      else if (strcmp(m_RAPIinstr, "$ST 6") == 0) { // string compare
        EVSE_STATE = 6;
      }
      else if (strcmp(m_RAPIinstr, "$ST 7") == 0) { // string compare
        EVSE_STATE = 7;
      }
      g_RAPI.flush();
      m_RAPIstrCount = 0; // get ready for new input... reset strCount
      m_RAPIinByte = 0; // reset the inByte variable
      digitalWrite(13, LOW);
      for(int i = 0; m_RAPIinstr[i] != '\0'; i++) { // while the string does not have null
        m_RAPIinstr[i] = '\0'; // fill it with null to erase it
      }
    }
        
  
}
}


void setup() {
  //pinMode(13, OUTPUT);
  Serial.begin(9600);
  uView.begin();
  uView.clear(PAGE);
  uView.println("OpenEVSE");
  uView.println("Remote API");	
	uView.display();
        delay(4000);
        	
}

void loop() {
  
{
 g_RAPI.getInput();
} 
   
      
         
if(EVSE_STATE != EVSE_LAST_STATE) { 
  
  
  if(EVSE_STATE == 0) {
    uView.clear(PAGE);
    uView.setCursor(0,0); 
    uView.println("OpenEVSE");
    uView.display(); 
  
  }
  
  if (EVSE_STATE == 1) {
    uView.clear(PAGE);
    uView.setCursor(0,0);
    uView.println("OpenEVSE");
    uView.println("Ready");
    uView.println("Vehicle");
    uView.println("None");
    uView.display();
  }
   if (EVSE_STATE == 2) {
     uView.clear(PAGE);
     uView.setCursor(0,0);
     uView.println("OpenEVSE");
     uView.println("Ready");
     uView.println("Vehicle");
     uView.println("Connected");
     uView.display();
  
   }
   if (EVSE_STATE == 3) {
      uView.clear(PAGE);
      uView.setCursor(0,0);
      uView.println("OpenEVSE");
      uView.println("Charging");
      uView.println("Vehicle");
     uView.println("Connected");	
      uView.display();
   }
   if (EVSE_STATE > 3) {
     uView.clear(PAGE);
     uView.setCursor(0,0);
     uView.println("OpenEVSE"); 
     uView.println("Error");	
     uView.display();
   }
   EVSE_LAST_STATE = EVSE_STATE;
}
}


