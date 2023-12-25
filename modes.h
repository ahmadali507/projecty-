#pragma once

#include "fundamentals.h"
#include "helper.h"
#include "display.h"
#include "maze.h"

void timer()
{
    int timeLimit = 30; // Time limit in seconds

    // Timer logic
    std::time_t start_time = std::time(nullptr); // Get current time
    std::time_t current_time;
    std::time_t end_time = start_time + timelimit;

    while (true)
    {

        // Check the time
        current_time = time(nullptr);
        if (current_time >= end_time)
        {
            // clearing the screen and showing Time's up!
            system("cls");
            cout << "\nTime's up! Game Over.\n";
            cout << "your score is as follows . " << score;
            break;
        }
        gotoxy(1, 1);
        // Display time remaining to the player
        cout << "Time remaining: " << end_time - current_time << " seconds";

        // this_thread::sleep_for(chrono::seconds(1));
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
        if (current_time >= end_time)
        {
            // clearing the screen and showing Time's up!
            system("cls");
            Sleep(1000);
            cout << "\nTime's up! Game Over.\n";
            cout << "your score is as follows . " << score;

            exit(0);
        }
        gotoxy(0, 1);
        // Display time remaining to the player
        cout << "Time remaining: " << end_time - current_time << " seconds";

        // this_thread::sleep_for(chrono::seconds(1));

        gotoxy(x, y);
        std::cout << c;

        if (_kbhit())
        {
            char key = _getch();
            gotoxy(x, y);
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
                    (getASCIIAtPosition(x, y) == -37) || // giving -37 for solid block as ascii value
                    (getCharacterAtPosition(x, y) == '|') ||
                    (getCharacterAtPosition(x, y) == '*')))
            {
                x = prevX;
                y = prevY;
            }

            // CHECKING FOR THW
            for (int i = 0; i < numberOfEnemies; i++)
            {
                encounterEnemy(x, enemiesArray[i].x, y, enemiesArray[i].y);
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
void combat(Player *b, Monster *a)
{
    centerText("Get ready to Face the wrath of the Monster");
    cout << endl;
    centerText(a->name);
    cout << endl;
    Sleep(5000);
    string combatOptions[3] = {"Attack", "Defend", "Special Power"};
    // system("color e0");
    // change turn of each
    bool turnchanger = true;
    srand(time(NULL));
    while (true)
    {
        system("cls");
        cout << "\033[31m+==========================+\033[0m" << endl;
        cout << "| Monster's Health  = " << a->health << "   |" << endl;
        cout << "| Player's  Health  = " << b->health << "   |" << endl;
        cout << "\033[31m+==========================+\033[0m" << endl;
        // clearing the screen everytime to show the newstats.
        Sleep(2000);

        if (b->health <= 0)
        {
            centerText("\x1b[31mYou Lose! The Monster killed you .\x1b[0m");
            cout << endl;
            // to make the gameover we use the exit statement.
            exit(0);
            break;
        }
        else if (a->health <= 0)
        {
            centerText("You won the battle. You have killed the Monster. \n  Now you pass to the next level. Beware of the future dangers ");
            cout << endl;
            break;
        }

        // creating the variables for the task of performing the choices.
        int respons;
        int attack;
        int monsterresponse;
        int monsterattack = 0;
        // asking the user what they want to do and getting their answer.
        // creating a variable bool to change the tufn of the attacks by the Monster and the player.
        if (turnchanger)
        {
            // displayOptions(combatOptions, 3);
            int d = displayOptions(combatOptions, 3);
            switch (d)
            {
            case 0:
                attack = rand() % 10;
                cout << "Monster lost " << attack << " amount of health." << endl;
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
            cout << "Monster's turn. " << endl;
            cout << "let's see what the Monster does." << endl;
            // checking randomly what the Monster wants to do.
            monsterresponse = 1 + rand() % 3;
            if (monsterresponse == 1)
            {
                monsterattack = 1 + rand() % 10;
                cout << "the Monster attacked and you lost " << monsterattack << "  health." << endl;
                b->health -= monsterattack;
            }
            else if (monsterresponse == 2)
            {
                // increasing the Monster's health  by 5 to make the battle difficult.
                cout << "The Monster healed your attack." << endl;
                a->health += 5;
            }
            else
            {
                cout << "The Monster used its special ability, which deals massive damage!" << endl;
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
void movePlayer(int x, int y, char c)
{
    enableBGText(BACKGROUND_SILVER);
    // Character representing the player
    while (true)
    {
        gotoxy(x, y);
        std::cout << c;
        // using the _kbhit to detect which key is being hit by hte uer.
        if (_kbhit())
        {
            char key = _getch();
            gotoxy(x, y);
            std::cout << ' ';
            // Clear previous position

            int prevX = x;

            // Move the player based on arrow key input
            int prevY = y;
            switch (key)
            {
            case 72: // Up Arrow key code
                prevY = y;
                y--;
                break;
            case 80: // Down Arrow key code
                prevY = y;
                y++;
                break;
            case 75: // Left Arrow key code
                prevX = x;
                x--;
                break;
            case 77: // Right Arrow key code
                prevX = x;
                x++;
                break;
            default:
                break;
            }

            if (
                (getASCIIAtPosition(x, y) == -37) || // getting -37 for solid block as ascii value
                (getCharacterAtPosition(x, y) == 'S'))
            {
                x = prevX;
                y = prevY;
            }

            // for checking if there is enemy at this position.
            for (int i = 0; i < numberOfEnemies; i++)
            {
                encounterEnemy(x, enemiesArray[i].x, y, enemiesArray[i].y);
            }
            // for checking if there is chest at this position.
            for (int i = 0; i < numberOfChests; i++)
            {
                encounterChest(x, chestsArray[i].x, y, chestsArray[i].y);
            }
            // introducing the createria for facing a Monster.
            // this feature will only be able if the player is playing the storyline mode

            if (levelno >= 6 && levelno < 11)
            {
                if (getCharacterAtPosition(x, y) == 'E' && response >= 1)
                {
                    system("cls");
                    centerText(" get ready to face the Monster that protects the endway of this path.");
                    cout << endl;
                    Monster currentmonster = monsters[e];
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
void storyline()
{

    // system("cls");
    // loadingbar();
    // system("cls");
    // cout << "Welcome to the story line of the game." << endl;
    // cout << "enter the player with whom you want to play the game. " << endl;
    // cin >> superman.player;

    system("cls");

    // system("color e0");
    // cout << "\nThis story is about a lost survivor who has lost himself in the forest. " << endl;
    // cout << "in order to reach out of the forest he has to pass through different mazes." << endl;
    // cout << "If he succesfully cleares all the mazes, then he finds himself out of the maze. " << endl;
    // cout << "The game starts in a HUT. Player's is looking for the path out can you help him. " << endl;
    // system("cls");
    while (true)
    {
        // using a switch case statement to handle the game based on the level no.

        if (levelno == 1)
        {
            changeSystemColor();
            numberOfEnemies = 3;
            centerText("Welcome to level 1.");
            centerText("The MONSTEROUS HUT");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 1;
            mazeCols += 2;
            levelno++;
            system("cls");
            loadingbar();
        }
        else if (levelno == 2)
        {
            changeSystemColor();
            // system("color d0");
            numberOfEnemies = 5;
            system("cls");
            centerText("Welcome to level 2.");
            centerText("ENTERING THE JUNGLE");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 1;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 3)
        {
            changeSystemColor();
            // system("color c0");
            numberOfEnemies = 7;
            system("cls");
            centerText("Welcome to level 3.");
            centerText("JUNGLE SURVIVAL");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 1;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 4)
        {
            changeSystemColor();
            // system("color b0");
            numberOfEnemies = 9;
            system("cls");
            centerText("Welcome to level 4.");
            centerText("REACHING THE RIVER");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 1;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 5)
        {
            changeSystemColor();
            // system("color a0");
            numberOfEnemies = 11;
            system("cls");
            centerText("Welcome to level 5.");
            centerText("ENTERING THE DUNGEON");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 2;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 6)
        {
            changeSystemColor();
            // system("color 90");
            numberOfEnemies = 13;
            system("cls");
            centerText("Welcome to level 6.");
            centerText("The DUNGEON PART 2");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 2;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 7)
        {
            changeSystemColor();
            // system("color 80");
            numberOfEnemies = 15;
            system("cls");
            centerText("Welcome to level 7.");
            centerText("DEATH VALLEY");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 2;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 8)
        {
            changeSystemColor();
            // system("color 70");
            numberOfEnemies = 17;
            system("cls");
            centerText("Welcome to level 8.");
            centerText("DEATH BRIDGE");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 3;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 9)
        {
            changeSystemColor();
            // system("color 60");
            numberOfEnemies = 19;
            system("cls");
            centerText("Welcome to level 9.");
            centerText("DEAD END");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            mazeRows += 4;
            mazeCols += 2;
            levelno++;
        }
        else if (levelno == 10)
        {
            changeSystemColor();
            // system("color 50");
            numberOfEnemies = 21;
            system("cls");
            centerText("Welcome to level 10.");
            centerText("PATH TO THE EARTH");
            gotoxy(0, 4);
            vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
            displayGame(maze);
            movePlayer(superman.x, superman.y, superman.player);
            // if the user completes the game then, displaying the user the message showing the victory message.
            system("cls");

            cout << "CONGRATULTIONS, You have Completed the game MR." << username << endl;
            cout << "You have now reached back to the Earth. " << endl;
        }
        if (levelno == 11)
        {
            break;
        }
    }
}
void timetrail()
{
    system("cls");
    loadingbar();
    system("cls");
    // system("color E0");
    // giving the user the introduction when he enters the maze game.
    cout << "Welcone to the time trial." << endl;
    cout << "Here you will be given specific time to solve the maze " << endl;
    cout << "if you do solve the maze in the required time then you procedd to the next maze";
    cout << "We hope that you will enjoy this mode of the game. " << endl;
    cout << "\n choose the character that you want to play the game ; " << endl;
    cin >> superman.player;
    while (true)
    {
        system("cls");

        gotoxy(2, 2);
        vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
        displayMaze(maze);
        movePlayerwithtimer(superman.x, superman.y, superman.player);

        // incresing the score by 20 when the user clears a maze.
        score += 20;
        // updatintg the size of the maze every time the user survives the game.
        mazeRows += 2;
        mazeCols += 4;

        // After the maze is displayed, start player movement
    }
}
void classic()
{
    system("cls");
    loadingbar();
    system("cls");
    centerText("WELCOME TO THE CLASSIC MODE OF THIS GAME.");
    cout << endl;
    centerText("+=========================================================================+");
    cout << endl;
    centerText("||");
    cout << endl;
    centerText("\x1b[036mIn this mode, you have to survive as long as you can.\x1b[0m");
    cout << endl;
    centerText("The Rules For this mode are Below : ");
    cout << endl;
    centerText("-> No revival");
    cout << endl;
    centerText("-> Score by solving only.");
    cout << endl;
    centerText("||");
    cout << endl;
    centerText("+=========================================================================+");
    cout << endl;
    Sleep(9000);
    // system("color e0");
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
    while (superman.health != 0)
    {
        // clearing the screen every time the playerr wins the game.
        system("cls");
        Sleep(900);
        gotoxy(0, 0);
        cout << "+=================================+" << endl;
        cout << "|       Health Bar = " << superman.health << "         |" << endl;
        cout << "|       current score = " << score << "         |" << endl;
        cout << "+=================================+" << endl;

        // moving the cursor on the top to display the score on the right top most corner of the console.

        vector<vector<char>> maze = generateMaze(mazeRows, mazeCols);
        gotoxy(1, 4);
        displayMaze(maze);
        movePlayer(superman.x, superman.y, superman.player);
        // incresing the score by 20 when the user clears a maze.
        score += 20;
        // updatintg the size of the maze every time the user survives the game.
        mazeRows += 2;
        mazeCols += 4;
    }
}
void finalBoss()
{

    string news;
    centerText("+========================================+");
    string warning = " HE HE HOO HOOO HAAA HAAA HAAA  \n   YOU HAVE DONE A GREAT JOB SOO FAR   \n BUT NOW IT IS TIME TO DIE .\n AND THE BATTLE BEGINS";
    for (char &c : warning)
    {
        news += c;
        Sleep(800);
        centerText(news);
    }

    system("cls");
}
