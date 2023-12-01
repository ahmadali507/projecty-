#include <iostream>
#include <cctype>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;


// comment updated
////////////////////////////////////// STRUCTS DEFINED //////////////////////////////////////

struct Player
{
	char player;
	int x;
	int y;
};

struct Enemy
{
	char enemy;
	int x;
	int y;
	Enemy(char enemy = '&', int x = 0, int y = 0) : enemy(enemy), x(x), y(y) {}
};

struct InitialPosition
{
	int x;
	int y;
	InitialPosition(int x = 2, int y = 2) : x(x), y(y) {}
};

struct Destination
{
	int x;
	int y;
	Destination(int x = 2, int y = 2) : x(x), y(y) {}
};

struct Question
{
	string question;
	string answer;

	Question(const string& q, const string& a) : question(q), answer(a) {}
};

////////////////////////////////////// GLOBAL VARIABLES //////////////////////////////////////

unsigned int Health = 100;
const int width = 30;
const int height = 30;
unsigned int score = 0;
int encounteredEnemies = 0;

Question questions[10] = {
	Question("What's the capital of Pakistan", "Islamabad"),
	Question("What's the capital of France", "Paris"),
	Question("What's the capital of Turkey", "Ankara"),
	Question("What's the capital of China", "Beijing"),
	Question("What's the capital of Japan", "Tokyo"),
	Question("What's the capital of USA", "Washington"),
	Question("What's the capital of England", "London"),
	Question("What's the capital of Norway", "Oslo"),
	Question("What's the capital of Spain", "Madrid"),
	Question("What's the capital of Portugal", "Lisbon") };

////////////////////////////////////// STRUCTS INITIALIZED //////////////////////////////////////
Enemy enemy1;
Enemy enemy2;
Enemy enemy3;
Player superman;

////////////////////////////////////// FUNCTIONS //////////////////////////////////////
char getCharacterAtPosition(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		// Handle error
		return '\0';
	}

	// Get console screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		// Handle error
		return '\0';
	}

	// Set position
	COORD coord;
	coord.X = x;
	coord.Y = y;

	DWORD dwRead;
	CHAR_INFO chi;
	if (!ReadConsoleOutputCharacter(hConsole, &chi.Char.UnicodeChar, 1, coord, &dwRead))
	{
		// Handle error
		return '\0';
	}

	return chi.Char.UnicodeChar;
}
void menu() {
	string first = " Welcome! to the game: THE MAZE QUEST: enigmatic lybrinth";
	for (char& c : first) {
		Sleep(80);
		cout << c;
	}
	cout << endl;
	string second = " The story of the game is about a survivor who is lost in the valley.";
	string third = " now he has to pass through the mazes to find his way home. \n For this he has to encounter different enemies, monsters and wise creatures\n  Using all things he has to pass through the valley to succeed.";
		for (char& c : second) {
			Sleep(20);
			cout << c;
		}
		cout << endl;
	for (char& c : third) {
		Sleep(20);
		cout << c;
	}
	cout << endl;
	system("cls");
	// in the next screen displaying the following text on the screen .
	cout << "Now, the game starts with the user finding himself in the lockroom." << endl
		<< " This lockroom is the first maze that the player has to pass."<<endl 
		<<"If he passes through the maze after facing all the enemies he is sure to succeed.";
	char c; 
	cout << "press the backspace key to continue.";
	cin >> c;
	if (c == 'f')
		system("cls");

}


