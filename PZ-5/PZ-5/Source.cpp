#define CAPACITY 17 //������������ ���������� ��������� �������

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <fstream>

using namespace std;

struct work_field_t //���� � ������� �� ����� work
{
   int quantity;
   string name, key;
};

struct work_table //������� �� ����� work
{
   int size = 0;
   work_field_t fields[CAPACITY];
};

struct price_field_t //���� ������� �� ����� price
{
   string key, price;
};

struct price_table //������� �� ����� price
{
   int size = 0;
   price_field_t fields[CAPACITY];
};

struct result_field_t //���� �������� �������
{
   int quantity;
   string name, key, price = "�� �������";
};

struct result_table //�������� �������
{
   int size = 0;
   result_field_t fields[CAPACITY];
};

//������� ��� ������ � �������� �� ����� work
void insertFieldAtTable(work_table& table, work_field_t field); //��������� ���� � �������, �������� �������
int getPosForFieldInsert(work_table table, work_field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(work_table& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(work_table table); //������������� ������� � �������
void printField(work_field_t field); //������������� ���� ������� � �������
int getPosField(work_table table, string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(work_table& table, string key); //������� ���� � ������� �� �����

//������� ��� ������ � �������� �� ����� price
void insertFieldAtTable(price_table& table, price_field_t field); //��������� ���� � �������, �������� �������
int getPosForFieldInsert(price_table table, price_field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(price_table& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(price_table table); //������������� ������� � �������
void printField(price_field_t field); //������������� ���� ������� � �������
int getPosField(price_table table, string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(price_table& table, string key); //������� ���� � ������� �� �����

//������� ��� ������ � �������� �������� �������� 
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldT, price_field_t fieldP); //��������� ���� � �������, �������� �������, ���� ���� ������� ���� 
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldT); //��������� ���� � �������, �������� �������, ���� ���� �� ���� �������
int getPosForFieldInsert(result_table table, work_field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(result_table& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(result_table table); //������������� ������� � �������
void printField(result_field_t field); //������������� ���� ������� � �������
int getPosField(result_table table, int quantity); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(result_table& table, int quantity); //������� ���� � ������� �� �����
void transformTables(work_table tableT, price_table tableP, result_table& tableR); //��������������� ������� �� ������ work � price � �������� �������

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

   price_table tableP;
   price_field_t fieldP;
   ifstream fin("price.txt");
   while(fin >> fieldP.key >> fieldP.price) //���� �� ����� ����� ������������ ��������� ������ � �������
      insertFieldAtTable(tableP, fieldP);

   cout << "������� �� ����� price:" << endl; //������������� ������� price
   printTable(tableP);

   result_table tableR;
   transformTables(tableT, tableP, tableR); //����������� ������� work � price � �������� �������

   cout << "�������� �������:" << endl; //������� �������� ������� ��� ��������
   printTable(tableR);
}



//�������� ������� ��� ������ � �������� �� ����� work
void insertFieldAtTable(work_table& table, work_field_t field)
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

int getPosForFieldInsert(work_table table, work_field_t field) //�������� ����� ����� � ������� ��� �������
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

void shiftTableFieldsFromPos(work_table& table, int insert_pos)
{
   table.size++;
   for (int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(work_table table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(work_field_t field)
{
   cout << field.key << " " << field.name << " " << field.quantity << endl;
}

int getPosField(work_table table, string key) //�������� ����� ���� � �������
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

void deleteField(work_table& table, string key)
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
void insertFieldAtTable(price_table& table, price_field_t field)
{
   int insert_pos = getPosForFieldInsert(table, field);  //���� ������� ��� �������
   if (field.key.compare(table.fields[insert_pos].key) != 0)
   {
      shiftTableFieldsFromPos(table, insert_pos); //��������� ���� �� ������ �������
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(price_table table, price_field_t field) //�������� ����� ����� � ������� ��� �������
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

void shiftTableFieldsFromPos(price_table& table, int insert_pos)
{
   table.size++;
   for (int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(price_table table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(price_field_t field)
{
   cout << field.key << " " << field.price << endl;
}


int getPosField(price_table table, string key) //�������� ����� ���� � �������
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

void deleteField(price_table& table, string key)
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
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldT, price_field_t fieldP)
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

void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldT)
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

int getPosForFieldInsert(result_table table, work_field_t field) //�������� ����� ����� � ������� ��� �������
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

void shiftTableFieldsFromPos(result_table& table, int insert_pos)
{
   table.size++;
   for (int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(result_table table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(result_field_t field)
{
   cout << field.key << " " << field.name << " " << field.quantity << " " << field.price << endl;
}

int getPosField(result_table table, int quantity) //�������� ����� ���� � �������
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

void deleteField(result_table& table, int quantity)
{
   int field_pos = getPosField(table, quantity);
   if (field_pos >= 0) //���� ������ ����� � ����� �������, �� �������
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}

void transformTables(work_table tableT, price_table tableP, result_table& tableR) //������� ���������� ����� �������
{
   for (int i = 0; i < tableT.size; i++) //���� ������ ���� �� ������� work
   {
      int price_pos = getPosField(tableP, tableT.fields[i].key); //���� �������������� ��� ���� � ������� price
      if (price_pos >= 0) 
         QuanInsertFieldAtTable(tableR, tableT.fields[i], tableP.fields[price_pos]); //���� ���� ���� �������, �� ��������� ���� �� ������� work � �������������� ��� ����
      else 
         QuanInsertFieldAtTable(tableR, tableT.fields[i]); //���� ���� �� ���� �������, �� ��������� ���� �� ������� work, �������� ���� "�� �������" �� ���������
   }
}