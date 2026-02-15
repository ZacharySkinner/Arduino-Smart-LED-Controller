// Board: Arduino Mega (DATA_PIN = 31)
// LEDs: ~900x WS2812B (external 5V supply required)
// Notes:
//  - Shared ground between Arduino and LED power supply
//  - Power injection recommended every ~250 LEDs
//  - Series resistor on data line recommended (220–470Ω)

#include <FastLED.h>
#include <IRremote.h> 

//ir definition
#define IR_RECEIVE_PIN      2
#define ENABLE_LED_FEEDBACK true

//led definitions
#define DATA_PIN    31
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    894
CRGB leds[NUM_LEDS];
uint8_t gHue = 0; 
int state = 0;
int lastChangeTime = 0;

int BRIGHTNESS = 15;
void setup() {
  Serial.begin(115200);

  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fullWhite();

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  lastChangeTime = millis();
  
}

void loop() {
  //Serial.println(state);
  if (IrReceiver.decode()) { 
        //Serial.println(IrReceiver.decodedIRData.decodedRawData);
        //Serial.println("HIIIIIIIIIIIIIIIIIII");
        IrReceiver.resume();
        if (IrReceiver.decodedIRData.decodedRawData == 0xB946FF00){
          //Up Arrow
          BRIGHTNESS = constrain(BRIGHTNESS + 10, 0, 255);
          FastLED.setBrightness(BRIGHTNESS);
          FastLED.show();
          Serial.println(BRIGHTNESS);
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xEA15FF00) {
          //Down Arrow
          BRIGHTNESS = constrain(BRIGHTNESS - 10, 0, 255);
          FastLED.setBrightness(BRIGHTNESS);
          FastLED.show();
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xBB44FF00) {
          //LeftArrow

        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xBC43FF00) {
          //RightArrow

        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xBF40FF00) {
        //Power/OK  

          if (BRIGHTNESS == 0){
            BRIGHTNESS =255;
            FastLED.setBrightness(BRIGHTNESS);
            FastLED.show();
          }
          else {
            BRIGHTNESS =0;
            FastLED.setBrightness(BRIGHTNESS);
            FastLED.show();
          }
          state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xE916FF00) {
            // 1
            fullWhite();
            state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xE619FF00) {
            // 2
            fullGreen();
            state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00) {
            // 3
            fullPurple();
            state = 0;
        }        
        else if (IrReceiver.decodedIRData.decodedRawData == 0xF30CFF00) {
            // 4
            fullBlue();
            state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xE718FF00) {
            // 5
            fullCyan();
            state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xA15EFF00) {
            // 6
            fullRed();
            state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xF708FF00) {
            // 7
            fullYellow();
            Serial.println("state");
            state = 0;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xE31CFF00) {
            // 8
            bpm();
            state = 1;
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xA55AFF00) {
            // 9
            
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00) {
            // 0
            
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xBD42FF00) {
            // *
            
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xB54AFF00) {
            // #
            
        }                
  }
  else if ((state == 1) //&&(millis()-lastChangeTime>100)
  ){
    EVERY_N_MILLISECONDS(100){
  bpm();
  lastChangeTime = millis();
  }}
}


void fullWhite()
{
  fill_solid(leds,NUM_LEDS,CRGB::White);
  FastLED.show();
}
void fullGreen()
{
  fill_solid(leds,NUM_LEDS,CRGB::Green);
  FastLED.show();
}
void fullPurple()
{
  fill_solid(leds,NUM_LEDS,CRGB::Purple);
  FastLED.show();
}
void fullBlue()
{
  fill_solid(leds,NUM_LEDS,CRGB::Blue);
  FastLED.show();
}
void fullYellow()
{
  fill_solid(leds,NUM_LEDS,CRGB::Yellow);
  FastLED.show();
}
void fullRed()
{
  fill_solid(leds,NUM_LEDS,CRGB::Red);
  FastLED.show();
  
}
void fullCyan()
{
  fill_solid(leds,NUM_LEDS,CRGB::Cyan);
  FastLED.show();
}
void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
  FastLED.show();
  //FastLED.delay(1000/120);
}