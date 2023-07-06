#include <iostream>
#include <conio.h>
#include <ctime>

#include "snake.h"
#include "Food.h"
#include "snake.cpp"
#include "Food.cpp"

#define WIDTH 50
#define HEIGHT 25

using namespace std;

Snake snake({WIDTH / 2, HEIGHT / 2}, 1);
Food food;

int score;

void board()
{

    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.gen_pos();
    vector<COORD> snake_body = snake.get_body();

    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1)
                cout << "#";
            else if (i == snake_pos.Y && j + 1 == snake_pos.X)
                cout << "0";
            else if (i == food_pos.Y && j + 1 == food_pos.X)
                cout << "*";
            else
            {
                bool isBodyPart = false;
                for (int k = 0; k < snake_body.size() - 1; k++)
                {
                    if (i == snake_body[k].Y && j + 1 == snake_body[k].X)
                    {
                        cout << "0";
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart)
                {
                    cout << " ";
                }
            }
        }
        cout << "#" << endl;
    }
}

int game()
{
    score = 0;
    cout << "\nENTER w FOR UP\nENTER s FOR DOWN\nENTER a FOR LEFT\nENTER d FOR RIGHT\n";
    cout << "Horizontal walls are passable while vertical are not \n";
    srand(time(NULL));
    food.gen_food();
    bool game_over = 0;
    while (!game_over)
    {
        board();
        if (kbhit())
        {
            switch (getch())
            {
            case 'w':
                snake.change_dir('u');
                break;
            case 'a':
                snake.change_dir('l');
                break;
            case 's':
                snake.change_dir('d');
                break;
            case 'd':
                snake.change_dir('r');
                break;
            }
        }

        if (snake.collided())
            game_over = 1;

        if (snake.eaten(food.gen_pos()))
        {
            food.gen_food();
            snake.grow();
            score++;
        }

        snake.move_snake();

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
    if (game_over)
    {
        cout << "Game Over!!!\n";
        cout << "You Scored:-" << score << " points" << endl;
    }
}

int main()
{
    cout << "Do you want to play snake game developed by Naman!!!" << endl;
    cout << "Please type Yes/No" << endl;
    string s;
    cin >> s;
    for (auto x : s)
        x = tolower(x);
    if (s == "yes")
    {
        game();
    }
    else
    {
        cout << "Maybe you changed your mind!!!";
    }
}