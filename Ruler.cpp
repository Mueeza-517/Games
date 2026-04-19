#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void setColor(int color)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y);
const int enemyMaxCount = 10;
int enemyX[enemyMaxCount], enemyY[enemyMaxCount], enemyLocation[5] = {6, 13, 20, 27, 34}, enemiesKilled = 0;
string enemyMovementType[enemyMaxCount]; // horizontal, vertical, diagonal
bool isEnemyKilled[enemyMaxCount];

int enemyCount = 0;
void moveEnemy();
void generateEnemy(int x, int y);
void printEnemy(int x, int y);
void eraseEnemy(int x, int y);
void killEnemy(int idx);

void generateBullet(int pX, int pY);
void eraseBullet(int x, int y);
void printBullet(int x, int y);
void moveBullet();
void makeBulletInactive(int idx);


int BulletX[100];
int BulletY[100];
bool isBulletActive[100];
int BulletCount = 0;

void Print_Maze();
void Print_Player();
void Erase_Player();
void Move_Player_left();
void Move_Player_Up();
void Move_Player_Down();
void Move_Player_Right();
void Print_Score();
char getCharAtxy(short int x, short int y);

void win();
void lose();
void header();
int subheader();

int pX = 14, pY = 34; // Coordinates for the player
int Sx = 145, Sy = 2; // Coordinates for score display

int score = 0;
bool isGameOver = false;
bool isWin = false;

main()
{
  system("cls");
  int option;
  header();
  cout <<endl <<endl<<endl<<endl<<endl<<endl;
  cout <<"\t\t\t\t\t\t\tpress any key to continue ........"<<endl<<endl<<endl;
  getch();
   option=subheader();
  {
  if(option == 1)
  {
  system("cls");
  Print_Maze();
  Print_Player();
  int y = 6, counter = 0, timer = 0;
  int random = rand() % 5;
  generateEnemy(125, enemyLocation[random]);
  while (!isGameOver)
  {
  
    Print_Score();
    Sleep(150);
    if (GetAsyncKeyState(VK_LEFT))
    {
      Move_Player_left();
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
      Move_Player_Right();
    }
    if (GetAsyncKeyState(VK_UP))
    {
      Move_Player_Up();
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
      Move_Player_Down();
    }
    if (GetAsyncKeyState(VK_SPACE))
    {
      generateBullet(pX, pY);
    }

    if (counter == 40 && enemyCount < enemyMaxCount)
    {
      random = rand() % 5;
      generateEnemy(125, enemyLocation[random]);
      counter = 0;
    }

    counter++;
    
    if (timer == 25)
    {
      moveEnemy();
      timer = 0;
    }
    timer++;
    moveBullet();

    if(enemiesKilled == 10)
    {
      isWin = true;
      isGameOver =  true;
    
    }
  }

  if (isGameOver)
  {
    system("cls");
    if(isWin)
      win();
    else 
      lose();

  }
}
}
  if(option==2)
  {
    system("cls");
    header();
    cout <<endl<<endl<<endl<<endl;
    cout <<"\t\t\t\t\t\t       INSTRUCTIONS FOR GAME"<<endl;
    cout<<"\t\t\t\t\t\t\t press up key to move player up"<<endl;
    cout<<"\t\t\t\t\t\t\t press down key to move player down"<<endl;
    cout<<"\t\t\t\t\t\t\t press right key to move right"<<endl;
    cout<<"\t\t\t\t\t\t\t press left key to move player left"<<endl;
    cout<<"\t\t\t\t\t\t\t press space to release the bullets"<<endl;
    cout<<"\t\t\t\t\t\t\t avoid enemies to enter in home"<<endl;
    cout<<"\t\t\t\t\t\t\t press any key to continue........"<<endl;
    getch();
    Sleep(1000);
    system("cls");
    header();
    cout <<endl<<endl<<endl<<endl;
    subheader();
  }
  if(option==3)
  {
    exit(0);
  }
}
int subheader()
{
  int number;
  cout <<"\t\t\t\t\t\t\t 1.  Start Game"<<endl;
  cout <<"\t\t\t\t\t\t\t 2.  To view instructions"<<endl;
  cout <<"\t\t\t\t\t\t\t 3.  To exit"<<endl;
  cout <<"\t\t\t\t\t\t\t Your option...";
  cin >> number;
  return number;
}

