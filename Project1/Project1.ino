#include <avr/io.h>
#include <avr/pgmspace.h>
#include <Tone.h>
#include <MOS.h>
#include "pitches.h" 
#include "durations.h" 

// https://electronics.stackexchange.com/questions/67087/analogread0-or-analogreada0

int columns[] = {7,6,5,4,3,2,1,0}; 
int rows[] = {A0,A1,A2,A3,A4,A5,10,11}; 

// NOTES FOR BACKGROUND MUSIC
const PROGMEM uint16_t bgnotes[] = {

              NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                
                NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
            
                NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
              
                NOTE_D4, NOTE_D4, 0, NOTE_D4, NOTE_D4, NOTE_D4, 0, NOTE_D4, 
                NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4,
                NOTE_A4, NOTE_A4, 0, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_A4, 
                NOTE_E4, 0, 
              
                NOTE_D4, NOTE_D4, 0, NOTE_D4, NOTE_D4, NOTE_D4, 0, NOTE_D4, 
                NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4,
                NOTE_A4, NOTE_A4, 0, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_A4, 
                NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_GS4, 

                NOTE_FS3, 0, NOTE_FS4, 0, NOTE_FS3, NOTE_FS4, 0, 
                NOTE_D3, 0, NOTE_D4, 0, NOTE_D3, NOTE_D4, NOTE_D3,
                NOTE_E3, 0, NOTE_E4, 0, NOTE_E3, NOTE_E4, 0,
                
                NOTE_GS3, 0, NOTE_CS4, NOTE_GS3, NOTE_F3, 0, NOTE_CS4,0,
                
                
                NOTE_FS3, 0, NOTE_FS4, 0, NOTE_FS3, NOTE_FS4, 0, 
                NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_FS4, 0, 0,
                NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_A3, 
                NOTE_CS4, NOTE_F3, NOTE_FS3,
                0,
                0
                };
const PROGMEM uint16_t bgdur[] = {

           EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
               
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH,
           
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH,
              DOT_HALF, QUARTER,
            
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH,
              QUARTER, QUARTER, QUARTER, QUARTER, 
      
              EIGHTH, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, EIGHTH,                  
              EIGHTH, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, EIGHTH,
              
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH,EIGHTH,
              

              EIGHTH, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, EIGHTH,
              EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, DOT_QUARTER, SIXTEENTH, EIGHTH,
              QUARTER, QUARTER, QUARTER, QUARTER, 
              QUARTER, QUARTER, WHOLE, 
              HALF, 
              WHOLE
              };
int bgidx = 0; 
int bgstart = millis(); 
int bgwait = 0;  // gap between notes
int bgnotes_size = sizeof(bgnotes)/sizeof(uint16_t); 

// NOTES FOR PLAYER MUSIC
const PROGMEM uint16_t mainnotes[] = {
 
                NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3, 
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
                NOTE_A2, NOTE_A2, NOTE_A2, NOTE_A2,
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
               
                NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3, 
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
                NOTE_A2, NOTE_A2, NOTE_A2, NOTE_A2,
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
             
                NOTE_FS3, NOTE_FS3, NOTE_A3, NOTE_FS3,NOTE_A3,NOTE_FS3,NOTE_A3,NOTE_FS3,NOTE_A3,
                NOTE_E3, NOTE_E3, NOTE_GS3, NOTE_E3,NOTE_GS3,NOTE_E3,NOTE_GS3,NOTE_E3,NOTE_GS3,
                NOTE_A2, NOTE_A2, NOTE_CS3, NOTE_A2, NOTE_CS3,NOTE_A2, NOTE_CS3,NOTE_A2, NOTE_CS3,
                NOTE_E3, NOTE_E3, NOTE_GS3, NOTE_E3,NOTE_GS3,NOTE_E3,NOTE_GS3,NOTE_E3,NOTE_GS3,
               
                NOTE_B3, 
                NOTE_D4, NOTE_FS4, NOTE_GS4, 
                NOTE_FS4, 
                NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_E4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_E4, NOTE_GS4, 
                
                NOTE_B3, 
                NOTE_D4, NOTE_FS4, NOTE_GS4, 
                NOTE_FS4,
                NOTE_CS4, NOTE_E4, NOTE_F3, NOTE_B3, 

                NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_FS4, NOTE_A4, NOTE_CS5, NOTE_FS5, NOTE_CS5, 0,
                NOTE_D5, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_CS5, 0, 
                
                NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_GS4, NOTE_F4, NOTE_GS4, NOTE_A4, NOTE_B4, NOTE_CS5, 0,0, 
                
                
                NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_FS5, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_FS4, NOTE_A4, NOTE_CS5, NOTE_FS5, NOTE_CS5, 0,                
                NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_CS5, NOTE_A4, 0, 0,
                NOTE_A5, NOTE_CS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, 0, NOTE_GS5, NOTE_A5,
                NOTE_F5, NOTE_FS5, NOTE_FS5, 
                0, 
                NOTE_FS4, NOTE_FS4, NOTE_FS4, 0,0,0
                
                }; 
