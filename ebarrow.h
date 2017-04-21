#ifndef myheader
#define myheader


#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include "110ct.h"
#include <Windows.h>
#define _WIN32_WINNT 0x0500
#pragma comment(lib, "winmm.lib")

using namespace std;


namespace erik //Start Namespace
{

	static CursorController crs;
	static ColourController cl;

	string strtoupper(string s); // Convert strings to upper case
	colour strtocol(string s); //convert strings into colours
	void cinstr(string& s); // cin strings includeing spaces
	void ConsolResize(unsigned int,unsigned int,int x, int y); //resize and move the consol
	string extentioncheck(string s);//Check a file name and return the extention (only works for files with only 1 dot)
	string filenamecheck(string s); //extrace the file name without extention

	enum direction {Up,Down,Left,Right};//directions - for use in games ect

	template <class T>
	class DArray  // dynamic arrays!
	{
		T*data;
		int length;

	public:
		DArray(){data = NULL; length=0;}
		DArray(int size){length =size; data=new T[size];initialise();}
		void initialise(){for(int i =0; i<length; ++i){data[i]=NULL;}}
		T& operator [](int i){return data[i];}
		~DArray(){if(data != NULL) {delete [] data; data = NULL;}}
		void resize(int);
		int getsize(){return length;}

	};

	template <class T>
	class LList //linked lists
	{
		struct node 
		{
			T nodeval;
			node*next;
			node*prev;
		} ;

		node*nav;
		node*head;
		node*tail;
		node*temp;

		long int size; 
		long int pointer;

	public:
		LList(){head = new node(); tail = head; nav=head; size =1; pointer=0; }
		void save(string); //save list
		void open(string); //open a list
		int GetSize(){return size;} // get the size of the list
		T& operator [](int i); // use the list like an array
		int moveto(int);
		int remove(int position);
		void insert(int position, T data);
		~LList(){ while(size!= 0) remove(0);}	
	};

	template<class T>
	class CenteredInputBox
	{
	protected:
		string s;
		T i;
		int xcd,ycd, cxcd;
		string password;
	public:
		CenteredInputBox(){}
		CenteredInputBox(string msg, int x, int y){s=msg; xcd=x; ycd=y;}
		void setMessage(string msg){s=msg;}
		void setPosition(int x, int y){xcd=x; ycd=y;}
		void display(T& input);
		void displaypass(T& input); // for pasword input
		void erase();
	};


	class CenteredMessage
	{
		string s;
		int xpos, ypos, cxpos;
		colour col;
	public:
		CenteredMessage();
		CenteredMessage(string, int, int);
		void setMessage(string);
		void setPosition(int, int);
		void display();
		void erase();
		void setColour(colour colour_input){col = colour_input;}
	};

	class yesnoBox
	{
		string message;
		colour text, box;
		int xpos, ypos, cxpos;
		int xtopleft, xbottomright,ytopleft, ybottomright;
	public:
		yesnoBox(){}
		yesnoBox(string message_text,int x,int y,colour colour_input, colour colour_box){cxpos=x; ypos=y;message = message_text;text = colour_input; box =colour_box; }
		bool display()
		{
			xpos = cxpos - (message.length()/2) ; 
			crs.setPosition(xpos,ypos); 
			cl.setForeground(text); 
			cout<<message;
			crs.setPosition(cxpos-2,ypos+1);
			cout<<"(Y/N)"; 
			crs.setPosition(xpos-2,ypos-2); 
			xtopleft = xpos-2;
			ytopleft = ypos-2;
			cout.width((message.length()+5));
			cl.setBackground(box);
			cout<<"";
			crs.setPosition(xpos-2,ypos+3); 
			cout.width((message.length()+5));
			cout<<"";
			xbottomright = message.length() +xpos+2;
			ybottomright = ypos+3;
			crs.setPosition(xpos-2,ypos+2); cout.width(1); cout<<"";
			crs.setPosition(xpos-2,ypos+1); cout.width(1); cout<<"";
			crs.setPosition(xpos-2,ypos); cout.width(1); cout<<"";
			crs.setPosition(xpos-2,ypos-1); cout.width(1); cout<<"";

			crs.setPosition(xpos+message.length()+2,ypos+2); cout.width(1); cout<<"";
			crs.setPosition(xpos+message.length()+2,ypos+1); cout.width(1); cout<<"";
			crs.setPosition(xpos+message.length()+2,ypos); cout.width(1); cout<<"";
			crs.setPosition(xpos+message.length()+2,ypos-1); cout.width(1); cout<<"";
			cl.setBackground(Black);
			cl.setForeground(White);
			char input;
			bool inputloop = false;
			while (inputloop == false)
			{
				qin>>input;
				input = toupper(input);
				if (input == 'Y'){inputloop = true; return true; }
				if (input == 'N'){ inputloop = true;return false; }
				inputloop = false;
			}
			return false;
		}
		void erase()
		{
			int cwidth = message.length() + 5;
			int height = ybottomright - ytopleft; 
			cl.setBackground(Black);
			cl.setForeground(White);

			for ( int i = 0; i<=height; ++i)
			{
				crs.setPosition(xtopleft,ytopleft+i);
				cout.width(cwidth);
				cout<<"";
			}

		}
		void setColour(colour colour_input, colour colour_box){text = colour_input; box =colour_box; }
		void setMessage(string message_text){message = message_text;}
		void setPosition(int x, int y){cxpos=x; ypos=y;}
	};



