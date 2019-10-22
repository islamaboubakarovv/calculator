#include "C:\Users\alfre\Desktop\tec\QuintoSemestre\ArquitecturaDeComputadoras\U3\calculadora\main.h"
#fuses xt,nowdt
#define lcd_data_port getenv("srf:portd")
#define lcd_enable_pin pind0
#define lcd_rs_pin pin_d1
#define lcd_rw_pin pin_d2
#define use_portb_kbd true
#include <lcd.c>
#include <kbd4x4_1.c>
#include <math.h>
void main()
{
   char k,flag='0',flag2='0',opera='n';
   int pos=1,pindex=0,i=0;
   double save1=0.0,save2=0.0,savep1=0.0,savep2=0.0;
   float mod=0,mod1,mod2;
   port_b_pullups(true);
   lcd_init();
   kbd_init();
   while(true){
      k=kbd_getc();
      if(k!=0&&k!='A'&&k!='B'&&k!='C'&&k!='D'&&k!='*'&&k!='#'){
      /////////////////////////////////guardar valores/////////////////////////////////////////////////////////////////////////
         if(flag=='0'&&flag2=='0')//bandera que se activa cuando se oprime un operador
            save1=(save1*10)+k-48;
         else if(flag=='0'&&flag2=='1'){
            savep1=(savep1*10)+k-48;
            pindex++;
         }
         else if(flag=='1'&&flag2=='0')
            save2=(save2*10)+k-48;
         else if(flag=='1'&&flag2=='1'){
            savep2=(savep2*10)+k-48;
            pindex++;
         }
////////////////////////////escribir el lcd los numeros///////////////////////////////////////////////////////////////////////
         lcd_gotoxy(pos,1);
         printf(lcd_putc,"%c",k);
          
         if(pos<16)
         pos++;
         else
         pos=16;
      }
      
/////////////////////////////detccion de teclas especiales////////////////////////////////////////////////////////////////////
      if(k=='*'){
         k='.';
         lcd_gotoxy(pos,1);
         printf(lcd_putc,"%c",k);
         flag2='1';
         pos++;
         
      }
////////////////////////////////division/////////////////////////////////////////////////////////////
            
         if(k=='A'){
            k='/';
            opera='d';
            flag='1';
            flag2='0';
            while(pindex!=0){
               savep1=savep1/10;
               pindex=pindex-1;
            }
               
            save1=save1+savep1;
            pindex=0;
            lcd_gotoxy(pos,1);
            printf(lcd_putc,"%c",k);
            pos++;
         }
///////////////////////////multiplicacion////////////////////////////////////////////////////////
         if(k=='B'){
            k='*';
            opera='m';
            flag='1';
            flag2='0';
            while(pindex!=0){
               savep1=savep1/10;
               pindex=pindex-1;
            }
               
            save1=save1+savep1;
            pindex=0;
            lcd_gotoxy(pos,1);
            printf(lcd_putc,"%c",k);
            pos++;
         }
////////////////////////////////resta///////////////////////////////////////////////////////////////////  
         if(k=='C'){
            k='-';
            opera='r';
            flag='1';
            flag2='0';
            while(pindex!=0){
               savep1=savep1/10;
               pindex=pindex-1;
            }
               
            save1=save1+savep1;
            pindex=0;
            lcd_gotoxy(pos,1);
            printf(lcd_putc,"%c",k);
            pos++;
         }
///////////////////////////////////suma//////////////////////////////////////////////////////////////////
         if(k=='D'){
            k='+';
            opera='s';
            flag='1';
            flag2='0';
            while(pindex!=0){
               savep1=savep1/10;
               pindex=pindex-1;
            }
               
            save1=save1+savep1;
            pindex=0;
            lcd_gotoxy(pos,1);
            printf(lcd_putc,"%c",k);
            pos++;
         }
/////////////////////////////igual-resultado//////////////////////////////////////////////////////////////
         if(k=='#'){//igual
            while(pindex!=0){
               savep2=savep2/10;
               pindex=pindex-1;
            }
            save2=save2+savep2;
            if(opera=='d'){
               mod1=save1;
               mod2=save2;
               save1=save1/save2;
               mod=fmod(mod1,mod2);
               
            }
            else if(opera=='m')
               save1=save1*save2;
            else if(opera=='r')
               save1=save1-save2;   
            else if(opera=='s')
               save1=save1+save2;
            else save1=0.0;   
            lcd_gotoxy(1,2);
            printf(lcd_putc,"%f",save1);
            lcd_gotoxy(10,2);
            printf(lcd_putc,"%f",mod);
         }
            
   }

}
