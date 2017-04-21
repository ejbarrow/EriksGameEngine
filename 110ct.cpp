#include "110ct.h"

QuickIO& QuickIO::operator >> (int& var)
{
	do
		if(echo)
			var = getche();
		else
			var = getch();
	while(var==0||var==224);
	return *this;
}

QuickIO& QuickIO::operator >> (char& var)
{
	int p;
	do
		if(echo)
			p = getche();
		else
			p = getch();
	while(p==0||p==224);
	var = (char) p;
	return *this;
}


Stopwatch::Stopwatch()
{
	procelapsed = 0;
	running = false;
}

void Stopwatch::start()
{
	proctime = clock();
	running = true;
}

float Stopwatch::stop()
{
	running = false;
	procelapsed = clock() - proctime;
	return float(procelapsed)/CLOCKS_PER_SEC;
}

void Stopwatch::reset()
{
if(!running)
	procelapsed = 0;
}
 
float Stopwatch::read()
{
	if(running)
		return float(clock() - proctime)/CLOCKS_PER_SEC;
	else 
		return float(procelapsed)/CLOCKS_PER_SEC;
}

void ColourController::setForeground(colour c)
{
if(c < 8)
foreground = c + (foreground >= 8) * 8;
setConsole();
}

void ColourController::setBackground(colour c)
{
if(c < 8)
background = c + (background >= 8) * 8;
setConsole();
}

void ColourController::setBackBright(bool b)
{
if(b && background < 8)
background += 8;
else if(!b && background >= 8)
background -= 8;
setConsole();
}

void ColourController::setForeBright(bool b)
{
if(b && foreground < 8)
foreground += 8;
else if(!b && foreground >= 8)
foreground -= 8;
setConsole();
}

void ColourController::invert()
{
foreground = foreground ^ background;
background = background ^ foreground;
foreground = foreground ^ background;
setConsole();
}

void CursorController::clearAll()
{
	COORD origin = {0,0};
	if(!GetConsoleScreenBufferInfo(hout,&csbi))return;
	DWORD consize = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD charsWritten;
	if(!FillConsoleOutputCharacter( hout,(TCHAR) ' ', consize, origin, &charsWritten ))return;
	if(!FillConsoleOutputAttribute( hout, csbi.wAttributes, consize, origin, &charsWritten ))return;
	SetConsoleCursorPosition(hout, origin);
}

int Random::get()
{
	value = rand()%(mupper-mlower+1)+mlower;
	return value;
}