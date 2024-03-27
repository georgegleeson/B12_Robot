void setup() {
  // put your setup code here, to run once:
  DDRB |= (1<<7); // set port b pin 7 as a direction
  DDRD |= (1<<0); // set port d pin 0 as a direction (output)
  PORTE |= (1<<6);

  TCCR0A = (1<<COM0A1)|(0<<COM0A0)
          |(1<<COM0B1)|(0<<COM0B0)
          |(1<<WGM01)|(1<<WGM00);
  TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
  

}

void drive_straight()
{
  OCR0A = 0.3*255;
  OCR0B = 0.  *255;
  _delay_ms(2000);
}
void turn_around()
{
  OCR0A = 0*255;
  OCR0B = 0.63*255;
  _delay_ms(500);
}
void stop()
{
  OCR0A = 0*255;
  OCR0B = 0*255;
  _delay_ms(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  drive_straight();
  stop();
  turn_around();
  stop();
  drive_straight();
  stop();
  turn_around();
  stop();
  drive_straight();
  stop();
  
  
  while(1);
  


}
