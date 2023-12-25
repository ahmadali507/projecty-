#include "fundamentals.h"
#include "helper.h"
#include "display.h"
#include "maze.h"
#include "modes.h"
#include "menu.h"

int main()
{
	// const char *filePath = "C:/Users/Track Computers/Desktop/track.wav";
	// playAudio(filePath);

	changeSystemColor();
	mainMenu();

	system("cls");

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