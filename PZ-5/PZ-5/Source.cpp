#define CAPACITY 17 //максимальное количество элементов таблицы

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <fstream>

using namespace std;

struct field_t //Поле в таблице из файла work
{
   int quantity;
   string name, key;
};

struct table_t //Таблица из файла work
{
   int size = 0;
   field_t fields[CAPACITY];
};

struct field_p //Поле таблицы из файла price
{
   string key, price;
};

struct table_p //Таблица из файла price
{
   int size = 0;
   field_p fields[CAPACITY];
};

struct field_r //Поле итоговой таблицы
{
   int quantity;
   string name, key, price = "Не указана";
};

struct table_r //Итоговая таблица
{
   int size = 0;
   field_r fields[CAPACITY];
};

//Функции для работы с таблицей из файла work
void insertFieldAtTable(table_t& table, field_t field); //Вставляет поле в таблицу, сохраняя порядок
int getPosForFieldInsert(table_t table, field_t field); //Определяет позицию в таблице, в которую поле нужно вставить
void shiftTableFieldsFromPos(table_t& table, int pos); //Смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(table_t table); //Распечатывает таблицу в консоль
void printField(field_t field); //Распечатывает поле таблицы в консоль
int getPosField(table_t table, string key); //Выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(table_t& table, string key); //Удаляет поле в таблице по ключу

//Функции для работы с таблицей из файла price
void insertFieldAtTable(table_p& table, field_p field); //Вставляет поле в таблицу, сохраняя порядок
int getPosForFieldInsert(table_p table, field_p field); //Определяет позицию в таблице, в которую поле нужно вставить
void shiftTableFieldsFromPos(table_p& table, int pos); //Смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(table_p table); //Распечатывает таблицу в консоль
void printField(field_p field); //Распечатывает поле таблицы в консоль
int getPosField(table_p table, string key); //Выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(table_p& table, string key); //Удаляет поле в таблице по ключу

//Функции для работы с итоговой таблицей таблицей 
void insertFieldAtTable(table_r& tableR, field_t fieldT, field_p fieldP); //Вставляет поле в таблицу, сохраняя порядок, если была найдена цена 
void insertFieldAtTable(table_r& tableR, field_t fieldT); //Вставляет поле в таблицу, сохраняя порядок, если цена не была найдена
int getPosForFieldInsert(table_r table, field_t field); //Определяет позицию в таблице, в которую поле нужно вставить
void shiftTableFieldsFromPos(table_r& table, int pos); //Смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(table_r table); //Распечатывает таблицу в консоль
void printField(field_r field); //Распечатывает поле таблицы в консоль
int getPosField(table_r table, int quantity); //Выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(table_r& table, int quantity); //Удаляет поле в таблице по ключу
void transformTables(table_t tableT, table_p tableP, table_r& tableR); //Преобразовывает таблицы из файлов work и price в итоговую таблицу

int main()
{
   setlocale(LC_CTYPE, "Russian");

   ifstream in("work.txt");
   table_t tableT;
   field_t fieldT;
   while (in >> fieldT.key >> fieldT.name >> fieldT.quantity) //Пока не конец файла упорядоченно вставлять записи в таблицу
      insertFieldAtTable(tableT, fieldT);

   cout << "Таблица из файла work:" << endl; //Распечатываем таблицу work
   printTable(tableT); 

   table_p tableP;
   field_p fieldP;
   ifstream fin("price.txt");
   while(fin >> fieldP.key >> fieldP.price) //Пока не конец файла упорядоченно вставлять записи в таблицу
      insertFieldAtTable(tableP, fieldP);

   cout << "Таблица из файла price:" << endl; //Распечатываем таблицу price
   printTable(tableP);

   table_r tableR;
   transformTables(tableT, tableP, tableR); //Преобразуем таблицы work и price в итоговую таблицу

   cout << "Итоговая таблица:" << endl; //Выводим итоговую таблицу для проверки
   printTable(tableR);
}



