#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h> // Для кольору та очікування
#include <conio.h> // Для _kbhit()

using namespace std;

// Функція для створення матриці 7x6 заповненої пробілами
vector<vector<char>> createEmptyMatrix() 
{
    return vector<vector<char>>(7, vector<char>(6, ' '));
}

// Випадковий вибір кольору, який не зливається з фоном
int getRandomColor(bool excludeBlack = false) 
{
    int color;

    do 
    {
        color = rand() % 15 + 1; // Від 1 до 15, бо 0 - це чорний
    } while (excludeBlack && color == 0);

    return color;
}

// Випадковий вибір букви з української абетки, окрім м’якого знака
char getRandomUkrainianLetter(bool specialSet = false) 
{
    if (specialSet) 
    {
        string letters = "шдрШДР";

        int index = rand() % letters.size();

        return letters[index];
    }
    else 
    {
        string letters = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя"; // Без м’якого знака

        int index = rand() % letters.size();

        return letters[index];
    }
}

void displayMatrix(const vector<vector<char>>& matrix) 
{
    system("cls"); // Очищуємо екран
    for (const auto& row : matrix) 
    {
        for (char cell : row) 
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() 
{
    system("chcp 1251 > null");
    srand(time(NULL)); // Ініціалізація генератора випадкових чисел
    vector<vector<char>> matrix;
    bool programRunning = true;
    int choice;

    while (programRunning) 
    {
        cout << "1. Запустити\n2. Зупинити\n3. Вийти\nВаш вибір: ";
        cin >> choice;

        if (choice == 1) 
        {
            bool running = true;
            while (running && !_kbhit()) 
            { // Працює, поки не натиснута клавіша

                matrix = createEmptyMatrix();

                int x = rand() % 6; // Вибір стовпця
                int y = rand() % 5; // Вибір рядка, щоб залишити місце внизу

                // Встановлення випадкової букви в матрицю
                matrix[y][x] = getRandomUkrainianLetter();
                matrix[y + 1][x] = getRandomUkrainianLetter(true);

                // Зміна кольору та відображення матриці
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getRandomColor());
                displayMatrix(matrix);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Відновлення стандартного кольору

                Sleep(rand() % 9000 + 1000); // Очікування від 1 до 9 секунд
            }
            if (_kbhit()) 
            {
                _getch(); // Читаємо натиснуту клавішу, щоб зупинити
            }
        }
        else if (choice == 2) 
        {
            // Зупинка програми (програма зупиниться сама, коли користувач натисне клавішу)
            continue;
        }
        else if (choice == 3) 
        {
            programRunning = false;
        }
    }

    return 0;
}
