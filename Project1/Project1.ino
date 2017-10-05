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


int letter_O[] = {B01111110, 
                  B11100111, 
                  B11000011, 
                  B11000011, 
                  B11000011, 
                  B11000011, 
                  B11100111,
                  B01111110};

int letter_K[] = {B01100011, 
                  B01100110, 
                  B01101100, 
                  B01111000, 
                  B01101100, 
                  B01100110, 
                  B01100011, 
                  B01100001};

int letter_size = sizeof(letter_O)/sizeof(int); 

Tone notePlayer[2];

int row; 
int col; 
int OKidx;
int prevtime; 
int currtime; 

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

void write_OK(PTCB tcb) {
  MOS_Continue(tcb);  
  prevtime = millis(); 
  
  while (1) {
    currtime = millis(); 
    if(currtime < prevtime +1000) {
      for(OKidx = 0; OKidx < letter_size; OKidx++) {
        PORTD = letter_O[OKidx];
        digitalWrite(rows[OKidx], LOW); 
        
        MOS_Delay(tcb,1); 
        
        PORTD = 0;
        digitalWrite(rows[OKidx], HIGH); 
      }
    }

    else if(currtime >= prevtime+2000) {
      prevtime = currtime;
    }

    else if(currtime >= prevtime +1000) {
    
      for(OKidx = 0; OKidx < letter_size; OKidx++) {
        PORTD = letter_K[OKidx];
        digitalWrite(rows[OKidx], LOW); 
        
        MOS_Delay(tcb,1); 
        
        PORTD = 0;
        digitalWrite(rows[OKidx], HIGH); 
      }
    }

    
  }

} 

void PlayMelody1(PTCB tcb) {
  MOS_Continue(tcb);    
  bgidx= 0; 
  while (1) { 
    
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
     
  }
}
void PlayMelody2(PTCB tcb) {
  MOS_Continue(tcb);   
  mainidx = 0; 
  bool done = false;
  while (1) {
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
    
  } 
}


void loop() {
  //testloop();  
  MOS_Call(PlayMelody1);
  MOS_Call(PlayMelody2);
  MOS_Call(write_OK);
}
