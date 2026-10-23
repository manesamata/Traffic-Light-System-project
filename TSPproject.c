#include<reg51.h>
sbit redled=P1^1;
sbit greenled=P1^2;
sbit yellowled=P1^3;

sbit RS=P1^4;
sbit RW=P1^5;
sbit EN=P1^6;
#define data_line P2
void lcd_init(void); //this all are declaration
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void delay(int);
void main()
{
	int i;
	redled=0; //call
	greenled=0;
	yellowled=0;
	lcd_init();
	while(1)
	{
		lcd_cmd(0x80);
		lcd_string("REDled ON");
		redled=1;
		greenled=0;
		yellowled=0;
		for(i=9;i>=0;i--)
		{
			lcd_cmd(0xc0);
			lcd_data(i+'0');
			delay(1000);
		}
		redled=0;
		greenled=1;
		yellowled=0;
		lcd_cmd(0x80);
		lcd_string("GREENled ON");
		for(i=6;i>=0;i--)
		{
			lcd_cmd(0xc0);
			lcd_data(i+'0');
			delay(1000);
		}
		redled=0;
		greenled=0;
		yellowled=1;
		lcd_cmd(0x80);
		lcd_string("YELLOWled ON");
		for(i=3;i>=0;i--)
		{
			lcd_cmd(0xc0);
			lcd_data(i+'0');
			delay(1000);
		}
	}
}
void delay(int t) //defination
{
	int i;
	for(i=0;i<t;i++)
	{
		TMOD=0X01;
		TH0=0XFC;
		TL0=0X67;
		TR0=1;
		while(TF0==0);
		TF0=0;
		TR0=0;
	}
}
void lcd_cmd(unsigned char c)
{
	data_line=c;
	RS=0;
	RW=0;
	EN=1;
	delay(10);
	EN=0;
}
void lcd_data(unsigned char c)
{
	data_line=c;
	RS=1;
	RW=0;
	EN=1;
	delay(10);
	EN=0;
}
void lcd_init(void)
{
	lcd_cmd(0x30);
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x0F);
}
void lcd_string(unsigned char *p)
{
	while(*p!='\0')
	{
		lcd_data(*p);
		p++;
	}
}

		