const PROGMEM uint16_t maindur[] = {

                QUARTER, QUARTER, QUARTER, QUARTER, 
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER, 
              
                QUARTER, QUARTER, QUARTER, QUARTER, 
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER, 
            
                EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, EIGHTH,SIXTEENTH, EIGHTH,
                EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, EIGHTH,SIXTEENTH, EIGHTH,
                EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, EIGHTH,SIXTEENTH, EIGHTH,
                EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, EIGHTH,SIXTEENTH, EIGHTH,
               
                WHOLE,
                DOT_HALF, EIGHTH, EIGHTH,
                WHOLE,
                EIGHTH, SIXTEENTH, SIXTEENTH, EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, SIXTEENTH, EIGHTH, EIGHTH,
                
                WHOLE,
                DOT_HALF, EIGHTH, EIGHTH,
                WHOLE,
                QUARTER, QUARTER, QUARTER, QUARTER, 

                EIGHTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, EIGHTH, SIXTEENTH, SIXTEENTH, 
                EIGHTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, HALF, SIXTEENTH,
                
                EIGHTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, DOT_EIGHTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, DOT_EIGHTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, DOT_QUARTER,SIXTEENTH,EIGHTH,                
                
                EIGHTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, EIGHTH, SIXTEENTH, SIXTEENTH,
                EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, DOT_QUARTER,SIXTEENTH, EIGHTH, 
                EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, DOT_QUARTER, SIXTEENTH, SIXTEENTH, SIXTEENTH, 
                DOT_QUARTER, EIGHTH, WHOLE,
                DOT_QUARTER,
                SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, DOT_QUARTER, HALF
                };
int mainidx = 0; 
int mainstart = millis(); 
int mainwait = 0; // gap between notes
int mainnotes_size = sizeof(mainnotes)/sizeof(uint16_t); 

// gap between notes
int gapdur = 500-QUARTER; 

