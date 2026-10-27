#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <windows.h> 

using namespace std;

// Генерація випадкових елементів масиву в діапазоні [Low, High]
void Create(int* a, const int size, const int Low, const int High)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = Low + rand() % (High - Low + 1);
    }
}

// Форматне виведення елементів масиву в рядок
void Print(const int* a, const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << setw(4) << a[i];
    }
    cout << endl;
}

// 1.1. Обчислення добутку елементів масиву з парними номерами (індекси 0, 2, 4...)
int ProductEvenIndices(const int* a, const int size)
{
    int product = 1;
    for (int i = 0; i < size; i += 2)
    {
        product *= a[i];
    }
    return product;
}

// Пошук індексу першого нульового елемента (-1, якщо нулів немає)
int FirstZero(const int* a, const int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] == 0)
            return i;
    }
    return -1;
}

// Пошук індексу останнього нульового елемента (-1, якщо нулів немає)
int LastZero(const int* a, const int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (a[i] == 0)
            return i;
    }
    return -1;
}

// 1.2. Обчислення суми елементів між першим і останнім нульовими елементами
int SumBetweenZeros(const int* a, const int size)
{
    int first = FirstZero(a, size);
    int last = LastZero(a, size);

    // Якщо 0 відсутні, є лише один 0 або між ними немає елементів
    if (first == -1 || last == -1 || first >= last - 1)
        return 0;

    int sum = 0;
    for (int i = first + 1; i < last; i++)
    {
        sum += a[i];
    }
    return sum;
}

// 2. Перетворення масиву: спочатку додатні та нулі (>= 0), потім від'ємні (< 0)
// із збереженням початкового відносного порядку елементів
void Rearrange(int* a, const int size)
{
    int* temp = new int[size];
    int index = 0;

    // Крок 1: Копіюємо елементи >= 0
    for (int i = 0; i < size; i++)
    {
        if (a[i] >= 0)
        {
            temp[index++] = a[i];
        }
    }

    // Крок 2: Копіюємо елементи < 0
    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            temp[index++] = a[i];
        }
    }

    // Крок 3: Переносимо результат назад у початковий масив
    for (int i = 0; i < size; i++)
    {
        a[i] = temp[i];
    }

    delete[] temp; // Звільнення тимчасового масиву
}

int main()
{
    // Встановлення кириличної кодової сторінки Windows-1251 для консолі
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand((unsigned)time(NULL));

    int n;
    cout << "n = ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Розмір масиву повинен бути більшим за 0!" << endl;
        return 1;
    }

    // Створення динамічного масиву
    int* a = new int[n];

    // Діапазон значень (включає від'ємні, додатні значення та нуль)
    int Low = -10;
    int High = 10;

    Create(a, n, Low, High);

    cout << "\nПочатковий масив:" << endl;
    Print(a, n);

    // 1.1 Обчислення добутку елементів з парними індексами
    int product = ProductEvenIndices(a, n);
    cout << "\n1.1. Добуток елементів з парними номерами: " << product << endl;

    // 1.2 Обчислення суми між першим і останнім 0
    int sum = SumBetweenZeros(a, n);
    cout << "1.2. Сума елементів між першим і останнім 0: " << sum << endl;

    // 2. Перетворення масиву
    Rearrange(a, n);

    cout << "\nМодифікований масив (спочатку >= 0, потім < 0):" << endl;
    Print(a, n);

    // Звільнення виділеної динамічної пам'яті
    delete[] a;

    return 0;
}