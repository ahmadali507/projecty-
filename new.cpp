#include <iostream>
#include <iomanip>
#include <windows.h>
#include <chrono>
using namespace std;
void cursorPosition(int,int);
void loadingScreen();
bool mainMenu();
int options();
bool controls();
bool theme();
bool background();
bool text();
bool credits();
int maind(){
    loadingScreen();
    system("cls");
    int result;
     do{
     if(mainMenu()==true){
     //startGame();
     break;
     }
     else{
          do{
          result=options();
          if(result==1){
               if(controls()==true){
                    continue;
               }
          }
          else if(result==2){
               if(theme()==true){
                    continue;
               }
          }
          else if(result==3){
               if(credits()==true){
                    continue;
               }
          }
          else if(result==4){
               result=0;
               break;
          }
          }while(true);
          if(result==0){
               continue;
          }
          else{
               break;
          }
     }
     }while(true);
    return 0;
}
void cursorPosition(int x,int y){
    COORD coordinates;
    coordinates.X=x;
    coordinates.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
void loadingScreen(){
    cout<<setw(115)<<"______ _   _ _____    ____ _____ ____ _   _ _____    _____ _____ _____ _____ _____ _____"<<endl;
    cout<<setw(115)<<"  |    |   | |       |   | |   | |    |   | |        |     |     |   | |   | |   | |    "<<endl;
    cout<<setw(115)<<"  |    |   | |       |   | |   | | -| |   | |        |     |     |     |   | |   | |    "<<endl;
    cout<<setw(115)<<"  |    |___| |____   |___| |   | |__| |   | |____    |____ |___| |     |___| |___| |____"<<endl;
    cout<<setw(115)<<"  |    |   | |       |\\    |   |    | |   | |        |         | |     |   | |     |    "<<endl;
    cout<<setw(115)<<"  |    |   | |       | \\   |   |    | |   | |        |         | |   | |   | |     |    "<<endl;
    cout<<setw(115)<<"  |    |   | |____   |  \\  |___|    | |___| |____    |____ ____| |___| |   | |     |____"<<endl;
   cout<<endl<<endl;
   cout<<setw(60)<<"Loading... ";
    for(int i=0;i<22;i++){
        cout<<char(177);
    }
    for (int i=0;i<22;i++) {
        cursorPosition(60+i,11);
        Sleep(250);
        cout<<char(178);
    }
}
bool mainMenu(){
        cout<<setw(100)<<"_______ _____ _____ _     _      _______ _____ _      _ _    _   "<<endl;
        cout<<setw(97)<<"|  |  | |   |   |   |\\    |      |  |  | |     |\\     | |    |"<<endl;
        cout<<setw(97)<<"|  |  | |   |   |   | \\   |      |  |  | |     | \\    | |    |"<<endl;
        cout<<setw(97)<<"|  |  | |___|   |   |  \\  |      |  |  | |____ |   \\  | |    |"<<endl;
        cout<<setw(97)<<"|  |  | |   |   |   |   \\ |      |  |  | |     |    \\ | |    |"<<endl;
        cout<<setw(97)<<"|  |  | |   |   |   |    \\|      |  |  | |     |     \\| |    |"<<endl;
        cout<<setw(100)<<"|  |  | |   | __|__ |     |      |  |  | |____ |      | |____|   "<<endl;
        cout<<endl;
        cout<<setw(70)<<"1. Start "<<endl<<endl;
        cout<<setw(71)<<"2. Options"<<endl<<endl;
        cout<<setw(68)<<"3. Quit"<<endl<<endl;
        string mainInput;
        do{
          cout<<"\t\t\t\t\t\t\t\t";
        getline(cin,mainInput);
        if (mainInput=="1"){
            system("cls");
            return true;
          break;
        }
        else if(mainInput=="2"){
            system("cls");
          return false;
          break;
        }
        else if(mainInput=="3"){
          cout<<setw(77)<<"Thanks For Playing!!!"<<endl;
          exit(0);
        }
        else{
          cout<<setw(73)<<"Invalid Input"<<endl;
        }}while(true);
}
int options(){
    cout<<setw(90)<<"_____ _____ _______ _____ _____ _      _ _______"<<endl;
    cout<<setw(90)<<"|   | |   |    |      |   |   | |\\     | |     "<<endl;
    cout<<setw(90)<<"|   | |   |    |      |   |   | | \\    | |     "<<endl;
    cout<<setw(90)<<"|   | |___]    |      |   |   | |  \\   | |_____"<<endl;
    cout<<setw(90)<<"|   | |        |      |   |   | |   \\  |      |"<<endl;
    cout<<setw(90)<<"|   | |        |      |   |   | |    \\ |      |"<<endl;
    cout<<setw(90)<<"[___] |        |    __|__ [___] |     \\| _____]"<<endl;
    cout<<endl<<endl;
    cout<<setw(70)<<"1. Controls"<<endl<<endl;
    cout<<setw(70)<<"2. Theme   "<<endl<<endl;
    cout<<setw(70)<<"3. Credits "<<endl<<endl;
    cout<<setw(75)<<"Press X to go back"<<endl<<endl;
    string optionsInput;
    do{
          cout<<"\t\t\t\t\t\t\t\t";
        getline(cin,optionsInput);
        if (optionsInput=="1"){
            system("cls");
           return 1;
        }
        else if(optionsInput=="2"){
            system("cls");
           return 2;
        }
        else if(optionsInput=="3"){
            system("cls");
          return 3;
        }
        else if(optionsInput=="X"||optionsInput=="x"){
           system("cls");
           return 4;
        }
     }while(true);
}
bool controls(){
    cout<<setw(100)<<"_______ ______ _      _ _______ ______ ______ _       ______ "<<endl;
    cout<<setw(100)<<"|       |    | |\\     |    |    |    | |    | |       |      "<<endl;
    cout<<setw(100)<<"|       |    | | \\    |    |    |    | |    | |       |      "<<endl;
    cout<<setw(100)<<"|       |    | |  \\   |    |    |____| |    | |       |_____ "<<endl;
    cout<<setw(100)<<"|       |    | |   \\  |    |    |\\     |    | |            | "<<endl;
    cout<<setw(100)<<"|       |    | |    \\ |    |    | \\    |    | |            | "<<endl;
    cout<<setw(100)<<"|______ |____| |     \\|    |    |  \\   |____| |______ _____| "<<endl;
    cout<<endl<<endl;
    cout<<setw(65)<<"Action\t\t\tKey"<<endl<<endl;
    cout<<setw(68)<<"Move Up\t\t Up Key"<<endl;
    cout<<setw(71)<<"Move Down\t\tDown Key"<<endl;
    cout<<setw(71)<<"Move Left\t\tLeft Key"<<endl;
    cout<<setw(73)<<"Move Right\t\tRight Key"<<endl;
    cout<<endl<<setw(72)<<"Press X to go back"<<endl<<endl;
    string input;
    do{
     cout<<"\t\t\t\t\t\t\t\t";
     getline(cin,input);
     if(input=="x"||input=="X"){
          system("cls");
          return true;
     }
    }while(true);
}
bool theme(){
     label1:
    cout<<setw(80)<<"_______ _   _ _____ _            _ _____ "<<endl;
    cout<<setw(80)<<"   |    |   | |     |\\          /| |    "<<endl;
    cout<<setw(80)<<"   |    |   | |     | \\        / | |    "<<endl;
    cout<<setw(80)<<"   |    |___| |____ |  \\      /  | |____"<<endl;
    cout<<setw(80)<<"   |    |   | |     |   \\    /   | |    "<<endl;
    cout<<setw(80)<<"   |    |   | |     |    \\  /    | |    "<<endl;
    cout<<setw(80)<<"   |    |   | |____ |     \\/     | |____"<<endl;
    cout<<endl<<endl;
    cout<<setw(70)<<"1. Background Color"<<endl;
    cout<<endl;
    cout<<setw(70)<<"2. Text Color      "<<endl<<endl;
    cout<<setw(69)<<"Press X to go back"<<endl<<endl;
    string themeInput;
    do{
     cout<<"\t\t\t\t\t\t\t";
     getline(cin,themeInput); 
     if(themeInput=="1"){
          system("cls");
          if(background()==true){
               system("cls");
               goto label1;
          }
     }
     else if(themeInput=="2"){
          system("cls");
          if(text()==true){
               system("cls");
               goto label1;
          }
     }
     else if(themeInput=="X"||themeInput=="x"){
          system("cls");
          return true;
     }
    }while(true);

}
bool background(){
    cout<<setw(70)<<"Please Select the Color"<<endl;
    cout<<setw(65)<<"0\tBlack       "<<endl;
    cout<<setw(65)<<"1\tBlue        "<<endl;	
    cout<<setw(65)<<"2\tGreen       "<<endl;	
    cout<<setw(65)<<"3\tAqua        "<<endl;	
    cout<<setw(65)<<"4\tRed	        "<<endl;	
    cout<<setw(65)<<"5\tPurple      "<<endl;	
    cout<<setw(65)<<"6\tYellow      "<<endl;	
    cout<<setw(65)<<"7\tWhite       "<<endl;	
    cout<<setw(65)<<"8\tGray        "<<endl;	
    cout<<setw(65)<<"9\tLight Blue  "<<endl;
    cout<<setw(65)<<"A\tLight Green "<<endl;
    cout<<setw(65)<<"B \tLight Aqua "<<endl;
    cout<<setw(65)<<"C\tLight Red   "<<endl;
    cout<<setw(65)<<"D\tLight Purple"<<endl;
    cout<<setw(65)<<"E\tLight Yellow"<<endl;
    cout<<setw(65)<<"F\tBright White"<<endl;
    cout<<endl<<setw(69)<<"Press X to go back"<<endl<<endl;
    string colorInput;

    do{
    cout<<"\t\t\t\t\t\t\t";
    getline(cin,colorInput);
    if(colorInput=="1"){
        system("color 10");
    }
    else if(colorInput=="2"){
        system("color 20");
    }
    else if(colorInput=="3"){
        system("color 30");
    }
    else if(colorInput=="4"){
        system("color 40");
    }
    else if(colorInput=="5"){
        system("color 50");
    }
    else if(colorInput=="6"){
        system("color 60");
    }
    else if(colorInput=="7"){
        system("color 70");
    }
    else if(colorInput=="8"){
        system("color 80");
    }
    else if(colorInput=="9"){
        system("color 90");
    }
    else if(colorInput=="A"){
        system("color A0");
    }
    else if(colorInput=="B"){
        system("color B0");
    }
    else if(colorInput=="C"){
        system("color C0");
    }
    else if(colorInput=="D"){
        system("color D0");
    }
    else if(colorInput=="E"){
        system("color E0");
    }
    else if(colorInput=="F"){
        system("color F0");
    }
    else if(colorInput=="X"||colorInput=="x"){
     return true;
    }
    else{
        continue;
    }
    }while(true);
}
bool text(){
    cout<<setw(70)<<"Please Select the Color"<<endl;
    cout<<setw(65)<<"0\tBlack       "<<endl;
    cout<<setw(65)<<"1\tBlue        "<<endl;	
    cout<<setw(65)<<"2\tGreen       "<<endl;	
    cout<<setw(65)<<"3\tAqua        "<<endl;	
    cout<<setw(65)<<"4\tRed	        "<<endl;	
    cout<<setw(65)<<"5\tPurple      "<<endl;	
    cout<<setw(65)<<"6\tYellow      "<<endl;	
    cout<<setw(65)<<"7\tWhite       "<<endl;	
    cout<<setw(65)<<"8\tGray        "<<endl;	
    cout<<setw(65)<<"9\tLight Blue  "<<endl;
    cout<<setw(65)<<"A\tLight Green "<<endl;
    cout<<setw(65)<<"B \tLight Aqua "<<endl;
    cout<<setw(65)<<"C\tLight Red   "<<endl;
    cout<<setw(65)<<"D\tLight Purple"<<endl;
    cout<<setw(65)<<"E\tLight Yellow"<<endl;
    cout<<setw(65)<<"F\tBright White"<<endl;
    cout<<endl<<setw(69)<<"Press X to go back"<<endl<<endl;
    string colorInput;

    do{
    cout<<"\t\t\t\t\t\t\t";
    getline(cin,colorInput);
    if(colorInput=="1"){
        system("color 1");
    }
    else if(colorInput=="2"){
        system("color 2");
    }
    else if(colorInput=="3"){
        system("color 3");
    }
    else if(colorInput=="4"){
        system("color 4");
    }
    else if(colorInput=="5"){
        system("color 5");
    }
    else if(colorInput=="6"){
        system("color 6");
    }
    else if(colorInput=="7"){
        system("color 7");
    }
    else if(colorInput=="8"){
        system("color 8");
    }
    else if(colorInput=="9"){
        system("color 9");
    }
    else if(colorInput=="A"){
        system("color A");
    }
    else if(colorInput=="B"){
        system("color B");
    }
    else if(colorInput=="C"){
        system("color C");
    }
    else if(colorInput=="D"){
        system("color D");
    }
    else if(colorInput=="E"){
        system("color E");
    }
    else if(colorInput=="F"){
        system("color F");
    }
    else if(colorInput=="X"||colorInput=="x"){
     return true;
    }
    else{
        continue;
    }
    }while(true);
}
bool credits(){
    cout<<setw(80)<<"1. Producer          ..........        "<<endl;
    cout<<setw(80)<<"2. Programmers       ..........        "<<endl;
    cout<<setw(80)<<"                     ..........        "<<endl;
    cout<<setw(80)<<"3. Writter           ..........        "<<endl;
    cout<<setw(80)<<"4. Music             ..........        "<<endl;
    cout<<setw(80)<<"5. Composer          ..........        "<<endl;
    cout<<setw(80)<<"6. Design Artist     ..........        "<<endl;
    cout<<endl<<setw(65)<<"Press X to go back"<<endl<<endl;
    string input;
    do{
     cout<<"\t\t\t\t\t\t\t";
     getline(cin,input);
     if(input=="x"||input=="X"){
          system("cls");
          return true;
     }
    }while(true);
}