	class Shape
	{
	protected:
		int xpos, ypos; //x and y pos
		int h, w; //height and width
		colour c,b;
	public:
		Shape(){ xpos=0;ypos=0;h=1; w=1;c=Red; b=Black;}
		Shape( int x, int y){xpos = x; ypos=y;h=1; w=1;c=Red; b=Black;}
		void SetPos(int x, int y){xpos = x; ypos=y; }
		void SetDimentions(int height, int width){h = height; w = width;}
		void SetColour(colour col){c=col;}
		void SetBackground(colour col){b=col;}
	};

	class Rect : public Shape
	{
	public:
		Rect () : Shape(){}
		Rect (int x, int y, int height, int width) : Shape(x,y){h=height;w=width;}
		void display();
		void erase();

	};

	class Square : public Shape 
	{
	public:
		Square () : Shape(){}
		Square (int x, int y, int size) : Shape(x,y){h=size;w=size;}
		void display();
		void erase();
	};


	class Stairs : public Shape 
	{
	public:
		Stairs () : Shape(){}
		Stairs ( int x, int y, int size) : Shape(x,y){h=size;}
		void display();
		void erase();
	};



	class Bart : public Shape // Ascii art from http://www.chris.com/ascii/index.php?art=cartoons%2Fsimpsons
	{
		string bart[23];
		void initialise();
	public:
		Bart () : Shape(){initialise();}
		Bart (int x, int y) : Shape(x,y){initialise();}
		void display();
		void erase();
	};

	template <class T>
	void DArray<T>::resize (int size) //Resize dynamic array
	{
		if (data != NULL)
		{
			if (size > length)
			{
				T*newdata;
				newdata=new T[size];
				for ( int i=0; i<length; ++i)
				{
					newdata[i]=data[i];
				}
				for (int i = length; i<size; ++i)
				{
					newdata[i] = NULL;
				}
				delete [] data;
				data = NULL;
				data= newdata;
				length = size;

			}
			else
			{
				length = size;
			}
		}
		else
		{
			length =size; 
			data = new T[size];
		}

	}

	template <class T>
	void LList<T>::insert(int position, T data)
	{
		moveto(position); 

		if (position == 0) 
		{
			temp = new node();
			head = temp;
			nav->prev = temp;
			temp->next = nav;
			temp->nodeval = data;
			nav = temp;
			++size;
		}
		else
		{
			temp = new node();
			tail = temp;
			temp->prev = nav->prev;
			temp->next = nav;
			temp->nodeval = data;
			nav->prev = temp;
			nav = temp->prev;
			nav->next = temp;
			nav = temp;
			++size;
		}


	}

