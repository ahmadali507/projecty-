
#include <iostream>
#include<iomanip>
#include <vector>
#include<fstream>
#include<string>
#include <random>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include<chrono>
#include<thread>
#include<ctime>


using namespace std;


#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m"


// GLOBAL VARIABLES
bool enemytraverser = false; // creating a varibable to keep teh track of associated powerups. 
int response;
int cols = 8;
int rows = 8;
char enter;
int score = 0;
//int Health = 100;
int timelimit = 30;
int levelno = 1;
int seconds = 30;
int encounteredenemies = 0;
int numberOfEnemies = 5;
int numberOfChests = 1;
string username; // making a global variable to ask for the name of the user. 

struct Wall
{
	pair<int, int> cell1;
	pair<int, int> cell2;
};
struct Enemyy
{
	int x;
	int y;
	char enemy;
};
struct monster {
	int health;
	string name;
	string status;

	monster(const int& a, const string& b) : health(a), name(b) {}
};
struct Player
{
	int x;
	int y;
	char player;
	int health;
	bool immune;	// if he has, he can bypass enemy
};
struct Chest {
	char character;
	int x;
	int y;
	string reward; // immune, score, health refill, null.
};
struct Question
{
	string question;
	string answer;

	Question(const string& q, const string& a) : question(q), answer(a) {}
};

struct Riddle {
	string riddle;
	vector<string> options;
	char answer;

	Riddle(const string& r, const vector<string>& a, const char& ans) : riddle(r), options(a), answer(ans) {}
};


Riddle easyRiddles[10] = {
	Riddle("What has keys but can't open locks?", {"A. piano", "B. keyboard", "C. typewriter", "D. computer"}, 'A'),
	Riddle("What has a head and a tail but no body?", {"A. coin", "B. snake", "C. book", "D. ship"}, 'A'),
	Riddle("What has one eye but can't see?", {"A. needle", "B. tornado", "C. potato", "D. fish"}, 'A'),
	Riddle("What is always in front of you but can't be seen?", {"A. The future", "B. The past", "C. The present", "D. Air"}, 'D'),
	Riddle("I am taken from a mine and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?", {"A. A pencil", "B. Gold", "C. Coal", "D. A diamond"}, 'A'),
	Riddle("What comes once in a minute, twice in a moment, but never in a thousand years?", {"A. The letter 'M'", "B. A clock", "C. Laughter", "D. The number 1"},'A'),
	Riddle("The more you take, the more you leave behind. What am I?", {"A. Footsteps", "B. Memories", "C. Presents", "D. Footprints"}, 'D'),
	Riddle("What is full of holes but still holds water?", {"A. A sponge", "B. A net", "C. A sieve", "D. A bottle"}, 'A'),
	Riddle("What has a neck but no head?", {"A. A bottle", "B. A shirt", "C. A snake", "D. A balloon"}, 'B'),
	Riddle("I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?", {"A. An echo", "B. A thought", "C. A dream", "D. A cloud"}, 'D')
};

Question questions[20] = {
	Question("What's the capital of Pakistan", "Islamabad"),
	Question("What's the capital of France", "Paris"),
	Question("What's the capital of France", "Paris"),
	Question("What's the capital of Turkey", "Ankara"),
	Question("What's the capital of China", "Beijing"),
	Question("What's the capital of Japan", "Tokyo"),
	Question("What's the capital of USA", "Washington"),
	Question("What's the capital of England", "London"),
	Question("What's the capital of England", "London"),
	Question("What's the capital of Norway", "Oslo"),
	Question("What's the capital of Spain", "Madrid"),
	Question("What's the capital of Italy", "Room"),
	Question("What's the capital of India", "Delhi"),
	Question("What's the capital of Bangladesh", "Dhaka"),
	Question("What's the capital of Denmark", "Copenhegan"),
	Question("What's the capital of Canada", "Toronto"),
	Question("What's the capital of Srilanka", "Columbo"),
	Question("What's the capital of Saudi Arabia", "Riaz"),
	Question("What's the capital of Saudi Arabia", "Riaz"),
	Question("What's the capital of Portugal", "Lisbon")
};
Player superman;
monster monsters[6] = {
	monster(40, "Kazuma"),
	monster(50, "toughieee"),
	monster(60, "noyan"),
	monster(65, "dirtuuuu"),
    monster(75, "jarasim"),
	monster(100, "DEADLY DIRT")
};

Enemyy * enemiesArray = new Enemyy[numberOfEnemies];
Chest* chestsArray = new Chest[numberOfChests];



// MAZE
int find(vector<int>& parent, int i);
void Union(vector<int>& parent, vector<int>& rank, int x, int y);
vector<vector<char>> generateMaze(int rows, int cols);

// DISPLAY
void displayChest();
void displayEnemiess();
void displayMaze(const vector<vector<char>>& maze);
int chooseOptions(string arr[], int size);
void playAudio(const char* filePath);

