
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AudioAnalyzer.h>

#include <Fonts/Org_01.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define StrobePin GPIO_NUM_14
#define ResetPin GPIO_NUM_13
#define InputPin GPIO_NUM_12

#define StrobePin1 GPIO_NUM_15
#define ResetPin1 GPIO_NUM_4
#define InputPin1 GPIO_NUM_2


#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Analyzer Audio = Analyzer(StrobePin, ResetPin, InputPin);
Analyzer Audio1 = Analyzer(StrobePin1, ResetPin1, InputPin1);

byte audio_bar_height[7];
byte audio_bar_peak[7];

int freqVal[7];
int freqVal1[7];

byte audio_bar_height1[7];
byte audio_bar_peak1[7];


void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }else{
    Serial.println("DISPLAY 0 CONNECTED!");
  }

  if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  } else{
    Serial.println("DISPLAY 1 CONNECTED!");
  }

  Audio.Init();
  Audio1.Init();
}


void analyze1(){
  Audio1.ReadFreq(freqVal1);
  display1.clearDisplay();

  for (int i=0; i<7; i++) {
    
    audio_bar_height1 [i] = map(max((freqVal1 [i]-100), 0) , 0, 1024, 0, 53);
    if(audio_bar_peak1[i]<audio_bar_height1[i]){
      audio_bar_peak1[i]=audio_bar_height1[i];
    } else if(audio_bar_peak1[i]>audio_bar_height1[i]){
      audio_bar_peak1[i]--;
    }


    display1.fillRect(2 + i*19,53-audio_bar_height1[i], 10, audio_bar_height1[i], SSD1306_WHITE);
    display1.fillRect(2 + i*19,53-audio_bar_peak1[i], 10, 1, SSD1306_WHITE);

  }

  display1.setFont(&Org_01);
  display1.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);

  display1.setCursor(1, 62);
  display1.print("63");

  display1.setCursor(19, 62);
  display1.print("160");

  display1.setCursor(36, 62);
  display1.print("400");

  display1.setCursor(61, 62);
  display1.print("1k");

  display1.setCursor(75, 62);
  display1.print("2.5k");

  display1.setCursor(95, 62);
  display1.print("6.3k");

  display1.setCursor(116, 62);
  display1.print("16k");

  display1.display();
}

void analyze(){

  Audio.ReadFreq(freqVal);
  display.clearDisplay();

  for (int i=0; i<7; i++) {
    audio_bar_height [i] = map(max((freqVal [i]-100), 0) , 0, 1024, 0, 53);
    if(audio_bar_peak[i]<audio_bar_height[i]){
      audio_bar_peak[i]=audio_bar_height[i];
    } else if(audio_bar_peak[i]>audio_bar_height[i]){
      audio_bar_peak[i]--;
    }


    display.fillRect(2 + i*19,53-audio_bar_height[i], 10, audio_bar_height[i], SSD1306_WHITE);
    display.fillRect(2 + i*19,53-audio_bar_peak[i], 10, 1, SSD1306_WHITE);

  }

  display.setFont(&Org_01);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(1, 62);
  display.print("63");

  display.setCursor(19, 62);
  display.print("160");

  display.setCursor(36, 62);
  display.print("400");

  display.setCursor(61, 62);
  display.print("1k");

  display.setCursor(75, 62);
  display.print("2.5k");

  display.setCursor(95, 62);
  display.print("6.3k");

  display.setCursor(116, 62);
  display.print("16k");

  display.display();
}

void loop() {

  analyze();
  analyze1();
  

}

