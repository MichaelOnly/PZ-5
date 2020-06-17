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
   work_table tableT;
   work_field_t fieldT;
   while (in >> fieldT.key >> fieldT.name >> fieldT.quantity) //Пока не конец файла упорядоченно вставлять записи в таблицу
      insertFieldAtTable(tableT, fieldT);

   cout << "Таблица из файла work:" << endl; //Распечатываем таблицу work
   printTable(tableT); 
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
   transformTables(tableT, tableP, tableR); //Преобразуем таблицы work и price в итоговую таблицу

   cout << "Итоговая таблица:" << endl; //Выводим итоговую таблицу для проверки
   printTable(tableR);
   cout << endl;

   _getch();
   return 0;
}