// HELPER
//string captureConsoleScreen() {
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
//	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
//
//	COORD bufferSize = consoleInfo.dwSize;
//	DWORD cells = bufferSize.X * bufferSize.Y;
//
//	CHAR_INFO* buffer = new CHAR_INFO[cells];
//	COORD bufferCoord = { 0, 0 };
//	SMALL_RECT readRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };
//
//	ReadConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion);
//
//	string screenContent;
//	for (int i = 0; i < cells; ++i) {
//		screenContent += static_cast<char>(buffer[i].Char.AsciiChar);
//	}
//
//	delete[] buffer;
//	return screenContent;
//}

int getConsoleWidth();
int getConsoleHeight();
char getCharacterAtPosition(int x, int y);
int getASCIIAtPosition(int x, int y);
void moves(int x, int y);
bool isCollisiona(int x, int y);
void loadingbar();
bool enemyCoordiCorrectness(int x, int y);
bool chestCoordiCorrectness(int x, int y);
void askQuestions();
void chestReward();
void centerText(const string& text);
string toLowerCase(string answer);
void askRiddles();
void printOptions(string arr[], int size, int activeOption);
void finalBoss();


// MODES
void encounterChests(int playerX, int chestX, int playerY, int chestY);
void encounterEnemys(int playerX, int enemyX, int playerY, int enemyY);
void timer();
void movePlayerwithtimer(int x, int y, char c);
void movePlayer(int x, int y, char c);
void storyline();
void timetrail();
void classic();
void combat(Player* b, monster* a);

int main()

{
	cout << cols;
	const char* filePath = "C:/Users/Track Computers/Desktop/track.wav";
	playAudio(filePath);


	// making the properties of the struct.
	

	// variable that will determine the input of the user's choice..

	superman.x = 2;
	superman.y = 5;
	superman.player;
	superman.health = 100;

	system("color 0e");
	centerText("Welcome to the game : MAZE QUEST the enigmatic lybrinth,"); cout << endl;
	Sleep(900);
	system("cls");
	centerText(" ----- |    | |----    ||    /|   /|   ____ -----     --  |   | -----   /  ----- ");   cout << endl;
	centerText("   |   |____| |____    | |  / |  /__|     / |____    /  | |   | |___   /_    |   ");   cout << endl;;
	centerText("   |   |    | |____    |  |/  | /    |   /  |____    |__/ |___/ |____   /    |   ");   cout << endl;
	centerText("   |   |    |          |      |/      | /___            |              /     |   ");   cout << endl;
	cout << "press any key to continue. ";
	enter = _getch();
	loadingbar();
	system("cls");
	// asking the user to enter the name by initializing the global variable. 
	cout << "Please enter your name. ";
	getline(cin, username);
	system("cls");

	centerText("\x1b[36mWELCOME TO THE GAME MR.\x1b[0m"); cout << username << endl;

	//cin >> response;
	string optionss[3] = { "Classic", "Storyline", "Timetrial" };
	response = chooseOptions(optionss, 3);
	switch (response)
	{
	case 0: {

		classic();
		break;
	}
	case 1:

		storyline();
		break;
	case 2:
		timetrail();
		break;
	}

	ofstream  out("Source2.txt", ios::app);
	if (out.is_open()) {
		out << endl << username << "\t\t\t\t\t" << score << endl;
		out.close();
	}
	else cout << "unable to load file ";
	return 0;
}




