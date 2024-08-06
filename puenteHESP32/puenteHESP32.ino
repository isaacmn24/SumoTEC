// Wired connections
#define HG7881_B_1A 36
#define HG7881_B_2A 16
#define HG7881_A_1A 6
#define HG7881_A_1B 5

// Functional connections
#define MOTOR_B_PWM HG7881_B_1A // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_2A // Motor B Direction
#define MOTOR_A_PWM HG7881_A_1A // Motor A PWM Speed
#define MOTOR_A_DIR HG7881_A_1B // Motor A Direction
 
// The actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 50  // Arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // Arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // Brief delay for abrupt motor changes
 
void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_B_DIR, OUTPUT);
  
  // Configure PWM channels
  ledcAttach(MOTOR_A_PWM, 500, 8); // 500 Hz 8 bits resolucion
  ledcAttach(MOTOR_B_PWM, 500, 8); // 500 Hz 8 bits resolucion

  // Set the motor speed and direction
  digitalWrite(MOTOR_A_DIR, HIGH); // Direction = forward
  digitalWrite(MOTOR_B_DIR, LOW); // Direction = backward

  // NO SE MUEVEN
  ledcWrite(MOTOR_A_PWM, 250); // Set PWM duty cycle
  ledcWrite(MOTOR_B_PWM, 0); // Set PWM duty cycle
}
 
void loop() {
  // Uncomment the following code to enable the menu for motor control via Serial Monitor
  
  /*
  boolean isValidInput;
  // Draw a menu on the serial port
  Serial.println("-----------------------------");
  Serial.println("MENU:");
  Serial.println("1) Fast forward");
  Serial.println("2) Forward");
  Serial.println("3) Soft stop (coast)");
  Serial.println("4) Reverse");
  Serial.println("5) Fast reverse");
  Serial.println("6) Hard stop (brake)");
  Serial.println("-----------------------------");
  do {
    byte c;
    // Get the next character from the serial port
    Serial.print("?");
    while (!Serial.available())
      ; // LOOP...
    c = Serial.read();
    // Execute the menu option based on the character received
    
    switch (c) {
      case '1': // 1) Fast forward
        Serial.println("Fast forward...");
        // Always stop motors briefly before abrupt changes
        digitalWrite(MOTOR_B_DIR, LOW);
        ledcWrite(0, 0);
        delay(DIR_DELAY);
        // Set the motor speed and direction
        digitalWrite(MOTOR_B_DIR, HIGH); // Direction = forward
        ledcWrite(0, 255 - PWM_FAST);
        isValidInput = true;
        break;      
         
      case '2': // 2) Forward      
        Serial.println("Forward...");
        // Always stop motors briefly before abrupt changes
        digitalWrite(MOTOR_B_DIR, LOW);
        ledcWrite(0, 0);
        delay(DIR_DELAY);
        // Set the motor speed and direction
        digitalWrite(MOTOR_B_DIR, HIGH); // Direction = forward
        ledcWrite(0, 255 - PWM_SLOW);
        isValidInput = true;
        break;      
         
      case '3': // 3) Soft stop (preferred)
        Serial.println("Soft stop (coast)...");
        digitalWrite(MOTOR_B_DIR, LOW);
        ledcWrite(0, 0);
        isValidInput = true;
        break;      
 
      case '4': // 4) Reverse
        Serial.println("Reverse...");
        // Always stop motors briefly before abrupt changes
        digitalWrite(MOTOR_B_DIR, LOW);
        ledcWrite(0, 0);
        delay(DIR_DELAY);
        // Set the motor speed and direction
        digitalWrite(MOTOR_B_DIR, LOW); // Direction = reverse
        ledcWrite(0, PWM_SLOW);
        isValidInput = true;
        break;      
         
      case '5': // 5) Fast reverse
        Serial.println("Fast reverse...");
        // Always stop motors briefly before abrupt changes
        digitalWrite(MOTOR_B_DIR, LOW);
        ledcWrite(0, 0);
        delay(DIR_DELAY);
        // Set the motor speed and direction
        digitalWrite(MOTOR_B_DIR, LOW); // Direction = reverse      
        ledcWrite(0, PWM_FAST);
        isValidInput = true;
        break;
         
      case '6': // 6) Hard stop (brake)
        Serial.println("Hard stop (brake)...");
        digitalWrite(MOTOR_B_DIR, HIGH);
        ledcWrite(0, 255);
        isValidInput = true;
        break;      
         
      default:
        // Wrong character! Display the menu again!
        isValidInput = false;
        break;
    }
  } while (isValidInput == true);
  */
  // Repeat the main loop and redraw the menu...
}
/*EOF*/
