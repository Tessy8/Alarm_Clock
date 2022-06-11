// Write to data register of LCD
void lcd_data(unsigned char _data){
  PORTD = _data;
  PORTB |= (1<<PB0);    // RS = 1 passes info to data register
  PORTB &= (~(1<<PB1));  // RW = 0 writes to LCD
  // enable and clear the enable pin of LCD
  PORTB |= (1<<PB2);    
  _delay_ms(10);
  PORTB &= (~(1<<PB2));
}

// Write to instruction register of LCD
void lcd_cmd(unsigned char cmd){
  PORTD = cmd;
  PORTB &= (~(1<<PB0));  // RS = 0 passes info to instruction register
  PORTB &= (~(1<<PB1));  // RW = 0 writes to LCD
  // enable and clear the enable pin of LCD
  PORTB |= (1<<PB2);
  _delay_ms(10);
  PORTB &= (~(1<<PB2));
}

// prints a string
void lcd_string(const unsigned char *str, unsigned char len){
  char i = 0;
  for (i=0; i<len; i++){
    lcd_data(str[i]);
  }
}

// initialises the LCD
void lcd_initialise(){
  lcd_cmd(0x38);   // sets LCD in 16 by 2 format
  lcd_cmd(0x06);   // used to auto implement cursor of LCD
  lcd_cmd(0x0C);   // used to set display on and cursor off
  lcd_cmd(0x01);   // used to clear screen
}



void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
  lcd_initialise();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd_cmd(0x80);  // Cursor at first line
  lcd_string("ALARM CLOCK", 11);
  lcd_cmd(0xC0);  // Cursor at second line
  lcd_string("Welcome", 7);
}
