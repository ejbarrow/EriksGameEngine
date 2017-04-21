//  @ Project : Pacman
//  @ File Name : game_pacman.cpp
//  @ Date : 15/04/2012
//  @ Author : Erik Barrow
//
//

#include "game_pacman.h"



namespace games //Start Namespace
{


	void PacController::Levelspeedcalc()
	{
		LevelSpeeds[0] = CalcLevel<0>::VALUE;
		LevelSpeeds[1] = CalcLevel<1>::VALUE;
		LevelSpeeds[2] = CalcLevel<2>::VALUE;
		LevelSpeeds[3] = CalcLevel<3>::VALUE;
		LevelSpeeds[4] = CalcLevel<4>::VALUE;
		LevelSpeeds[5] = CalcLevel<5>::VALUE;
		LevelSpeeds[6] = CalcLevel<6>::VALUE;
		LevelSpeeds[7] = CalcLevel<7>::VALUE;
		LevelSpeeds[8] = CalcLevel<8>::VALUE;
		LevelSpeeds[9] = CalcLevel<9>::VALUE;
		LevelSpeeds[10] = CalcLevel<10>::VALUE;
		LevelSpeeds[11] = CalcLevel<11>::VALUE;
		LevelSpeeds[12] = CalcLevel<12>::VALUE;
		LevelSpeeds[13] = CalcLevel<13>::VALUE;
		LevelSpeeds[14] = CalcLevel<14>::VALUE;
		LevelSpeeds[15] = CalcLevel<15>::VALUE;
		LevelSpeeds[16] = CalcLevel<16>::VALUE;
		LevelSpeeds[17] = CalcLevel<17>::VALUE;
		LevelSpeeds[18] = CalcLevel<18>::VALUE;
		LevelSpeeds[19] = CalcLevel<19>::VALUE;
		LevelSpeeds[20] = CalcLevel<20>::VALUE;
		LevelSpeeds[21] = CalcLevel<21>::VALUE;
		LevelSpeeds[22] = CalcLevel<22>::VALUE;
		LevelSpeeds[23] = CalcLevel<23>::VALUE;
		LevelSpeeds[24] = CalcLevel<24>::VALUE;
		LevelSpeeds[25] = CalcLevel<25>::VALUE;
		LevelSpeeds[26] = CalcLevel<26>::VALUE;
		LevelSpeeds[27] = CalcLevel<27>::VALUE;
		LevelSpeeds[28] = CalcLevel<28>::VALUE;
		LevelSpeeds[29] = CalcLevel<29>::VALUE;
		LevelSpeeds[30] = CalcLevel<30>::VALUE;
		LevelSpeeds[31] = CalcLevel<31>::VALUE;
		LevelSpeeds[32] = CalcLevel<32>::VALUE;
		LevelSpeeds[33] = CalcLevel<33>::VALUE;
		LevelSpeeds[34] = CalcLevel<34>::VALUE;
		LevelSpeeds[35] = CalcLevel<35>::VALUE;
		LevelSpeeds[36] = CalcLevel<36>::VALUE;
		LevelSpeeds[37] = CalcLevel<37>::VALUE;
		LevelSpeeds[38] = CalcLevel<38>::VALUE;
		LevelSpeeds[39] = CalcLevel<39>::VALUE;
		LevelSpeeds[40] = CalcLevel<40>::VALUE;
		LevelSpeeds[41] = CalcLevel<41>::VALUE;
		LevelSpeeds[42] = CalcLevel<42>::VALUE;
		LevelSpeeds[43] = CalcLevel<43>::VALUE;
		LevelSpeeds[44] = CalcLevel<44>::VALUE;
		LevelSpeeds[45] = CalcLevel<45>::VALUE;
		LevelSpeeds[46] = CalcLevel<46>::VALUE;
		LevelSpeeds[47] = CalcLevel<47>::VALUE;
		LevelSpeeds[48] = CalcLevel<48>::VALUE;
		LevelSpeeds[49] = CalcLevel<49>::VALUE;
	}