// HELPERS
int getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwSize.X;
}
int getConsoleHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwSize.Y;
}
char getCharacterAtPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) {
		std::cerr << "Invalid handle." << std::endl;
		return '\0';
	}

	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	DWORD charsRead;
	char charBuffer;

	if (!ReadConsoleOutputCharacterA(hConsole, &charBuffer, 1, coord, &charsRead)) {
		std::cerr << "ReadConsoleOutputCharacterA failed." << std::endl;
		return '\0';
	}

	return charBuffer;
}
int getASCIIAtPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) {
		std::cerr << "Invalid handle." << std::endl;
		return 0; // Return 0 to indicate an error
	}

	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	DWORD charsRead;
	char charBuffer;

	if (!ReadConsoleOutputCharacterA(hConsole, &charBuffer, 1, coord, &charsRead)) {
		std::cerr << "ReadConsoleOutputCharacterA failed." << std::endl;
		return 0; // Return 0 to indicate an error
	}

	// Convert the character to ASCII value (cast to int)
	int asciiValue = static_cast<int>(charBuffer);
	return asciiValue;
}
void moves(int x, int y)
{
	// Set console cursor position
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
bool isCollisiona(int x, int y)
{
	// Check for collision with ASCII character 219 or '|'
	char charAtPos = getCharacterAtPosition(x, y);
	return (charAtPos == (char)219 || charAtPos == '|');
}
void loadingbar() {
	system("color 0e");
	system("cls");
	printf("\e[?251");

	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	int bar1 = 177, bar2 = 219;

	cout << "/n/n/n\t\t\t\t\t\t\t\t\t  Loading.....";
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t";
	for (int i = 1; i <= 25; i++)
		cout << (char)bar1;

	cout << "\r";
	cout << "\t\t\t\t\t\t\t\t\t";
	for (int i = 0; i <= 25; i++) {
		cout << (char)bar2;
		Sleep(100);
	}
}
void centerText(const string& text)
{
	int width = getConsoleWidth();
	if (width > 0)
	{
		int padding = (width - static_cast<int>(text.length())) / 2;
		for (int i = 0; i < padding; i++)
		{
			cout << " ";
		}
		cout << text; // Display centered text.
	}
	else
	{
		cerr << "Unable to determine console width." << endl; // Print an error message if console width cannot be determined.
	}
}
string toLowerCase(string answer)
{
	for (char& c : answer)
	{
		c = tolower(c);
	}
	return answer;
}
bool enemyCoordiCorrectness(int x, int y)
{
	return (getCharacterAtPosition(x, y) != (char)219 && getCharacterAtPosition(x, y) != '+');
}
bool chestCoordiCorrectness(int x, int y)
{
	return (getCharacterAtPosition(x, y) != (char)219 && getASCIIAtPosition(x, y) != -80);// -80 is for enemies.

}
void askRiddles() {

	srand(time(0));
	int riddlesLength = size(easyRiddles);
	moves(70, 7);
	// randomly choosing the question based on the value given by the rand function . 
	int index = rand() % riddlesLength;
	char answer;
	Riddle easyRiddle = easyRiddles[index];

	moves(40 + rows, 0);
	cout << "Enemy " << encounteredenemies + 1 << ": Answer this Riddle " << easyRiddle.riddle << endl;
	moves(40 + rows, 1);
	for (int i = 0; i < 4; i++)
	{
		cout << easyRiddle.options[i] << "  ";
	}
	cout << endl << "Your answer: ";

	moves(40 + rows, 2);
	cin >> answer;
	answer = tolower(answer);
	easyRiddle.answer = tolower(easyRiddle.answer);

	// Check the player's answer and affect health accordingly
	if (answer == easyRiddle.answer)
	{
		moves(40 + rows, 3);
		cout << "Enemy: Correct! You escaped without damage." << endl;
	}
	else
	{
		moves(40 + rows, 3);
		cout << "Enemy: Wrong answer! You lost 20 points of health." << endl;
		superman.health -= 20;
		// updating the health of the player on the screen without using the system cls function on the console . 
		// if the health reaches zero then the player loses the game in case of the classic mode , 
		if (superman.health == 0) {
			system("cls");
			cout << "you have lost all of your health." << endl;
			cout << "your current health is " << superman.health << endl;
			cout << "your score after completing the game is as follows. " << score << endl;
			exit(0);
		}
		// this will be happening only when we have the classic mode of the game. 
		if (response == 0) {
			moves(0, 0);
			cout << "+=================================+" << endl;
			cout << "|       Health Bar = " << superman.health << "         |" << endl;
			cout << "|       current score = " << score << "          |" << endl;
			cout << "+=================================+" << endl;
		}
	}


}

void askQuestions()
{
	// Ask a question when the player encounters the enemy
	//int qPosY = 1 + encounteredenemies * 6; // for each question, we need 4 lines, so multiplying by 4
	srand(time(0));
	int questionsLength = size(questions);
	moves(70, 7);
	// randomly choosing the question based on the value given by the rand function . 
	int index = rand() % questionsLength;
	string answer;
	Question question = questions[index];

	// using a while loop to set the position of the cursor after asking each question to the user. 
	while (answer != question.answer) {

		moves(40 + rows, 0);
		cout << "Enemy " << encounteredenemies + 1 << ": Answer this question : " << question.question << endl;
		moves(40 + rows, 1);
		cout << "Your answer: ";

		moves(40 + rows, 2);
		cin >> answer;
		answer = toLowerCase(answer);
		question.answer = toLowerCase(question.answer);

		// Check the player's answer and affect health accordingly
		if (answer == question.answer)
		{
			moves(40 + rows, 3);
			cout << "Enemy: Correct! You escaped without damage." << endl;

		}
		else
		{
			moves(40 + rows, 3);
			cout << "Enemy: Wrong answer! You lost 20 points of health." << endl;
			superman.health -= 20;
			// updating the health of the player on the screen without using the system cls function on the console . 
			// if the health reaches zero then the player loses the game in case of the classic mode , 
			if (superman.health == 0) {
				system("cls");
				cout << "you have lost all of your health." << endl;
				cout << "your current health is " << superman.health << endl;
				cout << "your score after completing the game is as follows. " << score << endl;
				exit(0);
			}
			// this will be happening only when we have the classic mode of the game. 
			if (response == 0) {
				moves(0, 0);
				cout << "+=================================+" << endl;
				cout << "|       Health Bar = " << superman.health << "          |" << endl;
				cout << "|       current score = " << score << "          |" << endl;
				cout << "+=================================+" << endl;
			}
		}
		break;
	}
}
void chestReward() {
	//string rewards[4] = { "immune", "score", "health", "!!!!NULL!!!!" };
	int random = rand() % 4;
	switch (random) {
	case 0:
		system("cls");
		centerText("YOU HAVE FOUND THE IMMUNE POWER UP .");
		enemytraverser = true;
		break;
	case 1:
		system("cls");
		centerText("\x1b[0mYOUR SCORE INCREASES BY 12.\x1b[0m");
		score += 12;
		break;
	case 2:
		system("cls");
		centerText("\x1b[0mYOUR SCORE HEALTH IS RESTORED BY 5.\x1b[0m");
		superman.health += 5;
		break;
	case 3:
		system("cls");
		centerText("\x1b[34mYOUR CHEST IS EMPTY PLEASE\x1b[0m");
		break;
	default:
		break;
	}
}
void printOptions(string arr[], int size, int activeOption) {
	system("cls");
	// Clear the console (for Windows, use system("clear") for Unix-based systems)
	cout << "\x1b[33m\n\nSelect your choice. \x1b[0m" << endl;

	cout << "+=============================+" << endl;
	for (int i = 0; i < size; i++) {
		if (i == activeOption) {
			cout << BOLD << UNDERLINE << "      " << arr[i] << RESET << endl;
		}
		else {
			cout << "      " << arr[i] << endl;
		}
	}
	cout << "+=============================+" << endl;

}





// MAZE
int find(vector<int>& parent, int i)
{
	if (parent[i] == i)
	{
		return i;
	}
	return find(parent, parent[i]);
}
void Union(vector<int>& parent, vector<int>& rank, int x, int y)
{
	int xRoot = find(parent, x);
	int yRoot = find(parent, y);

	if (rank[xRoot] < rank[yRoot])
	{
		parent[xRoot] = yRoot;
	}
	else if (rank[xRoot] > rank[yRoot])
	{
		parent[yRoot] = xRoot;
	}
	else
	{
		parent[yRoot] = xRoot;
		rank[xRoot]++;
	}
}
vector<vector<char>> generateMaze(int rows, int cols)
{
	vector<Wall> walls;
	vector<vector<char>> maze(rows * 2 + 1, vector<char>(cols * 2 + 1, 219));	// 219 is ASCII value of solid box (of maze wall)

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (i > 0)
			{
				walls.push_back({ {i, j}, {i - 1, j} }); // Vertical walls
			}
			if (j > 0)
			{
				walls.push_back({ {i, j}, {i, j - 1} }); // Horizontal walls
			}
		}
	}

	random_device rd;
	mt19937 g(rd());
	shuffle(walls.begin(), walls.end(), g);

	vector<int> parent(rows * cols);
	vector<int> rank(rows * cols, 0);

	for (int i = 0; i < rows * cols; ++i)
	{
		parent[i] = i;
	}

	for (const auto& wall : walls)
	{
		auto cell1 = wall.cell1;
		auto cell2 = wall.cell2;

		int root1 = find(parent, cell1.first * cols + cell1.second);
		int root2 = find(parent, cell2.first * cols + cell2.second);

		if (root1 != root2)
		{
			maze[2 * cell1.first + 1][2 * cell1.second + 1] = ' ';
			maze[2 * cell2.first + 1][2 * cell2.second + 1] = ' ';
			maze[cell1.first + cell2.first + 1][cell1.second + cell2.second + 1] = ' ';
			Union(parent, rank, root1, root2);
		}
	}

	// Entrance and exit points
	maze[1][0] = 'S';                   // Start
	maze[rows * 2 - 1][cols * 2] = 'E'; // End

	return maze;
}





