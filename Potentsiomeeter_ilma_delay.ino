#define klemmLED1 42
#define klemmLED2 41
#define klemmLED3 40
#define klemmLED4 39
#define klemmLED5 38
#define klemmLED6 37
#define klemmLED7 36
#define klemmLED8 35
#define klemmlyliti 3
#define klemmpote1 10
#define var_off 0
#define var_on 1
#define moving_up 2
#define moving_down 3

#define muster_veerev 1
#define muster_sujuv 2
#define muster_jarsk 3

int viide = 10; 

int var_clamp(int muutuja)
{
  return max(0, min(muutuja, 255));
}

class POTE
{
  private:
    int* viitepointer;

  public:
    POTE(int pin, int *ptr);
    int klemm;
    void begin();
    int loe();
    void loedisk();
};

POTE::POTE(int pin, int *ptr)
{
  viitepointer = ptr;
  klemm = pin;
}

void POTE::begin()
{
  pinMode(klemm, INPUT);
}

int POTE::loe()
{
  return analogRead(klemm);
}

void POTE::loedisk()
{
  int lugem = analogRead(klemm);
  *viitepointer = map(lugem, 0, 1023, 2, 35);
}

class LED
{
  public:
    LED(int pin);
    int klemm;
    void begin();
    void on();
    void off();
    void update();
    void smooth_on_nodelay();
    void smooth_off_nodelay();

    unsigned long eelmineaeg = 0;
    unsigned long praeguneaeg = 0;
    int eredus = 0;
    int olek = var_off;
    bool blink = false;
};

LED::LED(int pin)
{
  klemm = pin;
}

void LED::begin()
{
  pinMode(klemm, OUTPUT);
  off();
  eelmineaeg = millis();
}

void LED::update()
{
  switch (olek)
  {
    case var_off:
      eredus = 0;
      analogWrite(klemm, 0);
      if (blink)
      {
        olek = moving_up;
        eelmineaeg = millis();
      }
      break;

    case var_on:
      eredus = 255;
      analogWrite(klemm, 255);
      if (blink)
      {
        olek = moving_down;
        eelmineaeg = millis();
      }
      break;

    case moving_up:
      smooth_on_nodelay();
      break;

    case moving_down:
      smooth_off_nodelay();
      break;
  }
}

void LED::on()
{
  blink = false;
  olek = var_on;
  eredus = 255;
  analogWrite(klemm, 255);
}

void LED::off()
{
  blink = false;
  olek = var_off;
  eredus = 0;
  analogWrite(klemm, 0);
}

void LED::smooth_on_nodelay()
{
  praeguneaeg = millis();
  if ((praeguneaeg - eelmineaeg) >= (unsigned long)viide)
  {
    eredus = var_clamp(eredus + 5);
    analogWrite(klemm, eredus);
    eelmineaeg = praeguneaeg;
  }

  if (eredus >= 255)
  {
    olek = var_on;
  }
}

void LED::smooth_off_nodelay()
{
  praeguneaeg = millis();
  if ((praeguneaeg - eelmineaeg) >= (unsigned long)viide)
  {
    eredus = var_clamp(eredus - 5);
    analogWrite(klemm, eredus);
    eelmineaeg = praeguneaeg;
  }

  if (eredus <= 0)
  {
    olek = var_off;
  }
}

LED ledid[] = {
  LED(klemmLED1),
  LED(klemmLED2),
  LED(klemmLED3),
  LED(klemmLED4),
  LED(klemmLED5),
  LED(klemmLED6),
  LED(klemmLED7),
  LED(klemmLED8)
};

const int ledideArv = sizeof(ledid) / sizeof(ledid[0]);
POTE pote1(klemmpote1, &viide);

int muster = muster_veerev;
int aktiivneLed = 0;
int suund = 1;
bool jarskOlek = false;
unsigned long eelmineSamm = 0;

bool eelmineLugem = HIGH;
bool lylitiOlek = HIGH;
unsigned long lylitiAeg = 0;
const unsigned long debounceAeg = 40;

void kustutaLedid()
{
  for (int i = 0; i < ledideArv; i++)
  {
    ledid[i].off();
  }
}

void valiMuster(int uusMuster)
{
  muster = uusMuster;
  kustutaLedid();
  eelmineSamm = millis();

  switch (muster)
  {
    case muster_veerev:
      aktiivneLed = 0;
      suund = 1;
      ledid[aktiivneLed].on();
      break;

    case muster_sujuv:
      for (int i = 0; i < ledideArv; i++)
      {
        ledid[i].blink = true;
      }
      break;

    case muster_jarsk:
      jarskOlek = false;
      break;
  }
}

bool lylitiVajutatud()
{
  bool lugem = digitalRead(klemmlyliti);

  if (lugem != eelmineLugem)
  {
    lylitiAeg = millis();
    eelmineLugem = lugem;
  }

  if ((millis() - lylitiAeg) > debounceAeg)
  {
    if (lugem != lylitiOlek)
    {
      lylitiOlek = lugem;
      return lylitiOlek == LOW;
    }
  }

  return false;
}

void uuendaVeerevMuster()
{
  unsigned long sammuViide = (unsigned long)viide * 12;

  if ((millis() - eelmineSamm) >= sammuViide)
  {
    ledid[aktiivneLed].off();

    if (aktiivneLed >= ledideArv - 1)
    {
      suund = -1;
    }
    else if (aktiivneLed <= 0)
    {
      suund = 1;
    }

    aktiivneLed = aktiivneLed + suund;
    ledid[aktiivneLed].on();
    eelmineSamm = millis();
  }
}

void uuendaSujuvMuster()
{
  for (int i = 0; i < ledideArv; i++)
  {
    ledid[i].blink = true;
    ledid[i].update();
  }
}

void uuendaJarskMuster()
{
  unsigned long vilkumiseViide = (unsigned long)viide * 20;

  if ((millis() - eelmineSamm) >= vilkumiseViide)
  {
    jarskOlek = !jarskOlek;

    for (int i = 0; i < ledideArv; i++)
    {
      if (jarskOlek)
      {
        ledid[i].on();
      }
      else
      {
        ledid[i].off();
      }
    }

    eelmineSamm = millis();
  }
}

void uuendaMuster()
{
  switch (muster)
  {
    case muster_veerev:
      uuendaVeerevMuster();
      break;

    case muster_sujuv:
      uuendaSujuvMuster();
      break;

    case muster_jarsk:
      uuendaJarskMuster();
      break;
  }
}

void setup()
{
  pinMode(klemmlyliti, INPUT_PULLUP);
  pote1.begin();

  for (int i = 0; i < ledideArv; i++)
  {
    ledid[i].begin();
  }

  valiMuster(muster_veerev);
}

void loop()
{
  pote1.loedisk();

  if (lylitiVajutatud())
  {
    int uusMuster = muster + 1;
    if (uusMuster > muster_jarsk)
    {
      uusMuster = muster_veerev;
    }
    valiMuster(uusMuster);
  }

  uuendaMuster();
}
