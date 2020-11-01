//1. Создать объект - контейнер в соответствии с вариантом задания и заполнить его данными,
//    тип которых определяется вариантом задания.
//2. Просмотреть контейнер.
//3. Создать второй контейнер этого же класса и заполнить его данными того же типа,
//    что и первый контейнер.
//4. Изменить первый контейнер, удалив из него n элементов после заданного и добавив затем в
//    него все элементы из второго контейнера.
//5. Просмотреть первый и второй контейнеры.
//6. Отсортировать первый и второй контейнеры по возрастанию элементов.
//    Условие сортировки(по какому пункту производится сортировка) задает пользователь.
//7. Просмотреть их.
//8. Получить третий контейнер путем слияния первых двух.
//9. Просмотреть третий контейнер.
//10.Подсчитать, сколько элементов, удовлетворяющих заданному условию, 
//    содержит третий контейнер(по варианту).
//
//queue     Дешевле заданной стоимости      Класс «Автомобиль». Mарка, максимальная скорость, цена

#include <fstream>
#include <queue>
#include <algorithm>
#include <functional>
#include "Car.h"

string GetFilename()
{
    string filename = "";
    fstream file;

    while (!file.is_open())
    {
        cout << "Введите имя файла\n";
        cin >> filename;
        file.open(filename);
    }
    file.close();
    system("cls");
    return filename;
}
void takefromfile(queue<Auto>& alfa)
{
    ifstream file;
    file.open(GetFilename());
    string name = "";
    int speed = 0;
    int price = 0;
    while (!file.eof())
    {
        file >> name >> speed >> price;
        alfa.push(Auto(name, speed, price));
    }
    file.close();
}

void printQ(queue<Auto> Q)
{
    while (!Q.empty())
    {
        Q.front().print();
        cout << endl;
        Q.pop();
    }
}

function <bool(Auto&, Auto&)> choosemode(int mychoise = -1)
{
    int choose = 2;
    if (mychoise == -1)
    {
        do {
            if (choose < 1 || choose > 3) cout << "Введите корректные значения";
            cout << "\n\nВыберите, по какому параметру сортировать\n";
            cout << "1 - по названию\n";
            cout << "2 - по скорости\n";
            cout << "3 - по цене\n";
            cin >> choose;
        } while (choose < 1 || choose > 3);
    }
    else choose = mychoise;
    if (choose == 1) return [](Auto& a, Auto& b) {return a.GetName() < b.GetName(); };
    if (choose == 2) return [](Auto& a, Auto& b) {return a.GetSpeed() < b.GetSpeed(); };
    return [](Auto& a, Auto& b) {return a.GetPrice() < b.GetPrice(); };
}
void Sort(queue<Auto>& Q, int mychoise = -1)
{
    if (Q.empty()) return;

    std::vector<Auto> alfa;
    int n = Q.size();
    int i = 0;
    while (!Q.empty())
    {
        alfa.push_back(Q.front());
        Q.pop();
    }

    std::sort(alfa.begin(), alfa.end(), choosemode(mychoise));

    for (i = 0; i < n; i++)
        Q.push(alfa[i]);
}

void change(queue<Auto>& Q, queue<Auto>& Q2)
{
    cout << "Удаляем числв из интервала и в конец - всю 2 очередь";
    queue<Auto> Q_buff = Q;
    function <int(int)> input = [](int n)
    {
        int a = 0;
        do
        {
            cout << "Введите число от 0 до " << n;
            cout << "\n\nВведите число\n";
            cin >> a;
        } while (a < 0 || a > n);
        return a;
    };
    int b = input(Q.size());
    int a = input(b);

    while (!Q.empty()) Q.pop();
    int i = 0;
    for (; i < a; i++)
    {
        Q.push(Q_buff.front());
        Q_buff.pop();
    }
    for (; i < b; i++) Q_buff.pop();
    for (; !Q_buff.empty();)
    {
        Q.push(Q_buff.front());
        Q_buff.pop();
    }
    Q_buff = Q2;
    for (; !Q_buff.empty();)
    {
        Q.push(Q_buff.front());
        Q_buff.pop();
    }
}

queue<Auto> merge(queue<Auto>& Q, queue<Auto> Q2)
{
    queue<Auto> Q3 = Q;
    for (; !Q2.empty();)
    {
        Q3.push(Q2.front());
        Q2.pop();
    }
    return Q3;
}

void cheaper(queue<Auto> Q3)
{
    int price = 100;
    queue<Auto> Q_help;
    do
    {
        if (price <= 0) cout << "Введите цену, больше 0";
        cout << "\n\nВведите максимальную для вас цену на машину\n\n";
        cin >> price;
    } while (price <= 0);
    for (; !Q3.empty();)
    {
        if (Q3.front().GetPrice() <= price) Q_help.push(Q3.front());
        Q3.pop();
    }
    Sort(Q_help, 3); // sort by price
    if (Q_help.empty()) 
    {
        cout << "\n\nМы не нашли машин, дешевле " << price << "$"; return;
    }
    cout << "\n\nМы нашли " << Q_help.size() << " машин, дешевле " << price << " $" << endl;
    for (; !Q_help.empty();)
    {
        Q_help.front().print();
        cout << endl;
        Q_help.pop();
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    queue<Auto> Q,Q2;
    cout << "Введите название файла для 1 очереди\n";
    takefromfile(Q);
    cout << "Введите название файла для 2 очереди\n";
    takefromfile(Q2);
    cout << endl; 
    cout << "\n\n=============================\n\n";
    printQ(Q);
    cout << endl;
    printQ(Q2);

    cout << "\n\n=============================\n\n";
    change(Q, Q2);
    printQ(Q);
    cout << endl;
    printQ(Q2);
    cout << "\n\n=============================\n\n";
    
    Sort(Q);
    printQ(Q);
    cout << endl;
    Sort(Q2);
    printQ(Q2);
    cout << "\n\n=============================\n\n";

    queue<Auto> Q3 = merge(Q, Q2);
    printQ(Q3);
    cout << "\n\n=============================\n\n";
    cheaper(Q3);
    return 0;
}