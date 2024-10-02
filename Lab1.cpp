#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#define ESC 27
using namespace std;

string parseToTwoDigit(int number)
{
    string str = to_string(number);

    if (str.length() < 2) 
        str.insert(0, 1, '0');

    return str;
}

struct Time
{
    unsigned short hours;
    unsigned short minutes; 
};


struct Train
{
    unsigned short number;
    string destination;
    Time departure_time;
};

struct Node
{
    Train data;
    Node* next;
};

class TrainDepartureList
{
private:
    Node* head;

public:
    TrainDepartureList()
    {
        head = NULL; // нет элементов
    }

    void addNode(Train train)
    {
        Node* nd = new Node;

        nd->data = train;
        nd->next = NULL;  // т.к. новый элемент добавляется в конец

        if (head == NULL) // если первый элемент
            head = nd;
        else
        {
            Node* current = head;

            // проходим по всем элементам от начала, пока не найдем последний
            while (current->next != NULL)
                current = current->next;

            // добавляем к последнему элементу указатель на новый элемент
            current->next = nd;
        }
    }

    void printList()
    {
        Node* current = head;
        while (current != NULL)
        {
            string formatted_hour = parseToTwoDigit(current->data.departure_time.hours);
            string formatted_minutes = parseToTwoDigit(current->data.departure_time.minutes);

            cout << "Номер поезда: " << current->data.number << endl
                << "Станция назначения: " << current->data.destination << endl
                << "Время отправления: " << formatted_hour << ":" << formatted_minutes << endl << endl;

            current = current->next;
        }
    }

    void printList(unsigned short number)
    {
        Node* current = head;
        while (current != NULL)
        {
            string formatted_hour = parseToTwoDigit(current->data.departure_time.hours);
            string formatted_minutes = parseToTwoDigit(current->data.departure_time.minutes);

            if (current->data.number == number)
            {
                cout << "Номер поезда: " << current->data.number << endl
                    << "Станция назначения: " << current->data.destination << endl
                    << "Время отправления: " << formatted_hour << ":" << formatted_minutes << endl << endl;
            }

            current = current->next;
        }
    }

    void printList(string destination)
    {
        Node* current = head;
        while (current != NULL)
        {
            string formatted_hour = parseToTwoDigit(current->data.departure_time.hours);
            string formatted_minutes = parseToTwoDigit(current->data.departure_time.minutes);

            if (current->data.destination == destination)
            {
                cout << "Номер поезда: " << current->data.number << endl
                    << "Станция назначения: " << current->data.destination << endl
                    << "Время отправления: " << formatted_hour << ":" << formatted_minutes << endl << endl;
            }

            current = current->next;
        }
    }
};

void showList(TrainDepartureList);
void showDataByNumber(TrainDepartureList);
void showDataByDestination(TrainDepartureList);

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);

    bool is_data_filled = false;
    TrainDepartureList tdList;

    do
    {
        int number;
        char destination[200] = "";
        int departure_time_hour;
        int departure_time_minutes;

        cout << "Введите информацию об отправлении поезда." << endl;

        do
        {
            cout << "Номер поезда (от 0 до 65535 включительно): ";
            cin >> number;

        } while (number < 0 || number > 65535);
         
        do
        {
            cout << "Станция назначения (не более 200 символов): ";
            cin >> destination;

        } while (strlen(destination) > 200);

        do
        {
            cout << "Час отправления: ";
            cin >> departure_time_hour;           

        } while (departure_time_hour < 0 || departure_time_hour > 23);

        do
        {
            cout << "Минута отправления: ";
            cin >> departure_time_minutes;

        } while (departure_time_minutes < 0 || departure_time_minutes > 59);

        Train train = { number, destination, {departure_time_hour, departure_time_minutes} };
        tdList.addNode(train);

        cout << "\nУспешно! Информация об отправлении поезда была добавлена!" << endl
            << "Нажмите любую клавишу, чтобы продолжить вводить данные или ESC для выхода в меню." << endl << endl;

        char key = _getch();
        if (key == ESC)
            is_data_filled = true;
        
    } while (!is_data_filled);

    // показать меню взаимодействия
    bool exit_menu = false;
    do
    {
        system("cls");
        cout << "Введите цифру из пункта меню." << endl 
            << "1. Вывести весь список отправлений" << endl
            << "2. Вывод данных о поезде по его номеру" << endl
            << "3. Вывод данных о поездах, следующих до заданной станции назначения" << endl
            << "4. Выход" << endl;

        switch (_getch())
        {
        case '1':
            showList(tdList);
            break;
        case '2':
            showDataByNumber(tdList);
            break;
        case '3':
            showDataByDestination(tdList);
            break;
        case '4':
            exit_menu = true;
            break;
        }

    } while (!exit_menu);
}

void showList(TrainDepartureList tdList)
{
    system("cls");
    tdList.printList();

    cout << "Для продолжения нажмите любую клавишу...";
    _getch();
}

void showDataByNumber(TrainDepartureList tdList)
{
    system("cls");

    int number;
    cout << "Введите номер поезда: ";
    cin >> number;

    system("cls");
    cout << "Информация о поезде с номером " << number << endl << endl;
    tdList.printList(number);

    cout << "Для продолжения нажмите любую клавишу...";
    _getch();
}

void showDataByDestination(TrainDepartureList tdList)
{
    system("cls");

    string destination;
    cout << "Введите станцию назначения: ";
    cin >> destination;

    system("cls");
    cout << "Информация о поезде со станцией отправления " << destination << endl << endl;
    tdList.printList(destination);

    cout << "Для продолжения нажмите любую клавишу...";
    _getch();
}