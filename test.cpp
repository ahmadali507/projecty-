#include "fundamenta.h"
#include "helper.h"
#include "display.h"
#include "maze.h"
#include "mode.h"

int main()
{
	 //const char *filepath = "c:/users/track computers/desktop/track.wav";
	 //playaudio(filepath);

	system("color e0");
	 
	//centerText("Welcome to the game : MAZE QUEST the enigmatic lybrinth,");
	string welcomeline = "WELCOME TO THE GAME ::: THE MAZE QUEST :: THE ENIGMATIC LYBRINTH";
	animateText(welcomeline); 
	 cout << endl;
	 Sleep(1100);
	 system("cls");
	 centerText(" ----- |    | |----    ||    /|   /|   ____ -----     --  |   | -----   /  ----- ");
	 cout << endl;
	 centerText("   |   |____| |____    | |  / |  /__|     / |____    /  | |   | |___   /_    |   ");
	 cout << endl;
	 ;
	 centerText("   |   |    | |____    |  |/  | /    |   /  |____    |__/ |___/ |____   /    |   ");
	 cout << endl;
	 centerText("   |   |    |          |      |/      | /___            |              /     |   ");
	 cout << endl;
	 cout << "press any key to continue. ";
	 cin.ignore(); 
	 enter = _getch();
	 loadingbar();
	 system("cls");
	 //asking the user to enter the name by initializing the global variable.
	 string askName = "PLEASE ENTER YOUR GOOD NAME TO CONTINUE THE GAME. ";
	 cout << endl;
	 // username is a global variable that is defined up in the section. 
	 cin.ignore(); 
	 animateText(askName); 
	 getline(cin, username);
	 system("cls");

	 // it depends upon the user that what username he chooses. 
	 // convertint the string to the uppercase and then displaying it in on the console window. 
	 string abc = "WELCOME TO THE GAME MR.";
	 for (char& c : username) {
		 c = toupper(c); 
	 }
	 animateText(abc); 
	 animateText(username);
	 // using the cin.ignore to empty the console buffer. 
	 cin.ignore(); 
	 Sleep(500); 

	 system("cls"); 
	 // cin >> response;
	string modeOptions[3] = { "Classic", "Storyline", "Timetrial" };
	response = displayOptions(modeOptions, 3);
	switch (response)
	{
	case 0:
		classic();
		break;
	case 1:
	    storyline();
		break;
	case 2:
		timetrail();
		break;
	}

	ofstream out("Source2.txt", ios::app);
	if (out.is_open())
	{
		out << endl
			<< username << "\t\t\t\t\t" << score << endl;
		out.flush(); 
		out.close();
	}

	else
		cout << "unable to load file ";
	return 0;
}