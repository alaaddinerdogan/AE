// Software I2C bağlantıları
sbit Soft_I2C_Scl           at RB7_bit;
sbit Soft_I2C_Sda           at RB6_bit;
sbit Soft_I2C_Scl_Direction at TRISB7_bit;
sbit Soft_I2C_Sda_Direction at TRISB6_bit;
// End Software I2C bağlantıları


// LCD module bağlantıları
sbit LCD_RS at RC6_bit;
sbit LCD_EN at RC7_bit;
sbit LCD_D0 at RD0_bit;
sbit LCD_D1 at RD1_bit;
sbit LCD_D2 at RD2_bit;
sbit LCD_D3 at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISC6_bit;
sbit LCD_EN_Direction at TRISC7_bit;
sbit LCD_D0_Direction at TRISD0_bit;
sbit LCD_D1_Direction at TRISD1_bit;
sbit LCD_D2_Direction at TRISD2_bit;
sbit LCD_D3_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module bağlantıları
sbit motor at RC0_bit;
sbit buzzer at RC2_bit;
char seconds=0, minutes, hours, week_day, day, month, year,tus=2,ekran_temiz=1,kesme_sayisi=0,temp=1,istenen_nem=0,temp2=0;
int nem=0,su_miktari=0,sulama_sayisi,sulama_suresi,sulama_saati;
char anaekran=0;
char txt[3];
 char txt1[4][18] = {"Saat :  :  :  ",
                     "Tarih:  /  /20  ",
                     "Su Seviyesi =%   ",
                     "Nem Orani   =%   "};
 char txt2[3][15] = {"Manuel Sulama",
                     "Baslamak icin",
                     "Tamam 'a Bas "};
 char txt3[1][17] = {"Otomatik Sulama"};
 char txt4[4][21] = {"Zaman Ayarli Sulama ",
                     "Haft.Sula. Sayisi=",
                     "SulamaSaati(0-23)= ",
                     "Sulama Suresi(sn)="};
 char txt5[1][12] = {"Zaman Ayari"};
 char txt6[2][17] = {"iste. Nem Orani=",
                     "Hava. Nem Orani="};


 

void Write_Time() {
    Soft_I2C_Start();
    Soft_I2C_Write(0xD0);               // I2C write address
    Soft_I2C_Write(0x00);               // Start at REG 0 - Seconds
    Soft_I2C_Write(Dec2Bcd(seconds));       // REG 0
    Soft_I2C_Write(Dec2Bcd(minutes));       // REG 1
    Soft_I2C_Write(Dec2Bcd(hours));        // REG 2
    Soft_I2C_Write(Dec2Bcd(week_day));       // REG 3
    Soft_I2C_Write(Dec2Bcd(day));       // REG 4
    Soft_I2C_Write(Dec2Bcd(month));       // REG 5
    Soft_I2C_Write(Dec2Bcd(year));      // REG 6
    Soft_I2C_Write(0x80);               // REG 7 - Disable squarewave output pin
    Soft_I2C_Stop();
}
void Read_Time() {

  Soft_I2C_Start();               // Start sinyali oluşturuluyor
  Soft_I2C_Write(0xD0);           // DS1307'nin adresi gönderiliyor (DS1307 datasheets)
  Soft_I2C_Write(0);              // Adres 0'dan başlanıyor
  Soft_I2C_Start();               // Start sinyali tekrarlanıyor
  Soft_I2C_Write(0xD1);           // DS1307'nin adresi gönderiliyor (R/W=1)

  seconds = Soft_I2C_Read(1);     // saniye bilgisi okundu
  minutes = Soft_I2C_Read(1);     // dakika bilgisi okundu
  hours = Soft_I2C_Read(1);       // saat bilgisi okundu
  week_day = Soft_I2C_Read(1);    // haftanın günü bilgisi okundu
  day = Soft_I2C_Read(1);         // ayın günü bilgisi okundu
  month = Soft_I2C_Read(1);       // ay bilgisi okundu
  year = Soft_I2C_Read(0);        // yıl bilgisi okundu
  Soft_I2C_Stop();                // stop sinyali gönderildi

}