void generateEnemy(int x, int y)
{
  enemyX[enemyCount] = x;
  enemyY[enemyCount] = y;
  isEnemyKilled[enemyCount] = false;
  gotoxy(x, y);

  setColor(12);
  cout << " ._.";
  gotoxy(x, y + 1);
  cout << "(x x)";
  gotoxy(x, y + 2);
  cout << "/ ^ \\";
  gotoxy(x, y + 3);
  cout << " U U ";
  setColor(15);
  enemyCount++;
}

void printEnemy(int x, int y)
{
  setColor(12);
  gotoxy(x, y);
  cout << " ._.";
  gotoxy(x, y + 1);
  cout << "(x x)";
  gotoxy(x, y + 2);
  cout << "/ ^ \\";
  gotoxy(x, y + 3);
  cout << " U U ";
  setColor(15);
}

void eraseEnemy(int x, int y)
{
  gotoxy(x, y);
  cout << "    ";
  gotoxy(x, y + 1);
  cout << "     ";
  gotoxy(x, y + 2);
  cout << "      ";
  gotoxy(x, y + 3);
  cout << "     ";
}

void moveEnemy()
{
  for (int i = 0; i < enemyCount; i++)
  {
    if (!isEnemyKilled[i])
    {
      int movement = rand() % 3;
      if (enemyX[i] > 13)
      {
        eraseEnemy(enemyX[i], enemyY[i]);
        if (movement == 2)
        {
          enemyX[i] -= 8;
          if (getCharAtxy(enemyX[i], enemyY[i] + 2) != '#' && getCharAtxy(enemyX[i], enemyY[i] - 2) != '#')
          {
            if (getCharAtxy(enemyX[i] - 7, enemyY[i] - 6) == ' ')
            {
              enemyY[i] -= 7;
            }
          }
        }
        else if (movement == 1)
        {
          if (enemyY[i] >= 6 && enemyY[i] <= 24)
            enemyY[i] += 7;
          else if (enemyY[i] == 34)
            enemyY[i] -= 7;
        }
        else
        {
          enemyX[i] -= 8;
        }
        printEnemy(enemyX[i], enemyY[i]);
      }
      else
      {
        isGameOver = true;
      }
    }
  }
}

void killEnemy(int idx)
{
  isEnemyKilled[idx] = true;
  enemiesKilled++;
}


// player functions
void Print_Player()
{
  setColor(6);
  gotoxy(pX, pY);
  cout << " ^_^";
  gotoxy(pX, pY + 1);
  cout << "(-_-)";
  gotoxy(pX, pY + 2);
  cout << "(3 /";
  gotoxy(pX, pY + 3);
  cout << " L/J";
  setColor(15);
}

void Erase_Player()
{
  gotoxy(pX, pY);
  cout << "                 ";
  gotoxy(pX, pY + 1);
  cout << "                 ";
  gotoxy(pX, pY + 2);
  cout << "                 ";
  gotoxy(pX, pY + 3);
  cout << "                 ";
}

void Move_Player_left()
{
  if (getCharAtxy(pX - 1, pY + 3) == ' ' && pX > 15)
  {
    Erase_Player();
    pX = pX - 2;
    Print_Player();
  }
  Sleep(90);
}

void Move_Player_Right()
{
  if (getCharAtxy(pX + 17, pY + 3) == ' ')
  {
    Erase_Player();
    pX = pX + 2;
    Print_Player();
  }
  Sleep(90);
}

void Move_Player_Up()
{
  if (pY > 6)
  {
    Erase_Player();
    pY = pY - 7;
    Print_Player();
  }
  Sleep(90);
}

void Move_Player_Down()
{
  if (pY < 34)
  {
    Erase_Player();
    pY = pY + 7;
    Print_Player();
  }
  Sleep(90);
}

