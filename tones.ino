/*
Copyright (c) 2019 Alan Vitullo, #MayTheForceBeWithYou 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

const int sp = 6;               //speaker
const int r_led = 9;            //red led
const int g_led = 10;           //green led
const int light_sensor = A0;    //photoresistor

//ISO Letter Notes
const char *letter_note [] = {"G#1","G#0","G#3","G#2","G#5","G#4","G#7","G#6","G7","G6","G5","G4","G3","G2","G1","G0","Eb4","Eb5","Eb6","Eb7",
"Eb0","Eb1","Eb2","Eb3","Eb8","D#8","E5","Db0","E7","E6","Db5","E0","B4","B5","B6","B7","B0","B1","B2","B3","Db6","F#0","F#1","F#2","F#3","F#4",
"F#5","F#6","F#7","Db8","Db1","E4","Db3","Db2","E1","Db4","E3","E2","A#3","A#2","A#1","A#0","A#7","A#6","A#5","A#4","Gb6","Gb7","Gb4","Gb5","Gb2",
"Gb3","Gb0","Gb1","C8","C3","C2","C1","C0","C7","C6","C5","C4","Bb7","Bb6","Bb5","Bb4","Bb3","Bb2","Bb1","Bb0","F0","F1","F2","F3","F4","F5","F6",
"F7","Db7","A1","A0","A3","A2","A5","A4","A7","A6","D#6","D#7","D#4","D#5","D#2","D#3","D#0","D#1","C#8","C#5","C#4","C#7","C#6","C#1","C#0",
"C#3","C#2","Ab0","Ab1","Ab2","Ab3","Ab4","Ab5","Ab6","Ab7","D8","D6","D7","D4","D5","D2","D3","D0","D1"};
//ISO Note Frequencies
const unsigned int note_frequency [] = {51,25,207,103,830,415,3322,1661,3135,1567,783,392,196,98,49,24,311,622,1244,2489,19,38,77,155,4978,4978,
659,17,2637,1318,554,20,493,987,1975,3951,30,61,123,246,1108,23,46,92,185,369,739,1479,2959,4434,34,329,138,69,41,277,164,82,233,116,58,29,3729,
1864,932,466,1479,2959,369,739,92,185,23,46,4186,130,65,32,16,2093,1046,523,261,3729,1864,932,466,233,116,58,29,21,43,87,174,349,698,1396,2793,
2217,55,27,220,110,880,440,3520,1760,1244,2489,311,622,77,155,19,38,4434,554,277,2217,1108,34,17,138,69,25,51,103,207,415,830,1661,3322,4698,
1174,2349,293,587,73,146,18,36};

//**************************************************************Binary Sunset*********************************************************************
//*********************************************************Encoding by Alan Vitullo***************************************************************
const char *song_notes [] = {"D4","G4","A4","A#4","C5","A#4","D4","D4","G4","A4","A#4","D4","A#4","G4","D5","C5","D4","G4","A4","A#4","D4","D5",
"G4","G5","G4","A#4","A4","G4","D5","A#4","G4","D4","D4","G4","A3","A3","F4","E4","D4","C4","C4","D4","E4","D4","A3","B3","G4","G4","A3","F4",
"E4","D4","C4","G4","D4","D4", "G3","A3","A3 F4","E4","D4","C4","C4","D4","E4","D4","A3","B3","G4","G4","C5","As4","G#4","G4","F4","D#4","D4",
"C4","G4","G4","G4","G4","G4","C3","F3","D3","C3","G3","F3","E3","D3","C5","G3","F3","E3","D3","C5","G3","F3","E3","F3","D3","C4","G4","F4","E4",
"D4","C5","G4","F4","E4","D4","C5 G4","F4","E4","F4","D4","G4","G4","C5"};
const double song_beats [] = {2.75, 2.0, 1.5, 0.25, 0.25, 1.25, 2.25, 0.75, 1.0, 0.75, 0.25, 0.25, 0.25, 0.25, 0.25, 2.25, 0.75, 0.5, 0.5, 
0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
const double song_bpm = 77;

void setup() {
  pinMode(sp, OUTPUT);
  pinMode(r_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(light_sensor, INPUT);
}

void loop() {
  
  double song_bps = song_bpm /60;
  for (int i = 0; i < (sizeof(song_notes) / sizeof(song_notes[0])); i++) {
    int light_amp = analogRead(light_sensor);
    light_amp = map(light_amp, 0, 1023, 0, 255);
    analogWrite(g_led, light_amp);
    analogWrite(r_led, (1023-light_amp));
    int current_note = frequency(song_notes[i]);
    double current_note_length = double(song_beats[i] * song_bps) *1000;
    tone(sp, current_note, current_note_length);
    pause(current_note_length);
  }
  
//replay after 5s
delay(5000);
}
void pause(double note_length) {
  delay(note_length/2.0);
  noTone(sp);
}

int frequency(char note[]){
  for (int i = 0; i < (sizeof(letter_note) / sizeof(letter_note[0])); i++) {
    if(note == letter_note[i]){
      return note_frequency[i];
    }
  }
}