//Описание функций для работы с таблицей из файла work
void insertFieldAtTable(table_t& table, field_t field)
{
   int insert_pos = getPosForFieldInsert(table, field);
   if (field.key.compare(table.fields[insert_pos].key) == 0) //При коллизиции прибавим quantity
      table.fields[insert_pos].quantity += field.quantity;
   else //Если коллизиции нет, то освободим место в таблице смещением и добавим запись
   {
      shiftTableFieldsFromPos(table, insert_pos);
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(table_t table, field_t field) //Бинарный поиск места в массиве для вставки
{
   int left_search_edge = 0; //Левый край диапазона поиска == 0
   int right_search_edge = table.size; //Правый край == правый край массива + 1, так как вставить запись можем и в том числе и в самый конец таблицы
   while (left_search_edge < right_search_edge) //Пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //Сравниваем с серединой(округление к левому краю)
      if (field.key.compare(table.fields[cmp_pos].key) <= 0) //Если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //Если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //Не важно какой край возвращать
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

int getPosField(table_t table, string key) //Бинарный поиск поля в таблице
{
   int left_search_edge = 0; //Левый край диапазона поиска == 0
   int right_search_edge = table.size - 1; //Правый край == правый край массива
   while (left_search_edge < right_search_edge) //Пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //Сравниваем с серединой(округление к левому краю)
      if (key.compare(table.fields[cmp_pos].key) <= 0) //Если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //Если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   if (key.compare(table.fields[left_search_edge].key) != 0)
      return -1;//Если ключи не равны, то вернём -1
   return left_search_edge; //Если же равны, то не важно какой край возвращать
}

void deleteField(table_t& table, string key)
{
   int field_pos = getPosField(table, key);
   if (field_pos >= 0) //Если запись нашли в нашей таблице, то удаляем
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}




//Описание функций для работы с таблицей из фалйа price
void insertFieldAtTable(table_p& table, field_p field)
{
   int insert_pos = getPosForFieldInsert(table, field);  //Ищем позицию для вставки
   if (field.key.compare(table.fields[insert_pos].key) != 0)
   {
      shiftTableFieldsFromPos(table, insert_pos); //Вставляем поле на нужную позицию
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(table_p table, field_p field) //Бинарный поиск места в массиве для вставки
{
   int left_search_edge = 0; //Левый край диапазона поиска == 0
   int right_search_edge = table.size; //Правый край == правый край массива + 1, так как вставить запись можем и в том числе и в самый конец таблицы
   while (left_search_edge < right_search_edge) //Пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //Сравниваем с серединой(округление к левому краю)
      if (field.key.compare(table.fields[cmp_pos].key) <= 0) //Если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //Если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //Не важно какой край возвращать
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


int getPosField(table_p table, string key) //Бинарный поиск поля в таблице
{
   int left_search_edge = 0; //Левый край диапазона поиска == 0
   int right_search_edge = table.size - 1; //Правый край == правый край массива
   while (left_search_edge < right_search_edge) //Пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //Сравниваем с серединой(округление к левому краю)
      if (key.compare(table.fields[cmp_pos].key) <= 0) //Если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //Если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   if (key.compare(table.fields[left_search_edge].key) != 0)
      return -1;//Если ключи не равны, то вернём -1
   return left_search_edge; //Если же равны, то не важно какой край возвращать
}

void deleteField(table_p& table, string key)
{
   int field_pos = getPosField(table, key);
   if (field_pos >= 0) //Если запись нашли в нашей таблице, то удаляем
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}




//Функции для работы с итоговой таблицы
void insertFieldAtTable(table_r& tableR,field_t fieldT, field_p fieldP) 
{
   int insert_pos = getPosForFieldInsert(tableR, fieldT); //Ищем позицию для вставки
   if (fieldT.quantity != tableR.fields[insert_pos].quantity)
   {
      shiftTableFieldsFromPos(tableR, insert_pos); 
      tableR.fields[insert_pos].quantity = fieldT.quantity; //Вставляем все нужные элементы полей из соответствующих таблиц
      tableR.fields[insert_pos].key = fieldT.key;
      tableR.fields[insert_pos].name = fieldT.name;
      tableR.fields[insert_pos].price = fieldP.price;
   }
}

void insertFieldAtTable(table_r& tableR, field_t fieldT)
{
   int insert_pos = getPosForFieldInsert(tableR, fieldT); //Ищем позицию для вставки
   if (fieldT.quantity != tableR.fields[insert_pos].quantity) //Вставляем все нужные элементы полей из соответствующих таблиц
   {
      shiftTableFieldsFromPos(tableR, insert_pos);
      tableR.fields[insert_pos].quantity = fieldT.quantity;
      tableR.fields[insert_pos].key = fieldT.key;
      tableR.fields[insert_pos].name = fieldT.name;
   }
}

int getPosForFieldInsert(table_r table, field_t field) //Бинарный поиск места в массиве для вставки
{
   int left_search_edge = 0; //Левый край диапазона поиска == 0
   int right_search_edge = table.size; //Правый край == правый край массива + 1, так как вставить запись можем и в том числе и в самый конец таблицы
   while (left_search_edge < right_search_edge) //Пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //Сравниваем с серединой(округление к левому краю)
      if (field.quantity <= table.fields[cmp_pos].quantity) //Если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //Если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //Неважно какой край возвращать
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

int getPosField(table_r table, int quantity) //Бинарный поиск поля в таблице
{
   int left_search_edge = 0; //Левый край диапазона поиска == 0
   int right_search_edge = table.size - 1; //Правый край == правый край массива
   while (left_search_edge < right_search_edge) //Пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //Сравниваем с серединой(округление к левому краю)
      if (quantity  <= table.fields[cmp_pos].quantity) //Если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //Если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   if (quantity != table.fields[left_search_edge].quantity)
      return -1;//Если ключи не равны, то вернём -1
   return left_search_edge; //Если же равны, то не важно какой край возвращать
}

void deleteField(table_r& table, int quantity)
{
   int field_pos = getPosField(table, quantity);
   if (field_pos >= 0) //Если запись нашли в нашей таблице, то удаляем
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}

void transformTables(table_t tableT, table_p tableP, table_r& tableR) //Функция заполнения новой таблицы
{
   for (int i = 0; i < tableT.size; i++) //Берём каждое поле из таблицы work
   {
      int price_pos = getPosField(tableP, tableT.fields[i].key); //Ищем соответсвующую ему цену в таблице price
      if (price_pos >= 0) 
         insertFieldAtTable(tableR, tableT.fields[i], tableP.fields[price_pos]); //Если цена была найдена, то вставляем поле из таблицы work и соответсвующую ему цену
      else 
         insertFieldAtTable(tableR, tableT.fields[i]); //Если цена не была найдена, то вставляем поле из таблицы work, оставляя цену "Не указана" по умолчанию
   }
}