#include <avr/io.h>
#include <Tone.h>
#include <MOS.h>
#include "pitches.h" 
#include "durations.h" 

// https://electronics.stackexchange.com/questions/67087/analogread0-or-analogreada0

int columns[] = {7,6,5,4,3,2,1,0}; 
int rows[] = {A0,A1,A2,A3,A4,A5,10,11}; 

// NOTES FOR BACKGROUND MUSIC
int bgnotes[] = {NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_FS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4, 
                NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, NOTE_CS4, NOTE_CS4, 0, NOTE_CS4, 
                NOTE_E4, NOTE_E4, 0, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_E4};
int bgdur[] = {EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, 
              EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH, EIGHTH};
int bgidx = 0; 
int bgstart = millis(); 
int bgwait = 0;  // gap between notes
int bgnotes_size = sizeof(bgnotes)/sizeof(int); 

// NOTES FOR PLAYER MUSIC
int mainnotes[] = {NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3, 
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
                NOTE_A2, NOTE_A2, NOTE_A2, NOTE_A2,
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
                NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3, 
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
                NOTE_A2, NOTE_A2, NOTE_A2, NOTE_A2,
                NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3}; 
int maindur[] = {QUARTER, QUARTER, QUARTER, QUARTER, 
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER, 
                QUARTER, QUARTER, QUARTER, QUARTER, 
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER,
                QUARTER, QUARTER, QUARTER, QUARTER};
int mainidx = 0; 
int mainstart = millis(); 
int mainwait = 0; // gap between notes
int mainnotes_size = sizeof(mainnotes)/sizeof(int); 

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

void write_O(bool inverse){

  for(int idx = 0; idx < letter_size; idx++) {
    PORTD = inverse? ~letter_O[idx] : letter_O[idx];
    digitalWrite(rows[idx], LOW); 
    
    delay(1); 
    
    PORTD = 0;
    digitalWrite(rows[idx], HIGH); 
  }
  
}

void write_K(bool inverse){
  for(int idx = 0; idx < letter_size; idx++) {
    PORTD = inverse? ~letter_K[idx] : letter_K[idx];
    digitalWrite(rows[idx], LOW); 
    
    delay(1); 
    
    PORTD = 0;
    digitalWrite(rows[idx], HIGH); 
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
  
/*
 * // custom timing code -- will still use MOS library for clarity
  int timenow = millis(); 
  if(bgwait == 0 && timenow < bgstart + bgdur[bgidx]) {
    if(bgnotes[bgidx] > 0)
      notePlayer[0].play(bgnotes[bgidx]); 
  }
  else if(bgwait == 0 && timenow >= bgstart + bgdur[bgidx]) {
    notePlayer[0].stop();
    bgwait = timenow; 
  }
  if(bgwait > 0 && timenow >= bgwait + gapdur) {
    if(bgidx < bgnotes_size-1) {
      bgstart = timenow; 
      bgwait = 0; 
      bgidx++; 
    }
  }

  
  if(mainwait == 0 && timenow < mainstart + maindur[mainidx]) {
    if(mainnotes[mainidx] > 0)
      notePlayer[1].play(mainnotes[mainidx]); 
  }
  else if(mainwait == 0 && timenow >= mainstart + maindur[mainidx]) {
    notePlayer[1].stop();
    mainwait = timenow; 
  }
  if(mainwait > 0 && timenow >= mainwait + gapdur) {
    if(mainidx < mainnotes_size-1) {
      mainstart = timenow; 
      mainwait = 0; 
      mainidx++; 
    }
  }  
  */
  /*
  else if (timenow < start+2000) {
    write_K(false); 
  } 

  else if(timenow < start+3000) {
    write_O(true); 
  }
  
  else if (timenow < start+4000) {
    write_K(true); 
  } 
  
  else if (timenow >= start+4000) {
    start = millis(); 
  }
  */
}
