#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>

using namespace std;

//global variable declaration
int k = 7, r = 0, flag = 0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// function for drawing line
void drawlines(int lengthOfLine)
{
    for (int i = 0; i < lengthOfLine; i++)
    {
        cout << "=";
    }
}

struct date
{
    int mm, dd, yy;
};

ofstream fout;
ifstream fin;

class Product
{
    int productNo;
    char productName[25];
    date d;

public:
    void add()
    {
        cout << "\n\n\tProduct No: ";
        cin >> productNo;
        cout << "\n\n\tName of the Product: ";
        cin >> productName;
        //gets(name);
        cout << "\n\n\tManufacturing Date(dd-mm-yy): ";
        cin >> d.mm >> d.dd >> d.yy;
    }
    void show()
    {
        cout << "\n\tProduct No: ";
        cout << productNo;
        cout << "\n\n\tName of the Product: ";
        cout << productName;
        cout << "\n\n\tDate : ";
        cout << d.mm << "-" << d.dd << "-" << d.yy;
    }
    void report()
    {
        gotoxy(3, k);
        cout << productNo;
        gotoxy(13, k);
        puts(productName);
    }
    int retno()
    {
        return (productNo);
    }
};

class amount : public Product
{

public:
    float price, qty, tax, gross, dis, netamt;
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return (netamt);
    }
} amt;

void amount::add()
{
    Product::add();
    cout << "\n\n\tPrice: ";
    cin >> price;
    calculate();
    fout.write((char *)&amt, sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross = price + (price * (tax / 100));
    netamt = qty * (gross - (gross * (dis / 100)));
}
void amount::show()
{
    fin.open("Productstore.dat", ios::binary);
    fin.read((char *)&amt, sizeof(amt));
    Product::show();
    cout << "\n\n\tNet amount: ";
    cout << netamt;
    fin.close();
}

void amount::report()
{
    Product::report();
    gotoxy(23, k);
    cout << price;
    gotoxy(33, k);
    cout << qty;
    gotoxy(44, k);
    cout << tax;
    gotoxy(52, k);
    cout << dis;
    gotoxy(64, k);
    cout << netamt;
    k = k + 1;
    if (k == 50)
    {
        gotoxy(25, 50);
        cout << "PRESS ANY KEY TO CONTINUE...";
        getch();
        k = 7;
        system("cls");
        gotoxy(30, 3);
        cout << " Product DETAILS ";
        gotoxy(3, 5);
        cout << "NUMBER";
        gotoxy(13, 5);
        cout << "NAME";
        gotoxy(23, 5);
        cout << "PRICE";
    }
}
//amount //
void amount::pay()
{
    // show();
    cout << "\n\n\n\t\t*********************************************";
    cout << "\n\t\t                 DETAILS                  ";
    cout << "\n\t\t*********************************************";
    cout << "\n\n\t\tPRICE                     :" << price;
    cout << "\n\n\t\tQUANTITY                  :" << qty;
    cout << "\n\t\tTAX PERCENTAGE              :" << tax;
    cout << "\n\t\tDISCOUNT PERCENTAGE         :" << dis;
    cout << "\n\n\n\t\tNET AMOUNT              :Rs." << netamt;
    cout << "\n\t\t*********************************************";
}