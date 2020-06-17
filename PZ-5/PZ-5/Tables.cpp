#include "Tables.h"

//Описание функций для работы с таблицей из файла work
void insertFieldAtTable(work_table& table, work_field_t field)
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

int getPosForFieldInsert(work_table table, work_field_t field) //Бинарный поиск места в массиве для вставки
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
   std::cout << field.key << " " << field.name << " " << field.quantity << std::endl;
}

int getPosField(work_table table, std::string key) //Бинарный поиск поля в таблице
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

void deleteField(work_table& table, std::string key)
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
void insertFieldAtTable(price_table& table, price_field_t field)
{
   int insert_pos = getPosForFieldInsert(table, field);  //Ищем позицию для вставки
   if (field.key.compare(table.fields[insert_pos].key) != 0)
   {
      shiftTableFieldsFromPos(table, insert_pos); //Вставляем поле на нужную позицию
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(price_table table, price_field_t field) //Бинарный поиск места в массиве для вставки
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
   std::cout << field.key << " " << field.price << std::endl;
}


int getPosField(price_table table, std::string key) //Бинарный поиск поля в таблице
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

void deleteField(price_table& table, std::string key)
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
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldT, price_field_t fieldP)
{
   int insert_pos = getPosForFieldQuanInsert(tableR, fieldT); //Ищем позицию для вставки
   shiftTableFieldsFromPos(tableR, insert_pos); 
   tableR.fields[insert_pos].quantity = fieldT.quantity; //Вставляем все нужные элементы полей из соответствующих таблиц
   tableR.fields[insert_pos].key = fieldT.key;
   tableR.fields[insert_pos].name = fieldT.name;
   tableR.fields[insert_pos].price = fieldP.price;
}

void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldT)
{
   int insert_pos = getPosForFieldQuanInsert(tableR, fieldT); //Ищем позицию для вставки                                                      
   shiftTableFieldsFromPos(tableR, insert_pos);//Вставляем все нужные элементы полей из соответствующих таблиц
   tableR.fields[insert_pos].quantity = fieldT.quantity;
   tableR.fields[insert_pos].key = fieldT.key;
   tableR.fields[insert_pos].name = fieldT.name;
}

int getPosForFieldQuanInsert(result_table table, work_field_t field) //Бинарный поиск места в массиве для вставки
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
   std::cout << field.key << " " << field.name << " " << field.quantity << " " << field.price << std::endl;
}

int getPosField(result_table table, int quantity) //Бинарный поиск поля в таблице
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

void deleteField(result_table& table, int quantity)
{
   int field_pos = getPosField(table, quantity);
   if (field_pos >= 0) //Если запись нашли в нашей таблице, то удаляем
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}

void transformTables(work_table tableT, price_table tableP, result_table& tableR) //Функция заполнения новой таблицы
{
   for (int i = 0; i < tableT.size; i++) //Берём каждое поле из таблицы work
   {
      int price_pos = getPosField(tableP, tableT.fields[i].key); //Ищем соответсвующую ему цену в таблице price
      if (price_pos >= 0) 
         QuanInsertFieldAtTable(tableR, tableT.fields[i], tableP.fields[price_pos]); //Если цена была найдена, то вставляем поле из таблицы work и соответсвующую ему цену
      else 
         QuanInsertFieldAtTable(tableR, tableT.fields[i]); //Если цена не была найдена, то вставляем поле из таблицы work, оставляя цену "Не указана" по умолчанию
   }
}