// Display Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED reset pin (not used)
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analog input pin for UV sensor
#define UV_INPUT_PIN A0

// LED pins
#define GREEN_LED_PIN 7
#define RED_LED_PIN 8
#define YELLOW_LED_PIN 9

// Threshold values for bill validation
#define BILL_MISSING_MAX 110
#define BILL_VALID_MIN 120
#define BILL_VALID_MAX 300
#define BILL_INVALID_MIN 350

int uvValue = 0; // Variable to store UV sensor value

char formattedOutput[5]; // Array to hold formatted output

void setup() {
  // Initialize pin modes
  pinMode(UV_INPUT_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  // Initialize LEDs to off state
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);

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
  display.print("UV TEST");

  display.setCursor(0, 18);
  display.print("A0: ");
  
  // Read initial UV sensor value
  uvValue = analogRead(UV_INPUT_PIN);

  // Format the UV sensor value
  formatToFourDigits(uvValue, formattedOutput);

  // Display the formatted UV sensor value
  display.setCursor(40, 18);
  display.print(formattedOutput);
  display.display();
}

void loop() {
  // Read UV sensor value
  uvValue = analogRead(UV_INPUT_PIN);

  // Format the UV sensor value
  formatToFourDigits(uvValue, formattedOutput);

  // Display the formatted UV sensor value
  display.setCursor(40, 18);
  display.print(formattedOutput);

  // Move cursor for status message
  display.setCursor(0, 50);

  // Check UV sensor value and control LEDs accordingly
  if (uvValue < BILL_MISSING_MAX) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    display.print("EMPTY   ");
  } 
  else if (uvValue > BILL_INVALID_MIN) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    display.print("FAKE    ");
  } 
  else if (uvValue > BILL_VALID_MIN && uvValue < BILL_VALID_MAX) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    display.print("REAL    ");
  } 
  else {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    display.print("        ");
  }

  // Update the display with the new content
  display.display();

  // Delay before next loop iteration
  delay(100); // Delay 100ms before printing again
}

void formatToFourDigits(int num, char* formattedOutput) {
  // Format the number as a 4-digit integer with leading zeros if necessary
  sprintf(formattedOutput, "%04d", num);
}