// DISPLAY
void displayChests()
{
	for (int i = 0; i < numberOfChests; i++) {
		chestsArray[i].character = '+';
	}
	srand(static_cast<unsigned int>(time(0)));

	while (true)
	{   // doing the necessary modifidcations so that the chests do not get out of the maze 
		for (int i = 0; i < numberOfChests; i++) {
			chestsArray[i].x = (5 + (rand() % cols));
			chestsArray[i].y = (5 + (rand() % cols));
		}
		bool isEncounter = false;
		// checking enemy correctness
		for (int i = 0; i < numberOfChests; i++) {
			if (chestCoordiCorrectness(chestsArray[i].x, chestsArray[i].y)) {
				isEncounter = true;
				break;
			}
		}

		if (isEncounter)
		{
			break;
		}
	}

	for (int i = 0; i < numberOfChests; i++) {
		moves(chestsArray[i].x, chestsArray[i].y);
		cout << chestsArray[i].character;
	}

}
void displayEnemiess()
{
	for (int i = 0; i < numberOfEnemies; i++) {
		//enemiesArray[i].enemy = '@';
		enemiesArray[i].enemy = 176;
	}


	srand(static_cast<unsigned int>(time(0)));

	while (true)
	{   // doing the necessary modifidcations so that the enemies do not get out of the maze 

		for (int i = 0; i < numberOfEnemies; i++) {
			enemiesArray[i].x = (5 + (rand() % cols));
			enemiesArray[i].y = (5 + (rand() % cols));
		}

		bool isEncounter = false;


		// checking enemy correctness
		for (int i = 0; i < numberOfEnemies; i++) {
			if (enemyCoordiCorrectness(enemiesArray[i].x, enemiesArray[i].y)) {
				isEncounter = true;
				break;
			}
		}

		if (isEncounter)
		{
			break;
		}
	}

	for (int i = 0; i < numberOfEnemies; i++) {
		moves(enemiesArray[i].x, enemiesArray[i].y);
		cout << enemiesArray[i].enemy;
	}

}
void displayMaze(const vector<vector<char>>& maze)
{
	for (const auto& row : maze)
	{
		for (char cell : row)
		{
			cout << cell << "";
		}
		cout << " " << endl;
	}
	displayEnemiess();
	displayChests();
	moves(20, 20);
}
int chooseOptions(string arr[], int size) {
	int activeOption = 0;
	char arbitrary;

	printOptions(arr, size, activeOption);

	while (true) {
		if (_kbhit()) {
			arbitrary = _getch();
			if (arbitrary == 72 && activeOption > 0) {
				activeOption--;
			}
			else if (arbitrary == 80 && activeOption < size - 1) {
				activeOption++;
			}
			else if (arbitrary == 13) { // Enter key to confirm selection
				return activeOption;
				break;
			}

			printOptions(arr, size, activeOption); // Update the displayed options
		}
	}
}
void playAudio(const char* filePath) {
	PlaySound(TEXT("C:/Users/Track Computers/Desktop/track.wav"), NULL, SND_FILENAME | SND_ASYNC);
}



