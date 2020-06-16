#define CAPACITY 17 //������������ ���������� ��������� �������

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <fstream>

using namespace std;

struct field_t //���� � ������� �� ����� work
{
   int quantity;
   string name, key;
};

struct table_t //������� �� ����� work
{
   int size = 0;
   field_t fields[CAPACITY];
};

struct field_p //���� ������� �� ����� price
{
   string key, price;
};

struct table_p //������� �� ����� price
{
   int size = 0;
   field_p fields[CAPACITY];
};

struct field_r //���� �������� �������
{
   int quantity;
   string name, key, price = "�� �������";
};

struct table_r //�������� �������
{
   int size = 0;
   field_r fields[CAPACITY];
};

//������� ��� ������ � �������� �� ����� work
void insertFieldAtTable(table_t& table, field_t field); //��������� ���� � �������, �������� �������
int getPosForFieldInsert(table_t table, field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(table_t& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(table_t table); //������������� ������� � �������
void printField(field_t field); //������������� ���� ������� � �������
int getPosField(table_t table, string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(table_t& table, string key); //������� ���� � ������� �� �����

//������� ��� ������ � �������� �� ����� price
void insertFieldAtTable(table_p& table, field_p field); //��������� ���� � �������, �������� �������
int getPosForFieldInsert(table_p table, field_p field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(table_p& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(table_p table); //������������� ������� � �������
void printField(field_p field); //������������� ���� ������� � �������
int getPosField(table_p table, string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(table_p& table, string key); //������� ���� � ������� �� �����

//������� ��� ������ � �������� �������� �������� 
void insertFieldAtTable(table_r& tableR, field_t fieldT, field_p fieldP); //��������� ���� � �������, �������� �������, ���� ���� ������� ���� 
void insertFieldAtTable(table_r& tableR, field_t fieldT); //��������� ���� � �������, �������� �������, ���� ���� �� ���� �������
int getPosForFieldInsert(table_r table, field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(table_r& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(table_r table); //������������� ������� � �������
void printField(field_r field); //������������� ���� ������� � �������
int getPosField(table_r table, int quantity); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(table_r& table, int quantity); //������� ���� � ������� �� �����
void transformTables(table_t tableT, table_p tableP, table_r& tableR); //��������������� ������� �� ������ work � price � �������� �������

int main()
{
   setlocale(LC_CTYPE, "Russian");

   ifstream in("work.txt");
   table_t tableT;
   field_t fieldT;
   while (in >> fieldT.key >> fieldT.name >> fieldT.quantity) //���� �� ����� ����� ������������ ��������� ������ � �������
      insertFieldAtTable(tableT, fieldT);

   cout << "������� �� ����� work:" << endl; //������������� ������� work
   printTable(tableT); 

   table_p tableP;
   field_p fieldP;
   ifstream fin("price.txt");
   while(fin >> fieldP.key >> fieldP.price) //���� �� ����� ����� ������������ ��������� ������ � �������
      insertFieldAtTable(tableP, fieldP);

   cout << "������� �� ����� price:" << endl; //������������� ������� price
   printTable(tableP);

   table_r tableR;
   transformTables(tableT, tableP, tableR); //����������� ������� work � price � �������� �������

   cout << "�������� �������:" << endl; //������� �������� ������� ��� ��������
   printTable(tableR);
}



//�������� ������� ��� ������ � �������� �� ����� work
void insertFieldAtTable(table_t& table, field_t field)
{
   int insert_pos = getPosForFieldInsert(table, field);
   if (field.key.compare(table.fields[insert_pos].key) == 0) //��� ���������� �������� quantity
      table.fields[insert_pos].quantity += field.quantity;
   else //���� ���������� ���, �� ��������� ����� � ������� ��������� � ������� ������
   {
      shiftTableFieldsFromPos(table, insert_pos);
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(table_t table, field_t field) //�������� ����� ����� � ������� ��� �������
{
   int left_search_edge = 0; //����� ���� ��������� ������ == 0
   int right_search_edge = table.size; //������ ���� == ������ ���� ������� + 1, ��� ��� �������� ������ ����� � � ��� ����� � � ����� ����� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (field.key.compare(table.fields[cmp_pos].key) <= 0) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //�� ����� ����� ���� ����������
}

void shiftTableFieldsFromPos(table_t& table, int insert_pos)
{
   table.size++;
   for (int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(table_t table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(field_t field)
{
   cout << field.key << " " << field.name << " " << field.quantity << endl;
}

int getPosField(table_t table, string key) //�������� ����� ���� � �������
{
   int left_search_edge = 0; //����� ���� ��������� ������ == 0
   int right_search_edge = table.size - 1; //������ ���� == ������ ���� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (key.compare(table.fields[cmp_pos].key) <= 0) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   if (key.compare(table.fields[left_search_edge].key) != 0)
      return -1;//���� ����� �� �����, �� ����� -1
   return left_search_edge; //���� �� �����, �� �� ����� ����� ���� ����������
}

void deleteField(table_t& table, string key)
{
   int field_pos = getPosField(table, key);
   if (field_pos >= 0) //���� ������ ����� � ����� �������, �� �������
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}




//�������� ������� ��� ������ � �������� �� ����� price
void insertFieldAtTable(table_p& table, field_p field)
{
   int insert_pos = getPosForFieldInsert(table, field);  //���� ������� ��� �������
   if (field.key.compare(table.fields[insert_pos].key) != 0)
   {
      shiftTableFieldsFromPos(table, insert_pos); //��������� ���� �� ������ �������
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(table_p table, field_p field) //�������� ����� ����� � ������� ��� �������
{
   int left_search_edge = 0; //����� ���� ��������� ������ == 0
   int right_search_edge = table.size; //������ ���� == ������ ���� ������� + 1, ��� ��� �������� ������ ����� � � ��� ����� � � ����� ����� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (field.key.compare(table.fields[cmp_pos].key) <= 0) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //�� ����� ����� ���� ����������
}

void shiftTableFieldsFromPos(table_p& table, int insert_pos)
{
   table.size++;
   for (int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(table_p table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(field_p field)
{
   cout << field.key << " " << field.price << endl;
}


int getPosField(table_p table, string key) //�������� ����� ���� � �������
{
   int left_search_edge = 0; //����� ���� ��������� ������ == 0
   int right_search_edge = table.size - 1; //������ ���� == ������ ���� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (key.compare(table.fields[cmp_pos].key) <= 0) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   if (key.compare(table.fields[left_search_edge].key) != 0)
      return -1;//���� ����� �� �����, �� ����� -1
   return left_search_edge; //���� �� �����, �� �� ����� ����� ���� ����������
}

void deleteField(table_p& table, string key)
{
   int field_pos = getPosField(table, key);
   if (field_pos >= 0) //���� ������ ����� � ����� �������, �� �������
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}




//������� ��� ������ � �������� �������
void insertFieldAtTable(table_r& tableR,field_t fieldT, field_p fieldP) 
{
   int insert_pos = getPosForFieldInsert(tableR, fieldT); //���� ������� ��� �������
   if (fieldT.quantity != tableR.fields[insert_pos].quantity)
   {
      shiftTableFieldsFromPos(tableR, insert_pos); 
      tableR.fields[insert_pos].quantity = fieldT.quantity; //��������� ��� ������ �������� ����� �� ��������������� ������
      tableR.fields[insert_pos].key = fieldT.key;
      tableR.fields[insert_pos].name = fieldT.name;
      tableR.fields[insert_pos].price = fieldP.price;
   }
}

void insertFieldAtTable(table_r& tableR, field_t fieldT)
{
   int insert_pos = getPosForFieldInsert(tableR, fieldT); //���� ������� ��� �������
   if (fieldT.quantity != tableR.fields[insert_pos].quantity) //��������� ��� ������ �������� ����� �� ��������������� ������
   {
      shiftTableFieldsFromPos(tableR, insert_pos);
      tableR.fields[insert_pos].quantity = fieldT.quantity;
      tableR.fields[insert_pos].key = fieldT.key;
      tableR.fields[insert_pos].name = fieldT.name;
   }
}

int getPosForFieldInsert(table_r table, field_t field) //�������� ����� ����� � ������� ��� �������
{
   int left_search_edge = 0; //����� ���� ��������� ������ == 0
   int right_search_edge = table.size; //������ ���� == ������ ���� ������� + 1, ��� ��� �������� ������ ����� � � ��� ����� � � ����� ����� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (field.quantity <= table.fields[cmp_pos].quantity) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //������� ����� ���� ����������
}

void shiftTableFieldsFromPos(table_r& table, int insert_pos)
{
   table.size++;
   for (int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(table_r table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(field_r field)
{
   cout << field.key << " " << field.name << " " << field.quantity << " " << field.price << endl;
}

int getPosField(table_r table, int quantity) //�������� ����� ���� � �������
{
   int left_search_edge = 0; //����� ���� ��������� ������ == 0
   int right_search_edge = table.size - 1; //������ ���� == ������ ���� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (quantity  <= table.fields[cmp_pos].quantity) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   if (quantity != table.fields[left_search_edge].quantity)
      return -1;//���� ����� �� �����, �� ����� -1
   return left_search_edge; //���� �� �����, �� �� ����� ����� ���� ����������
}

void deleteField(table_r& table, int quantity)
{
   int field_pos = getPosField(table, quantity);
   if (field_pos >= 0) //���� ������ ����� � ����� �������, �� �������
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}

void transformTables(table_t tableT, table_p tableP, table_r& tableR) //������� ���������� ����� �������
{
   for (int i = 0; i < tableT.size; i++) //���� ������ ���� �� ������� work
   {
      int price_pos = getPosField(tableP, tableT.fields[i].key); //���� �������������� ��� ���� � ������� price
      if (price_pos >= 0) 
         insertFieldAtTable(tableR, tableT.fields[i], tableP.fields[price_pos]); //���� ���� ���� �������, �� ��������� ���� �� ������� work � �������������� ��� ����
      else 
         insertFieldAtTable(tableR, tableT.fields[i]); //���� ���� �� ���� �������, �� ��������� ���� �� ������� work, �������� ���� "�� �������" �� ���������
   }
}