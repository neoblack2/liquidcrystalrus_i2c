#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  
  lcd.init();
  lcd.backlight();
  
  print_rus(0,0,"АаБбВвГгДдЕеЖжЗзИиЙй");
  print_rus(0,1,"КкЛлМмНнОоПпРрСсТтУу");
  print_rus(0,2,"ФфХхЦцЧчШшЩщЪъЫыЬьЭэ");
  print_rus(0,3,"ЮюЯя");
 
  lcd.setCursor(5,3);
  lcd.print("\xD9");
  lcd.print("\xDA");
  lcd.print("\xDB");
  lcd.print("\xDC");
  lcd.print("\x7E");
  lcd.print("\xDF");
  lcd.print("\xED");
  lcd.print("\xD7");
  lcd.print("\xD8");
  lcd.print("\xD2");
  lcd.print("\xD3");
  lcd.print("\xC8");
  lcd.print("\xC9");
  lcd.print("\xF4");
  lcd.print("\x5E");

}

void loop() {
  
}

void print_rus(char *str) { // процедура вывода русских букв
  static char rus_letters[] = {'А','а','Б','б','В','в','Г','г','Д','д','Е','е','Ж','ж','З','з','И','и','Й','й','К','к','Л','л','М','м','Н','н','О','о','П','п','Р','р','С','с','Т','т','У','у','Ф','ф','Х','х','Ц','ц','Ч','ч','Ш','ш','Щ','щ','Ъ','ъ','Ы','ы','Ь','ь','Э','э','Ю','ю','Я','я'};
  static char trans_letters[] = {'A','a','\xA0','\xB2','B','\xB3','\xA1','\xB4','\xE0','\xE3','E','e','\xA3','\xB6','\xA4','\xB7','\xA5','\xB8','\xA6','\xB9','K','\xBA','\xA7','\xBB','M','\xBC','H','\xBD','O','o','\xA8','\xBE','P','p','C','c','T','\xBF','\xA9','y','\xAA','\xE4','X','x','\xE1','\xE5','\xAB','\xC0','\xAC','\xC1','\xE2','\xE6','\xAD','\xC2','\xAE','\xC3','b','\xC4','\xAF','\xC5','\xB0','\xC6','\xB1','\xC7'};
  int lcount = sizeof(rus_letters)/sizeof(char), i, j;
  for( i=0; i<strlen(str); i++ ) { 
    if( (byte(str[i]) == 208 and byte(str[i+1]) != 208) or (byte(str[i]) == 209 and byte(str[i+1]) != 209)) continue; // 208 209 игнор, первый байт UTF8
    bool found = false;
    for(j=0; j < lcount; j++) if( byte(str[i]) == byte(rus_letters[j]) ) {lcd.write(trans_letters[j]); found = true; break;} 
    if (!found) lcd.write(str[i]);
  }
}

void print_rus(int x, int y, char *str) { // процедура вывода русских букв
  lcd.setCursor(x, y);
  print_rus(str);
}