	void PacController::Run()
	{
		SetConsoleTitle("Eriks Game Controller - Pacman");
		int px,py,gx,gy; //to store starting positions of pacman and ghosts
		level=1; //starting level
		score=0; //starting score
		ConsolResize(80,45,50,50); //resize the consol to display the maps
		Levelspeedcalc(); //run template meta function to calculate level speeds
		ShowInstructions(); //show user the instructions
		SelectMap(); //let the user choose a map
		Maps map; 
		HUD hud;
		Pacman pac;
		RedGhost Blinky;
		PinkGhost Pinky;
		TurquoiseGhost Inky;
		GreenGhost Clyde;
		map.LoadMap(mapname); //load the map chosen
		map.getGhostStart(gx,gy); //get the starting positions for ghosts
		map.getPacStart(px,py); //get the starting positions for pacman
		map.Draw(); //draw the map

		pac.setlocation(px,py); //set the starting positions  
		Blinky.setstart(gx,gy); //set the starting positions  
		Pinky.setstart(gx,gy); //set the starting positions  
		Inky.setstart(gx,gy); //set the starting positions  
		Clyde.setstart(gx,gy); //set the starting positions  

		pac.passmap(&map); //setup pointers
		pac.passghosts(&Blinky,&Clyde,&Inky,&Pinky); //setup pointers
		pac.passhud(&hud); //setup pointers

		hud.setscore(score); //setup head up display
		pac.EditLifes(3);// setup head up display

		Blinky.passscore(&score); //setup pointers
		Inky.passscore(&score); //setup pointers
		Pinky.passscore(&score); //setup pointers
		Clyde.passscore(&score); //setup pointers

		Blinky.passmap(&map); //setup pointers
		Blinky.passpac(&pac); //setup pointers
		Pinky.passmap(&map); //setup pointers
		Pinky.passpac(&pac); //setup pointers
		Inky.passmap(&map); //setup pointers
		Inky.passpac(&pac); //setup pointers
		Clyde.passmap(&map); //setup pointers
		Clyde.passpac(&pac); //setup pointers
		Stopwatch scat; //to time the length of scat
		bool scatt=false; //to set the sound for scat on and off
		bool palive = true; //to tell the loops if pacman is alive
		char Keypress;
		PlaySound(TEXT("pacman_intro.wav"), NULL, SND_FILENAME);// Sound from http://www.wavsource.com/video_games/pac-man.htm //sound info http://msdn.microsoft.com/en-us/library/windows/desktop/dd743680%28v=vs.85%29.aspx
		while((pac.getlifes()>0)&&(level<=50)) //while alive run
		{
			hud.setlevel(level);
			while ((map.getPelletCount()>0)&&(pac.getlifes()>0))//while level still running
			{
				while ((map.getPelletCount()>0)&&(pac.getlifes()>0))//while pac is alive //(pac.CheckAlive() ==true)&&
				{
					while((qin.waiting() == true)&&(palive!=false)&&(map.getPelletCount()>0))//while no key pressed
					{
						int x,y; //to store pacman position
						pac.Move();//move pacman
						pac.Getlocation(x,y);//find pacman				//SOUND from http://www.digitpress.com/dpsoundz/soundfx.htm   //purges sound if exiting scat mode before trying to play
						if (map.PointCheck(x,y) == true){++score;if((scat.read()>10)||(scatt==false)){if(scat.read()>10)PlaySound(NULL, NULL, SND_ASYNC + SND_PURGE);PlaySound(TEXT("wakka.wav"), NULL,SND_NOSTOP + SND_ASYNC);scat.stop();scat.reset();scatt=false;}} //check pelet & play pelet sound if not in scat mode
						if (map.PowerPelletCheck(x,y) == true) // check power pellet
						{
							score=score+10; 
							if(Blinky.CheckAlive() == true) Blinky.SetScatter(true); // Check ghost alive before setting scatter
							if(Inky.CheckAlive() == true) Inky.SetScatter(true);// Check ghost alive before setting scatter
							if(Clyde.CheckAlive() == true) Clyde.SetScatter(true);// Check ghost alive before setting scatter
							if(Pinky.CheckAlive() == true) Pinky.SetScatter(true);// Check ghost alive before setting scatter
							PlaySound(TEXT("siren.wav"), NULL, SND_ASYNC + SND_LOOP);// Sound from http://soundfxcenter.com/download-sound/pacman-waka-waka-sound-effect/
							scat.start(); //start scat stopwatch (the stopwatch and bool value Is only for the benefit of sound - the ghosts keep their own scat counters as if they are eaten they leave scat mode
							scatt = true; //set scat on
						}
						if((scat.read()>10)&&(scatt==true)){PlaySound(NULL, NULL, SND_ASYNC + SND_PURGE);scat.stop();scat.reset();scatt=false;} //stop scat siren when scat finished
						if(pac.CheckAlive()==false)palive =false ;//check alive //Run before and after ghost move to make sure collision has not been missed
						Inky.move();//move ghosts
						Blinky.move();//move ghosts
						Pinky.move();//move ghosts
						Clyde.move();//move ghosts
						hud.setscore(score);//update score
						Sleep(LevelSpeeds[level-1]);//use sleep to produce pre defined delay. 
						if(pac.CheckAlive()==false)palive =false ;//check alive
						if(palive==false){PlaySound(TEXT("pacdies.wav"), NULL, SND_FILENAME);break;} // sound File from http://www.wavsource.com/video_games/pac-man.htm
						if (map.getPelletCount()==0)PlaySound(TEXT("intermission.wav"), NULL, SND_FILENAME);// Sound from http://soundfxcenter.com/download-sound/pacman-waka-waka-sound-effect/
					}

					if (map.getPelletCount()>0) //Deal with keypress if not end of map
					{
						Keypress=getch();
						Keypress=toupper(Keypress);
						if (Keypress =='W'){pac.SetDirection(Up);}
						if (Keypress =='A'){pac.SetDirection(Left);}
						if (Keypress =='S'){pac.SetDirection(Down);}
						if (Keypress =='D'){pac.SetDirection(Right);}
					}

					if (palive==false)
					{
						pac.EditLifes(pac.getlifes()-1);
						pac.setlocation(px,py);
						Inky.setpos(gx,gy);
						Inky.reset();
						Pinky.setpos(gx,gy);
						Pinky.reset();
						Clyde.setpos(gx,gy);
						Clyde.reset();
						Blinky.setpos(gx,gy);
						Blinky.reset();
						palive=true;
					}
				}
			}

			++level;// set next level
			map.Erase();
			map.LoadMap(mapname);//reset map for next level
			map.Draw();//reset map for next level
			pac.setlocation(px,py);//reset map for next level
			Inky.setpos(gx,gy);//reset map for next level
			Inky.reset();//reset map for next level
			Pinky.setpos(gx,gy);//reset map for next level
			Pinky.reset();//reset map for next level
			Clyde.setpos(gx,gy);//reset map for next level
			Clyde.reset();//reset map for next level
			Blinky.setpos(gx,gy);//reset map for next level
			Blinky.reset();//reset map for next level
			palive=true;//reset map for next level

		}
		gameover();
	}