// MODES
void encounterEnemys(int playerX, int enemyX, int playerY, int enemyY)
{
	// Check if the player encounters the enemy

	//if (playerX == enemyX && playerY == enemyY && getCharacterAtPosition(enemyX, enemyY) == '@')
	if (playerX == enemyX && playerY == enemyY && getASCIIAtPosition(enemyX, enemyY) == -80) //-80 for the enemies.
	{

		askQuestions();
		encounteredenemies++;
	}
	if (playerX == enemyX && playerY == enemyY && getASCIIAtPosition(enemyX, enemyY) == -80 && levelno > 2) {
		askRiddles();
		encounteredenemies++;
	}
}
void encounterChests(int playerX, int chestX, int playerY, int chestY)
{
	if (playerX == chestX && playerY == chestY && getCharacterAtPosition(chestX, chestY) == '+')
	{
		//		chestReward();

	}
}
void timer() {
	int timeLimit = 30; // Time limit in seconds

	// Timer logic
	std::time_t start_time = std::time(nullptr); // Get current time
	std::time_t current_time;
	std::time_t end_time = start_time + timelimit;

	while (true) {

		// Check the time
		current_time = time(nullptr);
		if (current_time >= end_time) {
			// clearing the screen and showing Time's up!
			system("cls");
			cout << "\nTime's up! Game Over.\n";
			cout << "your score is as follows . " << score;
			break;
		}
		moves(1, 1);
		// Display time remaining to the player
		cout << "Time remaining: " << end_time - current_time << " seconds";

		this_thread::sleep_for(chrono::seconds(1));


	}
}
void movePlayerwithtimer(int x, int y, char c)
{
	int timeLimit = 30; // Time limit in seconds

	// Timer logic
	std::time_t start_time = std::time(nullptr); // Get current time
	std::time_t current_time;
	std::time_t end_time = start_time + timelimit;


	while (true)
	{
		current_time = time(nullptr);
		if (current_time >= end_time) {
			// clearing the screen and showing Time's up!
			system("cls");
			Sleep(1000);
			cout << "\nTime's up! Game Over.\n";
			cout << "your score is as follows . " << score;


			exit(0);
		}
		moves(0, 1);
		// Display time remaining to the player
		cout << "Time remaining: " << end_time - current_time << " seconds";

		//this_thread::sleep_for(chrono::seconds(1));



		moves(x, y);
		std::cout << c;

		if (_kbhit())
		{
			char key = _getch();
			moves(x, y);
			std::cout << ' '; // Clear previous position

			int prevX = x;
			int prevY = y;

			// Move the player based on arrow key input
			switch (key)
			{
			case 'w':
				prevY = y;
				y--;
				break;
			case 's':
				prevY = y;
				y++;
				break;
			case 'a':
				prevX = x;
				x--;
				break;
			case 'd':
				prevX = x;
				x++;
				break;
			default:
				break;
			}


			// Check for collisions with walls or obstacles
			if ((
				(getASCIIAtPosition(x, y) == -37) ||	// giving -37 for solid block as ascii value
				(getCharacterAtPosition(x, y) == '|') ||
				(getCharacterAtPosition(x, y) == '*')))
			{
				x = prevX;
				y = prevY;
			}

			// CHECKING FOR THW 
			for (int i = 0; i < numberOfEnemies; i++) {
				encounterEnemys(x, enemiesArray[i].x, y, enemiesArray[i].y);
			}
			// encounterEnemys(x, enemy1.x, y, enemy1.y);
			// encounterEnemys(x, enemy2.x, y, enemy2.y);
			// encounterEnemys(x, enemy3.x, y, enemy3.y);
			// condition to check whether the player has reached out of the maze or not.
			if (getCharacterAtPosition(x, y) == 'E')
			{
				system("cls");
				cout << "Congratulations! You have won the game." << endl;
				cout << "Now proceed to the next level." << endl;
				Sleep(400);

				break;
			} // now display  a portal at the final destination.
		}
	}
}
void combat(Player* b, monster* a)
{
	centerText("Get ready to Face the wrath of the monster");
	centerText(a->name);
	string combatOptions[3] = { "Attack", "Defend", "Special Power" };
	system("color 0e");
	// change turn of each 
	bool turnchanger = true;
	srand(time(NULL));
	while (true)
	{
		// clearing the screen everytime to show the newstats.

		if (b->health <= 0)
		{
			system("color 0");
			centerText("\x1b[31mYou Lose! The monster killed you .\x1b[0m"); cout << endl; 
			// to make the gameover we use the exit statement. 
				exit(0); 
			break;
		}
		else if (a->health <= 0)
		{
			centerText("You won the battle. You have killed the monster. \n  Now you pass to the next level. Beware of the future dangers "); cout << endl;
			break;
		}
		cout << "\033[31m+==========================+\033[0m" << endl;
		cout << "| Monster's Health  = " << a->health << "   |" << endl;
		cout << "| Player's  Health  = " << b->health << "   |" << endl;
		cout << "\033[31m+==========================+\033[0m" << endl;
		// creating the variables for the task of performing the choices.
		int respons;
		int attack;
		int monsterresponse;
		int monsterattack = 0;
		// asking the user what they want to do and getting their answer.
		// creating a variable bool to change the tufn of the attacks by the monster and the player.
		if (turnchanger)
		{
			//chooseOptions(combatOptions, 3);
			int d = chooseOptions(combatOptions, 3);
			switch (d)
			{
			case 0:
				attack = rand() % 10;
				cout << "monster lost " << attack << " amount of health." << endl;
				a->health -= attack;
				break;

			case 1:
				int heal;
				cout << "you have choosen to defend the attack of the enemy." << endl;
				heal = 1 + rand() % 3;
				if (heal == 1)
				{
					cout << "you have restored 9 points of health. " << endl;
					b->health += 9;
				}
				else if (heal == 2)
				{
					cout << "you have only defended the attack with no damage." << endl;
					b->health = b->health;
				}
				else
				{
					cout << "defense failed. You have to face the damage." << endl;
					b->health -= monsterattack;
				}
				break;
			case 2:
				attack = 5 + (rand() % 20);
				cout << "you have choosen the special attack if executed right, a high damage will be caused to the enemy" << endl;
				cout << "the damage to the enemy is as follows. " << attack << endl;
				a->health -= attack;
				break;

			default:
				break;
			}
			// giving the boolean variable the signal to change the turn.
			turnchanger = false;
			Sleep(2000);
			system("cls");
		}
		else if (!turnchanger)
		{
			cout << "monster's turn. " << endl;
			cout << "let's see what the monster does." << endl;
			// checking randomly what the monster wants to do.
			monsterresponse = 1 + rand() % 3;
			if (monsterresponse == 1)
			{
				monsterattack = 1 + rand() % 10;
				cout << "the monster attacked and you lost " << monsterattack << "  health." << endl;
				b->health -= monsterattack;
			}
			else if (monsterresponse == 2)
			{
				// increasing the monster's health  by 5 to make the battle difficult.
				cout << "The monster healed your attack." << endl;
				a->health += 5;
			}
			else
			{
				cout << "The monster used its special ability, which deals massive damage!" << endl;
				monsterattack = 15;
				cout << "now you have lost " << monsterattack << "of health." << endl;
				b->health -= monsterattack;
			}
			// giveng the turn back to the player.
			turnchanger = true;
			Sleep(6000);
			system("cls");
		}

	}
}
// we have made this function to move the player please. 

