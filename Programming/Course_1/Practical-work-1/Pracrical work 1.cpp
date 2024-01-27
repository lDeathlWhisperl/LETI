#include <iostream>

void memoryView(long long int, int order, int space = -1);

union Unity_f
{
    int tool;
    float num_f;
    Unity_f()
    {
        std::cout << "(float)  Введите  положительное  вещественное число: ";
        std::cin >> num_f;
    }
};

union Unity_d
{
    long long int tool1;
    double num_d;
    Unity_d()
    {
        std::cout << "(double) Введите  положительное  вещественное число: ";
        std::cin >> num_d;
    }
};

int main()
{
    setlocale(0, "");
    int num_i;
    std::cout << "(int)    Введите  положительное целочисленное число: ";
    std::cin >> num_i;
    Unity_f unity_f;
    Unity_d unity_d;
    system("Cls");

    /*1*/
    std::cout << "\n1)--------------------\n" <<
        "int:           " << sizeof(int) << " байта\n"
        "short int:     " << sizeof(short int) << " байта\n"
        "long long int: " << sizeof(long long) << " байт\n"
        "float:         " << sizeof(float) << " байта\n"
        "double:        " << sizeof(double) << " байт\n"
        "long double:   " << sizeof(long double) << " байт\n"
        "char:          " << sizeof(char) << " байт\n"
        "bool:          " << sizeof(bool) << " байт\n";

    /*2*/
    std::cout << "\n2)--------------------\n";

    std::cout << " " << num_i << " = ";
    memoryView(num_i, 32);

    std::cout << "" << -num_i << " = ";
    memoryView(-num_i, 32);

    /*3*/
    std::cout << "\n3)--------------------\n";

    std::cout << " " << unity_f.num_f << " = ";
    memoryView(unity_f.tool, 32, 23);

    std::cout << "" << -unity_f.num_f << " = ";
    memoryView(-unity_f.tool, 32, 23);

    /*4*/
    std::cout << "\n4)--------------------\n";

    std::cout << " " << unity_d.num_d << " = ";
    memoryView(unity_d.tool1, 64, 52);

    std::cout << "" << -unity_d.num_d << " = ";
    memoryView(-unity_d.tool1, 64, 52);
}

void memoryView(long long int value, int order, int space)
{
    unsigned long long int mask = 1;
    char *arr = new char[order]; //массив для отзеркаливания числа

    for (int i = 1; i <= order; i++)
    {
        arr[i - 1] = (value & mask ? '1' : '0');
        mask <<= 1;
    }

    for (int i = order - 1; i >= 0; i--)
    {
        std::cout << arr[i];
        if (i == space)
            std::cout << ' ';
        if (i == order - 1)
            std::cout << ' ';
    }
    std::cout << '\n';
    delete[] arr;
}
