#include <esp_now.h>
#include <WiFi.h>

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

#define MAX_MOTOR_SPEED 250

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

#define SIGNAL_TIMEOUT 1000  // This is signal timeout in milli seconds. We will reset the data if no signal
unsigned long lastRecvTime = 0;

struct PacketData
{
  byte xAxisValue;
  byte yAxisValue;
  byte switchPressed;
};
PacketData receiverData;

bool throttleAndSteeringMode = false;

// callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info * mac, const uint8_t *incomingData, int len) 
{
  if (len == 0)
  {
    return;
  }
  memcpy(&receiverData, incomingData, sizeof(receiverData));
  String inputData ;
  inputData = inputData + "values " + receiverData.xAxisValue + "  " + receiverData.yAxisValue + "  " + receiverData.switchPressed;
  //Serial.println(inputData);
  simpleMovements();
  lastRecvTime = millis();   
}

void simpleMovements()
{
  if (receiverData.yAxisValue >= 175)       //Move car Forward
  {
    digitalWrite(MOTOR_B_DIR, LOW); // Direction = forward
    ledcWrite(MOTOR_B_PWM, MAX_MOTOR_SPEED); // Set PWM duty cycle

    digitalWrite(MOTOR_A_DIR, HIGH); // Direction = forward
    ledcWrite(MOTOR_A_PWM, 255-MAX_MOTOR_SPEED); // Set PWM duty cycle
  }
  else if (receiverData.yAxisValue <= 75)   //Move car Backward
  {
    digitalWrite(MOTOR_B_DIR, HIGH); // Direction = forward
    ledcWrite(MOTOR_B_PWM, 255-MAX_MOTOR_SPEED); // Set PWM duty cycle

    digitalWrite(MOTOR_A_DIR, LOW); // Direction = forward
    ledcWrite(MOTOR_A_PWM, MAX_MOTOR_SPEED); // Set PWM duty cycle
  }
  else if (receiverData.xAxisValue >= 175)  //Move car Right
  {
    digitalWrite(MOTOR_B_DIR, HIGH); // Direction = forward
    ledcWrite(MOTOR_B_PWM, 255-MAX_MOTOR_SPEED); // Set PWM duty cycle

    digitalWrite(MOTOR_A_DIR, HIGH); // Direction = forward
    ledcWrite(MOTOR_A_PWM, 255-MAX_MOTOR_SPEED); // Set PWM duty cycle
  }
  else if (receiverData.xAxisValue <= 75)   //Move car Left
  {
    digitalWrite(MOTOR_B_DIR, LOW); // Direction = forward
    ledcWrite(MOTOR_B_PWM, MAX_MOTOR_SPEED); // Set PWM duty cycle

    digitalWrite(MOTOR_A_DIR, LOW); // Direction = forward
    ledcWrite(MOTOR_A_PWM, MAX_MOTOR_SPEED); // Set PWM duty cycle
  }
  else                                      //Stop the car
  {
    turnOff();
  }   
}

void turnOff()
{
  digitalWrite(MOTOR_B_DIR, LOW); // Direction = forward
  ledcWrite(MOTOR_B_PWM, 0); // Set PWM duty cycle

  digitalWrite(MOTOR_A_DIR, LOW); // Direction = forward
  ledcWrite(MOTOR_A_PWM, 0); // Set PWM duty cycle
}

void setup() 
{
  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_B_DIR, OUTPUT);

  // Configure PWM channels
  ledcAttach(MOTOR_A_PWM, PWMFreq, PWMResolution); // 500 Hz 8 bits resolucion
  ledcAttach(MOTOR_B_PWM, PWMFreq, PWMResolution); // 500 Hz 8 bits resolucion
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() 
{
  //Check Signal lost.
  unsigned long now = millis();
  if ( now - lastRecvTime > SIGNAL_TIMEOUT ) 
  {
    turnOff();
  }
}
