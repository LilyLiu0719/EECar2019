#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 400
//#define RST_PIN      A0        // RFID resetpin
//#define SS_PIN       13       // RFID selection pin
//MFRC522 mfrc522(SS_PIN, RST_PIN);
//SoftwareSerial BT(4,2);   //bluetooth RX,TX

#define R2  A5  // Define Second Right Sensor Pin
#define R1  A4  // Define First Right Sensor Pin
#define M   A3  // Define Middle Sensor Pin
#define L1  A2  // Define First Left Sensor Pin
#define L2  A1  // Define Second Leftt Sensor Pin

#define IN1  12  //定義 I1 接腳（左）
#define IN2  13  //定義 I2 接腳（左）
#define IN3  8   //定義 I3 接腳（右）
#define IN4  7  //定義 I4 接腳（右）
#define ENA  11  //定義 ENA (PWM調速) 接腳
#define ENB  9  //定義 ENB (PWM調速) 接腳
const byte speed = 130;
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup() {
  // put your setup code here, to run once:
//  BT.begin(9600); //bluetooth initialization
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(R1, INPUT); 
  pinMode(R2, INPUT);
  pinMode(M,  INPUT);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
    
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}

void loop() {
  Tracking();
  //馬達電壓
//    analogWrite(ENA, speed);
//    analogWrite(ENB, speed);
    
    // 轉五秒 
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, LOW);
//    digitalWrite(IN3, HIGH);
//    digitalWrite(IN4, LOW);
    
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
//    delay(5000);
//    // 轉五秒 
//    digitalWrite(IN2, HIGH);
//    digitalWrite(IN1, LOW);
//    digitalWrite(IN4, HIGH);
//    digitalWrite(IN3, LOW);
//    delay(5000);
  
}

void MotorWriting(double vR, double vL) {
  if (vR >= 0) {
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, HIGH); //這邊的Motor第幾個對應到的High/Low是助教的車對應到的，請自己測試自己車該怎麼填!
  } 
  else if (vR < 0) {
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW);
    vR = -vR; //因為analogWrite只吃正數，所以如果本來是負數，就要乘-1
  }
  if (vL >= 0) {
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH); //這邊的Motor第幾個對應到的High/Low是助教的車對應到的，請自己測試自己車該怎麼填!
  } 
  else if (vL < 0) {
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
    vL = -vL; //因為analogWrite只吃正數，所以如果本來是負數，就要乘-1
  }
  analogWrite(ENA, vL);
  analogWrite(ENB, vR);
}
//
//void Tracking() {
//  int r1 = digitalRead(R1);
//  int r2 = digitalRead(R2);
//  int m = digitalRead(M);
//  int l2 = digitalRead(L2);
//  int l1 = digitalRead(L1);
//  if ((r1 == HIGH) && (r2 == LOW) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(-150, 250);    // big right turn
//  } 
//  else if ((r1 == HIGH) && (r2 == HIGH) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(-120, 250); // right turn
//  } 
//  else if ((r1 == HIGH) && (r2 == HIGH) && (m == HIGH) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(-50, 150);     // smaller right turn
//  } 
//  else if ((r1 == LOW) && (r2 == HIGH) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(50, 150);      // even smaller right turn
//  } 
//  else if ((r1 == LOW) && (r2 == HIGH) && (m == HIGH) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(100, 200);     // even smaller right turn
//  } 
//  else if ((r1 == LOW) && (r2 == HIGH) && (m == HIGH) && (l2 == HIGH) && (l1 == LOW)) {
//      MotorWriting(200, 200); // center
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == HIGH) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(200, 200);     // center
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == HIGH) && (l2 == HIGH) && (l1 == LOW)) {
//      MotorWriting(200, 100);     // even smaller left turn
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == HIGH) && (l1 == LOW)) {
//      MotorWriting(150, 50);      // even smaller left turn
//  }
//  else if ((r1 == LOW) && (r2 == LOW) && (m == HIGH) && (l2 == HIGH) && (l1 == HIGH)) {
//      MotorWriting(150, -50);     // smaller left turn
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == HIGH) && (l1 == HIGH)) {
//      MotorWriting(250, -120); // left turn
//} 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == LOW) && (l1 == HIGH)) {
//      MotorWriting(250, -150);    // big left turn
//  } 
//  else if ((r1 == LOW) && (r2 == LOW) && (m == LOW) && (l2 == LOW) && (l1 == LOW)) {
//      MotorWriting(50, 50);
//  } 
//  else {
//    MotorWriting(-60, -60);
//  }
// }




void Tracking(){
  int r1 = digitalRead(R1);
  int r2 = digitalRead(R2);
  int m = digitalRead(M);
  int l2 = digitalRead(L2);
  int l1 = digitalRead(L1);
  double error = 1*l1 + 0.5*l2 - 0.75*(l1 == l2) - 0.25*(m == l2)-(1*r1 + 0.5*r2 - 0.75*(r1 == r2) - 0.25*(m == r2)); //Total error from sensor outputs//其中，1、0.5、0.75、0.25都是權重係數，可以自己調整~
  double vR = 130 + 100*error;
  double vL = 130 - 100*error; //根據車身偏移量指數，調配MotorWriting需要的值，一樣可以自由調整數字及調配方式
  MotorWriting(int(vR),int(vL)); //Feedback to motors
  }


//////////////////////////// Blinking ////////////////////////////

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.





 
