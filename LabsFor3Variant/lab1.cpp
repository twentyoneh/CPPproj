
#include<iostream>
using namespace std;

const double epsilon = 0.001;

double  calculate_series(double x) {
    double term = x;       // Первый член ряда
    double sum = term;     // Начальная сумма ряда
    int n = 1;             // Индекс члена ряда

    while (std::abs(term) > epsilon) {
        n++;  // Увеличиваем индекс

        // Рассчитываем следующий член ряда по формуле (-1)^(n-1) * (x^(2n-1)) / (2n-1)
        term *= (-1) * x * x;  // x^(2n-1) = предыдущий член умножаем на x^2, (-1) для чередования знаков
        term /= (2 * n - 1);   // Делим на (2n-1)

        sum += term;           // Добавляем член ряда к сумме
    }

    return sum;
}


int fact(int num) {
    int res = 1;
    for (int i = 1; i <= num; i++)
    {
        res *= i;
    }
    return res;
}

bool is_odd_and_tripled(int number) {
    return (number % 3 == 0) && ((number / 3) % 2 != 0);
}
// 1_1
void  lab1_1() {

    double pi = 3.1415926535;
    double a, b;
    double res;
    cout << "Введите а:";
    cin >> a;
    cout << "Введите b:";
    cin >> b;
    res = atan(sin(a + pi) / cos(b + 2.87)) / sqrt(a + pow(cos(b), 2));
    cout << "Значение равное: %f", res;
}



void  lab1_2() {
    double x1 = 0.1;
    double x2 = 0.9;
    double x3 = -0.62;

    cout << "F(x1) = " << calculate_series(x1) << std::endl;
    cout << "F(x2) = " << calculate_series(x2) << std::endl;
    cout << "F(x3) = " << calculate_series(x3) << std::endl;
}

//1_3
void  lab1_3_1() {
    int n, j = 1;
    cout << "Введите n: ";
    cin >> n;
    while (j <= n) {
        if (n % j == 0) {
            cout << j << "; ";
        }
        j++;
    }
}

void  lab1_3_2() {
    const int size = 100;
    double numbers[size];
    double max_val = std::numeric_limits<double>::lowest();  // Инициализация минимальным возможным значением
    double min_val = std::numeric_limits<double>::max();     // Инициализация максимальным возможным значением

    // Ввод 100 вещественных чисел
    std::cout << "Enter 100 real numbers: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> numbers[i];

        // Находим максимальное и минимальное значение
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
        if (numbers[i] < min_val) {
            min_val = numbers[i];
        }
    }

    // Вычисляем разность
    double difference = max_val - min_val;

    // Выводим результат
    std::cout << "Максимальное значение: " << max_val << std::endl;
    std::cout << "Минимальное значение: " << min_val << std::endl;
    std::cout << "Разница межд max и min: " << difference << std::endl;
}

void lab1_3_3() {
    int n;
    long long res = 1;
    cout << "Введитe n: ";
    cin >> n;
    if (n % 2 == 0) {
        for (int i = 1; i <= n; i += 2)
        {
            res *= i;
        }
    }
    else
    {
        for (int i = 1; i <= n; i += 1)
        {
            res *= i;
        }
    }
    cout << "Результат: " << res;
}

void lab1_3_4() {
    int k, x, m, n;
    float res = 0;
    cout << "Введитe n: ";
    cin >> n;
    cout << "Введитe x: ";
    cin >> x;
    for (int k = 1; k < n; k++)
    {
        for (int m = 1; m < n; m++)
        {
            res += (x + k) / m;
        }
    }
    cout << "Результат: " << res;
}

void lab1_3_5() {
    int i, j, n;
    float res = 0;
    cout << "Введитe n: ";
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            res += 1 / i+j;
        }
    }
    cout << "Результат: " << res;
}



void lab1_3_6() {
    double tmp = 0, res = 0;
    for (int k = 1; k  < 10; k++)
    {
        for (int n = 1; n  < k; n++)
        {
            tmp = sin(k * n);
        }
        res += tmp / fact(k);
    }
    cout << "Результат: " << res;
}

void lab1_3_7() {
    int n;
    int sum = 0;

    cout << "Введите n";
    std::cin >> n;

    // Цикл по значениям i от 1 до n
    for (int i = 1; i <= n; i++) {
        // Вычисление числа по формуле (i^3) - 3 * i * (n^2) + n
        int result = (i * i * i) - 3 * i * (n * n) + n;

        // Проверка, является ли результат утроенным нечётным числом
        if (is_odd_and_tripled(result)) {
            sum += result;  // Добавляем к сумме, если условие выполнено
        }
    }

    std::cout << "Результат: " << sum << std::endl;

}

void lab1_4() {
    int n;
    cout << "Введите n";
    cin >> n;
    if (n >= 5 && n <= 0) {
        cout << "Число входит в дапазин от 0 до 5";
    }
    else
    {
        cout << "Число не входит в дапазин от 0 до 5";
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;
    std::cout << "Введите номер лабы(1-10): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        lab1_1();
        break;
    case 2:
        lab1_2();
        break;
    case 3:
        lab1_3_1();
        break;
    case 4:
        lab1_3_2();
        break;
    case 5:
        lab1_3_3();
        break;
    case 6:
        lab1_3_4();
        break;
    case 7:
        lab1_3_5();
        break;
    case 8:
        lab1_3_6();
        break;
    case 9:
        lab1_3_7();
        break;
    case 10:
        lab1_4();
        break;
    default:
        std::cout << "Неверно ввели номер!" << std::endl;
    }
    return 0;
}