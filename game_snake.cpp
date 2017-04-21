//  @ Project : Snake
//  @ File Name : game_Snake.cpp
//  @ Date : 15/04/2012
//  @ Author : Erik Barrow
//
//

#include "game_snake.h"



namespace games //Start Namespace
{

	void SnakeController::gameover()
	{
		crs.clearAll();
		snakeScoreBoard sb;
		sb.setmapname(mapname);
		sb.LoadScores();
		if (sb.CheckScore(score)==true)sb.AddScore(score,username);
		sb.DisplayScores(20,5);
		sb.SaveScores();
		myplayer.Addscore(score,Gsnake);
		Sleep(2000);
		qin.get();
		sb.erase();
	}
	void SnakeController::run()
	{
		SetConsoleTitle("Eriks Game Controller - Snake");
		ConsolResize(80,45,50,50);
		showinstructions();
		mapselect();
		levelselect();
		score =0; //startingscore
		SMaps map;
		snakeHUD hud;
		snake sna;
		map.load(mapname);
		map.Draw();
		map.passSnake(&sna);
		sna.passmap(&map);
		sna.draw();
		hud.setlevel(level);
		hud.setscore(score);
		char Keypress;
		bool alive =true;
		bool play =true;
		map.setfirstpelet(); //generate first pelet

		while (alive==true)
		{
			Keypress=getch();
			Keypress=toupper(Keypress);
			//check key, make sure not heading back on yourself and dont move if of side of map
			if ((Keypress =='W')&&(sna.getheading()!=Down)&&(sna.offmap()==false)){sna.setheading(Up);}
			if ((Keypress =='A')&&(sna.getheading()!=Right)&&(sna.offmap()==false)){sna.setheading(Left);}
			if ((Keypress =='S')&&(sna.getheading()!=Up)&&(sna.offmap()==false)){sna.setheading(Down);}
			if ((Keypress =='D')&&(sna.getheading()!=Left)&&(sna.offmap()==false)){sna.setheading(Right);}


			while ((qin.waiting() == true)&&(alive==true))
			{
				int x,y;
				alive = sna.move();
				sna.gethead(x,y);
				if(map.PeletCheck(x,y)==true){score=score+level;hud.setscore(score);}
				Sleep(120-(level*30));
			}
		}


		gameover();
		crs.clearAll();

	}
	void SnakeController::levelselect()
	{
		crs.clearAll();
		char key;
		cout<<"What difficulty would you like?"<<endl;
		cout<<"A)Slow"<<endl;
		cout<<"B)Medium"<<endl;
		cout<<"C)fast"<<endl;
		qin>>key;
		key=toupper(key);
		switch (key)
		{
		case 'A':level=1;  break;
		case 'B':level=2;   break;
		case 'C':level=3;   break;
		default: levelselect();break;
		}

	}
	void SnakeController::mapselect()
	{
		LList <string> maps;
		crs.clearAll();
		cout<<"Please select a map:"<<endl;
		int count =0;
		int input;
		ifstream ifs;
		const string file = "smaps.dat";
		ifs.open(file,ios::in);

		while (!ifs.eof()) //get maps
		{
			ifs>>maps[count];
			count++;
		}

		for (int i=0; i<maps.GetSize(); ++i) //display map names
		{
			cout<<i+1<<") "<<maps[i]<<endl;
		}
		cout<<endl<<"Please Enter A Selection: ";
		bool valid = false;
		while (valid ==false) //get valid input
		{
			cin>>input;
			if ((input<=0)||(input>maps.GetSize()))
			{cout<<"Invalid Entry! Try Again  :";}
			else
			{valid = true;}
		}
		mapname = maps[input-1];
	}
	void SnakeController::showinstructions()
	{
		crs.clearAll();
		cout<<"Welcome To My Snake Game"<<endl<<endl;
		cout<<"There are 3 difficultys"<<endl;
		cout<<endl<<"Move using the ";
		cl.setForeground(Yellow);
		cl.setForeBright(true);
		cout<<"W,A,S,D";
		cl.setForeground(White);
		cout<<" keys"<<endl;
		cout<<"Eat pelets to get points"<<endl;
		cout<<"# means a wall, dont run into it or youl die, also dont run into yourself!"<<endl;
		cout<<endl<<"Press any key to begin";
		qin.get();
	}

