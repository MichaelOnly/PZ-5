#include <iostream>
#include <conio.h>
#include <locale.h>
#include <fstream>

#include "Tables.h"

using namespace std;

int main()
{
   setlocale(LC_CTYPE, "Russian");

   ifstream in("work.txt");
   work_table tableW;
   work_field_t fieldW;
   while (in >> fieldW.key >> fieldW.name >> fieldW.quantity) //Пока не конец файла упорядоченно вставлять записи в таблицу
      insertFieldAtTable(tableW, fieldW);

   cout << "Таблица из файла work:" << endl; //Распечатываем таблицу work
   printTable(tableW); 
   cout << endl;

   price_table tableP;
   price_field_t fieldP;
   ifstream fin("price.txt");
   while(fin >> fieldP.key >> fieldP.price) //Пока не конец файла упорядоченно вставлять записи в таблицу
      insertFieldAtTable(tableP, fieldP);

   cout << "Таблица из файла price:" << endl; //Распечатываем таблицу price
   printTable(tableP);
   cout << endl;

   result_table tableR;
   transformTables(tableW, tableP, tableR); //Преобразуем таблицы work и price в итоговую таблицу

   cout << "Итоговая таблица:" << endl; //Выводим итоговую таблицу для проверки
   printTable(tableR);
   cout << endl;

   _getch();
   return 0;
}