const PROGMEM int note_display[] = {   
  
  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11000000,  

  B00000011, 
  B11000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,  

  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,    

  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,  

  B00110000,
  B00110000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,  

  B00000011,
  B00001100,
  B00000000,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,

  B00001100,
  B00110000,
  B00001100,
  B00001100,
  B00110000,
  B00110000,
  B00000011,
  B00000011,  

  B00000000,
  B00000000,
  B00000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  B11000000,

  B11000000,
  B00001100,
  B00110000,
  B00110000,
  B00001100,
  B00001100,
  B00000011,
  B00000011,

  B00000000,  
  B00001100,
  B00000011,
  B00000011,
  B00001100,
  B00110000,
  B11000000,
  B00000000,  

  B11000000,
  B00110000,
  B00001100,
  B00000011,
  B00001100,
  B00110000,
  B11000000,
  B11000000, 

  B00000000,

  B00000000,
  B00000000,
  B00000000,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100, 

  B00001100,
  B00000011,
  B00001100,
  B00110000,
  B11000000, 
  B00001100,
  B00110000,  
  B00110000,  

  B00110000,
  B00001100,
  B00000011,
  B00001100,
  B00110000,
  B00001100,
  B00110000,
  B00110000,

  B00110000,
  B00001100,
  B00000011,
  B00001100,
  B00110000,
  B00001100,
  B00110000,  
  B00110000, 

  B00000000,   

  B00000000,
  B00110000,  
  B00110000,
  B00110000,  
  B00110000,
  B00110000,  
  B00110000,
  B00110000,  

  B00110000,
  B00001100,
  B00000011,
  B00001100,
  B00110000,
  B00001100,
  B00110000,
  B00110000, 

  B00000000,  
  B00001100,
  B00000011,
  B00000011,
  B00001100,
  B00110000,
  B11000000,
  B00000000,   

  B11000000,
  B00110000,
  B00001100,
  B00000011,
  B00001100,
  B00110000,
  B11000000,
  B11000000,  // BOSS BATTLE

  B00000000,
  B00000000,
  B00000000,
  
  B00001100,      
  B00001100,   
  B00001100,      
  B00001100,    
  B11000000,  
  B11000000,       
  B11000000,    
  B11000000,   
  
  B00000011,   
  B00000011,   
  B00000011,   
  B00000011, 
  B00110000,   
  B00110000,   
  B00110000,   
  B00110000,  
  
  B00001100,
  B00001100, 
  B00001100,
  B00001100, 
  B00001100,
  B00001100,   
  B00001100,  
  B00001100,
     
  B00001100,
  B00001100, 
  B00001100,
  B00001100, 
  B00001100,
  B00001100,   
  B00001100,
  B00001100, 
  
  B00000011,
  B00000011, 
  B00001100,
  B00001100,    
  B00110000,  
  B00110000,    
  B00110000,  
  B00110000,  
  
  B00110000,  
  B00110000,    
  B00110000,  
  B00110000,  
  B00110000,  
  B00110000,  
  B00110000,  
  B00110000,

  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,  
  
  B00001100,    
  B00001100,    
  B00110000,    
  B00110000,    
  B00001100,   
  B00110000,    
  B11000000,  
  B11000000, 
   
  B00001100,    
  B00001100,    
  B00110000,    
  B00110000,    
  B00001100,   
  B00110000,    
  B11000000,  
  B11000000,
  
  B00001100,
  B00001100, 
  B00001100,
  B00001100, 
  B00001100,
  B00001100,   
  B00001100,
  B00001100,   
  
  B00001100,
  B00001100, 
  B00001100,
  B00001100, 
  B00001100,
  B00001100,   
  B00001100,
  B00001100,
   
  B00000011,
  B00000011, 
  B00001100,
  B00001100,    
  B00110000,  
  B00110000,    
  B00110000,  
  B00110000,
    
  B00110000,  
  B00110000,    
  B00110000,  
  B00110000,  
  B00110000,  
  B00110000,  
  B00110000,  
  B00110000,
  
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  B11000000,  
  B11000000,
  
  B00000011,
  B00000011, 
  B00110000,
  B00000011,
  B00000011, 
  B00110000,
  B00000011,
  B00000011, 
  
  B00110000,
  B00110000,  
  B00000011,
  B00000011, 
  B00110000,
  B00110000,  
  B11000000,  
  B11000000,
  
  B00001100,
  B00001100,  
  B00110000,
  B00001100,
  B00001100,  
  B00110000,
  B00001100,
  B00001100,
    
  B00110000,
  B00110000,  
  B00001100,
  B00001100,  
  B00110000,
  B00110000,  
  B11000000,
  B11000000,
  
  B00000011,
  B00000011,   
  B00110000,  
  B00000011,
  B00000011,  
  B00110000,
  B00000011,
  B00000011,
  
  B00110000,
  B00110000,
  B00000011,
  B00000011,
  B00110000,
  B00110000,
  B11000000,
  B11000000,
  
  B00000011,
  B00000011,
  B00001100,
  B00000011,
  B00000011,
  B00001100,  
  B00000011,
  B00000011,
  
  B00001100,
  B00001100,
  B00000011,
  B00000011,
  B00001100,
  B00001100,
  B00110000,
  B00110000,

  B00000000,
  B00000000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B11000000,
  B11000000,
  B11000000,
  B11000000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  
  B00000011, 
  B00000011,
  B00000011,
  B00000011,
  B00001100,
  B00001100,
  B00001100,
  B00001100,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00000000, 
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
  };

int notedisp_size = sizeof(note_display)/sizeof(uint16_t); 

//int notedisp_size = 40*8; 

int dispstart = notedisp_size-8; 
int dispstart2 = notedisp_size-8; 
int dispend = notedisp_size-1;
int disprow;   
bool startMelody = false;

Tone notePlayer[2];

int row; 
int col; 
int OKidx;
long prevtime; 
long currtime; 

int noteIdx; 

long startTime;  

void setup() {
  // put your setup code here, to run once:
  for(int col = 0; col < 8; col++) {
    pinMode(columns[col], OUTPUT); 
    digitalWrite(columns[col], LOW); 
  }

  for(int row = 0; row < 8; row++) {
    pinMode(rows[row], OUTPUT); 
    digitalWrite(rows[row], HIGH); 
  }

  notePlayer[0].begin(8);
  notePlayer[1].begin(9);

  //pinMode(speakerPin, OUTPUT); 
  //noTone(speakerPin);
  startTime = millis(); 
}

