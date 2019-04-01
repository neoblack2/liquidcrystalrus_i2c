#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

static byte addon_letters[16];      //для русских букв

void setup() {
  
  lcd.init();
  lcd.backlight();
   
  init_rus("ПИУИЪЫДЖ");  // добавляем пользовательские русские буквы (8 штук макс)
  
  print_rus(0,0,"ПРИВЕТ МИР !");
  print_rus(0,1,"ЖИВИ ДРУЖНО!");
  delay(3000); 
  lcd.clear();

  init_rus("ФЗПЛХЖИЙ");  // возможна переинициализация на другие 8 символов
  
  print_rus(0,0,"ПОЛЕТ !");
  print_rus(0,1,"ФАНТАЗИЙ!");
 
}

void loop() {
  
}

void init_rus(const char* letters_use ) { // процедура вывода русских букв
  
  static byte letters[][8]   = {
{ B11111, B10000, B10000, B11111, B10001, B10001, B11111, B00000 },//Б
{ B11111, B10000, B10000, B10000, B10000, B10000, B10000, B00000 },//Г
{ B01111, B01001, B01001, B01001, B01001, B11111, B10001, B00000 },//Д
{ B10101, B10101, B10101, B01110, B10101, B10101, B10101, B00000 },//Ж
{ B01110, B10001, B00001, B00110, B00001, B10001, B01110, B00000 },//З
{ B10001, B10001, B10011, B10101, B11001, B10001, B10001, B00000 },//И
{ B10101, B10101, B10011, B10101, B11001, B10001, B10001, B00000 },//Й
{ B00111, B01001, B10001, B10001, B10001, B10001, B10001, B00000 },//Л
{ B11111, B10001, B10001, B10001, B10001, B10001, B10001, B00000 },//П
{ B10001, B10001, B10001, B01111, B00001, B10001, B01110, B00000 },//У
{ B01110, B10101, B10101, B10101, B01110, B00100, B00100, B00000 },//Ф
{ B10001, B10001, B10001, B10001, B10001, B10001, B11111, B00001 },//Ц
{ B10001, B10001, B10001, B01111, B00001, B00001, B00001, B00000 },//Ч
{ B10101, B10101, B10101, B10101, B10101, B10101, B11111, B00000 },//Ш
{ B10101, B10101, B10101, B10101, B10101, B10101, B11111, B00001 },//Щ
{ B10000, B10000, B10000, B11110, B10001, B10001, B11110, B00000 },//Ь
{ B11000, B01000, B01110, B01001, B01001, B01001, B01110, B00000 },//Ъ
{ B10001, B10001, B10001, B11101, B10101, B10101, B11101, B00000 },//Ы
{ B11110, B00001, B00001, B01111, B00001, B00001, B11110, B00000 },//Э
{ B00000, B00000, B10001, B11011, B10101, B10001, B10001, B00000 },//Ю
{ B01111, B10001, B10001, B01111, B10001, B10001, B10001, B00000 },//Я
  };
  static char chars[] = {'Б','Г','Д','Ж','З','И','Й','Л','П','У','Ф','Ц','Ч','Ш','Щ','Ь','Ъ','Ы','Э','Ю','Я'};
  static byte empty[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int index = 0, cl = sizeof(chars)/sizeof(char),i,j,symb;
  memset(addon_letters,0,sizeof(addon_letters));
  for( j = 0; j < strlen(letters_use) and j < 16; j++ )
          lcd.createChar(j, empty);

  for( j = 0; j < strlen(letters_use) and j < 16; j++ )
  {
          symb = -1;
          for( i=0; i < cl; i++ ) if( chars[i] == letters_use[j] ) { symb = i; addon_letters[index] = letters_use[j]; break; }
          if( symb != -1 ) { lcd.createChar(index, letters[symb]); index++; }
  }
}

void print_rus(char *str) { // процедура вывода русских букв
  static char rus_letters[] = {'А','В','Е','Ё','К','М','Н','О','Р','С','Т','Х'};
  static char trans_letters[] = {'A','B','E','E','K','M','H','O','P','C','T','X'};
  int lcount = sizeof(rus_letters)/sizeof(char), i, j;
  for( i=0; i<strlen(str); i++ )
  { 
        if( (byte(str[i]) == 208 and byte(str[i+1]) != 208) ) continue; // 208 игнор, первый байт UTF8
        bool found = false;
        for(j=0; j < 16; j++) if( addon_letters[j] != 0 and byte(str[i]) == byte(addon_letters[j]) ) { lcd.write(j); found = true; break; }
        if(!found) for(j=0; j < lcount; j++) if( byte(str[i]) == byte(rus_letters[j]) ) { lcd.write(trans_letters[j]); found = true; break; }
        if(!found) lcd.write(byte(str[i]));
  }  
}

void print_rus(int x, int y, char *str) { // процедура вывода русских букв
  lcd.setCursor(x, y);
  print_rus(str);
}