void Print_Score()
{
  gotoxy(Sx, Sy);
  cout << "Score : " << score << " ";
}

// printing maze
void Print_Maze()
{
  setColor(10);
  cout << "#################################################################################################################################################################" << endl;
  cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  cout << "##                                                                                                                                                             ##" << endl;
  cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  cout << "#################################################################################################################################################################" << endl;
  cout << "##   _____                                                                                                                                                     ##" << endl;
  cout << "##  /  o  \\                                                                                                                                                    ##" << endl;
  cout << "## /_______\\                                                                                                                                                   ##" << endl;
  cout << "## |   _   |                                                                                                                                                   ##" << endl;
  cout << "## |  | |  |                                                                                                                                                   ##" << endl;
  cout << "## |  |.|  |                                                                                                                                                   ##" << endl;
  cout << "## ----------------------------------------------------------------------------------------------------------------------------------------------------------- ##" << endl;
  cout << "##   _____                                                                                                                                                     ##" << endl;
  cout << "##  /  o  \\                                                                                                                                                    ##" << endl;
  cout << "## /_______\\                                                                                                                                                   ##" << endl;
  cout << "## |   _   |                                                                                                                                                   ##" << endl;
  cout << "## |  | |  |                                                                                                                                                   ##" << endl;
  cout << "## |  |.|  |                                                                                                                                                   ##" << endl;
  cout << "## ----------------------------------------------------------------------------------------------------------------------------------------------------------- ##" << endl;
  cout << "##   _____                                                                                                                                                     ##" << endl;
  cout << "##  /  o  \\                                                                                                                                                    ##" << endl;
  cout << "## /_______\\                                                                                                                                                   ##" << endl;
  cout << "## |   _   |                                                                                                                                                   ##" << endl;
  cout << "## |  | |  |                                                                                                                                                   ##" << endl;
  cout << "## |  |.|  |                                                                                                                                                   ##" << endl;
  cout << "## ----------------------------------------------------------------------------------------------------------------------------------------------------------- ##" << endl;
  cout << "##   _____                                                                                                                                                     ##" << endl;
  cout << "##  /  o  \\                                                                                                                                                    ##" << endl;
  cout << "## /_______\\                                                                                                                                                   ##" << endl;
  cout << "## |   _   |                                                                                                                                                   ##" << endl;
  cout << "## |  | |  |                                                                                                                                                   ##" << endl;
  cout << "## |  |.|  |                                                                                                                                                   ##" << endl;
  cout << "## ----------------------------------------------------------------------------------------------------------------------------------------------------------- ##" << endl;
  cout << "##   _____                                                                                                                                                     ##" << endl;
  cout << "##  /  o  \\                                                                                                                                                    ##" << endl;
  cout << "## /_______\\                                                                                                                                                   ##" << endl;
  cout << "## |   _   |                                                                                                                                                   ##" << endl;
  cout << "## |  | |  |                                                                                                                                                   ##" << endl;
  cout << "## |  |.|  |                                                                                                                                                   ##" << endl;
  cout << "## ------------------------------------------------------------------------------------------------------------------------------------------------------------##" << endl;
  cout << "#################################################################################################################################################################" << endl;
  cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
  setColor(15);
}
void win()
{
  setColor(2);
cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;  
cout<<"                                                                                             _                  "<<endl;
cout<<"                                                                                            (_)                 "<<endl;
cout<<"                                                             _   _   ___   _   _  __      __ _  _ __            "<<endl;
cout<<"                                                            | | | | / _ \\ | | | | \\ \\ /\\ / /| || '_ \\      "<<endl;
cout<<"                                                            | |_| || (_) || |_| |  \\ V  V / | || | | |         "<<endl;
cout<<"                                                             \\__, | \\___/  \\__,_|   \\_/\\_/  |_||_| |_|     "<<endl;
cout<<"                                                              __/ |                                             "<<endl;
cout<<"                                                             |___/                                              "<<endl;
 setColor(15);
}