	void SMaps::GeneratePelet()
	{
		int X,Y;
		Random x,y;
		x.setLimits(1,79);
		y.setLimits(1,39);
		bool valid = false;

		while (valid == false)//generate valid pelet 
		{
			X=x.get();
			Y=y.get();
			if ((CollisionCheck(X,Y) ==false)&&(sna->collisioncheck(X,Y)==false)){valid=true;mapstore[Y][X]='*';crs.setPosition(X,Y);cout<<"*";} //save pelet pos and output
		}
	}
	void SMaps::load(string location)
	{
		string line;
		ifstream ifs;
		ifs.open(location,ios::in);
		for(int i=0; i<40;++i)
		{
			getline(ifs,line);
			for (int a=0; a<80;++a)
			{
				mapstore[i][a]=line[a];
			}
		}
		ifs.close();
	}
	void SMaps::erase()
	{
		crs.setPosition(0,0);
		cl.setBackground(Black);
		cl.setForeground(White);
		for(int i =0; i<40;++i)
		{
			crs.setPosition(0,i);
			cout.width(80);
			cout<<"";
		}
	}
	bool SMaps::CollisionCheck(int x, int y)
	{
		if (mapstore[y][x] == '#') return true;
		return false;
	}
	bool SMaps::PeletCheck(int x, int y)
	{
		if (mapstore[y][x] == '*') {mapstore[y][x]=' '; GeneratePelet(); sna->add(); return true;}
		return false;
	}
	void SMaps::Draw()
	{
		crs.setPosition(0,0);
		for(int i=0; i<40;++i)
		{
			for (int a=0; a<80;++a)
			{
				crs.setPosition(a,i);
				if (mapstore[i][a] == '#') cl.setForeground(Blue);
				cout<<mapstore[i][a];
				if (mapstore[i][a] == '#')cl.setForeground(White);
			}
		}
	}

	void snake::draw()
	{
		if (addone ==true)
		{
			addone=false;
		}
		else
		{
			crs.setPosition(tempx,tempy);
			cout<<" ";
		}
		crs.setPosition(bodyx[0],bodyy[0]);
		cout<<"@"; //cout the head
		for (int i=1; i<bodyx.GetSize();++i)
		{
			crs.setPosition(bodyx[i],bodyy[i]);
			cout<<"o"; //cout the body
		}
		//crs.setPosition(1,1);cout<<"x: "<<bodyx[0]<<" y: "<<bodyy[0];              //debug code
		//crs.setPosition(1,2);cout<<"x: "<<bodyx[1]<<" y: "<<bodyy[1];              //debug code
		//crs.setPosition(1,3);cout<<"x: "<<bodyx[2]<<" y: "<<bodyy[2];              //debug code
		//crs.setPosition(1,4);cout<<"x: "<<bodyx[3]<<" y: "<<bodyy[3];qin.get();    //debug code
		

	}
	void snake::erase()
	{
		for(int i=0; i<bodyx.GetSize();i++)
		{
			crs.setPosition(bodyx[i],bodyy[i]);
			cout<<" ";
		}
	}
	bool snake::collisioncheck(int x, int y)
	{
		for (int i=0; i<bodyx.GetSize();++i)
		{
			if ((bodyx[i]==x)&&(bodyy[i]==y)){return true;}
		}
		return false;
	}
	bool snake::move()
	{
		int movex =0,movey =0;
		if(heading == Up){movex=0;movey =-1;}
		if(heading == Down){movex=0;movey =1;}
		if(heading == Left){movex=-1;movey =0;}
		if(heading == Right){movex=1;movey =0;}

		if(collisioncheck(bodyx[0]+movex,bodyy[0]+movey) ==true){return false;} //if cant move return false
		if(map->CollisionCheck(bodyx[0]+movex,bodyy[0]+movey) == true){return false;}//if cant move return false

		//move snake
		int temp2x,temp2y;
		tempx = bodyx[0];
		tempy = bodyy[0];
		bodyx[0]=bodyx[0]+movex; //move head first
		bodyy[0]=bodyy[0]+movey;

		if(bodyx[0] == 80)bodyx[0]=0; // if dropping off end of map set to other side
		else 
			if (bodyx[0] == -1)bodyx[0]=79;
			else
				if(bodyy[0] == -1)bodyy[0]=39;
				else
					if(bodyy[0] == 40)bodyy[0]=0;

		for (int i=1; i<bodyx.GetSize();++i) //set body to next pos 
		{
			temp2x = bodyx[i];//take a temp for the next body peice
			temp2y = bodyy[i];//take a temp for the next body peice
			bodyx[i]=tempx; //set x to prev loc
			bodyy[i]=tempy; //set y to prev loc
			tempx = temp2x;
			tempy = temp2y;
		}
		if (addone ==true){bodyx[bodyx.GetSize()]=tempx;bodyy[bodyy.GetSize()]=tempy;} //if adding length do this
		draw();
		return true;

	}
	bool snake::offmap()
	{
		if (bodyx[0] == -1){bodyx[0]=80;return true;} // if dropping off end of map set to other side
		else 
			if(bodyx[0] == 81){bodyx[0]=0;return true;}
			else
				if(bodyy[0] == -1){bodyy[0]=40;return true;}
				else
					if(bodyy[0] == 41){bodyy[0]=0;return true;}
					return false;
	}



