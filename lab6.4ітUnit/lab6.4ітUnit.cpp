#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Оголошення тестованих функцій програми
int ProductEvenIndices(const int* a, const int size)
{
    int product = 1;
    for (int i = 0; i < size; i += 2)
    {
        product *= a[i];
    }
    return product;
}

int FirstZero(const int* a, const int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] == 0)
            return i;
    }
    return -1;
}

int LastZero(const int* a, const int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (a[i] == 0)
            return i;
    }
    return -1;
}

int SumBetweenZeros(const int* a, const int size)
{
    int first = FirstZero(a, size);
    int last = LastZero(a, size);

    if (first == -1 || last == -1 || first >= last - 1)
        return 0;

    int sum = 0;
    for (int i = first + 1; i < last; i++)
    {
        sum += a[i];
    }
    return sum;
}

void Rearrange(int* a, const int size)
{
    int* temp = new int[size];
    int index = 0;

    for (int i = 0; i < size; i++)
    {
        if (a[i] >= 0)
        {
            temp[index++] = a[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            temp[index++] = a[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        a[i] = temp[i];
    }

    delete[] temp;
}

namespace UnitTestLab64
{
    TEST_CLASS(UnitTestLab64)
    {
    public:

        // Тест 1: Перевірка обчислення добутку елементів з парними індексами (0, 2, 4...)
        TEST_METHOD(TestProductEvenIndices)
        {
            const int size = 5;
            // Парні індекси [0, 2, 4]: елементи 2, 3, 4
            int a[size] = { 2, 5, 3, 7, 4 };
            int expected = 24; // 2 * 3 * 4 = 24

            int actual = ProductEvenIndices(a, size);

            Assert::AreEqual(expected, actual);
        }

        // Тест 2: Перевірка обчислення суми елементів між першим і останнім нулями
        TEST_METHOD(TestSumBetweenZeros)
        {
            const int size = 6;
            // Нулі знаходяться на індексах 1 та 4. Між ними елементи: 3 + 4 = 7
            int a[size] = { 1, 0, 3, 4, 0, 5 };
            int expected = 7;

            int actual = SumBetweenZeros(a, size);

            Assert::AreEqual(expected, actual);
        }

        // Тест 3: Перевірка перетворення масиву (спочатку >= 0, потім < 0 зі збереженням порядку)
        TEST_METHOD(TestRearrange)
        {
            const int size = 5;
            int a[size] = { -2, 5, 0, -3, 4 };
            int expected[size] = { 5, 0, 4, -2, -3 };

            Rearrange(a, size);

            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(expected[i], a[i]);
            }
        }
    };
}