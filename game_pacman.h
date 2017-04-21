//  @ Project : Pacman
//  @ File Name : game_pacman.h
//  @ Date : 15/04/2012
//  @ Author : Erik Barrow
//
//

#ifndef pacheader
#define pacheader

#include "ebarrow.h"
#include "110ct.h"
#include <iostream>
#include "games.h"

using namespace erik;
using namespace std;


namespace games //Start Namespace
{

	template <int i>
	struct CalcLevel //calculate level speeds using template meta!!!!
	{
		static const int multiple = 3; // edit this to change levels (higher number mean faster levels) -- Higher the level faster it gets (no more than 4)
		enum {VALUE = 200-(i*multiple)};
	};

	class Pacman;
	class Maps;
	class Ghost;
	class ScoreBoard;
	class PinkGhost;
	class RedGhost;
	class GreenGhost;
	class TurquoiseGhost;
	class HUD;

	class Maps
	{
	private:
		char mapstore[40][80];// [y][x]
		int PacStartX;
		int PacStartY;
		int ghostStartx;
		int ghostStarty;
	public:
		void LoadMap(string location);
		void Draw();
		void Erase();
		char getchar(int x, int y);
		bool CollisionCheck(int x, int y);
		bool PointCheck(int x, int y);
		bool PowerPelletCheck(int x, int y);
		void getPacStart(int & x, int & y);
		void getGhostStart(int &x, int &y);
		int getPelletCount();
	};

	class HUD
	{
	private:
		void drawlife();
		void drawscore();
		void drawlevel();
		int scr,lif,lev;
	public:
		HUD();
		void setscore(int score){scr=score;drawscore();}
		void setlifes(int life){lif=life;drawlife();}
		void setlevel(int level){lev=level;drawlevel();}
	};

	class PacController
	{
	private:
		int score;
		int level;
		int pelletseaten;
		string usern;
		int LevelSpeeds [50];
		void SelectMap();
		void ShowInstructions();
		void Levelspeedcalc();
		string mapname;
		void gameover();
	public:
		PacController(){}
		void setuser(string usr){usern=usr;}
		void Run();

	};

	class Ghost
	{
	protected:
		colour Col;
		int xpos;
		int ypos;
		bool galive;
		bool firstmove;
		bool timerstart;
		bool gscatter;
		char prevlochar;
		void movedead();
		void movescatter();
		void movealive();
		direction heading;
		Stopwatch Scat, Dea,start;
		static const char gho = 'G';
		Maps *map;
		Pacman *pac;
		bool junction();
		void movechase();
		void moverand();
		int *scores;
	public:
		Ghost(){heading=Up; galive =true; gscatter =false; prevlochar = ' ';firstmove =true; timerstart=false;}
		bool CheckColision(int x, int y);
		void SetScatter(bool scatter);
		bool checkscatter(){return gscatter;}
		void SetAlive(bool alive);
		bool CheckAlive() {return galive;}
		void move();
		void reset(){timerstart=false;firstmove=true;}
		void setstart(int x,int y);
		void setpos(int x, int y);
		void passmap (Maps *themap){map=themap;}// set a pointer to the maps
		void passpac (Pacman *thepac){pac=thepac;}//set a pointer to pac
		void passscore (int *scr){scores=scr;}
	};


	class Pacman
	{
	private:
		direction CurrentDirection;
		direction NextDirection;
		int Lifes;
		int xlocation;
		int ylocation;
		static const char pac = 'C';
		Maps *map;
		RedGhost * red;
		GreenGhost * green;
		TurquoiseGhost * turq;
		PinkGhost *pink;
		HUD *hud;

	public:
		Pacman();
		void SetDirection(direction move);
		void Move();
		void EditLifes(int life);
		void setlocation(int x, int y);
		bool CheckAlive();
		void Getlocation(int &x, int &y);
		int getlifes(){return Lifes;}
		void passhud(HUD *thehud){hud = thehud;}
		void passmap(Maps *themap){map=themap;}
		void passghosts(RedGhost * g_red,GreenGhost * g_green,TurquoiseGhost * g_turq,PinkGhost *g_pink){red=g_red;green=g_green;turq=g_turq;pink=g_pink;}
	};

	class ScoreBoard
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

	class RedGhost : public Ghost
	{
	private:
		void movealive();
		int delay;
	public:
		RedGhost(): Ghost(){Col = Red;}
		void move();
	};

	class GreenGhost : public Ghost
	{
	private:
		void movealive();
		int delay;
	public:
		GreenGhost(): Ghost(){Col = Green;}
		void move();
	};

	class TurquoiseGhost : public Ghost
	{
	private:
		void movealive();
		int delay;
	public:
		TurquoiseGhost(): Ghost(){Col = Aqua;}
		void move();
	};

	class PinkGhost : public Ghost
	{
	private:
		void movealive();
		int delay;
	public:
		PinkGhost(): Ghost(){Col =Purple ;}
		void move();

	};

}//End Namespace

#endif
