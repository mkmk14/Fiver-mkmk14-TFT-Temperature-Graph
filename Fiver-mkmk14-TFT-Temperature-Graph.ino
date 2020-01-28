#include <OneWire.h>
#include <DallasTemperature.h>
#include <UTFT.h>
#include <URTouch.h>
#include <SPI.h>
#include <SD.h>


#define ONE_WIRE_BUS 9
#define SD_CS_Pin    53
#define sd_save_tim  60000L // save temperature vlaue on sd card every one mintue

#define scr_main 1
#define scr_lu   2
#define scr_ru   3
#define scr_ld   4
#define scr_rd   5

#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C

#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49

#define arlen 100

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
UTFT    myGLCD(ILI9341_16, 38, 39, 40, 41);
URTouch  myTouch( 6, 5, 4, 3, 2);


extern uint8_t SmallFont[];
extern uint8_t BigFont[];

boolean display1 = true;
boolean display2 = true;
boolean display3 = true;
boolean display4 = true;
double ox , oy ;
unsigned long tim_sd = 0;
unsigned long tim_temp = 0;
unsigned long tim_disp = 0;
unsigned long tim_gr = 0;
int deviceCount = 0;
int temp[4];
int screen = scr_main;
bool dr = true;
int x, y;


byte sen1[arlen];
byte sen2[arlen];
byte sen3[arlen];
byte sen4[arlen];


void setup(void)
{
  Serial.begin(9600);
  
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS_Pin)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  
  temp_init();
  fillZero();
  welcome();
  delay(1000);
  drawMain();

  tim_disp = millis();
  tim_temp = millis();
  tim_sd = millis();
  tim_gr = millis();
}

void loop()
{
  save_data();
  update_temp();
  switch (screen)
  {
    case scr_main:
      checkMainButton();
      prinMainTemp();
      break;

    case scr_lu:
      
      if (millis() - tim_gr > 16)
      {
        tim_gr = millis();
        graph_lu();
      }
      checkBackButton();
      break;

    case scr_ru:
      
      if (millis() - tim_gr > 16)
      {
        tim_gr = millis();
        graph_ru();
      }
      checkBackButton();
      break;

    case scr_ld:
      
      if (millis() - tim_gr > 16)
      {
        tim_gr = millis();
        graph_ld();
      }
      checkBackButton();
      break;

    case scr_rd:
      
      if (millis() - tim_gr > 16)
      {
        tim_gr = millis();
        graph_rd();
      }
      checkBackButton();
      break;
  }
}
