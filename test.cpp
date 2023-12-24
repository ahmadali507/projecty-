#include "fundamentals.h"
#include "helper.h"
#include "display.h"
#include "maze.h"
#include "modes.h"

int main()
{
	// const char *filePath = "C:/Users/Track Computers/Desktop/track.wav";
	// playAudio(filePath);

	system("color e0");
	// centerText("Welcome to the game : MAZE QUEST the enigmatic lybrinth,");
	// cout << endl;
	// Sleep(900);
	// system("cls");
	// centerText(" ----- |    | |----    ||    /|   /|   ____ -----     --  |   | -----   /  ----- ");
	// cout << endl;
	// centerText("   |   |____| |____    | |  / |  /__|     / |____    /  | |   | |___   /_    |   ");
	// cout << endl;
	// ;
	// centerText("   |   |    | |____    |  |/  | /    |   /  |____    |__/ |___/ |____   /    |   ");
	// cout << endl;
	// centerText("   |   |    |          |      |/      | /___            |              /     |   ");
	// cout << endl;
	// cout << "press any key to continue. ";
	// enter = _getch();
	// loadingbar();
	// system("cls");
	// asking the user to enter the name by initializing the global variable.
	// cout << "Please enter your name. ";
	// getline(cin, username);
	system("cls");

	// centerText("\x1b[36mWELCOME TO THE GAME MR.\x1b[0m");
	// cout << username << endl;

	// cin >> response;
	string modeOptions[3] = {"Classic", "Storyline", "Timetrial"};
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
		out.close();
	}
	else
		cout << "unable to load file ";
	return 0;
}