#define klemmLED1 42
#define klemmLED2 41
#define klemmLED3 40
#define klemmLED4 39
#define klemmLED5 38
#define klemmLED6 37
#define klemmLED7 36
#define klemmLED8 35

#define POT_PIN  4
#define POT_MIN  0
#define POT_MAX  4095

#define TOTAL_LEDS  8
#define PWM_MIN  0
#define PWM_MAX  255

#define SMOOTH_DELAY_MIN  1
#define SMOOTH_DELAY_MAX  12

#define DISCRETE_DELAY_MIN  1
#define DISCRETE_DELAY_MAX  15

enum SpeedMode
{
  SmoothMode,
  DiscreteMode
};

const SpeedMode SPEED_MODE = SmoothMode;

class LED
{
private:
  int pin;

public:
  LED(int ledPin)
  {
    pin = ledPin;
  }

  void begin()
  {
    pinMode(pin, OUTPUT);
    off();
  }

  void on()
  {
    digitalWrite(pin, HIGH);
  }

  void off()
  {
    digitalWrite(pin, LOW);
  }

  void setBrightness(int brightness)
  {
    analogWrite(pin, brightness);
  }

  void smoothOn(int stepDelay)
  {
    for (int brightness = PWM_MIN; brightness <= PWM_MAX; brightness++)
    {
      setBrightness(brightness);
      delay(stepDelay);
    }
  }

  void smoothOff(int stepDelay)
  {
    for (int brightness = PWM_MAX; brightness >= PWM_MIN; brightness--)
    {
      setBrightness(brightness);
      delay(stepDelay);
    }
  }

  void blinkSmooth(int stepDelay)
  {
    smoothOn(stepDelay);
    smoothOff(stepDelay);
  }
};

class Potentsiomeeter
{
private:
  int pin;

public:
  Potentsiomeeter(int potPin)
  {
    pin = potPin;
  }

  void begin()
  {
    pinMode(pin, INPUT);
  }

  int readValue()
  {
    int value = analogRead(pin);

    if (value < POT_MIN)
    {
      value = POT_MIN;
    }

    if (value > POT_MAX)
    {
      value = POT_MAX;
    }

    return value;
  }

  int smoothDelay()
  {
    int value = readValue();
    return map(value, POT_MIN, POT_MAX, SMOOTH_DELAY_MAX, SMOOTH_DELAY_MIN);
  }

  int discreteLevel()
  {
    int value = readValue();
    int level = map(value, POT_MIN, POT_MAX, 1, 9);

    if (level < 1)
    {
      level = 1;
    }

    if (level > 8)
    {
      level = 8;
    }

    return level;
  }

  int discreteDelay()
  {
    int level = discreteLevel();
    return map(level, 1, 8, DISCRETE_DELAY_MAX, DISCRETE_DELAY_MIN);
  }

  int currentDelay()
  {
    if (SPEED_MODE == SmoothMode)
    {
      return smoothDelay();
    }

    return discreteDelay();
  }
};

LED leds[TOTAL_LEDS] =
{
  LED(klemmLED1),
  LED(klemmLED2),
  LED(klemmLED3),
  LED(klemmLED4),
  LED(klemmLED5),
  LED(klemmLED6),
  LED(klemmLED7),
  LED(klemmLED8)
};

Potentsiomeeter pot(POT_PIN);

void setup()
{
  for (int led = 0; led < TOTAL_LEDS; led++)
  {
    leds[led].begin();
  }

  pot.begin();
}

void lightOneLed(int index)
{
  int stepDelay = pot.currentDelay();
  leds[index].blinkSmooth(stepDelay);
}

void rollForward()
{
  for (int i = 0; i < TOTAL_LEDS; i++)
  {
    lightOneLed(i);
  }
}

void rollBackward()
{
  for (int i = TOTAL_LEDS - 2; i > 0; i--)
  {
    lightOneLed(i);
  }
}

void loop()
{
  rollForward();
  rollBackward();
}
