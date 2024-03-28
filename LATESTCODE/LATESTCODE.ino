volatile bool flag = false;
volatile uint8_t sensorValue;
ISR(ADC_vect)
{
  sensorValue = ADCH;
  flag = true;
}

void motorSetup()
{
  DDRB |= (1<<7);
  DDRD |= 1;
  TCCR0A = 0b10100011;
  TCCR0B = 1;
}
const uint8_t ADC_BASE = (0<<REFS1)|(1<<REFS0)|(1<<ADLAR);
const uint8_t ADC_0 = 0;
const uint8_t ADC_1 =1;
const uint8_t ADC_4 = 100;
const uint8_t ADC_5 =101;
void ADCSetup()
{
  ADMUX = ADC_BASE | ADC_1;

  ADCSRA = (1<<ADEN) // enable ADC
          |(0<<ADATE)
          |(1<<ADIE)
          |(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
void setup() {
  // put your setup code here, to run once:
  motorSetup();
  ADCSetup();
  sei();
  Serial.begin(9600);
}
uint8_t  readSensor(uint8_t muxBits)
{
  ADMUX = ADC_BASE | muxBits;
  ADCSRA |= (1<<ADSC);
  while (flag == false)
  {

  }
  flag = false;
  return sensorValue; 
}
void loop() {
  uint8_t Sen0= readSensor(ADC_4);
  uint8_t Sen1= readSensor(ADC_5);
  // put your main code here, to run repeatedly:
  //OCR0A = readSensor(ADC_0);
  //OCR0B = readSensor(ADC_1);
  if (Sen0 >= 235 && Sen1 >= 235)
  {
    OCR0A = 0;
    OCR0B = 0;
  }
  else if (Sen0 <= 20 && Sen1 <= 20)
  {
    OCR0A = 255;
    OCR0B = 255;
  }
  else if (Sen0 <= 20 && Sen1 >= 235)
  {
    OCR0A = 255/2;
    OCR0B = 255;
  }
  else if (Sen1 <= 20 && Sen0 >= 235)
  {
    OCR0A = 255;
    OCR0B = 255/2;
  }
 Serial.print(Sen0);
 Serial.print(" ");
 Serial.println(Sen1);

}