void Display_Time() {
   Lcd_Chr(1, 7, (hours / 10)   + 48);  // saatin onlar basamağı gönderiliyor
   Lcd_Chr(1, 8, (hours % 10)   + 48);  // saatin birler basamağı gönderiliyor
   Lcd_Chr(1, 10, (minutes / 10) + 48);  // dakikanın onlar basamağı gönderiliyor
   Lcd_Chr(1,11, (minutes % 10) + 48);  // dakikanın birler basamağı gönderiliyor
   Lcd_Chr(1,13, (seconds / 10) + 48);  // saniyenin onlar basamağı gönderiliyor
   Lcd_Chr(1,14, (seconds % 10) + 48);  // saniyenin birler basamağı gönderiliyor
   Lcd_Chr(2, 7, (day / 10)   + 48);  // saatin onlar basamağı gönderiliyor
   Lcd_Chr(2, 8, (day % 10)   + 48);  // saatin birler basamağı gönderiliyor
   Lcd_Chr(2, 10, (month / 10) + 48);  // dakikanın onlar basamağı gönderiliyor
   Lcd_Chr(2,11, (month % 10) + 48);  // dakikanın birler basamağı gönderiliyor
   Lcd_Chr(2,15, (year / 10) + 48);  // saniyenin onlar basamağı gönderiliyor
   Lcd_Chr(2,16, (year % 10) + 48);  // saniyenin birler basamağı gönderiliyor
   Lcd_Chr(4,15,(nem/100)+48);  // nem yüzler basamağı gönderiliyor
   Lcd_Chr(4,16,((nem/10)%10)+48);  // nem onlar basamağı gönderiliyor
   Lcd_Chr(4,17,(nem%10)+48);  // nem birler basamağı gönderiliyor
   Lcd_Chr(3,15,(su_miktari/100)+48);  // su_miktari basamağı gönderiliyor
   Lcd_Chr(3,16,((su_miktari/10)%10)+48);  // su_miktari basamağı gönderiliyor
   Lcd_Chr(3,17,(su_miktari%10)+48);  // su_miktari basamağı gönderiliyor
}
void Transform_Time() {
  seconds  =  ((seconds & 0xF0) >> 4)*10 + (seconds & 0x0F);  // saniye dönüştürüldü
  minutes  =  ((minutes & 0xF0) >> 4)*10 + (minutes & 0x0F);  // dakika dönüştürüldü
  hours    =  ((hours & 0xF0)  >> 4)*10  + (hours & 0x0F);    // saat dönüştürüldü
  year     =  ((year & 0xF0) >> 4)*10 + (year & 0x0F);        // yıl dönüştürüldü
  day      =  ((day & 0x30) >> 4)*10    + (day & 0x0F);       // gün dönüştürüldü
  month    =  ((month & 0x10)  >> 4)*10 + (month & 0x0F);     // ay dönüştürüldü
}
void interrupt()    // interrupt alt programı
{
 INTCON.INTF=0;     // RB0 kesmesi bayrağını sıfırla
 INTCON.GIE=0;
 tus=portb & 0b00011110;
 tus=tus>>1;
 if( tus==2 ||tus==3 ||tus==7 ||tus==11 ||tus==15){
 ekran_temiz=1;anaekran=0;}
  else {
  if(anaekran==0){
     switch (tus){
   case 1:tus=0;
   break;
   case 4:tus=1;
   break;
   case 5:tus=2;
   break;
   case 6:tus=3;
   break;
   case 8:tus=4;
   break;
   case 9:tus=5;
   break;
   case 10:tus=6;
   break;
   case 12:tus=7;
   break;
   case 13:tus=8;
   break;
   case 14:tus=9;
   break;
  }
  kesme_sayisi++;
  temp=1;
   ekran_temiz=0;}
  else tus=2;
  }


 INTCON.GIE=1;
}
void Init_Main() {
  trisa=255;
  TRISB = 255;                 // PORTB'yi giriş yönlendi
  portb=0;
  trisc=2;
  portc=0;
  trisd=0;
  portd=0;
  Soft_I2C_Init();           // yazılımsal I2C iletişimi ayarla
  Lcd_Init();                // LCD displayi yapılandır
  Lcd_Cmd(_LCD_CLEAR);       // LCD display ekranını temizle
  Lcd_Cmd(_LCD_CURSOR_OFF);  // LCD display ekranından imleci kaldır
  ADCON1 = 0x84;             //porta D D D D A D A A
  Adc_Init();
  //analog=ADC_Read(0);  0.kanaldan veri oku
  INTCON.GIE=1;            //INTCON – INTERRUPT CONTROL REGISTER'ındaki  GIE: Global Interrupt Enable bit'i  "1" yapılmalıdır.
  INTCON.INTE=1;          //INTCON – INTERRUPT CONTROL REGISTER'ındaki   INTE: RB0/INT External Interrupt Enable bit'i "1" yapılmalıdır
  OPTION_REG.INTEDG=0;    //OPTION_REG – OPTION REGISTER'ındaki INTEDG: Interrupt Edge Select bit'i yükselen kenar isteniyor ise "1" düşen kenar isteniyo ise "0" yapılmalıdır.
    Soft_I2C_Start();               // Start sinyali oluşturuluyor
    Soft_I2C_Write(0xD0);           // DS1307'nin adresi gönderiliyor (DS1307 datasheets)
    Soft_I2C_Write(0);              // Adres 0'dan başlanıyor
    Soft_I2C_Start();               // Start sinyali tekrarlanıyor
    Soft_I2C_Write(0xD1);           // DS1307'nin adresi gönderiliyor (R/W=1)
    seconds = Soft_I2C_Read(1);     // saniye bilgisi okundu
    Soft_I2C_Stop();
    seconds  =  ((seconds & 0xF0) >> 4)*10 + (seconds & 0x0F);  // saniye dönüştürüldü
    Soft_I2C_Start();
    Soft_I2C_Write(0xD0);               // I2C write address
    Soft_I2C_Write(0x00);               // Start at REG 0 - Seconds
    Soft_I2C_Write(Dec2Bcd(seconds));       // REG 0
    Soft_I2C_Stop();

}
 void ekran_temizle() {
 Lcd_Cmd(_LCD_CLEAR);       // LCD display ekranını temizle
 Delay_ms(100);
 }