void movePlayer(int x, int y, char c)
{
	// Character representing the player
	while (true)
	{
		moves(x, y);
		std::cout << c;
	// using the _kbhit to detect which key is being hit by hte uer. 
		if (_kbhit())
		{
			char key = _getch();
			moves(x, y);
			std::cout << ' '; 
			// Clear previous position

			int prevX = x;

			// Move the player based on arrow key input
			int prevY = y;
			switch (key)
			{
			case 'w':
				prevY = y;
				y--;
				break;
			case 's':
				prevY = y;
				y++;
				break;
			case 'a':
				prevX = x;
				x--;
				break;
			case 'd':
				prevX = x;
				x++;
				break;
			default:
				break;
			}


			if (
				(getASCIIAtPosition(x, y) == -37) ||	// getting -37 for solid block as ascii value
				(getCharacterAtPosition(x, y) == 'S')
				)
			{
				x = prevX;
				y = prevY;
			}

			// for checking if there is enemy at this position. 
			for (int i = 0; i < numberOfEnemies; i++) {
				encounterEnemys(x, enemiesArray[i].x, y, enemiesArray[i].y);
			}
			// for checking if there is chest at this position. 
			for (int i = 0; i < numberOfChests; i++) {
				encounterChests(x, chestsArray[i].x, y, chestsArray[i].y);
			}
			// introducing the createria for facing a monster.
			// this feature will only be able if the player is playing the storyline mode 

			if (levelno >= 1 && levelno < 11) {
				if (getCharacterAtPosition(x, y) == 'E' && response >= 1) {
					int e = 0; 
					system("cls");
					cout << "\033[4m get ready to face the monster that protects the endway of this path.\033[0m" << endl;
					monster currentmonster = monsters[e]; 
					combat(&superman, &currentmonster);
					Sleep(2000);
					system("cls");
					e++; 
					
					break;

				}
			}

			// condition to check whether the player has reached out of the maze or not.
			if (getCharacterAtPosition(x, y) == 'E')
			{
				system("cls");
				cout << "Congratulations! You have won the game." << endl;
				cout << "Now proceed to the next level." << endl;
				Sleep(400);

				break;
			} // now display  a portal at the final destination.
		}
	}
}
void storyline() {
	superman.x = 2;
	superman.y = 5;

	system("cls");
	loadingbar();
	system("cls");
	cout << "Welcome to the story line of the game." << endl;
	cout << "enter the player with whom you want to play the game. " << endl;
	cin >> superman.player;


	system("cls");
	system("color E0");
	cout << "\nthis story is about a lost survivor who has lost himself in the forest. " << endl;
	cout << "in order to reach out of the forest he has to pass through different mazes." << endl;
	cout << "If he succesfully cleares all the mazes, then he finds himself out of the maze. " << endl;
	cout << "the game starts in a HUT. Player's is looking for the path out can you help him. " << endl;
	system("cls");
	while (true) {
		// using a switch case statement to handle the game based on the level no. 

		if (levelno == 1) {
			numberOfEnemies = 3;
			cout << "Welcome to level 1. <<The MONSTEROUS HUT>>" << endl;
			cout << "escape the hut without losing the health.";
			cout << "AND the game begins , GOOD LUCK ";
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
			system("cls");
			loadingbar();
		}
		else if (levelno == 2) {
			numberOfEnemies = 5;
			system("cls");
			cout << "Welcome to the level 2.  << ENTERING THE JUNGLE >>" << endl;
			cout << "you have entered the jungle." << endl;
			cout << "cross the first half of the jungel" << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 3) {
			numberOfEnemies = 7;
			system("cls");
			cout << "Welcome to the level 3. << JUNGLE SURVIVAL >>" << endl;
			cout << " dangerous end of the jungle . " << endl;
			cout << " complete the passage through the jungle." << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 4) {
			numberOfEnemies = 9;
			system("cls");
			cout << "Welcome to the level 4. << REACHING THE RIVER >> " << endl;
			cout << "you now have to pass through the river" << endl;
			cout << "cross the river without losing any health. " << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 5) {
			numberOfEnemies = 11;
			system("cls");
			cout << "Welcome to the level 5. <<  ENTERING THE DUNGEON   >>" << endl;
			cout << "user enters the dungeon. " << endl;
			cout << "first portion of the dungeon. " << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 6) {
			numberOfEnemies = 13;
			system("cls");
			cout << "Welcome to the level 6. <<    The DUNGEON PART 2     >>" << endl;
			cout << "find the path out of the dungeon. " << endl;
			cout << "you out of the dungeon to DEATH VALLEY . " << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 7) {
			numberOfEnemies = 15;
			system("cls");
			cout << "Welcome to the level 7. <<    DEATH VALLEY   >> " << endl;
			cout << "you have to clear the first stage. " << endl;
			cout << "the next stage of the DEATH VALLEY" << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 8) {
			numberOfEnemies = 17;
			system("cls");
			cout << "welcome to the level 8, <<   DEATH BRIDGE    >> " << endl;
			cout << "a long bridge parts of the death valley" << endl;
			cout << "find the way to the DEAD END OF THE VALLEY" << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 9) {
			numberOfEnemies = 19;
			system("cls");
			cout << "welcome to the level 9 , <<   DEAD END    >> " << endl;
			cout << " the way to escaping this realm." << endl;
			cout << "once last level of the game" << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			rows += 1;
			cols += 5;
			levelno++;
		}
		else if (levelno == 10) {
			numberOfEnemies = 21;
			system("cls");
			cout << "Welcome to the level 10 , <<    PATH TO THE EARTH   >>" << endl;
			cout << "Solve to escape the mysterious realm . " << endl;
			cout << "you have won the game. " << endl;
			moves(0, 4);
			vector<vector<char>> maze = generateMaze(rows, cols);
			displayMaze(maze);
			movePlayer(superman.x, superman.y, superman.player);
			// if the user completes the game then, displaying the user the message showing the victory message. 
			system("cls");

			cout << "CONGRATULTIONS, You have Completed the game MR." << username << endl;
			cout << "You have now reached back to the Earth. " << endl;
			//rows += 1;
			//cols += 5;
			//levelno++;
		}
		if (levelno == 11) {
			break;
		}

	}
}
void timetrail()
{
	system("cls");
	loadingbar();
	system("cls");
	system("color E0");
	// giving the user the introduction when he enters the maze game. 
	cout << "Welcone to the time trial." << endl;
	cout << "Here you will be given specific time to solve the maze " << endl;
	cout << "if you do solve the maze in the required time then you procedd to the next maze";
	cout << "We hope that you will enjoy this mode of the game. " << endl;
	cout << "\n choose the character that you want to play the game ; " << endl;
	cin >> superman.player;
	while (true) {
		system("cls");

		moves(2, 2);
		vector<vector<char>> maze = generateMaze(rows, cols);
		displayMaze(maze);
		movePlayerwithtimer(superman.x, superman.y, superman.player);



		// incresing the score by 20 when the user clears a maze. 
		score += 20;
		// updatintg the size of the maze every time the user survives the game.
		rows += 2;
		cols += 4;

		// After the maze is displayed, start player movement

	}
}
void classic()
{
	system("cls");
	loadingbar();
	system("cls");
	centerText("WELCOME TO THE CLASSIC MODE OF THIS GAME."); cout << endl;
	centerText("+=========================================================================+"); cout << endl;
	centerText("||"); cout << endl;
	centerText("\x1b[036mIn this mode, you have to survive as long as you can.\x1b[0m"); cout << endl;
	centerText("The Rules For this mode are Below : "); cout << endl;
	centerText("-> No revival"); cout << endl;
	centerText("-> Score by solving only."); cout << endl;
	centerText("||"); cout << endl;
	centerText("+=========================================================================+"); cout << endl;
	Sleep(9000);
	system("color e0");
	system("cls");
	// asking the user to enter the character with which he wants to play the game. 
	cout << "+=================================+" << endl;
	cout << "|                                 |" << endl;
	cout << "|      enter your character :     |" << endl;
	cout << "|                                 |" << endl;
	cout << "+=================================+" << endl;
	superman.player = _getch();
	system("cls");
	// maiking the use of the system cls to create an illusion that character is entered within the box. 
	cout << "+=================================+" << endl;
	cout << "|                                 |" << endl;
	cout << "|    enter your character : " << superman.player << "     |" << endl;
	cout << "|                                 |" << endl;
	cout << "+=================================+" << endl;

	Sleep(2000);
	while (superman.health != 0) {
		// clearing the screen every time the playerr wins the game.
		system("cls");
		system("color F0");
		Sleep(900);
		moves(0, 0);
		cout << "+=================================+" << endl;
		cout << "|       Health Bar = " << superman.health << "         |" << endl;
		cout << "|       current score = " << score << "         |" << endl;
		cout << "+=================================+" << endl;

		// moving the cursor on the top to display the score on the right top most corner of the console.    

		vector<vector<char>> maze = generateMaze(rows, cols);
		moves(1, 4);
		displayMaze(maze);
		movePlayer(superman.x, superman.y, superman.player);
		// incresing the score by 20 when the user clears a maze. 
		score += 20;
		// updatintg the size of the maze every time the user survives the game.
		rows += 2;
		cols += 4;

	}
}
void finalBoss() {

	string news;
	centerText("+========================================+");
	string warning = " HE HE HOO HOOO HAAA HAAA HAAA  \n   YOU HAVE DONE A GREAT JOB SOO FAR   \n BUT NOW IT IS TIME TO DIE .\n AND THE BATTLE BEGINS";
	for (char& c : warning) {
		news += c;
		Sleep(800);
		centerText(news);
	}

	system("cls");


}






