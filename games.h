//  @ Project : games
//  @ File Name : games.h
//  @ Date : 15/04/2012
//  @ Author : Erik Barrow


#ifndef gameheader
#define gameheader


#include "ebarrow.h"
#include "110ct.h"
//#include "player.h"
#include "game_pacman.h"
#include "game_snake.h"
#include <iostream>


using namespace erik;
using namespace std;
//using namespace play;


namespace games //Start Namespace
{

	enum game {Gpacman,Gsnake}; //add new games here

	game strtogame(string s);//convert strings into games
	string gametostr(game wgame);//convert game to string

	class gamer
	{
	private:
		string username;
		string password;
		LList <game> games;
		LList <int> scores;
	public:
		gamer(){}
		void Createplayer();
		bool Loadplayer(string user_username);
		void Saveplayer();
		int GetScore(game wgame);
		string GetUsername() {return username;}
		void getusername(string &usr){usr=username;}
		void Addscore(int score, game wgame);
	};
	static gamer myplayer; // make the player easily availiable to all games
	class RunGames
	{
	private:
		void selectgame();
		void loadplayer(); 
	public:
		RunGames(){}
		void run(){SetConsoleTitle("Eriks Game Controller");loadplayer();selectgame();}
		~RunGames(){myplayer.Saveplayer();}

	};



}//End Namespace

#endif
