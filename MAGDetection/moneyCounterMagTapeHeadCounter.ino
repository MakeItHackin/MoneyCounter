#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define INTERRUPT_PIN1 2
#define MAG_INPUT_PIN 10
#define GREEN_LED_PIN 7
#define RED_LED_PIN 8
#define YELLOW_LED_PIN 9
#define RESET_BUTTON 6

// Threshold values for bill validation
#define BILL_MISSING_MAX 110
#define BILL_VALID_MIN 120
#define BILL_VALID_MAX 300
#define BILL_INVALID_MIN 350

// Global variables
volatile unsigned long counter1 = 0; // Counter for interrupt pin
volatile unsigned long magCounter = 0; // Counter for magnetic sensor flags
volatile unsigned long lastInterruptTime1 = 0; // Last interrupt time for pin 2
volatile int pinValue = 4; // Variable to store the read value
int magValue = 0; // Variable to store magnetic sensor value
char formattedOutput[5]; // Array to hold formatted output

void setup() {
  // Initialize pin modes
  pinMode(MAG_INPUT_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(INTERRUPT_PIN1, INPUT);
  pinMode(RESET_BUTTON, INPUT_PULLUP);

  // Initialize LEDs to off state
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);

  // Attach interrupt to pin 2 to trigger on rising edge
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN1), handleInterrupt1, RISING);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Enter infinite loop if display initialization fails
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text color to white
  display.setTextColor(SSD1306_WHITE, BLACK);

  // Set cursor and print initial text
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("MAG COUNT");

  display.setCursor(0, 18);
  display.print("D: ");
  
  // Read initial magnetic sensor value
  magValue = (PINB & B00000100) >> 2;

  // Display the formatted magnetic sensor value
  display.setCursor(30, 18);
  display.print(magValue);

  display.setCursor(0, 34);
  display.print("BIL: ");
  
  display.setCursor(0, 50);
  display.print("MAG: ");
  
  display.display();
}

void loop() {
  int resetButtonReading = digitalRead(RESET_BUTTON);
  
  // Reset counter if reset button is pressed
  if (resetButtonReading == LOW) {
    counter1 = 0;
    magCounter = 0;
    delay(100);
  }

  // Read magnetic sensor value
  magValue = (PINB & B00000100) >> 2;

  // Display the formatted magnetic sensor value
  display.setCursor(30, 18);
  display.print(magValue);

  // Display counters
  display.setCursor(50, 34);
  display.print(counter1);
  display.print("    ");

  display.setCursor(50, 50);
  display.print(magCounter);
  display.print("    ");

  display.display();

}

void handleInterrupt1() {
  counter1++;
  // Loop and read pin 10 for 50 cycles with a 1 ms delay
  for (int i = 0; i < 50; i++) {
    pinValue = (PINB & B00000100) >> 2;  // Read bit 2 of Port B (pin 10)
    if (pinValue == 0) {  // If pin 10 goes low
      magCounter++;
      break;  // Exit the loop
    }
    delay(1);  // 1 ms delay
  }
}

void formatToFourDigits(int num, char* formattedOutput) {
  // Format the number as a 4-digit integer with leading zeros if necessary
  sprintf(formattedOutput, "%04d", num);
}
