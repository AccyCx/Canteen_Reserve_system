#include "manager.h"
#include <string>
#include <iostream>
#include <vector>
#include<conio.h>//getch()������ͷ�ļ�
#include <chrono>
#include <thread>
#include <mysql.h>
#include <cstdlib>
#include <numeric>
using namespace std;
//���ݳ�ʼ��
manager::manager()
{
};
//��������
manager::~manager() {};
//�����λ���
void manager::smanage_seat() 
{
	while (true)
	{
		system("cls");
		cout << "1.���в�λ����" << endl;
		cout << "2.����������" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			manage_seat();
			break;
		}
		if (a == 2)
		{
			control();
			break;
		}

	}
};
//��λ����(�������ݿ�)
void manager::manage_seat() 
{
//�Ȳ�ѯ
	select_seat();
//�ٹ���
	int num;//��λ��
	string zt;//ԤԼ״̬
	cout << "������Ҫ�ٿصĲ�λ����:";
	cin >> num;
	cin.clear();
	cin.ignore(10124, '\n');
	cout << "������Ҫ�޸�ԤԼ״̬Ϊ:";
	cin >> zt;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	//����ԤԼ״̬
	string strQuery = "update seats set ԤԼ״̬='";
	strQuery.append(zt);
	strQuery.append("' where ID=");
	string snum = to_string(num);
	strQuery.append(snum);
	strQuery.append(";");
	if (0 == mysql_query(&mysql, strQuery.c_str()))
	{
		cout << "�����ɹ�!" << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	smanage_seat();
};
//��λ��ѯ
void manager::select_seat() 
{
	vector<vector<string>> data;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string queryStr = "select * from seats; ";
	if (0 != mysql_query(&mysql, queryStr.c_str())) {
		cout << "��ѯʧ��";
	}
	MYSQL_RES* result = mysql_store_result(&mysql);//������ݿ�����
	int row = mysql_num_rows(result);//��ý�����е�����
	int field = mysql_num_fields(result);//��ý�����е�����

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);
	string temp;
	while (NULL != line)
	{
		vector<string> linedata;
		for (int i = 0; i < field; i++) {//��ȡÿһ�е�����
			if (line[i]) {
				temp = line[i];
				linedata.push_back(temp);
			}
			else {
				temp = "NULL";
				linedata.push_back(temp);
			}
		}
		line = mysql_fetch_row(result);
		data.push_back(linedata);
	}

	cout << "��λ����:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
};
//�����Ʒ���
void manager::smanage_dish() 
{
	system("cls");
	while (true)
	{
		//�ȿ���
		select_dish();
		cout << "1.�޸Ĳ˼�" << endl;
		cout << "2.������ϼ����" << endl;
		cout << "0.�ص���ҳ��" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			manage_dishprice();
			break;
		}
		if (a == 2)
		{
			manage_dishsj();
			break;
		}
		if (a == 0)
		{
			control();
		}

	}
};
//�˼۹���
void manager::manage_dishprice() 
{
	string dish_name;
	double dish_price;
	cout << "�����������޸Ĳ˼۵Ĳ���:";
	cin >> dish_name;
	cout << "�����������޸ĵļ۸�:";
	cin >> dish_price;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string strQuery = "update dish set price=";
	string sdish_price = to_string(dish_price);
	strQuery.append(sdish_price);
	strQuery.append(" where name='");
	strQuery.append(dish_name);
	strQuery.append("';");
	if (0 == mysql_query(&mysql, strQuery.c_str()))
	{
		cout << "�޸Ĳ˼۳ɹ�!" << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	smanage_dish();

};
//�ϼܹ���
void manager::manage_dishsj() 
{
	string dish_name;
	string dish_zt;
	cout << "�����������ϻ��¼ܵĲ���:";
	cin >> dish_name;
	cout << "�������Ƿ����ϼ�:";
	cin >> dish_zt;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string strQuery = "update dish set �Ƿ��ϼ�='";
	strQuery.append(dish_zt);
	strQuery.append("' where name ='");
	strQuery.append(dish_name);
	strQuery.append("';");
	if (0 == mysql_query(&mysql, strQuery.c_str()))
	{
		cout << "�ϣ��£��ܳɹ�!" << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	smanage_dish();
};
//��Ʒ��ѯ
void manager::select_dish() 
{
	vector<vector<string>> data;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string queryStr = "select * from dish; ";
	if (0 != mysql_query(&mysql, queryStr.c_str())) {
		cout << "��ѯʧ��";
	}
	MYSQL_RES* result = mysql_store_result(&mysql);//������ݿ�����
	int row = mysql_num_rows(result);//��ý�����е�����
	int field = mysql_num_fields(result);//��ý�����е�����

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);
	string temp;
	while (NULL != line)
	{
		vector<string> linedata;
		for (int i = 0; i < field; i++) {//��ȡÿһ�е�����
			if (line[i]) {
				temp = line[i];
				linedata.push_back(temp);
			}
			else {
				temp = "NULL";
				linedata.push_back(temp);
			}
		}
		line = mysql_fetch_row(result);
		data.push_back(linedata);
	}

	cout << "��Ʒ����:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
};
//�鿴�˿���Ϣ
void manager::select_customer() 
{
	vector<vector<string>> data;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string queryStr = "select name,account,phonenumber from customer; ";
	if (0 != mysql_query(&mysql, queryStr.c_str())) {
		cout << "��ѯʧ��";
	}
	MYSQL_RES* result = mysql_store_result(&mysql);//������ݿ�����
	int row = mysql_num_rows(result);//��ý�����е�����
	int field = mysql_num_fields(result);//��ý�����е�����

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);
	string temp;
	while (NULL != line)
	{
		vector<string> linedata;
		for (int i = 0; i < field; i++) {//��ȡÿһ�е�����
			if (line[i]) {
				temp = line[i];
				linedata.push_back(temp);
			}
			else {
				temp = "NULL";
				linedata.push_back(temp);
			}
		}
		line = mysql_fetch_row(result);
		data.push_back(linedata);
	}

	cout << "�˿���Ϣ����:" << endl;
	cout << "Name\tAccount\tPhonenumber" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	control();
};
//��¼����
void manager::manager_login() 
{
		long long int act;//������˺Ż�������
		cout << "**********************����Ա��½����******************" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    1.�˺������¼                  |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    2.�ֻ������¼                  |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "******************************************************" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
			// �˺������¼
		case 1:
		{
			system("cls");
			cout << "�����������˺�:";
			cin >> act;
			cin.clear();
			cin.ignore(10124, '\n');
			cout << "��������������:";
			string pasd;
			cin >> pasd;
			if (act == account && pasd == password)
			{
				cout << "����ɹ���" << endl;
				system("pause");
				control();
			}
			else
			{
				cout << "�����˺Ż������������" << endl;
				system("pause");
				manager_login();
			}
		}
		break;
		//�ֻ������¼
		case 2:
		{
			system("cls");
			cout << "�����������ֻ�����:";
			cin >> act;
			cin.clear();
			cin.ignore(10124, '\n');
			cout << "��������������:";
			string pasd;
			cin >> pasd;
			if (act == phonenumber && pasd == password)
			{
				cout << "����ɹ���" << endl;
				system("pause");
				control();
			}
			else
			{
				cout << "�����ֻ�����������������" << endl;
				system("pause");
				manager_login();
			}
		}
		break;
		default:
			cout << "�������Ч����" << endl;
			system("pause");
			system("cls");
			break;
		}
};
//�������
void manager::control() 
{
	system("cls");
	cout << "*********************�������ԤԼ����*****************" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    1.�����λ״̬                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    2.�����Ʒ״̬                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    3.��ѯ�˿���Ϣ                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    4.�˳�ϵͳ                      |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "******************************************************" << endl;
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		system("cls");
		smanage_seat();
	}
	break;
	case 2:
	{
		system("cls");
		smanage_dish();
	}
	break;
	case 3:
	{
		system("cls");
		select_customer();
	}
	break;
	case 4:
	{
		exit(0);
	}
	break;
	default:
	{
		cout << "��������Ч����!" << endl;
		system("pause");
		control();
	}
	break;
	}
};