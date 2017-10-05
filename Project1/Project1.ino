#include <avr/io.h>
#include <Tone.h>
#include <MOS.h>
#include "pitches.h" 
#include "durations.h" 

// https://electronics.stackexchange.com/questions/67087/analogread0-or-analogreada0

int columns[] = {7,6,5,4,3,2,1,0}; 
int rows[] = {A0,A1,A2,A3,A4,A5,10,11}; 

// NOTES FOR BACKGROUND MUSIC
int bgnotes[] = {
  
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
int bgdur[] = {
  
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
int bgnotes_size = sizeof(bgnotes)/sizeof(int); 

// NOTES FOR PLAYER MUSIC
int mainnotes[] = {
  
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
int maindur[] = {
  
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
int mainnotes_size = sizeof(mainnotes)/sizeof(int); 

// gap between notes
int gapdur = 500-QUARTER; 



int speakerPin = A6; 

Tone notePlayer[2];

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

void PlayMelody1(PTCB tcb) {
  MOS_Continue(tcb);    
  bgidx= 0; 
  while (1) { 
    
    if(bgidx < bgnotes_size) {
      int currnote = bgnotes[bgidx]; 

      if(currnote > 0) {
        notePlayer[1].play(currnote);
      } else if (currnote == 0) {
        notePlayer[1].stop();
      }
      
      MOS_Delay(tcb, bgdur[bgidx]);
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
      int currnote = mainnotes[mainidx]; 

      if(currnote > 0) {
        notePlayer[0].play(currnote);
      } else if (currnote == 0) {
        notePlayer[0].stop();
      }
      
      MOS_Delay(tcb, maindur[mainidx]);
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
}