void ana_ekran() {
if(ekran_temiz==1){
ekran_temizle();
//irp_bit=1;
Lcd_Out(1,1,txt1[0]);
Lcd_Out(2,1,txt1[1]);
Lcd_Out(3,1,txt1[2]);
Lcd_Out(4,1,txt1[3]);
///irp_bit=0;
anaekran=1;
}

ekran_temiz=0;
Read_Time();             // RTC(DS1307)'den tarih ve zamanı oku
Transform_Time();        // formatını ayarla
Display_Time();          // LCD display'de görüntüle


}

void manuel_sulama() {
if(ekran_temiz==1){
ekran_temizle();
Lcd_Out(1,4,txt2[0]);
Lcd_Out(3,1,txt2[1]);
Lcd_Out(4,9,txt2[2]);
ekran_temiz=0;
anaekran=1;
}
while(1){
if(((portb & 0b00011110)>>1)==0){ekran_temizle();Lcd_Out(2,1,"Sulaniyor...");motor=1;buzzer=1;
while(1){
  if(Button(&PORTC, 1, 20, 0)) {motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==3){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==7){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==11){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==2){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
}}
if(Button(&PORTC, 1, 20, 0)) {motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==3){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==7){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==11){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}
  else if(ekran_temiz==1 && tus==2){motor=0;buzzer=0;tus=2;ekran_temiz=1;break;}

}

}
void otomatik_sulama() {
if(ekran_temiz==1){
ekran_temizle();
irp_bit=1;
Lcd_Out(1,4,txt3[0]);
//irp_bit=0;
Lcd_Out(3,1,txt6[0]);
Lcd_Out(4,1,txt6[1]);
irp_bit=0;
Lcd_Chr(4,18,(nem/100)+48);  // nem yüzler basamağı gönderiliyor
Lcd_Chr(4,19,((nem/10)%10)+48);  // nem onlar basamağı gönderiliyor
Lcd_Chr(4,20,(nem%10)+48);  // nem birler basamağı gönderiliyor
Lcd_Cmd(_LCD_BLINK_CURSOR_ON);  // LCD display ekranından imleci aç
Lcd_Chr(4,17,'%');
Lcd_Chr(3,18,istenen_nem/100+48);Lcd_Chr(3,19,(istenen_nem/10)%10+48);Lcd_Chr(3,20,istenen_nem%10+48);
Lcd_Chr(3,17,'%');
}
kesme_sayisi=0;
ekran_temiz=0;
while(1){
  if(Button(&PORTC, 1, 20, 0)) {break;}
  else if(ekran_temiz==1 && tus==2)break;
  else if(ekran_temiz==1 && tus==3)break;
  else if(ekran_temiz==1 && tus==7)break;
  else if(ekran_temiz==1 && tus==15)break;
  if(kesme_sayisi==1){
   if(temp==1){
   if(tus<=1){
   temp2=tus*100;
   Lcd_Chr(3, 18, tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}
   }}
   
    if(kesme_sayisi==2){
   if(temp==1){
   if(temp2<100){
   temp2+=tus*10;
   Lcd_Chr(3, 19, tus+48);
   temp=0;}
   if(temp2>=100){
   if(tus==0){
   Lcd_Chr(3, 19, tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}}
   }}
       if(kesme_sayisi==3){
   if(temp==1){
   if(temp2<100){
   temp2+=tus;
   Lcd_Chr(3,20, tus+48);
   temp=0;delay_ms(400);break;}
   if(temp2>=100){
   if(tus==0){
   Lcd_Chr(3,20, tus+48);
   temp=0;delay_ms(400);break;}
   else{temp=0;kesme_sayisi--;}}
   }}
} 
istenen_nem=temp2;
Lcd_Cmd(_LCD_CURSOR_OFF);  // LCD display ekranından imleci kaldır
ekran_temiz=1;
tus=2;
}


void zaman_ayarli_sulama() {
if(ekran_temiz==1){
ekran_temizle();
irp_bit=1;
Lcd_Out(1,1,txt4[0]);
Lcd_Out(2,1,txt4[1]);
Lcd_Out(3,1,txt4[2]);
Lcd_Out(4,1,txt4[3]);
irp_bit=0;
ekran_temiz=0;
anaekran=0;
Lcd_Cmd(_LCD_BLINK_CURSOR_ON);  // LCD display ekranından imleci aç
Lcd_Chr(2, 18,'=');
}


while(1){
  if(Button(&PORTC, 1, 20, 0)) {ekran_temiz=1;tus=2;break;}
  else if(ekran_temiz==1 && tus==2)break;
  else if(ekran_temiz==1 && tus==3)break;
  else if(ekran_temiz==1 && tus==11)break;
  else if(ekran_temiz==1 && tus==15)break;
  else if(((portb & 0b00011110)>>1)==0){ekran_temizle();Lcd_Chr(3, 11,'O');Lcd_Chr(3, 12,'K');delay_ms(200);tus=2;ekran_temiz=1;break;}

  if(kesme_sayisi==1){
   if(temp==1){
   sulama_sayisi=tus*10;
   Lcd_Chr(2, 19, tus+48);
   temp=0;}
   }
     if(kesme_sayisi==2){
   if(temp==1){
   sulama_sayisi+=tus;
   Lcd_Chr(2, 20, tus+48);
   temp=0;
   Lcd_Chr(3, 18,'=');}
   }

   
   if(kesme_sayisi==3){
   if(temp==1){
   if(tus<=2){
   sulama_saati=tus*10;
   Lcd_Chr(3, 19, tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}
   }}

   else if(kesme_sayisi==4){
    if(temp==1){
   if(sulama_saati<=10 && tus>0){
   sulama_saati+=tus;
   Lcd_Chr(3, 20, tus+48);
   temp=0;
   Lcd_Chr(4,18,'=');
   }
   else if(sulama_saati==20){
   if(tus<=4){
   sulama_saati+=tus;
   Lcd_Chr(3,20,tus+48);
   temp=0;
   Lcd_Chr(4,18,'=');}
   }
   else{temp=0;kesme_sayisi--;}
   }}
   if(kesme_sayisi==5){
   if(temp==1){
   sulama_suresi=tus*10;
   Lcd_Chr(4, 19, tus+48);
   temp=0;}
   }
     if(kesme_sayisi==6){
   if(temp==1){
   sulama_suresi+=tus;
   Lcd_Chr(4, 20, tus+48);
   temp=0;
   ekran_temizle();Lcd_Chr(3, 11,'O');Lcd_Chr(3, 12,'K');delay_ms(200);tus=2;break;}
   }

   
}



Lcd_Cmd(_LCD_CURSOR_OFF);  // LCD display ekranından imleci kaldır
ekran_temiz=1;
}
void zaman_ayari() {
if(ekran_temiz==1){
ekran_temizle();

Lcd_Out(1,4,txt5[0]);
//irp_bit=1;
Lcd_Out(2,1,txt1[0]);
Lcd_Out(3,1,txt1[1]);
//irp_bit=0;
kesme_sayisi=0;
ekran_temiz=0;
 Lcd_Chr(2, 7, (hours / 10)   + 48);  // saatin onlar basamağı gönderiliyor
   Lcd_Chr(2, 8, (hours % 10)   + 48);  // saatin birler basamağı gönderiliyor
   Lcd_Chr(2, 10, (minutes / 10) + 48);  // dakikanın onlar basamağı gönderiliyor
   Lcd_Chr(2,11, (minutes % 10) + 48);  // dakikanın birler basamağı gönderiliyor
   Lcd_Chr(2,13, (seconds / 10) + 48);  // saniyenin onlar basamağı gönderiliyor
   Lcd_Chr(2,14, (seconds % 10) + 48);  // saniyenin birler basamağı gönderiliyor
   Lcd_Chr(3, 7, (day / 10)   + 48);  // saatin onlar basamağı gönderiliyor
   Lcd_Chr(3, 8, (day % 10)   + 48);  // saatin birler basamağı gönderiliyor
   Lcd_Chr(3, 10, (month / 10) + 48);  // dakikanın onlar basamağı gönderiliyor
   Lcd_Chr(3,11, (month % 10) + 48);  // dakikanın birler basamağı gönderiliyor
   Lcd_Chr(3,15, (year / 10) + 48);  // saniyenin onlar basamağı gönderiliyor
   Lcd_Chr(3,16, (year % 10) + 48);  // saniyenin birler basamağı gönderiliyor
Lcd_Cmd(_LCD_BLINK_CURSOR_ON);  // LCD display ekranından imleci aç
Lcd_Chr(2, 6,':');
}
  while(1){
  if(Button(&PORTC, 1, 20, 0)) {tus=2;break;}
  else if(ekran_temiz==1 && tus==2)break;
  else if(ekran_temiz==1 && tus==7)break;
  else if(ekran_temiz==1 && tus==11)break;
  else if(ekran_temiz==1 && tus==15)break;
  else if(((portb & 0b00011110)>>1)==0){ekran_temizle();Lcd_Chr(3, 11,'O');Lcd_Chr(3, 12,'K');delay_ms(200);tus=2;Write_Time();break;}
  
  
  if(kesme_sayisi==1){
   if(temp==1){
   if(tus<=2){
   hours=tus*10;
   Lcd_Chr(2, 7, tus+48); 
   temp=0;}
   else{temp=0;kesme_sayisi--;}
   }}
   
   else if(kesme_sayisi==2){
    if(temp==1){
   if(hours<=10 && tus>0){
   hours+=tus;
   Lcd_Chr(2, 8, tus+48);
   temp=0;
   Lcd_Chr(2,9,':');
   }
   else if(hours==20){
   if(tus<=4){
   hours+=tus;
   Lcd_Chr(2,8,tus+48);
   temp=0;
   Lcd_Chr(2,9,':');}
   }
   else{temp=0;kesme_sayisi--;}
   }}
   else if(kesme_sayisi==3){
   if(temp==1){
   if(tus<=5){
   minutes=tus*10;
   Lcd_Chr(2,10,tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}}}
   
   else if(kesme_sayisi==4){
   if(temp==1){
   minutes+=tus;
   Lcd_Chr(2,11,tus+48);
   temp=0;
   Lcd_Chr(2,12,':');
   }}
   else if(kesme_sayisi==5){
   if(temp==1){
   if(tus<=5){
   seconds=tus*10;
   Lcd_Chr(2,13, tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}}}
   else if(kesme_sayisi==6){
   if(temp==1){
   seconds+=tus;
   Lcd_Chr(2,14, tus+48);
   temp=0;
   Lcd_Chr(3, 6,':');
   }}
   else if(kesme_sayisi==7){
   if(temp==1){
   if(tus<=3){
   day=tus*10;
   Lcd_Chr(3,7, tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}}}
   
   else if(kesme_sayisi==8){
   if(temp==1){
   if(day==30 && tus==1){
   day+=tus;
   Lcd_Chr(3,8, tus+48);
   temp=0;
   Lcd_Chr(3, 9,'/');}
   else if(day<30 && tus>0){
   day+=tus;
   Lcd_Chr(3,8, tus+48);
   temp=0;
   Lcd_Chr(3, 9,'/');}
   else{temp=0;kesme_sayisi--;}

   }}
   
    else if(kesme_sayisi==9){
   if(temp==1){
   if(tus<=1){
   month=tus*10;
   Lcd_Chr(3,10, tus+48);
   temp=0;}
   else{temp=0;kesme_sayisi--;}}}
   
   else if(kesme_sayisi==10){
   if(temp==1){
    if(month<10 && tus>0){month+=tus;Lcd_Chr(3,11, tus+48);temp=0;Lcd_Chr(3, 14,'0');}
    else if(month==10 && tus<=2){
    month+=tus;Lcd_Chr(3,11, tus+48);temp=0;Lcd_Chr(3, 14,'0');}
    else{temp=0;kesme_sayisi--;}
    }}
       else if(kesme_sayisi==11){
   if(temp==1){
   year=tus*10;
   Lcd_Chr(3,15, tus+48);
   temp=0;}}
   else if(kesme_sayisi==12){
   if(temp==1){
   year+=tus;
   Lcd_Chr(3,16, tus+48);
   temp=0;
   }Lcd_Chr(4, 19,'O');Lcd_Chr(4, 20,'K');Write_Time();tus=2;break;}
   
   

  }

  //{"Saat :  :  :  ",   "Tarih:  /  /20  ",

Lcd_Cmd(_LCD_CURSOR_OFF);  // LCD display ekranından imleci kaldır
ekran_temiz=1;
}
void sensor_read() {
nem=ADC_Read(0);         //0.kanaldan veri oku
if (nem<1000)nem=nem/10;
else if (nem>999)nem=100;
su_miktari=ADC_Read(1);  //1.kanaldan veri oku
if (su_miktari<257){su_miktari=(su_miktari/10)*3+24;}
else if (su_miktari>255)su_miktari=100;
if (su_miktari<25){motor=1;buzzer=1;}
else {motor=0;buzzer=0;}
}


void main() {
   Delay_ms(100);
   Init_Main();

   while(1){
   sensor_read();
   switch (tus){
   case 2:ana_ekran();
   break;
   case 3:zaman_ayari();
   break;
   case 7:zaman_ayarli_sulama();
   break;
   case 11:otomatik_sulama();
   break;
   case 15:manuel_sulama();
   break;
  }

 }




}