void move(int x, int y)
{
	// Set console cursor position
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void borders()
{
	// Draw borders
	for (int i = 1; i < width - 1; i++)
	{
		move(i, 0);
		cout << "#";
	}

	for (int i = 1; i < width - 1; i++)
	{
		move(i, height - 2);
		cout << "#";
	}

	for (int i = 1; i < height - 1; i++)
	{
		move(0, i);
		cout << "#";
	}

	for (int i = 1; i < height - 1; i++)
	{
		move(width - 2, i);
		cout << "#";
	}
}


bool isCollision(int x, int y)
{
	// Check for collision with specific characters
	return (getCharacterAtPosition(x, y) == '#' || getCharacterAtPosition(x, y) == '|' || getCharacterAtPosition(x, y) == '*');
}

void moveEnemy(int x, int y, char c)
{
	// Move enemy to a position and display
	move(x, y);
	cout << c;
}

bool enemyCoordCorrectness(int x, int y)
{
	return getCharacterAtPosition(x, y) != '*' &&
		getCharacterAtPosition(x, y) != '|' &&
		getCharacterAtPosition(x, y) != '&' &&
		getCharacterAtPosition(x, y) != '#';
}
void displayEnemies()
{

	srand(static_cast<unsigned int>(time(0)));

	while (true)
	{
		enemy1.x = rand() % 27;
		enemy1.y = rand() % 27;
		enemy2.x = rand() % 27;
		enemy2.y = rand() % 27;
		enemy3.x = rand() % 27;
		enemy3.y = rand() % 27;

		if (
			enemyCoordCorrectness(enemy1.x, enemy1.y) &&
			enemyCoordCorrectness(enemy2.x, enemy2.y) &&
			enemyCoordCorrectness(enemy3.x, enemy3.y))
		{
			break;
		}
	}

	move(50, 5);

	move(enemy1.x, enemy1.y);
	cout << enemy1.enemy;

	move(enemy2.x, enemy2.y);
	cout << enemy2.enemy;

	move(enemy3.x, enemy3.y);
	cout << enemy3.enemy;
}

void printmaze()
{
	for (int i = 1; i < width - 4; i++)
	{
		move(i, 3);
		cout << "*";
	}
	for (int i = 3; i < width - 2; i++)
	{
		move(i, 6);
		cout << "*";
	}
	for (int i = 1; i < width - 2; i++)
	{
		move(i, 9);
		if (i == 14)
		{
			cout << " ";
		}
		else
			cout << "*";
	}
	for (int i = 1; i < width - 4; i++)
	{
		move(i, 12);
		cout << "*";
	}
	for (int i = 4; i < width - 2; i++)
	{
		move(i, 15);
		cout << "*";
	}
	for (int i = 1; i < width - 4; i++)
	{
		move(i, 18);
		cout << "*";
	}
	for (int i = 3; i < width - 2; i++)
	{
		move(i, 21);
		cout << "*";
	}
	for (int i = 3; i < width - 2; i++)
	{
		move(i, 24);
		cout << "*";
	}
	for (int i = 2; i < width - 4; i++)
	{
		move(i, 27);
		cout << "*";
	}
}
string  lowercase(string str) {
	for (char& c : str) {
		c = tolower(c);
	}
	return str;
}
void health()
{
	// Display player's health
	char healthbar[9] = { '+', '+', '+', '+', '+', '+', '+', '+', '+' };
	//move(1, 31);
	
	switch (Health) {
	case 100:
		cout << "Player's Health |";
		for (int i = 0; i < 9; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 8)
				cout << "| ";

		}
		break;
	case 90:
		cout << "Player's Health |";
		for (int i = 0; i < 8; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 7)
				cout << "| ";
		}
		break;

	case 80:
		cout << "Player's Health |";
		for (int i = 0; i <7; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 6)
				cout << "| ";
		}
		break;

	case 70:
		cout << "Player's Health |";
		for (int i = 0; i < 6; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 5)
				cout << "| ";
		}
		break;

	case 60:
		cout << "Player's Health |";
		for (int i = 0; i < 5; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 4)
				cout << "| ";
		}
		break;

	case 50:
		cout << "Player's Health |";
		for (int i = 0; i < 4; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 3)
				cout << "| ";
		}
		break;

	case 40:
		cout << "Player's Health |";
		for (int i = 0; i < 3; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 2)
				cout << "| ";
		}
		break;

	case 30:
		cout << "Player's Health |";
		for (int i = 0; i < 2; i++)
		{
			cout << healthbar[i]<<" ";
			if (i == 1)
				cout << "| ";
		}
		break;
	}
	
}
void askQuestion()
{
	// Ask a question when the player encounters the enemy
	int qPosY = 1 + encounteredEnemies * 6;	// for each question, we need 4 lines, so multiplying by 4
	srand(time(0));
	int questionsLength = size(questions);
	move(50, 7);
	int index = rand() % questionsLength;
	Question question = questions[index];

	move(31, qPosY);
	cout << "Enemy " << encounteredEnemies + 1 << ": Answer this question : " << question.question << endl;
	move(31, qPosY + 1);
	cout << "Your answer: ";

	move(31, qPosY + 2);
	string answer;
	cin >> answer;
	answer = lowercase(answer);
	question.answer = lowercase(question.answer);

	// Check the player's answer and affect health accordingly
	if (answer == question.answer)
	{
		move(31, qPosY + 3);
		cout << "Enemy: Correct! You escaped without damage." << endl;
	}
	else
	{
		move(31, qPosY + 3);
		cout << "Enemy: Wrong answer! You lost 10 points of health." << endl;
		Health -= 10;
		move(31, qPosY + 4);
	    health();
		
	}
}
void encounterEnemy(int playerX, int enemyX, int playerY, int enemyY)
{
	// Check if the player encounters the enemy
	if (playerX == enemyX && playerY == enemyY && getCharacterAtPosition(enemyX, enemyY) == '&')
	{
		askQuestion();
		encounteredEnemies++;
	}
}
void movePlayer(int x, int y, char c)
{
	// Character representing the player
	while (true)
	{
		move(x, y);
		std::cout << c;

		if (_kbhit())
		{
			char key = _getch();
			move(x, y);
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
			if (
				(getCharacterAtPosition(x, y) == '#') ||
				(getCharacterAtPosition(x, y) == '|') ||
				(getCharacterAtPosition(x, y) == '*'))
			{
				x = prevX;
				y = prevY;
				score--;
			}
			if (x == 26 && y == 27)
			{
				break; // Exit the loop if the destination is reached
			}
			move(60, 6);

			encounterEnemy(x, enemy1.x, y, enemy1.y);
			encounterEnemy(x, enemy2.x, y, enemy2.y);
			encounterEnemy(x, enemy3.x, y, enemy3.y);
		}
	}
	system("cls");
	cout << "Congratulations! You have won the game." << endl;
	cout << "Now proceed to the next level." << endl;
} // now display  a portal at the final destination.
void destination()
{
	int desx = 26;
	int desy = 27;
	string des = "()";
	move(desx, desy);
	cout << des;
}
void printGame(const Player& player)
{
	// Clear screen
	system("cls");
	
	menu();

	// Redraw maze, player, and enemy at their updated positions
	borders();
	printmaze();
	displayEnemies();
	destination();
	move(player.x, player.y);
	cout << player.player;
}

int main()
{
	// Initializing player struct
	superman.x = 2;
	superman.y = 2;
	superman.player = '@';

	while (true)
	{
		system("color F0");
		printGame(superman);
		movePlayer(superman.x, superman.y, superman.player);
		Sleep(100);
	}
	return 0;
}