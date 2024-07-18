#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

const int width = 30;
const int height = 30;

void PrintGrid(vector<vector<bool>>& grid)  // Объявление функции, принимающей значение двумерного массива grid
{
    for (int x = 0; x < height; ++x)
    {
        for (int y = 0; y < width; ++y) // Вложенный двухуровневый цикл, объявляющий начальные значения поля
        {
            cout << (grid[x][y] ? 'O' : '.');   // Если изначально не объявлено значение клетки в точке (x, y), то она объявляется мертвой
        }
        cout << '\n'; // Следующий ряд
    }
}

int countNeighbors(vector<vector<bool>>& grid, int x, int y) {    // Объявление функции счеткика живых соседей, принимающий значение поля, а также координаты клетки
    int count = 0;    // Объявление счетчика соседей
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {     // Вложенный цикл, позволяющий рассмотреть все восемь клеток вокруг выбранной
            if (i == 0 && j == 0) continue;      // Продолжение, если клетка равна самой себе
            int nx = x + i;     // Клетка, сдвинутая на i по столбцу
            int ny = y + j;     // Клетка, сдвинутая на j по строке
            if (nx >= 0 && nx < height && ny >= 0 && ny < width)    // Если координата не за рамками поля, прибавляем значению счетчика значение клетки, с координатами (х + i, y + j)
                count += grid[nx][ny];
        }
    }
    return count;   // Возвращает результат счетчика
}


void updateGrid(vector<vector<bool>>& grid) {   // Обновление поля
    vector<vector<bool>> newGrid = grid;    // Новый динамический булев массив, совпадающий со старым
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {   // Вложенный цикл для проверки каждой клетки
            int neighbours = countNeighbors(grid, x, y);    // Переменная "соседи" равна возвращаемому из функции счетчика соседей значению счетчика
            if (grid[x][y]) {   // Если значение клетки 1, то клетка остается в данной ячейке если истинно, что у нее 2 или 3 соседа
                newGrid[x][y] = (neighbours == 2 || neighbours == 3);
            }
            else {  // Если изначально значение клетки 0, но у нее три соседа, то она принимает значение истинности
                newGrid[x][y] = (neighbours == 3);
            }
        }
    }
    grid = newGrid;     // Замена поля на новое
}

int main() {
    vector<vector<bool>> grid(height, vector<bool>(width, false));

    // Начальное состояние

    grid[0][1] = true;
    grid[1][0] = true;
    grid[0][0] = true;
    grid[1][2] = true;
    grid[2][2] = true;

    while (true) {
        PrintGrid(grid);
        updateGrid(grid);
    }
}
