/*
 * D&D Dice Roller
 * Name: Kay Chew
 * SN: 200367493

 */

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define SAMPLE_RATE 8000
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Dice_Roll.h"

int ledPin = 13;
int speakerPin = 11; // Can be either 3 or 11, two PWM outputs connected to Timer 2
volatile uint16_t sample;
byte lastSample;

const byte ROWS = 4; 
const byte COLS = 4; 

int lcdRow = 0;
int lcdCol = 0;
bool dice_val = false;
bool dice_amt = false;
bool dice_addsub = false;
const int dice_lim = 2;
char dice_char[dice_lim] = {'0', '0'};
char dice_amount[dice_lim] = {'0', '0'};
char dice_const[dice_lim] = {'0', '0'};
int dice_roll[10];
int total_roll = 0;
int array_count = 0;
int dice_set1 = 0;
int dice_set2 = 0;
int dice_set3 = 0;

char hexaKeys[ROWS][COLS] = {
  {'1', '4', '7', '+'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '-'},
  {'B', 'D', 'C', 'R'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal_I2C lcd(0x27, 16, 4);  

void stopPlayback()
{
    // Disable playback per-sample interrupt.
    TIMSK1 &= ~_BV(OCIE1A);

    // Disable the per-sample timer completely.
    TCCR1B &= ~_BV(CS10);

    // Disable the PWM timer.
    TCCR2B &= ~_BV(CS10);

    digitalWrite(speakerPin, LOW);
}

// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
    if (sample >= sounddata_length) {
        if (sample == sounddata_length + lastSample) {
            stopPlayback();
        }
        else {
            if(speakerPin==11){
                // Ramp down to zero to reduce the click at the end of playback.
                OCR2A = sounddata_length + lastSample - sample;
            } else {
                OCR2B = sounddata_length + lastSample - sample;                
            }
        }
    }
    else {
        if(speakerPin==11){
            OCR2A = pgm_read_byte(&sounddata_data[sample]);
        } else {
            OCR2B = pgm_read_byte(&sounddata_data[sample]);            
        }
    }

    ++sample;
}

void startPlayback()
{
    pinMode(speakerPin, OUTPUT);

    // Set up Timer 2 to do pulse width modulation on the speaker
    // pin.

    // Use internal clock (datasheet p.160)
    ASSR &= ~(_BV(EXCLK) | _BV(AS2));

    // Set fast PWM mode  (p.157)
    TCCR2A |= _BV(WGM21) | _BV(WGM20);
    TCCR2B &= ~_BV(WGM22);

    if(speakerPin==11){
        // Do non-inverting PWM on pin OC2A (p.155)
        // On the Arduino this is pin 11.
        TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
        TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
        // No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

        // Set initial pulse width to the first sample.
        OCR2A = pgm_read_byte(&sounddata_data[0]);
    } else {
        // Do non-inverting PWM on pin OC2B (p.155)
        // On the Arduino this is pin 3.
        TCCR2A = (TCCR2A | _BV(COM2B1)) & ~_BV(COM2B0);
        TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
        // No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

        // Set initial pulse width to the first sample.
        OCR2B = pgm_read_byte(&sounddata_data[0]);
    }
    // Set up Timer 1 to send a sample every interrupt.
    cli();

    // Set CTC mode (Clear Timer on Compare Match) (p.133)
    // Have to set OCR1A *after*, otherwise it gets reset to 0!
    TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
    TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

    // No prescaler (p.134)
    TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set the compare register (OCR1A).
    // OCR1A is a 16-bit register, so we have to do this with
    // interrupts disabled to be safe.
    OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 8000 = 2000

    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE1A);

    lastSample = pgm_read_byte(&sounddata_data[sounddata_length-1]);
    sample = 0;
    sei();
}


void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    randomSeed(analogRead(0));
    lcd.backlight();
    lcd.init(); 
    lcd.clear();
}

void loop()
{
 char customKey = customKeypad.getKey();
  if (customKey == 'B'){
    lcdRow++;
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print(' ');
  }
  if (customKey == 'C'){
    lcd.clear();
    lcdRow = 0;
    lcdCol = 0;
    array_count = 0;
    dice_val = false;
    dice_amt = false;
    dice_addsub = false;
    dice_char[0] = '0';
    dice_char[1] = '0';
    dice_amount[0] = '0';
    dice_amount[1] = '0';
    dice_const[0] = '0';
    dice_const[1] = '0';
    total_roll = 0;
    dice_set1 = 0;
    dice_set2 = 0;
    dice_set3 = 0;
  }
  if (customKey == 'D' && dice_val == false)
  {
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print(customKey);
    lcdRow++;
    dice_val = true;
    array_count = 0;
  }
  if ((customKey == '+' || customKey == '-') && dice_val == true){
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print(customKey);
    lcdRow++;
    dice_addsub = true;
    array_count = 0;
    
  }
  
  if (customKey && customKey != 'R' && customKey != 'D' && customKey != 'B' && customKey != 'C' && customKey != '+' && customKey != '-' && dice_val == false && dice_addsub == false){
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print(customKey);
    lcdRow++;
    dice_amount[array_count] = customKey;
    array_count++;
  }
  
  if (customKey && customKey != 'R' && customKey != 'D' && customKey != 'B' && customKey != 'C' && customKey != '+' && customKey != '-' && dice_val == true && dice_addsub == false){
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print(customKey);
    lcdRow++;
    dice_char[array_count] = customKey;
    array_count++;
  }
  
   if (customKey && customKey != 'R' && customKey != 'D' && customKey != 'B' && customKey != 'C' && customKey != '+' && customKey != '-' && dice_addsub == true){
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print(customKey);
    lcdRow++;
    dice_const[array_count] = customKey;
    array_count++;
  }


  if ((customKey == 'R') && dice_val == true){
    startPlayback();
    dice_set1 = ( 10 * (dice_amount[0] - '0' ) ) + dice_amount[1] - '0';
    dice_set2 = ( 10 * (dice_char[0] - '0' ) ) + dice_char[1] - '0';
    dice_set3 = ( 10 * (dice_const[0] - '0' ) ) + dice_const[1] - '0';

    if (dice_amount[1] == '0'){
      dice_set1 = (dice_set1 / 10);
    }
    if (dice_char[1] == '0' && dice_char[0] != '2'){
      dice_set2 = (dice_set2 / 10);
    }
    if (dice_const[1] == '0'){
      dice_set3 = (dice_set3 / 10);
    }
    array_count = 0;

    lcdRow = 0;
    lcdCol = 2;
    lcd.setCursor(lcdRow, lcdCol); 
    lcd.print("Roll = ");
    for (int i = 0; i < dice_set1; i++){
      dice_roll[i] = random(1, dice_set2);
      total_roll += dice_roll[i];
      lcd.print("(");
      lcd.print(dice_roll[i]);
      lcd.print(") ");
    }
    if (dice_set3 > 0){
      lcd.print("+ ");
      lcd.print(dice_set3);
    }

    total_roll += dice_set3;
    lcd.print(" = ");
    lcd.print(total_roll);
  }
  
}