void lose()
{
  setColor(5); 
cout<<endl;  
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;  
cout <<"                                                    __ _   __ _  _ __ ___    ___    ___  __   __  ___  _ __                "<<endl;  
cout <<"                                                   / _` | / _` || '_ ` _ \\  / _ \\  / _ \\ \\ \\ / / / _ \\| '__|         "<<endl;
cout <<"                                                  | (_| || (_| || | | | | ||  __/ | (_) | \\ V / |  __/| |                 "<<endl;
cout <<"                                                   \\__, | \\__,_||_| |_| |_| \\___|  \\___/   \\_/   \\___||_|            "<<endl;
cout <<"                                                    __/ |                                                                  "<<endl;
cout <<"                                                   |___/                                                                   "<<endl <<endl <<endl;
cout <<"                                                                            _                                              "<<endl; 
cout <<"                                                                           | |                                             "<<endl; 
cout <<"                                                      _   _   ___   _   _  | |  ___   ___   ___                            "<<endl;    
cout <<"                                                     | | | | / _ \\ | | | | | | / _ \\ / __| / _ \\                        "<<endl; 
cout <<"                                                     | |_| || (_) || |_| | | || (_) |\\__ \\|  __/                         "<<endl; 
cout <<"                                                      \\__, | \\___/  \\__,_| |_| \\___/ |___/ \\___|                      "<<endl; 
cout <<"                                                        _/ |                                                               "<<endl; 
cout <<"                                                      |___/                                                                "<<endl; 
 setColor(15);
}

void header()
 {  
   setColor(3);
cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;                       
cout<<"                                                      _____  _   _  _____      ______  _   _  _      _____ ______           "<<endl;
cout<<"                                                     |_   _|| | | ||  ___|     | ___ \\| | | || |    |  ___|| ___ \\        "<<endl;
cout<<"                                                       | |  | |_| || |__       | |_/ /| | | || |    | |__  | |_/ /          "<<endl;
cout<<"                                                       | |  |  _  ||  __|      |    / | | | || |    |  __| |    /           "<<endl;
cout<<"                                                       | |  | | | || |___      | |\\ \\ | |_| || |____| |___ | |\\ \\       "<<endl;
cout<<"                                                       \\_/  \\_| |_/\\_____|     \\_| \\_| \\___/ \\_____/\\____/ \\_| \\_|"<<endl;
  setColor(15);
}
void generateBullet(int pX, int pY)
{
  BulletX[BulletCount] = pX + 5;
  BulletY[BulletCount] = pY + 2;
  isBulletActive[BulletCount] = true;
  gotoxy(pX + 5, pY + 2);
  cout << "->";
  BulletCount++;
}

void printBullet(int x, int y)
{
  gotoxy(x, y);
  cout << "->";
}

void eraseBullet(int x, int y)
{
  gotoxy(x, y);
  cout << "  ";
}

void makeBulletInactive(int idx)
{
  isBulletActive[idx] = false;
}

void moveBullet()
{
  for (int x = 0; x < BulletCount; x++)
  {
    if (isBulletActive[x])
    {
      char nextChar = getCharAtxy(BulletX[x] + 2, BulletY[x]);
      if (nextChar != ' ')
      {
        eraseBullet(BulletX[x], BulletY[x]);
        makeBulletInactive(x);
        if (nextChar == '/')
        {
          score++;
          for (int i = 0; i < enemyCount; i++)
          {
            if (!isEnemyKilled[i] && (BulletX[x] + 2) == enemyX[i])
            {
              eraseEnemy(enemyX[i], enemyY[i]);
              killEnemy(i);
            }
          }
        }
      }
      else
      {
        eraseBullet(BulletX[x], BulletY[x]);
        BulletX[x] += 1;
        printBullet(BulletX[x], BulletY[x]);
      }
    }
  }
}

// gotoxy function
void gotoxy(int x, int y)
{
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

// get char function
char getCharAtxy(short int x, short int y)
{
  CHAR_INFO ci;
  COORD xy = {0, 0};
  SMALL_RECT rect = {x, y, x, y};
  COORD coordBufSize;
  coordBufSize.X = 1;
  coordBufSize.Y = 1;
  return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}