	template <class T>
	int LList<T>::moveto (int i)
	{
		if (i < size) 
		{
			// do this if list node exists
			if (pointer == i)
			{
				return 0;
			}

			if (pointer < i)
			{
				int move;
				move = i-pointer; //work out how far down the list to move

				for (int a=0; a<move; ++a)
				{
					nav = nav->next; //move to next node
					++pointer;
				}

				return 0;
			}

			if (pointer >i)
			{
				int move;
				move = pointer-i;

				for (int a=0; a<move; ++a)
				{
					nav = nav->prev; //move to previous node
					--pointer;
				}

				return 0;

			}
		}

		if  (i>=size)
		{
			//do this if node does not exist
			int move; //                               move to last node....
			move = (size-1) - pointer;
			for (int a=0; a<move; ++a)
			{
				nav = nav->next; //move to next node
				++pointer;
			}

			move = i-pointer; // how many nodes need creating

			for (int a=0; a<move; ++a)
			{
				nav->next = new node(); // set next node to new node
				++size; //increase size counter
				temp = nav; //store node location in temp
				nav = nav->next; // set nav to next node
				nav->prev = temp; // set previous node to temp
				++pointer; //increase pointer counter
				tail = nav;//move the tail pointer
			}


			return 0;
		}

		return 0; 

	}


	template <class T>
	int LList<T>::remove (int position)
	{
		moveto(position);

		if(size == 1)
		{
			head = NULL;
			tail= NULL;
			delete nav;
			nav= NULL;
			temp = NULL;
			size = 0;
			return 0;
		}

		if(position == 0)
		{
			temp = nav->next;
			temp->prev = NULL;
			head = nav->next;
			temp = nav;
			nav= nav->next;
			delete temp;
			temp = NULL;
		}
		else
			if (position == (size-1))
			{
				temp = nav->prev;
				temp->next = NULL;
				tail = temp;
				temp =nav;
				nav = nav->prev;
				delete temp;
				temp= NULL;
				--pointer;
			}
			else
			{
				temp = nav->next;
				temp->prev = nav->prev;
				temp = nav->prev;
				temp->next = nav->next;
				temp=nav;
				nav = nav->next;
				delete temp;
				temp=NULL;
			}
			--size;
			return 0;
	}

	template <class T>
	T& LList<T>:: operator [](int i)
	{
		moveto(i);
		return nav->nodeval; 
	}

	template <class T>
	void LList<T>::save (string s) //save linked list
	{
		nav=head;  // go to head of list
		ofstream ofs;
		ofs.open(s,ios::out); //open file
		ofs <<nav->nodeval<< std::endl; //add first line to file
		while (nav->next != NULL)  // loop through list and save to file
		{
			nav = nav->next; // move to next line / move pointer in list
			ofs <<nav->nodeval<< std::endl; //add current line to file
		}
		ofs.close();//close file
	}

	template <class T>
	void LList<T>::open (string s) //open a saved linked list
	{
		head = new node(); // create a new list and set the head
		tail = head; // set tail as head
		nav=head; //set nav pointer
		T i;
		ifstream ifs;
		ifs.open(s,ios::in); //open file
		if(ifs)
		{
			ifs >>i;
			nav->nodeval = i; //read first line and save it
			size =1; //set list size
			pointer=0; // set current pointer
			while (!ifs.eof()  )
			{
				ifs >>i;
				nav->next = new node(); // set next node to new node
				++size; //increase size counter
				temp = nav; //store node location in temp
				nav = nav->next; // set nav to next node
				nav->prev = temp; // set previous node to temp
				++pointer; //increase pointer counter
				tail = nav;//move the tail pointer
				nav->nodeval = i; // read file and save in nodeval
			}
		}
		else MessageBox(NULL, "File not found in directory", "Error", MB_OK);
		ifs.close();
	}

	template <class T>
	void CenteredInputBox<T>::erase()
	{
		crs.setPosition(cxcd,ycd);
		int sSize;
		sSize = s.length() + 2 + i.length();
		for (int i = 0 ; i<sSize; ++i)
		{cout<<" ";}

	}

	template <class T>
	void CenteredInputBox<T>::display(T& input)
	{

		cxcd = xcd - (s.length()/2);
		crs.setPosition(cxcd,ycd);
		cout << s << ": ";
		cin >> input;
		i = input;
	}

	template <class T>
	void CenteredInputBox<T>::displaypass(T& input)
	{
		char key;
		cxcd = xcd - (s.length()/2);
		crs.setPosition(cxcd,ycd);
		cout << s << ": ";
		qin >> key;
		while (key != 13)
		{
			cout<<"*";
			password= password+key;
			qin>> key;
		}
		input = password;
		i=password;
	}




}//End Namespace

#endif