	void PacController::gameover()
	{
		crs.clearAll();
		ScoreBoard sb;
		sb.setmapname(mapname);
		sb.LoadScores();
		if (sb.CheckScore(score)==true)sb.AddScore(score,usern);
		sb.DisplayScores(20,5);
		sb.SaveScores();
		//myplayer.Addscore(score,Gpacman);  //save users pac highscore
		qin.get();
	}

	void PacController::SelectMap()
	{
		LList <string> maps;
		crs.clearAll();
		cout<<"Please select a map:"<<endl;
		int count =0;
		int input;
		ifstream ifs;
		const string file = "pmaps.dat";
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

	void PacController::ShowInstructions()
	{
		crs.clearAll();
		cout<<"Welcome To My Pacman Game"<<endl<<endl;
		cout<<"There are 50 levels, to complete a level you must eat all the pelets"<<endl;
		cout<<"Eating power pelets allows you to eat ghosts"<<endl;
		cout<<"If you run out of lifes it is game over"<<endl<<endl;
		cout<<"You can use the ";
		cl.setForeground(Yellow);
		cl.setForeBright(true);
		cout<<"W,A,S,D";
		cl.setForeground(White);
		cout<<" Keys to move pacman"<<endl;
		cout<<"!!If you die or finish a level press any key to continue!!"<<endl<<endl;
		cout<<"Pelets are worth 1 point!"<<endl;
		cout<<"Power Pelets are worth 10 points!"<<endl;
		cout<<"Eating a Ghost is worth 5 points!"<<endl;
		cout<<endl<<"Press any key to begin";
		qin.get();
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Ghost::movedead()
	{
		SetScatter(false);
		Scat.stop();
		Scat.reset();
		int x,y;
		map->getGhostStart(x,y);
		if ((xpos != x)&&(ypos !=y))setpos(x,y);
		if (Dea.read() >=8){galive=true;Dea.stop();Dea.reset();}
	}

	void Ghost::movescatter()
	{
		if (Scat.read()>=10){gscatter=false;Scat.stop();Scat.reset();}
		if ((heading == Up) && (map->CollisionCheck(xpos,ypos-1)==false)){setpos(xpos,ypos-1);} //if heading up and can move
		else
			if ((heading == Down) && (map->CollisionCheck(xpos,ypos+1)==false)){setpos(xpos,ypos+1);}//if heading down and can move
			else
				if ((heading == Right) && (map->CollisionCheck(xpos+1,ypos)==false)){setpos(xpos+1,ypos);}//if heading right and can move
				else
					if ((heading == Left) && (map->CollisionCheck(xpos-1,ypos)==false)){setpos(xpos-1,ypos);}//if heading left and can move
					else //If you cant continue in the current direction choose a new direction
					{
						Random r;
						r.setLimits(1,4);
						bool clear =false;
						while(clear==false)
						{
							switch (r.get())
							{
							case 1: {if(map->CollisionCheck(xpos-1,ypos)==false){heading=Left; clear = true;setpos(xpos-1,ypos);}} break; //left
							case 2: {if(map->CollisionCheck(xpos+1,ypos)==false){heading=Right; clear = true;setpos(xpos+1,ypos);}} break; //right
							case 3: {if(map->CollisionCheck(xpos,ypos-1)==false){heading=Up; clear = true;setpos(xpos,ypos-1);}} break; //up 
							case 4: {if(map->CollisionCheck(xpos,ypos+1)==false){heading=Down; clear = true;setpos(xpos,ypos+1);}} break; //down
							default:    break;
							}
						}
					}
	}

	void Ghost::movealive()
	{

	}

	bool Ghost::CheckColision(int x, int y)
	{
		if ((x == xpos) && (y==ypos))return true;
		else return false;
	}

	void Ghost::SetScatter(bool scatter)
	{
		gscatter=scatter; 
		if (gscatter==true)Scat.start();
	}

	void Ghost::SetAlive(bool alive)
	{
		galive=alive;
		if (galive == false){Dea.start();scores=scores+5;}
	}

	void Ghost::move()
	{
		if (gscatter==true)movescatter();
		else
			if (galive==true) movealive();
			else
				if (galive==false) movedead();
	}

	void Ghost::setpos(int x, int y)
	{
		if(x == 80)x=0; // if dropping off end of map set to other side
		else 
			if (x == -1)x=79;
			else
				if(y == -1)y=39;
				else
					if(y == 40)y=0;

		//if(xpos == NULL){xpos =x; ypos=y;} //portals put this out of use
		crs.setPosition(xpos,ypos);
		cl.setForeground(White);
		cl.setBackground(Black);
		cout<<" "; //erase ghost

		prevlochar = map->getchar(xpos,ypos); 
		crs.setPosition(xpos,ypos);
		cout<<prevlochar; // Replace any characters it was over

		xpos = x; //new coords
		ypos = y;
		crs.setPosition(xpos,ypos);
		cl.setForeBright(true);
		cl.setForeground(Col);
		if (gscatter ==true)cl.setForeground(Blue);
		cout<<gho; //output ghost in new pos
		cl.setForeground(White);
	}

	void Ghost::setstart(int x, int y)
	{
		xpos = x; //start coords
		ypos = y;
		crs.setPosition(xpos,ypos);
		cl.setForeBright(true);
		cl.setForeground(Col);
		cout<<gho; //output ghost in new pos
		cl.setForeground(White);
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Maps::LoadMap(string location)
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
		ifs>>ghostStartx;
		ifs>>ghostStarty;
		ifs>>PacStartX;
		ifs>>PacStartY;
		ifs.close();

	}

	char Maps::getchar(int x, int y)
	{
		char val;
		val = mapstore[y][x] ;
		return val;
	}


	void Maps::Draw()
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

	void Maps::Erase()
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

	bool Maps::CollisionCheck(int x, int y)
	{
		if(x == 80)x=0; // if dropping off end of map set to other side
		else 
			if (x == -1)x=79;
			else
				if(y == -1)y=39;
				else
					if(y == 40)y=0;

		if (mapstore[y][x] == '#') return true;
		return false;
	}

	bool Maps::PointCheck(int x, int y)
	{
		if (mapstore[y][x] == '.') {mapstore[y][x]=' '; return true;}
		return false;
	}

	bool Maps::PowerPelletCheck(int x, int y)
	{
		if (toupper(mapstore[y][x]) == 'O') {mapstore[y][x]=' ';return true;}
		return false;
	}

	void Maps::getPacStart(int & x, int & y)
	{
		x=PacStartX;
		y=PacStartY;
	}

	void Maps::getGhostStart(int &x, int &y)
	{
		x=ghostStartx;
		y=ghostStarty;
	}

	int Maps::getPelletCount()
	{
		int pcount=0;
		for (int i=0; i<40; ++i)
		{
			for (int a=0; a<80;++a)
			{
				if ((mapstore[i][a] == '.')||(toupper(mapstore[i][a]) == 'O'))++pcount;
			}
		}
		return pcount;
	}

	/////////////////////////////////////////////////////////////////

	Pacman::Pacman()
	{
		Lifes =3;
	}

	void Pacman::SetDirection(direction move)
	{
		NextDirection = move;
	}

	void Pacman::Move()
	{
		int nextx =0 , nexty = 0;
		if (NextDirection == Up){nextx = xlocation; nexty = ylocation-1;}
		if (NextDirection == Down){nextx = xlocation; nexty = ylocation+1;}
		if (NextDirection == Left){nextx = xlocation-1; nexty = ylocation;}
		if (NextDirection == Right){nextx = xlocation+1; nexty = ylocation;}

		if(nextx == 80)nextx=0; // if dropping off end of map set to other side
		else 
			if (nextx == -1)nextx=79;
			else
				if(nexty == -1)nexty=39;
				else
					if(nexty == 40)nexty=0;

		if (map->CollisionCheck(nextx,nexty) == false) // If next direction is free to move do this
		{
			crs.setPosition(xlocation,ylocation);
			cout<<" ";
			crs.setPosition(nextx,nexty);
			cl.setForeground(Yellow);
			cout<<pac;
			cl.setForeground(White);
			CurrentDirection = NextDirection;
			xlocation = nextx;
			ylocation = nexty;
		}
		else // If next direction is not free to move try current direction
		{
			if (CurrentDirection == Up){nextx = xlocation; nexty = ylocation-1;}
			if (CurrentDirection == Down){nextx = xlocation; nexty = ylocation+1;}
			if (CurrentDirection == Left){nextx = xlocation-1; nexty = ylocation;}
			if (CurrentDirection == Right){nextx = xlocation+1; nexty = ylocation;}
			if(map->CollisionCheck(nextx,nexty) == false)// if current direction is clear
			{
				crs.setPosition(xlocation,ylocation);
				cout<<" ";
				crs.setPosition(nextx,nexty);
				cl.setForeground(Yellow);
				cout<<pac;
				cl.setForeground(White);
				xlocation = nextx;
				ylocation = nexty;
			}

		}
	}

	void  Pacman::setlocation(int x, int y)
	{

		if(x == 80)x=0; // if dropping off end of map set to other side
		else 
			if (x == -1)x=79;
			else
				if(y == -1)y=39;
				else
					if(y == 40)y=0;

		if ((xlocation != NULL)&&(ylocation !=NULL)) //if already set remove last position
		{
			crs.setPosition(xlocation,ylocation);
			cout<<" ";
		}
		crs.setPosition(x,y);
		cl.setForeground(Yellow);
		cout<<pac;
		cl.setForeground(White);
		xlocation = x;
		ylocation = y;
	}


	void Pacman::EditLifes(int life)
	{
		Lifes = life;
		hud->setlifes(Lifes);
	}

	bool Pacman::CheckAlive()
	{

		if (red->CheckColision(xlocation,ylocation)==true) //do if pac is at same pos as ghost
		{									
			if(red->checkscatter()==false) {return false;} //check if scatter is on and if not then pac dead
			if(red->checkscatter()==true){red->SetAlive(false);red->SetScatter(false);}//if collision and scatter on then set ghost to dead
		}

		if (green->CheckColision(xlocation,ylocation)==true) //do if pac is at same pos as ghost
		{
			if(green->checkscatter()==false) {return false;} //check if scatter is on and if not then pac dead
			if(green->checkscatter()==true){green->SetAlive(false);green->SetScatter(false);}//if collision and scatter on then set ghost to dead
		}

		if (turq->CheckColision(xlocation,ylocation)==true) //do if pac is at same pos as ghost
		{
			if(turq->checkscatter()==false) {return false;} //check if scatter is on and if not then pac dead
			if(turq->checkscatter()==true){turq->SetAlive(false);turq->SetScatter(false);}//if collision and scatter on then set ghost to dead
		}

		if (pink->CheckColision(xlocation,ylocation)==true) //do if pac is at same pos as ghost
		{
			if(pink->checkscatter()==false) {return false;} //check if scatter is on and if not then pac dead
			if(pink->checkscatter()==true){pink->SetAlive(false);pink->SetScatter(false);}//if collision and scatter on then set ghost to dead
		}


		return true;
	}

	void Pacman::Getlocation(int &x, int &y)
	{
		x= xlocation;
		y= ylocation;
	}

	/////////////////////////////////////////////////////////////////

	void ScoreBoard::LoadScores()
	{

		const string file =filenamecheck(mapname)+ "pacscores.sav";
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

	void ScoreBoard::SaveScores()
	{
		ofstream ofs;
		const string file = filenamecheck(mapname)+ "pacscores.sav";
		ofs.open(file,ios::out); //open file
		for(int i =0; i<scores.GetSize(); ++i)
		{
			ofs<<play[i]<<endl;
			ofs<<scores[i]<<endl;
		}
		ofs.close();//close file
	}

	void ScoreBoard::DisplayScores(int x, int y)
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

	void ScoreBoard::erase()
	{
		cl.setBackground(Black);
		crs.setPosition(xpos,ypos);
		for(int i=0; i<30;++i)
		{
			cout.width(40);
			cout<<"";
		}
	}

	bool ScoreBoard::CheckScore(int score)
	{
		for(int i =0; i<scores.GetSize(); ++i)
		{
			if (score > scores[i]) return true;
		}
		return false;
	}

	void ScoreBoard::AddScore(int score, string username)
	{

		for(int i =0; i<scores.GetSize(); ++i)
		{
			if (score > scores[i]) {scores.insert(i,score);play.insert(i,username); break;}
		}

		if (scores.GetSize() > 10)
		{
			scores.remove(10);
		}

	}

	////////////////////////////////////////////////////////////
	void PinkGhost::movealive()
	{
		movechase();
	}

	void PinkGhost::move()
	{
		delay = 4;
		if(timerstart ==false){ start.start(); timerstart=true;}
		if (start.read() >= delay){firstmove=false;start.stop();} //delayed start - different for each ghost

		if(firstmove ==false)
		{
			if (gscatter==true)movescatter();
			else
				if (galive==true) movealive();
				else
					if (galive==false) movedead();
		}
	}

	void RedGhost::movealive()
	{
		movechase();
	}

	void RedGhost::move()
	{
		delay = 2;
		if(timerstart ==false){ start.start(); timerstart=true;}
		if (start.read() >= delay){firstmove=false;start.stop();} //delayed start - different for each ghost

		if(firstmove ==false)
		{
			if (gscatter==true)movescatter();
			else
				if (galive==false) movedead();
				else
					if (galive==true) movealive();
		}
	}

	void GreenGhost::movealive()
	{
		moverand();
	}

	void GreenGhost::move()
	{
		delay = 1;
		if(timerstart ==false){ start.start(); timerstart=true;}
		if (start.read() >= delay){firstmove=false;start.stop();} //delayed start - different for each ghost

		if(firstmove ==false)
		{
			if (gscatter==true)movescatter();
			else
				if (galive==true) movealive();
				else
					if (galive==false) movedead();
		}
	}

	void TurquoiseGhost::movealive()
	{
		moverand();
	}

	void TurquoiseGhost::move()
	{
		delay = 3;
		if(timerstart ==false){ start.start(); timerstart=true;}
		if (start.read() >= delay){firstmove=false;start.stop();} //delayed start - different for each ghost

		if(firstmove ==false)
		{
			if (gscatter==true)movescatter();
			else
				if (galive==true) movealive();
				else
					if (galive==false) movedead();
		}
	}

	bool Ghost::junction() //check for junction
	{
		int paths=0;

		if(map->CollisionCheck(xpos-1,ypos)==false)++paths;//check left
		if(map->CollisionCheck(xpos+1,ypos)==false)++paths;//check right
		if(map->CollisionCheck(xpos,ypos-1)==false)++paths;//check up
		if(map->CollisionCheck(xpos,ypos+1)==false)++paths;//check down

		if(paths>=3)return true;
		else
			return false;
	}

	void Ghost::movechase() // Practically the same as random, but at junctions trys to make an inteligent decision
	{
		int px,py; 
		pac->Getlocation(px,py);
		int x,y;
		bool chooseNew =false;

		if(junction() == true)//if junction decide where to turn
		{
			// junctions always have at least 3 ways to turn. 
			//so i will calculate a horizontal and vertical value and then choose based on first come first served
			int number;
			bool valid=false;
			direction temp;
			bool above, below, right, left;
			if (xpos<=px){ right=true; left=false;} else { right=false; left=true;}   //locate pac
			if (ypos<=py){ above=false; below=true;} else { above=true; below=false;} //locate pac
			int loopcounter =0; //prevents infanate looping of the calculation, on long loop a random direction will be chosen.

			while(valid ==false)
			{
				if (above==true)number=1;
				if (below==true)number=2;
				if (left==true)number=3;
				if (right==true)number=4;
				switch (number) // In this case ghost is not allowed to move back the direction it came. Unless of course it gets stuck.
				{
				case 1: if((map->CollisionCheck(xpos,ypos-1) == false)&&(heading != Down)&&(above==true)){heading=Up;x=xpos;y=ypos-1; valid=true; } else {above=false;}  break;//up //else if incorect move dont choose again
				case 2: if((map->CollisionCheck(xpos,ypos+1) == false)&&(heading != Up)&&(below==true)){heading=Down;x=xpos;y=ypos+1; valid=true; }else {below=false;}   break;//down  //else if incorect move dont choose again
				case 3: if((map->CollisionCheck(xpos-1,ypos) == false)&&(heading != Right)&&(left==true)){heading=Left;x=xpos-1;y=ypos; valid=true; }else {left=false;}   break;//left  //else if incorect move dont choose again
				case 4: if((map->CollisionCheck(xpos+1,ypos) == false)&&(heading != Left)&&(right==true)){heading=Right;x=xpos+1;y=ypos; valid=true; } else {right=false;}  break;//right  //else if incorect move dont choose again
				}
				if (loopcounter >6){chooseNew=true;break;}
				++loopcounter;
			}

		}
		else //continue on if possible or choose new direction
		{
			if(heading == Up){if(map->CollisionCheck(xpos,ypos-1)==false){x=xpos;y=ypos-1;}else{chooseNew=true;}}
			if(heading == Down){if(map->CollisionCheck(xpos,ypos+1)==false){x=xpos;y=ypos+1;}else{chooseNew=true;}}
			if(heading == Left){if(map->CollisionCheck(xpos-1,ypos)==false){x=xpos-1;y=ypos;}else{chooseNew=true;}}
			if(heading == Right){if(map->CollisionCheck(xpos+1,ypos)==false){x=xpos+1;y=ypos;}else{chooseNew=true;}}
		}

		if (chooseNew == true) //chose new direction
		{

			Random r;
			int number;
			bool valid=false;
			r.setLimits(1,4);
			while(valid ==false)
			{
				number=r.get();
				switch (number)
				{
				case 1: if(map->CollisionCheck(xpos,ypos-1) == false){heading=Up;x=xpos;y=ypos-1; valid=true; }   break;//up
				case 2: if(map->CollisionCheck(xpos,ypos+1) == false){heading=Down;x=xpos;y=ypos+1; valid=true; }   break;//down
				case 3: if(map->CollisionCheck(xpos-1,ypos) == false){heading=Left;x=xpos-1;y=ypos; valid=true; }   break;//left
				case 4: if(map->CollisionCheck(xpos+1,ypos) == false){heading=Right;x=xpos+1;y=ypos; valid=true; }   break;//right
				}
			}

		}

		setpos(x,y);


	}
	void Ghost::moverand() //randomly move the ghost
	{
		int x,y;
		bool chooseNew =false;

		if(junction() == true)//if junction choose new heading
		{
			Random r;
			int number;
			bool valid=false;
			r.setLimits(1,4);
			while(valid ==false)
			{
				number=r.get();
				switch (number) // In this case ghost is not allowed to move back the direction it came.
				{
				case 1: if((map->CollisionCheck(xpos,ypos-1) == false)&&(heading != Down)){heading=Up;x=xpos;y=ypos-1; valid=true; }   break;//up
				case 2: if((map->CollisionCheck(xpos,ypos+1) == false)&&(heading != Up)){heading=Down;x=xpos;y=ypos+1; valid=true; }   break;//down
				case 3: if((map->CollisionCheck(xpos-1,ypos) == false)&&(heading != Right)){heading=Left;x=xpos-1;y=ypos; valid=true; }   break;//left
				case 4: if((map->CollisionCheck(xpos+1,ypos) == false)&&(heading != Left)){heading=Right;x=xpos+1;y=ypos; valid=true; }   break;//right
				}
			}

		}
		else //continue on if possible or choose new direction
		{
			if(heading == Up){if(map->CollisionCheck(xpos,ypos-1)==false){x=xpos;y=ypos-1;}else{chooseNew=true;}}
			if(heading == Down){if(map->CollisionCheck(xpos,ypos+1)==false){x=xpos;y=ypos+1;}else{chooseNew=true;}}
			if(heading == Left){if(map->CollisionCheck(xpos-1,ypos)==false){x=xpos-1;y=ypos;}else{chooseNew=true;}}
			if(heading == Right){if(map->CollisionCheck(xpos+1,ypos)==false){x=xpos+1;y=ypos;}else{chooseNew=true;}}
		}

		if (chooseNew == true) //chose new direction
		{

			Random r;
			int number;
			bool valid=false;
			r.setLimits(1,4);
			while(valid ==false)
			{
				number=r.get();
				switch (number)
				{
				case 1: if(map->CollisionCheck(xpos,ypos-1) == false){heading=Up;x=xpos;y=ypos-1; valid=true; }   break;//up
				case 2: if(map->CollisionCheck(xpos,ypos+1) == false){heading=Down;x=xpos;y=ypos+1; valid=true; }   break;//down
				case 3: if(map->CollisionCheck(xpos-1,ypos) == false){heading=Left;x=xpos-1;y=ypos; valid=true; }   break;//left
				case 4: if(map->CollisionCheck(xpos+1,ypos) == false){heading=Right;x=xpos+1;y=ypos; valid=true; }   break;//right
				}
			}

		}

		setpos(x,y);


	}

	void HUD::drawlife()
	{
		cl.setForeground(White);
		crs.setPosition(67,42);
		cout.width(10);
		cout<<"";//clear current lifes
		crs.setPosition(67,42);

		for (int i=0;i<lif;++i)
		{
			crs.setPosition(67+(i*2),42);
			cl.setForeground(Red);
			cout<<"@";
			cl.setForeground(White);
		}

	}
	void HUD::drawscore()
	{
		cl.setForeground(White);
		crs.setPosition(12,42);
		cout.width(5);//clear current score
		cout<<"";
		crs.setPosition(12,42);
		cout<<scr;
	}

	void HUD::drawlevel()
	{
		cl.setForeground(White);
		crs.setPosition(42,42);
		cout.width(5);//clear current level
		cout<<"";
		crs.setPosition(42,42);
		cout<<lev;
	}

	HUD::HUD()
	{
		cl.setForeground(White);
		crs.setPosition(5,42);
		cout<<"Score: ";
		crs.setPosition(60,42);
		cout<<"Lives: ";
		crs.setPosition(35,42);
		cout<<"Level: ";
	}



}
//end namespace