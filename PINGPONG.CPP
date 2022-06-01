#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
int x1,y1,x2,y2,x1old,x2old,ycenter,xcenter,i=0,j=1;
int xnewcenter,ynewcenter,radius,ballinx,balliny;
char sym;
void ball()
{
	xcenter=xnewcenter;
	ycenter=ynewcenter;
	xnewcenter=xcenter+ballinx;
	ynewcenter=ycenter+balliny;
	setcolor(0);
	setfillstyle(1,0);
	fillellipse(xcenter,ycenter,radius,radius);
	setfillstyle(1,YELLOW);
	fillellipse(xnewcenter,ynewcenter,radius,radius);
	setcolor(YELLOW);
	if(xnewcenter-radius<0)
		ballinx=-ballinx;
	if(xnewcenter+radius>640)
		ballinx=-ballinx;
	if(ynewcenter-radius<0)
		balliny=-balliny;
	if(ynewcenter+radius>340)
	{
		if(xnewcenter>=x1 && xnewcenter<=x2)
		{
			if(i==1)
			{
				ballinx=j;
				if(++j==10) j=1;
				i=0;
			}
			else
			{
				ballinx=-j;
				if(++j==10) j=1;
				i=1;
			}
			balliny=-3;
		}
		else
		{
			cleardevice();
			outtextxy(150,180,"Game Over");
			outtextxy(150,250,"Press Q to Exit");
			getch();
		}
		return;
	}
	delay(20);
}
void bat(char sym)
{
	switch(sym)
	{
		case 'z':if(x1>0)
			{
				x1old=x1;
				x2old=x2;
				x1=x1-5;
				x2=x2-5;
				delay(10);
				setfillstyle(1,0);
				bar(x1old,y1,x2old,y2);
				setfillstyle(1,LIGHTRED);
				bar(x1,y1,x2,y2);
			}
			if(x1==0)
			{
				delay(10);
				setfillstyle(1,LIGHTRED);
				bar(x1,y1,x2,y2);
			}
			break;

		case 'x':if(x2<640)
			{
				x1old=x1;
				x2old=x2;
				x1=x1+5;
				x2=x2+5;
				delay(10);
				setfillstyle(1,0);
				bar(x1old,y1,x2old,y2);
				setfillstyle(1,LIGHTRED);
				bar(x1,y1,x2,y2);
			}
			if(x2==640)
			{
				delay(10);
				setfillstyle(1,LIGHTRED);
				bar(x1,y1,x2,y2);
			}
			break;
		}
}
void play()
{
	while(inportb(0x60)!=16)
	{
		if(inportb(0x60)==44) bat('z');
		else if(inportb(0x60)==45) bat('x');
		ball();
	}
}
void initialize()
{
	x1=320;
	y1=341;
	x2=400;
	y2=360;
	xnewcenter=240;
	ynewcenter=100;
	ballinx=2;
	balliny=5;
	radius=10;
	play();
}
void loading()
{
	int i;
	outtextxy(215,277,"Your game is loading");
	for(i=191;i<=389;i++)
	{
		delay(30);
		line(i,300,i,320);
		if(i%10==0) i=i+3;
	}
	delay(500);
	cleardevice();
}
void instructions()
{
	int op;
	void main();
	outtextxy(135,180,"* Press Z on keyboard to move left *");
	outtextxy(135,200,"* Press X on keyboard to move right *");
	outtextxy(135,220,"* During Game if you want to exit press Q *");
	outtextxy(135,240,"* Press 1 to go to Main Screen *");
	op=getche();
	if(op=='1') main();
}
void main()
{
	int gd=DETECT,gm,option;
	initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	outtextxy(240,180,"1. Start Game");
	outtextxy(240,200,"2. Instructions");
	outtextxy(240,220,"3. Exit");
	option=getch();
	cleardevice();
	switch(option)
	{
		case '1':loading();
			  initialize();
			  break;
		case '2': instructions();
			  break;
		case '3': break;
		default: outtextxy(240,400,"Invalid Choice");
	}
}