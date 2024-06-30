/*
 * 
 *  MONEY COUNTER PROJECT BY MAKEITHACKIN
 *  USED WITH RBC-1003 MONEY COUNTER
 * 
 */


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button pins
#define INTERRUPT_PIN1 2
#define INTERRUPT_PIN2 3
#define buttonDebounce 5
#define buttonDenomination 4
#define buttonReset 6

// Variables for counters and debounce
volatile unsigned long counter1 = 0; // Counter for pin 2
volatile unsigned long counter2 = 0; // Counter for pin 3
volatile unsigned long lastInterruptTime1 = 0; // Last interrupt time for pin 2
volatile unsigned long lastInterruptTime2 = 0; // Last interrupt time for pin 3
int DEBOUNCE_TIME = 0; // Debounce time in milliseconds

// Variables for currency handling
int currencyIndex = 0;
int currencies[] = {1, 2, 5, 10, 20, 50, 100};
int numCurrencies = sizeof(currencies) / sizeof(currencies[0]);

String currencyNames[] = {"ONES", "TWOS", "FIVES", "TENS", "TWENTIES", "FIFTIES", "HUNDREDS"};
int numCurrencyNames = sizeof(currencyNames) / sizeof(currencyNames[0]);

int totalValue = counter1 * currencies[currencyIndex]; // Initial total value

// Variables for display
String previousText = "";
int previousX = 0; // Track previous starting x position

void setup() {
  // Set pin modes
  pinMode(INTERRUPT_PIN1, INPUT);
  pinMode(INTERRUPT_PIN2, INPUT);
  pinMode(buttonDebounce, INPUT_PULLUP);
  pinMode(buttonDenomination, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);
  
  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN1), handleInterrupt1, RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN2), handleInterrupt2, RISING);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }
  display.clearDisplay();   
  display.setTextColor(SSD1306_WHITE, BLACK); // Draw white text
  display.setTextSize(2); // Normal 1:1 pixel scale
  display.setCursor(0, 0); // Start drawing at top-left corner
  display.print("$");
  display.display(); // Display the contents of the buffer
  
  // Display initial values
  cycleCurrency();
}

void loop() {
  // Read button states
  int buttonDebounceReading = digitalRead(buttonDebounce);
  int buttonDenominationReading = digitalRead(buttonDenomination);
  int buttonResetReading = digitalRead(buttonReset);

  // Handle button presses
  if (buttonDebounceReading == LOW) {
    DEBOUNCE_TIME++;
    if (DEBOUNCE_TIME > 99) {
      DEBOUNCE_TIME = 0;
    }
    delay(DEBOUNCE_TIME);
  }

  if (buttonDenominationReading == LOW) {
    currencyIndex += 1;
    cycleCurrency(); // Cycle to the next currency value
    delay(DEBOUNCE_TIME);
  }

  if (buttonResetReading == LOW) {
    counter1 = 0;
    counter2 = 0;
    delay(DEBOUNCE_TIME);
  }
  
  // Update total value and display
  totalValue = counter1 * currencies[currencyIndex]; // Recalculate totalValue
  String formattedNumber = formatCurrency(totalValue);
  displayRightJustified(formattedNumber); // Update display
  
  // Display counter values
  display.setCursor(40, 18);
  display.print(counter1);
  display.print("    ");
  display.setCursor(40, 34);
  display.print(counter2);
  display.print("    ");
  display.display();
}

void handleInterrupt1() {
  // Debounce logic for pin 2
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime1 > DEBOUNCE_TIME) {
    counter1++;
    lastInterruptTime1 = currentTime;
  }
}

void handleInterrupt2() {
  // Debounce logic for pin 3
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime2 > DEBOUNCE_TIME) {
    counter2++;
    lastInterruptTime2 = currentTime;
  }
}

void displayRightJustified(String text) {
  // Calculate number of spaces to clear based on previousText length
  int numSpaces = previousText.length() - text.length();
  
  // Clear the specific area with spaces starting from previousX
  display.setCursor(previousX, 0); // Ensure y coordinate is always zero
  for (int i = 0; i < numSpaces; i++) {
    display.print(" ");
  }

  // Calculate the position for right justification
  int x = SCREEN_WIDTH - text.length() * 12; // Adjusted for text size 2
  display.setCursor(x, 0); // Ensure y coordinate is always zero
  display.print(text);
  display.display();

  // Update previous text and x position
  previousText = text;
  previousX = x;
}

String formatCurrency(int number) {
  String numStr = String(number);
  String formattedStr = "";
  int len = numStr.length();
  int counter = 0;

  for (int i = len - 1; i >= 0; i--) {
    formattedStr = numStr[i] + formattedStr;
    counter++;
    if (counter == 3 && i != 0) {
      formattedStr = "," + formattedStr;
      counter = 0;
    }
  }
  return formattedStr;
}

void cycleCurrency() {
  // Cycle through currency values
  currencyIndex = (currencyIndex) % numCurrencies;
  int currencyNameIndex = currencyIndex;
  
  // Display updated currency name
  String currencyName = currencyNames[currencyNameIndex] + "          ";
  display.setCursor(0, 50); // Set y coordinate for currency name
  display.print(currencyName);
  display.display();
}
