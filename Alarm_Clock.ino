// NEXT: set _time, _alarm and _date


unsigned int count = 0;


// Write to data register of LCD
void lcd_data(unsigned char _data){
  PORTD = _data;
  PORTB |= (1<<PB0);                                  // RS = 1 passes info to data register
  PORTB &= (~(1<<PB1));                               // RW = 0 writes to LCD
  // enable and clear the enable pin of LCD
  PORTB |= (1<<PB2);    
  _delay_ms(10);
  PORTB &= (~(1<<PB2));
}

// Write to instruction register of LCD
void lcd_cmd(unsigned char cmd){
  PORTD = cmd;
  PORTB &= (~(1<<PB0));                               // RS = 0 passes info to instruction register
  PORTB &= (~(1<<PB1));                               // RW = 0 writes to LCD
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
  lcd_cmd(0x38);                                      // sets LCD in 16 by 2 format
  lcd_cmd(0x06);                                      // used to auto implement cursor of LCD
  lcd_cmd(0x0C);                                      // used to set display on and cursor off
  lcd_cmd(0x01);                                      // used to clear screen
}

// displays Menu
void first_menu_page(){
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("      MENU", 10);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("Display Time", 12);
}
void second_menu_page(){
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("      MENU", 10);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("Set Time", 8);
}
void third_menu_page(){
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("      MENU", 10);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("Set Alarm", 9);
}
void fourth_menu_page(){
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("      MENU", 10);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("Set Date", 8);
}


// displays the current time
/**
void display_time(){
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string(_time, 8);                               // Output time
  lcd_string(" | ", 3);
  if (_alarm = ""){
    lcd_string(" NO", 3);
  }else{
    lcd_string(_alarm, 5);                            // Output nearest alarm
  }
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string(_date, 8);                               // Output date
  lcd_string(" | ", 3);
  lcd_string("ALARM", 5);
}
**/

// sets the time
void set_time(){
  
}

// sets an alarm
void set_alarm(){
  
}

// sets the date
void set_date(){
  
}



void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;                                        // set LCD pins as output
  DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);          // set RS, RW and E pins as output
  DDRB &= (~(1<<DDB3)) & (~(1<<DDB4));                // set Menu and navigation pin as input
  DDRB &= (~(1<<DDB5)) & (~(1<<DDB6));                // set Enter and navigation pin as input 
  //activate internal pull-up resistor for Menu and navigation pin
  PORTB |= (1 << PORTB3) | (1 << PORTB4) | (1 << PORTB5) | (1 << PORTB6);
               
  lcd_initialise();

  // First run
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("  ALARM CLOCK", 13);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("    Welcome", 11);
  _delay_ms(1000);                                     // One second delay
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("Press M button", 14);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("for Menu.", 9);
  _delay_ms(1000);
  lcd_cmd(0x80);                                      // Cursor at first line
  lcd_string("Press -> button", 15);
  lcd_cmd(0xC0);                                      // Cursor at second line
  lcd_string("to navigate.", 12);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (PINB & (1<<PINB3)){
    first_menu_page();
    count = 1; 
  }
  if (PINB & (1<<PINB4) && count == 1){
      second_menu_page();
      count ++;
    }
    if (PINB & (1<<PINB4) && count == 2){
      third_menu_page();
      count ++;
    }
    if (PINB & (1<<PINB4) && count == 3){
      fourth_menu_page();
      count ++;
    }
    if (PINB & (1<<PINB4) && count == 4){
      first_menu_page();
      count = 1;
    }
    
}
