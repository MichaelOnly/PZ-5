#pragma once

#define CAPACITY 17 //������������ ���������� ��������� �������

#include <iostream>

struct work_field_t //���� � ������� �� ����� work
{
   int quantity;
   std::string name, key;
};

struct work_table //������� �� ����� work
{
   int size = 0;
   work_field_t fields[CAPACITY];
};

struct price_field_t //���� ������� �� ����� price
{
   std::string key, price;
};

struct price_table //������� �� ����� price
{
   int size = 0;
   price_field_t fields[CAPACITY];
};

struct result_field_t //���� �������� �������
{
   int quantity;
   std::string name, key, price = "�� �������";
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
int getPosField(work_table table, std::string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(work_table& table, std::string key); //������� ���� � ������� �� �����

//������� ��� ������ � �������� �� ����� price
void insertFieldAtTable(price_table& table, price_field_t field); //��������� ���� � �������, �������� �������
int getPosForFieldInsert(price_table table, price_field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(price_table& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(price_table table); //������������� ������� � �������
void printField(price_field_t field); //������������� ���� ������� � �������
int getPosField(price_table table, std::string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(price_table& table, std::string key); //������� ���� � ������� �� �����

//������� ��� ������ � �������� �������� �������� 
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldW, price_field_t fieldP); //��������� ���� � �������, �������� �������(�������������� ��� �� ����������), ���� ���� ������� ���� 
void QuanInsertFieldAtTable(result_table& tableR, work_field_t fieldW); //��������� ���� � �������, �������� �������(�������������� ��� �� ����������), ���� ���� �� ���� �������
int getPosForFieldQuanInsert(result_table table, work_field_t field); //���������� ������� � �������, � ������� ���� ����� ��������((�������������� ��� �� ����������))
void shiftTableFieldsFromPos(result_table& table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(result_table table); //������������� ������� � �������
void printField(result_field_t field); //������������� ���� ������� � �������
int getPosField(result_table table, int quantity); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(result_table& table, int quantity); //������� ���� � ������� �� �����
void transformTables(work_table tableW, price_table tableP, result_table& tableR); //��������������� ������� �� ������ work � price � �������� �������
