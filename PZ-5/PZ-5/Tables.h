#pragma once

#define CAPACITY 17 //максимальное количество элементов таблицы

#include <iostream>

struct work_field_t //Поле в таблице из файла work
{
   int quantity;
   std::string name, key;
};

struct work_table //Таблица из файла work
{
   int size = 0;
   work_field_t fields[CAPACITY];
};

struct price_field_t //Поле таблицы из файла price
{
   std::string key, price;
};

struct price_table //Таблица из файла price
{
   int size = 0;
   price_field_t fields[CAPACITY];
};

struct result_field_t //Поле итоговой таблицы
{
   int quantity;
   std::string name, key, price = "Не указана";
};

struct result_table //Итоговая таблица
{
   int size = 0;
   result_field_t fields[CAPACITY];
};

//Функции для работы с таблицей из файла work
void insertFieldAtTable(work_table& table, work_field_t field); //Вставляет поле в таблицу, сохраняя порядок
int getPosForFieldInsert(work_table table, work_field_t field); //Определяет позицию в таблице, в которую поле нужно вставить
void shiftTableFieldsFromPos(work_table& table, int pos); //Смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(work_table table); //Распечатывает таблицу в консоль
void printField(work_field_t field); //Распечатывает поле таблицы в консоль
int getPosField(work_table table, std::string key); //Выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(work_table& table, std::string key); //Удаляет поле в таблице по ключу

//Функции для работы с таблицей из файла price
void insertFieldAtTable(price_table& table, price_field_t field); //Вставляет поле в таблицу, сохраняя порядок
int getPosForFieldInsert(price_table table, price_field_t field); //Определяет позицию в таблице, в которую поле нужно вставить
void shiftTableFieldsFromPos(price_table& table, int pos); //Смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(price_table table); //Распечатывает таблицу в консоль
void printField(price_field_t field); //Распечатывает поле таблицы в консоль
int getPosField(price_table table, std::string key); //Выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(price_table& table, std::string key); //Удаляет поле в таблице по ключу

//Функции для работы с итоговой таблицей таблицей 
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldW, price_field_t fieldP); //Вставляет поле в таблицу, сохраняя порядок(упорядочивание идёт по количеству), если была найдена цена 
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldW); //Вставляет поле в таблицу, сохраняя порядок(упорядочивание идёт по количеству), если цена не была найдена
int getPosForFieldQuanInsert(result_table table, work_field_t field); //Определяет позицию в таблице, в которую поле нужно вставить((упорядочивание идёт по количеству))
void shiftTableFieldsFromPos(result_table& table, int pos); //Смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(result_table table); //Распечатывает таблицу в консоль
void printField(result_field_t field); //Распечатывает поле таблицы в консоль
int getPosField(result_table table, int quantity); //Выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(result_table& table, int quantity); //Удаляет поле в таблице по ключу
void transformTables(work_table tableW, price_table tableP, result_table& tableR); //Преобразовывает таблицы из файлов work и price в итоговую таблицу