	void snakeScoreBoard::LoadScores()
	{
		const string file =filenamecheck(mapname)+ "Snakescores.sav";
		ifstream ifs;
		ifs.open(file,ios::in);
		int count=0;
		if(ifs)
		{
			while (!ifs.eof()  )
			{
				ifs>>play[count];
				ifs>>scores[count];
				++count;
			}
		}
		ifs.close();
	}
	void snakeScoreBoard::SaveScores()
	{
		ofstream ofs;
		const string file = filenamecheck(mapname)+ "Snakescores.sav";
		ofs.open(file,ios::out); //open file
		for(int i =0; i<scores.GetSize(); ++i)
		{
			ofs<<play[i]<<endl;
			ofs<<scores[i]<<endl;
		}
		ofs.close();//close file
	}
	void snakeScoreBoard::DisplayScores(int x, int y)
	{
		xpos =x;
		ypos = y;
		cl.setBackground(Green);
		crs.setPosition(x,y);
		cout.width(40);
		cout<<"";
		crs.setPosition(x,y+30);
		cout.width(41);
		cout<<"";
		for(int i=0; i<30;++i)
		{
			crs.setPosition(x,y+i);
			cout<<" ";
			crs.setPosition(x+40,y+i);
			cout<<" ";
		}
		crs.setPosition(x+11,y+3);
		cl.setBackground(Black);
		cout<<"!!MAP HIGH SCORES!!";
		for(int i=0; ((i<scores.GetSize())&&(i<10));++i)
		{
			crs.setPosition(x+10,y+6+(i*2));
			cout<<i+1<<". "<<play[i]<<myplayer.GetUsername()<<"  :  Score - "<<scores[i];
		}
	}
	bool snakeScoreBoard::CheckScore(int score)
	{
		for(int i =0; i<scores.GetSize(); ++i)
		{
			if (score > scores[i]) return true;
		}
		return false;
	}
	void snakeScoreBoard::AddScore(int score, string username)
	{
		for(int i =0; i<scores.GetSize(); ++i)
		{
			if (score > scores[i]) {scores.insert(i,score);play.insert(i,username); break;}
		}

		if (scores.GetSize() > 10)
		{
			for (int i=10; i<scores.GetSize();++i)
			{
				scores.remove(i);
			}
		}
	}
	void snakeScoreBoard::erase()
	{
		cl.setBackground(Black);
		crs.setPosition(xpos,ypos);
		for(int i=0; i<30;++i)
		{
			cout.width(40);
			cout<<"";
		}
	}


	void snakeHUD::drawscore()
	{
		cl.setForeground(White);
		crs.setPosition(12,42);
		cout.width(5);//clear current score
		cout<<"";
		crs.setPosition(12,42);
		cout<<scr;
	}
	void snakeHUD::drawlevel()
	{
		cl.setForeground(White);
		crs.setPosition(42,42);
		cout.width(5);//clear current level
		cout<<"";
		crs.setPosition(67,42);
		cout<<lev;
	}
	snakeHUD::snakeHUD()
	{
		cl.setForeground(White);
		crs.setPosition(5,42);
		cout<<"Score: ";
		crs.setPosition(60,42);
		cout<<"Level: ";

	}

}//end namespace