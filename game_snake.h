//  @ Project : Snake
//  @ File Name : game_Snake.h
//  @ Date : 15/04/2012
//  @ Author : Erik Barrow
//
//

#ifndef snakeheader
#define snakeheader

#include "ebarrow.h"
#include "110ct.h"
#include <iostream>
#include "games.h"


using namespace erik;
using namespace std;


namespace games //Start Namespace
{
	class SMaps;
	class SnakeController;
	class snakeScoreBoard;
	class snakeHUD;
	class snake;


	class SnakeController
	{
	private:
		int score;
		int level;
		void levelselect();
		void mapselect();
		void showinstructions();
		string username;
		string mapname;
		void gameover();

	public:
		void run();
		void setuser(string user){username = user;}
	};

	class SMaps
	{
	private:
		char mapstore[40][80];// [y][x]
		string map;
		void GeneratePelet();
		snake *sna;
	public:
		void Draw();
		void load(string location);
		void erase();
		bool CollisionCheck(int x, int y);
		bool PeletCheck(int x, int y);
		void passSnake(snake *thesnake){sna=thesnake;}
		void setfirstpelet(){ GeneratePelet();}
	};

	class snake
	{
	private:
		LList <int> bodyx;
		LList <int> bodyy;
		colour col;
		void erase();
		SMaps *map;
		direction heading;
		int tempx,tempy;
		bool addone;
	public:
		snake(){heading=Left;col=White;bodyx[0]=38;bodyx[1]=39;bodyx[2]=40;bodyx[3]=41;bodyy[0]=20;bodyy[1]=20;bodyy[2]=20;bodyy[3]=20;addone=false;}
		void draw();
		void setcolour(colour color) {col=color;heading=Left;}
		bool move();
		bool collisioncheck(int x, int y);
		void setheading(direction head){heading=head;}
		void passmap(SMaps *themap){map=themap;}
		void gethead(int &x, int &y){x=bodyx[0];y=bodyy[0];}
		direction getheading(){return heading;}
		bool offmap();
		void add(){addone=true;}
	};

	class snakeScoreBoard
	{
	private:
		LList <int> scores;
		LList <string> play;
		int xpos,ypos;
		string mapname;
	public:
		void LoadScores();
		void SaveScores();
		void setmapname(string map) {mapname=map;}
		void DisplayScores(int x, int y);
		bool CheckScore(int score);
		void AddScore(int score, string username);
		void erase();
	};

	class snakeHUD
	{
	private:
		void drawlife();
		void drawscore();
		void drawlevel();
		int scr,lev;
	public:
		snakeHUD();
		void setscore(int score){scr=score;drawscore();}
		void setlevel(int level){lev=level;drawlevel();}
	};


}//End Namespace

#endif
