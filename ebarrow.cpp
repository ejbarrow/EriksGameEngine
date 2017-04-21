#include "ebarrow.h"

namespace erik //Start Namespace
{

	string strtoupper(string s) //convert strings to upper case
	{
		transform(s.begin(), s.end(),s.begin(), ::toupper); 
		return s;
	}

	void cinstr(string& s) // cin strings includeing spaces
	{
		getline(cin,s);
	}

	colour strtocol(string s) //convert strings into colours
	{
		colour col;
		s = strtoupper(s);
		if (s == "RED")col = Red;
		if (s == "GREEN")col = Green;
		if (s == "BLACK")col = Black;
		if (s == "BLUE")col = Blue;
		if (s == "AQUA")col = Aqua;
		if (s == "PURPLE")col = Purple;
		if (s == "YELLOW")col = Yellow;
		if (s == "WHITE")col = White;
		return col;
	}


	void ConsolResize(unsigned int width,unsigned int height, int x, int y)  // http://msdn.microsoft.com/en-us/library/windows/desktop/ms686044%28v=vs.85%29.aspx  - http://www.cplusplus.com/forum/windows/10731/  - http://msdn.microsoft.com/library/ms686125  - http://www.cplusplus.com/forum/beginner/1481/
	{// Creating this function required my to find different peices of code from msdn and find out how to use them through google. 

		COORD size;
		size.X = width;
		size.Y = height;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),size); // sets the buffer size, ie how far down it scrolls. 

		MoveWindow(GetConsoleWindow(), x, y, (width*20), (height*20), TRUE); //forces the window to resize to size of the buffer
	}

	CenteredMessage::CenteredMessage(string str, int x, int y)
	{
		xpos = x;
		ypos = y;
		s = str;
	}

	CenteredMessage::CenteredMessage()
	{
		xpos = 0;
		ypos = 0;
		s = "I have no message";
	}


	void CenteredMessage::setMessage(string str)
	{
		s = str;
	}

	void CenteredMessage::setPosition(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	void CenteredMessage::display()
	{
		cl.setForeground(col);
		cxpos= xpos - (s.length()/2);
		crs.setPosition(cxpos, ypos);
		cout << s;
		cl.setForeground(White);

	}

	void CenteredMessage::erase()
	{
		crs.setPosition(cxpos,ypos);
		int sSize;
		sSize = s.length();
		for (int i = 0 ; i<sSize; ++i)
		{cout<<" ";}
	}



	void Stairs::erase()
	{
		cl.setBackBright(false);
		cl.setBackground(b);
		for (int i =0; i<h;++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout.width(i+1);
			cout<<" ";
		}
	}

	void Stairs::display()
	{ 
		cl.setBackBright(true);
		cl.setBackground(c);
		for (int i =0; i<h;++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout.width(i+1);
			cout<<" ";
		}
		cl.setBackBright(false);
		cl.setBackground(b);
	}

	void Bart::initialise()
	{
		bart[0] = "              ,  , ";
		bart[1] = "             / \\/ \\,'| _ ";
		bart[2] = "            ,'    '  ,' |,| ";
		bart[3] = "           ,'           ' |,'| ";
		bart[4] = "          ,'                 ;'| _ ";
		bart[5] = "         ,'                    '' | ";
		bart[6] = "        ,'                        ;-, ";
		bart[7] = "       (___                        / ";
		bart[8] = "     ,'    `.  ___               ,' ";
		bart[9] = "    :       ,`'   `-.           / ";
		bart[10] = "    |-._ o /         \\         / ";
		bart[11] = "   (    `-(           )       / ";
		bart[12] = "  ,'`.     \\      o  /      ,' ";
		bart[13] = " /    `     `.     ,'      / ";
		bart[14] = "(             `''''       / " ;
		bart[15] = " `._                     / ";
		bart[16] = "    `--.______        ' `. ";
		bart[17] = "       \\__,__,`---._   '`; ";
		bart[18] = "            ))`-^--')`,-' ";
		bart[19] = "          ,',_____,'  | ";
		bart[20] = "          \\_          `). ";
		bart[21] = "            `.      _,'  ` ";
		bart[22] = "            /`-._,-'      \\ ";
	}

	void Bart::display()
	{
		cl.setForeBright(true);
		cl.setForeground(c);

		for (int i=0; i<23; ++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout<<bart[i];
		}
		cl.setForeBright(true);
		cl.setForeground(White);
	}

	void Bart::erase()
	{
		cl.setForeBright(true);
		cl.setForeground(White);

		for (int i=0; i<23; ++i)
		{
			crs.setPosition(xpos,ypos+i);
			string a;
			a = bart[i];
			cout.width(a.length());
			cout<<" ";
		}
		cl.setForeBright(true);
		cl.setForeground(White);
	}

	void Square::display()
	{ 
		cl.setBackBright(true);
		cl.setBackground(c);
		for (int i =0; i<h;++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout.width(w);
			cout<<" ";
		}
		cl.setBackBright(false);
		cl.setBackground(b);
	}

	void Square::erase()
	{ 
		cl.setBackBright(false);
		cl.setBackground(b);
		for (int i =0; i<h;++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout.width(w);
			cout<<" ";
		}
	}

	void Rect::display()
	{ 
		cl.setBackBright(true);
		cl.setBackground(c);
		for (int i =0; i<h;++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout.width(w);
			cout<<" ";
		}
		cl.setBackBright(false);
		cl.setBackground(b);
	}

	void Rect::erase()
	{ 
		cl.setBackBright(false);
		cl.setBackground(b);
		for (int i =0; i<h;++i)
		{
			crs.setPosition(xpos,ypos+i);
			cout.width(w);
			cout<<" ";
		}
	}

	string extentioncheck(string s)
	{
		int length = s.length();
		string ext ="";
		bool found =false;
		for (int i =0; i<length; ++i)
		{
			if (found == true) ext= ext+s[i];
			if (s[i] == '.') found = true;
		}
		return ext;
	}

	string filenamecheck(string s)
	{
		string file ="";
		int length = s.length();
		bool found =false;
		for (int i =0; i<length; ++i)
		{
			if (s[i] == '.') found = true;
			if (found == false) file= file+s[i];
		}
		return file;
	}

}//End Namespace