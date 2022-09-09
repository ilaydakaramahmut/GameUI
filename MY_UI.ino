
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define BUTTON_PIN_UP 8
#define BUTTON_PIN_SELECT 9
#define BUTTON_PIN_DOWN 10
#define BUTTON_PIN_BACK 11
#define BACKLIGHT_PIN 2

// Declare LCD object for SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

boolean backLight = true;
int contrastValue = 60; // Default Contrast Value

int displayItem = 1;
int displayPage = 1;

// --- UP DOWN SELECT BACK -- //
volatile boolean buttonStatusUp = false;
volatile boolean buttonStatusDown = false;
volatile boolean buttonStatusSelect = false;
volatile boolean buttonStatusBack = false;

// --- READ -- //
int readButtonDown = 0;
int readButtonUp = 0;
int readButtonSelect = 0;
int readButtonBack = 0;

// --- CHECK -- //
int lastButtonStateDown = 0;
int lastButtonStateUp = 0;
int lastButtonStateSelect = 0;
int lastButtonStateBack = 0;

void setup() {
 
  pinMode(BUTTON_PIN_DOWN, INPUT);
  pinMode(BUTTON_PIN_UP, INPUT);
  pinMode(BUTTON_PIN_SELECT, INPUT);
  pinMode(BUTTON_PIN_BACK, INPUT);
  pinMode(BACKLIGHT_PIN, OUTPUT);

  digitalWrite(BACKLIGHT_PIN, HIGH); //Turn Backlight ON

  display.begin();
  display.setContrast(contrastValue); //Set contrast to 60
  display.clearDisplay();
  display.display();

  Serial.begin(9600);

}

void loop() {
  displayMenu();

  readButtonDown = digitalRead(BUTTON_PIN_DOWN);
  readButtonUp = digitalRead(BUTTON_PIN_UP);
  readButtonSelect = digitalRead(BUTTON_PIN_SELECT);
  readButtonBack = digitalRead(BUTTON_PIN_BACK);

  checkButtons();

  displayPages();
  statusSelect();
}

void checkButtonPressDown() {
  if (readButtonDown != lastButtonStateDown) {
    if (readButtonDown == 0) {
      buttonStatusDown = true;
    }
    delay(50);
  }
  lastButtonStateDown = readButtonDown;
}

void checkButtonPressUp() {
  if (readButtonUp != lastButtonStateUp) {
    if (readButtonUp == 0) {
      buttonStatusUp = true;
    }
    delay(50);
  }
  lastButtonStateUp = readButtonUp;
}

void checkButtonPressSelect() {
  if (readButtonSelect != lastButtonStateSelect) {
    if (readButtonSelect == 0) {
      buttonStatusSelect = true;
    }
    delay(50);
  }
  lastButtonStateSelect = readButtonSelect;
}

void checkButtonPressBack() {
  if (readButtonBack != lastButtonStateBack) {
    if (readButtonBack == 0) {
      buttonStatusBack = true;
    }
    delay(50);
  }
  lastButtonStateBack = readButtonBack;
}


