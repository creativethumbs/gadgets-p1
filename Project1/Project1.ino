#include <avr/io.h>
#include <avr/pgmspace.h>
#include <Tone.h>
#include <MOS.h>
#include "pitches.h" 
#include "durations.h" 


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
int mainnotes_size = sizeof(mainnotes)/sizeof(uint16_t); 

// gap between notes, useful for when you're playing two of the same note in succession
int gapdur = 500-QUARTER;

// where the game level is stored
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

int dispstart = notedisp_size-8; 
// need redundant variable because of the specifics of how the scheduling functions work
int dispstart2 = notedisp_size-8; 
int disprow;   
bool startMelody = false;

Tone notePlayer[2];

int row; 
int col;  
long prevtime; 
long currtime; 

int noteIdx; 

long startTime;  

int L1 = B11000000; int L1pin = 12; 
int L2 = B00110000; int L2pin = 13; 
int R1 = B00001100; int R1pin = A6; 
int R2 = B00000011; int R2pin = A7; 

int playerNote = 0; 
int correctNote = false;

int score = 0; 
bool checkInput = false;

// demo mode: just plays the song 
bool demo = true;

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

  pinMode(L1pin, INPUT);
  pinMode(L2pin, INPUT);
  pinMode(R1pin, INPUT);
  pinMode(R2pin, INPUT);

  notePlayer[0].begin(8);
  notePlayer[1].begin(9);
 
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
      // notes fall at a fixed rate, which is this case is approximately the length of a 
      // sixteenth note (the smallest note unit for the whole song)
      // ideally it would be exactly the length of a sixteenth note, but I had to somehow account for the 
      // accumulated delay (line 869) that is a consequence of running the LED display
      if(currtime < prevtime + 120) {
        for(dispstart = dispstart2; dispstart < dispstart2 + 8; dispstart++) {
          
          uint16_t dispnote = pgm_read_word_near(note_display + dispstart);           
          PORTD = dispnote; 
          
          if(disprow == 6) { 
            playerNote = dispnote;
            
            if(!checkInput)
              checkInput = true;
              
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
    else if (!demo && startMelody && checkInput) {  
      bool L1val = digitalRead(L1pin) == HIGH; 
      bool L2val = digitalRead(L2pin) == HIGH; 
      bool R1val = digitalRead(R1pin) == HIGH; 
      bool R2val = digitalRead(R2pin) == HIGH; 

      switch(playerNote) {
        case B11000000:
          correctNote = L1val && (!L2val) && (!R1val) && (!R2val); 
          break;
        case B00110000:
          correctNote = L2val && (!L1val) && (!R1val) && (!R2val); 
          break;
        case B00001100:
          correctNote = R1val && (!L2val) && (!L1val) && (!R2val); 
          break;
        case B00000011:
          correctNote = R2val && (!L2val) && (!R1val) && (!L1val); 
          break;
        case B00000000:
          correctNote = (!R2val) && (!L2val) && (!R1val) && (!L1val); 
          break;
      }

      checkInput = false;
    }
    else {
       MOS_Break(tcb);
    }
  }
}

void BGMelody(PTCB tcb) {
  MOS_Continue(tcb);    
  bgidx= 0; 
  
  while (1) {  
    if(startMelody && bgidx < bgnotes_size) {
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
void PlayerMelody(PTCB tcb) {
  MOS_Continue(tcb);   
  mainidx = 0; 

  while (1) { 
    if(startMelody && mainidx < mainnotes_size) { 
      uint16_t currnote = pgm_read_word_near(mainnotes + mainidx); 

        if(currnote > 0) {
          if(demo || correctNote) {
            notePlayer[0].play(currnote);
            score++; 
          } else {
            notePlayer[0].stop(); 
          }
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
  MOS_Call(BGMelody);
  MOS_Call(PlayerMelody);

}
