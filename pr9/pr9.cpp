// pr9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;
const int row = 5;
const int col = 2;
int mas2[col][row];
int result[row][row];
//int mas[row][col];

DWORD WINAPI RandomMas(LPVOID params) {
    int(*mas)[col] = (int(*)[col])params;
    DWORD threadId = GetCurrentThreadId();
    srand(time(NULL) + threadId);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mas[i][j] = rand()%10;
        }
    }
    return 0;
}
DWORD WINAPI  Multiply(LPVOID params) {
       int(*mas1)[col] = (int(*)[col])params;
     for (int i = 0; i < row; i++) {
            for (int j = 0; j < row; j++) {
                result[i][j] = 0;
                for (int k = 0; k < col; k++) {
                    result[i][j] += mas1[i][k] * mas2[k][j];
                }
            }
        }
        return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    INT mas1[row][col];
    HANDLE hThread1, hThread2, hThread3;
    DWORD IDThread1, IDThread2, IDThread3;
    hThread1 = CreateThread(NULL, 0, RandomMas, mas1, 0, &IDThread1);
    if (hThread1 == NULL) {
        return GetLastError();
    }
    hThread2 = CreateThread(NULL, 0, RandomMas, mas2, 0, &IDThread2);
    if (hThread2 == NULL) {
        CloseHandle(hThread1);
        return GetLastError();
    }
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    std::cout << "Первый массив:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << mas1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Второй массив:\n";
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            std::cout << mas2[i][j] << " ";
        }
        std::cout << std::endl;
    }
    hThread3 = CreateThread(NULL, 0, Multiply, (LPVOID)mas1, 0, &IDThread3);
    if (hThread3 == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hThread3, INFINITE);
    CloseHandle(hThread3);
    cout << "Результат умножения:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