void displayMenu()
{

  if (displayPage == 1) {

    // ---- INSIDE ---- //
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(25, 0);
    display.print("INSIDE");
    display.drawFastHLine(0, 10, 83, BLACK);


    // ---- NEW GAME ---- //
    if (displayItem == 1) {
      display.setTextColor(WHITE, BLACK);
    }
    else {
      display.setTextColor(BLACK, WHITE);
    }

    display.setCursor(0, 15);
    display.print(">NEW GAME");


    // ---- LOAD GAME ---- //
    if (displayItem == 2) {
      display.setTextColor(WHITE, BLACK);
    }
    else {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 25);
    display.print(">LOAD GAME");


    // ---- SETTINGS ---- //
    if (displayItem == 3) {
      display.setTextColor(WHITE, BLACK);
    }
    else {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 35);
    display.print(">SETTINGS");
    display.display();
  }


  // ---- SETTINGS INTERFACE---- //
  else if (displayPage == 4) {
    display.clearDisplay();

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(8, 0);
    display.print("SETTINGS");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);

    if (displayItem = 4) {
      display.setTextColor(WHITE, BLACK);

      if (backLight) {
        display.print("BACKLIGHT:");
        display.print("ON");
      }
      else {
        display.print("BACKLIGHT:");
        display.print("OFF");
      }

    } else {
      display.setTextColor(BLACK, WHITE);
    }

//
//    if (displayItem = 5) {
//      display.setTextColor(WHITE, BLACK);
//      display.setCursor(0, 24);
//      display.print("CONTRAST:");
//      display.print(contrastValue);
//    }
//    else {
//      display.setTextColor(BLACK, WHITE);
//      display.setCursor(0, 24);
//      display.print("CONTRAST:");
//      display.print(contrastValue);
//    }

    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 24);
    display.print("CONTRAST:");
    display.print(contrastValue);

    display.display();
  }
}

void displayPages() {

  if (displayPage == 1 && buttonStatusUp)
  {
    buttonStatusUp = false;
    displayItem--;
    if (displayItem == 0)//if you are on NEW GAME when you press up your cursor will be on SETTINGS
    {
      displayItem = 3;
    }
  }

  if (displayPage == 1 && buttonStatusDown)
  {
    buttonStatusDown = false;
    displayItem++;
    if (displayItem == 4)//if you are on SETTINGS when you press up your cursor will be on NEW GAME
    {
      displayItem = 1;
    }
  }

  else if (displayPage == 4 && buttonStatusDown)
  {
    buttonStatusDown = false;
    //BACKLIGHT
  }

  else if (displayPage == 2 && buttonStatusBack) {
    buttonStatusBack = false;
    //TURN BACK TO MENU
    displayPage = 1;
    displayItem = 1;
  }

  else if (displayPage == 3 && buttonStatusBack) {
    buttonStatusBack = false;
    //TURN BACK TO MENU
    displayPage = 1;
    displayItem = 1;
  }

  else if (displayPage == 4 && buttonStatusBack) {
    buttonStatusBack = false;
    //TURN BACK TO MENU
    displayPage = 1;
    displayItem = 1;
  }
}

void statusSelect() {

  if (buttonStatusSelect) {
    buttonStatusSelect = false;

    if (displayPage == 1 && displayItem == 1) {
      //NEW GAME
      displayPage = 2;
    }

    if (displayPage == 1 && displayItem == 2) {
      //LOAD GAME
      displayPage = 3;
    }

    if (displayPage == 1 && displayItem == 3)
    {
      displayPage = 4;
    }

    if (displayPage == 2) {
      newGame();
    }


    if (displayPage == 3) {
      loadGame();
    }

    if (displayPage == 4 && displayItem == 4) {
      if (backLight) {
        backLight = false;
        turnBacklightOff();
      }
      else {
        backLight = true;
        turnBacklightOn();
      }
    }

    if (displayPage == 4 && displayItem == 5) {
      setContrast();
    }

  }
}

void turnBacklightOn()
{
  digitalWrite(BACKLIGHT_PIN, HIGH);
}

void turnBacklightOff()
{
  digitalWrite(BACKLIGHT_PIN, LOW);
}


void setContrast()
{
  display.setContrast(contrastValue);
  display.display();
}


void newGame() {
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(8, 0);
  display.print("NEW GAME");
  display.drawFastHLine(0, 10, 83, BLACK);
  display.display();

}

void loadGame() {
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(8, 0);
  display.print("LOAD GAME");
  display.drawFastHLine(0, 10, 83, BLACK);
  display.display();

}

void settingsMenu() {

  if (displayItem == 4 && buttonStatusDown) {
    buttonStatusDown = false;
    displayItem++;
  }

}

void checkButtons() {
  checkButtonPressDown();
  checkButtonPressUp();
  checkButtonPressSelect();
  checkButtonPressBack();
}
