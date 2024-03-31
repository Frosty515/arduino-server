enum Commands {
  COMMAND_INIT = 0xFF,
  COMMAND_WRITE = 0,
  COMMAND_READ = 1,
  COMMAND_CONFIG = 2,
  COMMAND_INVALID = 0xFE
};

enum Responses {
  RESPONSE_INIT = 0xFF,
  RESPONSE_SUCCESS = 0,
  RESPONSE_ERROR = 1,
  RESPONSE_ACK = 2
};

struct PinState {
  int mode;
  int value;
};

PinState pins[14];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (true) {
    while (!Serial.available()) {

    }
  
    byte b;
    Serial.readBytes(&b, 1);

    if (b == COMMAND_INIT) {
      Serial.write(RESPONSE_INIT);
      break;
    }
  }

  for (uint8_t i = 0; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    pins[i] = {OUTPUT, LOW};
  }
}

enum STATE {
  STATE_COMMAND,
  STATE_DATA0,
  STATE_DATA1
};

int state = STATE_COMMAND;
int command = COMMAND_INVALID;
int pin = 0xFF;
int value = LOW;
int mode = OUTPUT;


void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial.available()) {

  }

  byte b;

  Serial.readBytes(&b, 1);

  switch (state) {
  case STATE_COMMAND:
    switch (b) {
    case COMMAND_WRITE:
      state = STATE_DATA0;
      command = COMMAND_WRITE;
      Serial.write(RESPONSE_ACK);
      break;
    case COMMAND_READ:
      state = STATE_DATA0;
      command = COMMAND_READ;
      Serial.write(RESPONSE_ACK);
      break;
    case COMMAND_CONFIG:
      state = STATE_DATA0;
      command = COMMAND_CONFIG;
      Serial.write(RESPONSE_ACK);
      break;
    default:
      Serial.write(RESPONSE_ERROR);
      break;
    }
    break;
  case STATE_DATA0:
    switch (command) {
    case COMMAND_WRITE:
      pin = b;
      state = STATE_DATA1;
      Serial.write(RESPONSE_ACK);
      break;
    case COMMAND_READ: {
      pin = b;
      Serial.write(RESPONSE_ACK);
      if (pin > 13) {
        Serial.write(RESPONSE_ERROR);
        state = STATE_COMMAND;
        break;
      }
      if (pins[pin].mode == INPUT)
        pins[pin].value = digitalRead(pin);
      state = STATE_COMMAND;
      Serial.write(RESPONSE_SUCCESS);
      Serial.write(pins[pin].value == HIGH ? 1 : 0);
      break;
    }
    case COMMAND_CONFIG:
      pin = b;
      state = STATE_DATA1;
      Serial.write(RESPONSE_ACK);
      break;
    default:
      Serial.write(RESPONSE_ERROR);
      break;
    }
    break;

  case STATE_DATA1:
    switch (command) {
    case COMMAND_WRITE:
      value = b == 1 ? HIGH : LOW;
      Serial.write(RESPONSE_ACK);
      digitalWrite(pin, value);
      state = STATE_COMMAND;
      pins[pin].value = value;
      Serial.write(RESPONSE_SUCCESS);
      break;
    case COMMAND_CONFIG:
      mode = b == 1 ? OUTPUT : INPUT;
      Serial.write(RESPONSE_ACK);
      pinMode(pin, mode);
      state = STATE_COMMAND;
      pins[pin].mode = mode;
      Serial.write(RESPONSE_SUCCESS);
      break;
    }
    break;
  default:
    // we should never get here
    break;
  }
}