void testloop() {
  for(int row = 0; row < 8; row++) {
    for(int col = 0; col < 8; col++) {
      digitalWrite(columns[col], HIGH); 
      digitalWrite(rows[row], LOW); 

      delay(100); 

      digitalWrite(columns[col], LOW); 
      digitalWrite(rows[row], HIGH); 
    }
  }
}

void TestLoop(PTCB tcb) {
  MOS_Continue(tcb);   

  while (1) { 
    for(row = 0; row < 8; row++) {
      for(col = 0; col < 8; col++) {
        digitalWrite(columns[col], HIGH); 
        digitalWrite(rows[row], LOW); 
  
        MOS_Delay(tcb, 100);
  
        digitalWrite(columns[col], LOW); 
        digitalWrite(rows[row], HIGH); 
      }
    }
  }
}

void displayNotes(PTCB tcb) {
  MOS_Continue(tcb);     
  prevtime = millis();  

  while (1) {  
    currtime = millis(); 
    disprow = 0; 
    
    if(dispstart2 >= 0) {
      if(currtime < prevtime + 120) {
        for(dispstart = dispstart2; dispstart < dispstart2 + 8; dispstart++) {
          
          uint16_t dispnote = pgm_read_word_near(note_display + dispstart); 
          
          //PORTD = note_display[dispstart];
          PORTD = dispnote; 
          if(disprow == 6) {
          
//            if(dispend == notedisp_size-8) {
//              if(!startMelody)
//                startMelody = true;
//            }
            PORTD = B11111111;
          }
          digitalWrite(rows[disprow], LOW); 
          
          MOS_Delay(tcb,1);  
          
          PORTD = 0;
          digitalWrite(rows[disprow], HIGH); 
          disprow++;
          
        }
      }
      
      else {
        dispstart2--;  
        dispstart--; 
        dispend--; 
        prevtime = currtime;
      } 
      
    }
    else { 
      for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
          digitalWrite(columns[col], HIGH); 
          digitalWrite(rows[row], LOW); 
    
          MOS_Delay(tcb, 50);
    
          digitalWrite(columns[col], LOW); 
          digitalWrite(rows[row], HIGH); 
        }
      }
      MOS_Break(tcb);
    }
  }
}

void ticker(PTCB tcb) {
  MOS_Continue(tcb);    
  while(1) {
    if(!startMelody && millis() >= startTime + 875) {
      startMelody = true;
    }
    else {
      MOS_Break(tcb);
    } 
  }
}

void PlayMelody1(PTCB tcb) {
  MOS_Continue(tcb);    
  bgidx= 0; 
  while (1) { 
    MOS_WaitForCond(tcb, startMelody);
    if(bgidx < bgnotes_size) {
      //int currnote = bgnotes[bgidx]; 
      uint16_t currnote = pgm_read_word_near(bgnotes + bgidx); 

      if(currnote > 0) {
        notePlayer[1].play(currnote);
      } else if (currnote == 0) {
        notePlayer[1].stop();
      }
      
      uint16_t dur = pgm_read_word_near(bgdur+ bgidx); 
      MOS_Delay(tcb, dur);
      notePlayer[1].stop();
      MOS_Delay(tcb,gapdur); 
      bgidx++;
    }
    else {
      MOS_Break(tcb);
    }
     
  }
}
void PlayMelody2(PTCB tcb) {
  MOS_Continue(tcb);   
  mainidx = 0; 

  while (1) {
    MOS_WaitForCond(tcb, startMelody);
    if(mainidx < mainnotes_size) {
      //int currnote = mainnotes[mainidx]; 
      uint16_t currnote = pgm_read_word_near(mainnotes + mainidx); 

      if(currnote > 0) {
        notePlayer[0].play(currnote);
      } else if (currnote == 0) {
        notePlayer[0].stop();
      }

      uint16_t dur = pgm_read_word_near(maindur+ mainidx); 
      MOS_Delay(tcb, dur);
      notePlayer[0].stop();
      MOS_Delay(tcb,gapdur); 
      
      mainidx++; 
    }

    else {
      MOS_Break(tcb);
    }
    
  } 
}


void loop() {
  //testloop();  
  MOS_Call(ticker); 
  MOS_Call(displayNotes);
  MOS_Call(PlayMelody1);
  MOS_Call(PlayMelody2);

}
