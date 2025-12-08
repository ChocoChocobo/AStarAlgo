#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include "shpingalet.h"

using namespace std;

struct Cell // координаты символа в двумерном массиве символов
{
    int x;
    int y;
};

struct Node // узел, который хранит состояние клетки
{
    int x;
    int y;
    int g; // стомость от начала клетки
    int f; // полная стоимость (g + h)
    Node* parent; // предыдущий узел
};

int DistanceToCell(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* алгоритм, который возвращает указатель на клетку, которую мы ищем
Cell* AStarSearch(string* map, int height, int width, Cell start, Cell end)
{
    // массив указателей на доступность узла
    bool** closed = new bool* [height]; // указываем строками на столбцы
    // массив указателей на стоимость узла
    int** gcost = new int* [height];
    Node** nodes = new Node * [height];

    // Инициализация поля и значений узлов
    for (int i = 0; i < width; i++)
    {
        // Выделяем строки
        closed[i] = new bool[width];
        gcost[i] = new int[width];
        nodes[i] = new Node[width];

        // Заполнение значений
        for (int j = 0; j < height; j++)
        {
            closed[i][j] = false;
            gcost[i][j] = 1000000000;
            nodes[i][j].x = i;
            nodes[i][j].y = j;
            nodes[i][j].g = 1000000000;
            nodes[i][j].f = 1000000000;
            nodes[i][j].parent = NULL;
        }
    }

    int maxOpen = height + width; // максимальное количество элементов в таблице
    int* openX = new int[maxOpen]; // массив X координат в открытых узлах
    int* openY = new int[maxOpen]; // массив Y координат в открытых узлах
    int* openG = new int[maxOpen]; // массив значений стоимости
    int* openF = new int[maxOpen]; // массив значений полной стоимости
    int openCount = 0; // текущее количество элементов 

    // Стартовая клетка
    gcost[start.x][start.y] = 0;
    nodes[start.x][start.y].g = 0;
    nodes[start.x][start.y].f = DistanceToCell(start.x, start.y, end.x, end.y);
    nodes[start.x][start.y].parent = NULL;

    openX[openCount] = start.x;
    openY[openCount] = start.y;
    openF[openCount] = nodes[start.x][start.y].f;
    openG[openCount] = 0;
    openCount++;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << SHPINGALET << endl;
    string map[] =
    {
        // ALT+0183
        // · - пустая клетка
        // ■ - стена
        "···+·",
        "++·+·",
        "·····",
        "·+++·",
        "·····"
    };

    int height = 5;
    int width = 5;

    Cell start; // структура клетки (символа в двумерном массиве)
    start.x = 0;
    start.y = 0;

    Cell end;
    end.x = 4;
    end.y = 4;

    int pathLength = 0;
    Cell path = AStarSearch();

    if (path != NULL)
    {
        PrintMap();
        delete[path];
    }
    else cout << "Не удалось построить пути к цели!\n";
}