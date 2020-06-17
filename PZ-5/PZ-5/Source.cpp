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
   while (in >> fieldT.key >> fieldT.name >> fieldT.quantity) //���� �� ����� ����� ������������ ��������� ������ � �������
      insertFieldAtTable(tableT, fieldT);

   cout << "������� �� ����� work:" << endl; //������������� ������� work
   printTable(tableT); 
   cout << endl;

   price_table tableP;
   price_field_t fieldP;
   ifstream fin("price.txt");
   while(fin >> fieldP.key >> fieldP.price) //���� �� ����� ����� ������������ ��������� ������ � �������
      insertFieldAtTable(tableP, fieldP);

   cout << "������� �� ����� price:" << endl; //������������� ������� price
   printTable(tableP);
   cout << endl;

   result_table tableR;
   transformTables(tableT, tableP, tableR); //����������� ������� work � price � �������� �������

   cout << "�������� �������:" << endl; //������� �������� ������� ��� ��������
   printTable(tableR);
   cout << endl;

   _getch();
   return 0;
}
