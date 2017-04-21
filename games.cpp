//  @ Project : Games
//  @ File Name : games.cpp
//  @ Date : 15/04/2012
//  @ Author : Erik Barrow


#include "games.h"


namespace games //Start Namespace
{

	void gamer::Createplayer() //create a new player
	{
		CenteredInputBox <string> user;
		CenteredInputBox <string> pass;
		user.setMessage("Please Choose a username");
		pass.setMessage("Please Choose a password");
		user.setPosition(40,12);
		pass.setPosition(40,12);
		user.display(username);
		user.erase();
		string file;
		ifstream ifs;//check username not in use
		file = username +".usr";
		ifs.open(file,ios::in);
		if(ifs){CenteredMessage error("Username already Exists - Try Again (Press any Key)",40,12); error.display(); qin.get(); error.erase();Createplayer();}
		ifs.close();
		pass.displaypass(password);
		pass.erase();
		Saveplayer();
	}

	bool gamer::Loadplayer(string user_username)  //load player from file
	{
		username = user_username;
		string s;
		int i;
		int count=0;
		ifstream ifs;
		string file = username +".usr";
		ifs.open(file,ios::in);
		if(ifs)
		{
			ifs >>s;
			password = s;
			while (!ifs.eof()  )
			{
				ifs >> s;
				games[count] = strtogame(s);
				ifs >>scores[count];
				++count;
			}
		}
		else {crs.setPosition(0,0);cout << "Player "<<username<<" Does not Exist!"<<endl;ifs.close(); return false;}

		string pass;
		CenteredInputBox <string> playerbox;
		playerbox.setPosition(24,10);
		playerbox.setMessage("What is your Password? (Case Sensitive)");
		playerbox.displaypass(pass);
		playerbox.erase();

		for(int i=0; i<password.length();++i) //low level password encrypt
		{
			password[i] = password[i]-16;
		}

		if (pass != password){crs.setPosition(0,0);cout << "Incorrect Password for User "<<username<<"!"<<endl;ifs.close(); return false;}
		ifs.close();
		return true;

	}

	void gamer::Saveplayer()
	{
		ofstream ofs;
		string s,pass;
		s= username + ".usr";
		ofs.open(s,ios::out); //open file
		pass=password;
		for(int i=0; i<password.length();++i) //low level password encrypt
		{
			pass[i] = password[i]+16;
		}

		ofs <<pass<<endl; //add first line to file

		for (int i=0; i < games.GetSize(); ++i)
		{
			string g;
			g= gametostr(games[i]);
			ofs <<g <<endl;
			ofs << scores[i];
		}

		ofs.close();//close file
	}

	int gamer::GetScore(game wgame)
	{
		int score =0; 

		for (int i=0; i < games.GetSize(); ++i)
		{
			if (games[i] = wgame){score = scores[i];}
		}

		return score ;
	}

	void gamer::Addscore(int Score, game wgame)
	{
		bool exist = false;
		for (int i=0; i < games.GetSize(); ++i) //check if score exists
		{
			if (games[i] = wgame){if(scores[i]<Score)scores[i] = Score; exist =true;}
		}
		if (exist==false) //if game isnt in list
		{
			int size;
			size = games.GetSize();
			games[size] = wgame;
			scores[size] = Score;
		}
	}

	game strtogame(string s) //convert strings into games
	{
		game wgame;
		s = strtoupper(s);
		if (s == "PACMAN")wgame = Gpacman;
		if (s == "SNAKE")wgame = Gsnake;
		//add new games here when added.
		return wgame;
	}

	string gametostr(game wgame) //convert games into strings
	{
		string s = "";
		if (wgame == Gpacman)s= "PACMAN";
		if (wgame == Gsnake) s= "SNAKE";
		//add new games here when added.
		return s;
	}


	void RunGames::selectgame() 
	{
		crs.clearAll();
		char input;
		cout<<"Welcome "<<myplayer.GetUsername()<<", Please select a game: "<<endl;
		cout<<"A) Pacman"<<endl;
		cout<<"B) Snake"<<endl;
		qin>>input;
		input=toupper(input);

		switch (input)
		{
		case 'A': {PacController pacman;pacman.setuser(myplayer.GetUsername()); pacman.Run();} break; //run pacman here
		case 'B': {SnakeController snake;snake.setuser(myplayer.GetUsername());snake.run();} break; //run snake here
		default: selectgame();   break;
		}
		bool value;
		crs.clearAll();
		yesnoBox exit;
		exit.setColour(White,Red);
		exit.setMessage("Woud you like to exit?");
		exit.setPosition(40,10);
		value = exit.display();
		if (value == false) {SetConsoleTitle("Eriks Game Controller");selectgame();}
	}

	void RunGames::loadplayer()
	{
		bool value;
		yesnoBox input;
		input.setMessage("Do You Have An Account?");
		input.setColour(White,Red);
		input.setPosition(40,10);
		value = input.display();
		input.erase();
		if (value == true)//existing player
		{
			string username;
			CenteredInputBox <string> playerbox;
			playerbox.setPosition(25,10);
			playerbox.setMessage("What is your username?");
			playerbox.display(username);
			playerbox.erase();
			bool success;
			success = myplayer.Loadplayer(username);
			if (success==false)//player not found
			{
				qin.get();
				crs.clearAll();
				loadplayer();
			}

		}
		if (value == false) //create player
		{
			myplayer.Createplayer();
		}
	}



}//end namespace