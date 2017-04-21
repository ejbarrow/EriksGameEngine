#ifndef QUICKIO_H
#define QUICKIO_H

#include <conio.h>
#include <time.h>
#include <windows.h>
#include <cstdlib>

static class QuickIO
{
	bool echo;
	char stored;
	public:
	QuickIO(){echo = false;}
	void Echo() {echo = true;}
	void DontEcho() {echo = false;}
	bool isEchoing(){return echo;}
	bool waiting(){return !kbhit();}
	void get(){if(echo) getche(); else getch();}
	QuickIO& operator >> (int& var);
	QuickIO& operator >> (char& var);
} qin;



class Stopwatch
{
	clock_t proctime, procelapsed;
	bool running;
public:
	Stopwatch(); //called automatically when a stopwatch object is created
	void start(); //starts the stopwatch
	float stop(); //stops the watch and returns the time
	void reset(); //resets the stopwatch to zero
	float read(); //returns the current time (without stopping the watch)
};

enum colour {Black, Blue, Green, Aqua, Red, Purple, Yellow, White};

class ColourController
{
	HANDLE hout;
	int foreground, background;
	void setConsole(){SetConsoleTextAttribute(hout, foreground + background*16);}
public:
	ColourController(): foreground(15), background(0) {hout = GetStdHandle(STD_OUTPUT_HANDLE);}
	void setForeground(colour c);
	void setBackground(colour c);
	void setForeBright(bool b);
	void setBackBright(bool b);
	void invert();
	~ColourController(){setForeground(White); setForeBright(true); setBackground(Black); setBackBright(false);}
};



class CursorController
{
	HANDLE hout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD c;
	void setConsole(){SetConsoleCursorPosition(hout, c);}
public:
	CursorController(){hout = GetStdHandle (STD_OUTPUT_HANDLE);GetConsoleScreenBufferInfo(hout,&csbi);c=csbi.dwCursorPosition;}
	void setPosition(short x, short y){c.X = x; c.Y = y; setConsole();}
	short getX(){GetConsoleScreenBufferInfo(hout,&csbi);c=csbi.dwCursorPosition;return c.X;}
	short getY(){GetConsoleScreenBufferInfo(hout,&csbi);c=csbi.dwCursorPosition;return c.Y;}
	void clearAll();
};



class Random
{
	int mlower, mupper;
protected:
	int value;
public:
	Random():mlower(0),mupper(RAND_MAX){time_t seconds;time(&seconds);srand((unsigned int) seconds);}
	void setLimits(double lower, double upper){mlower=lower; mupper=upper;}
	int get();	
	int getLast(){return value;}
};

#endif