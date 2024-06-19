#include "customer.h"
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
customer::customer() 
{
	
};
//��������
customer::~customer() {};
//��¼����(������)
void customer::manager_login() 
{
	long long int act;//������˺Ż�������
	vector <char>vec1;//���������
	char ch;//�޻�������
	system("cls");
	cout << "***********************�˿͵�½����*******************" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    1.�˺������¼                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    2.�ֻ������¼                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    3.ע��                          |" << endl;
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
		case 3:
		{
			system("cls");
			manager_register();
		}
		break;
		default:
			cout << "�������Ч����" << endl;
			system("pause");
			system("cls");
			break;
		}
};
//��½�������� 
void customer::control() 
{
	system("cls");
	cout << "***********************����ԤԼ����*******************" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    1.ԤԼ��λ                      |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    2.ԤԼ��Ʒ                      |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    3.��ѯ��ԤԼ��λ                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    4.��ѯ��ԤԼ��Ʒ                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    5.�˻���Ϣ��ѯ                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    6.�˻���Ϣ�޸�                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    7.�˳�ϵͳ                      |" << endl;
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
			sreserve_control();
		}
		break;
		case 2:
		{
			system("cls");
			dreserve_control();
		}
		break;
		case 3:
		{
			system("cls");
			finish_seat();
		}
		break;
		case 4:
		{
			system("cls");
			finish_dish();
		}
		break;
		case 5:
		{
			system("cls");
			select_information();
		}
		break;
		case 6:
		{
			system("cls");
			revise_information();
		}
		break;
		case 7:
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
//ע�Ṧ��
void customer::manager_register()
{
	long long int act; // ������˺�
	string nam ; // ���������
	long long int phb; // ����ĵ绰����
	string pasd;//���������
	cout << "�������˺�:";
	cin >> act;
	account = act;
	string pasd1;
	// ��������
	cout << "����������:";
	cin.clear();
	cin.ignore(10124, '\n');
	cin >> pasd;
	password = pasd;
	// �����ֻ����������
	cout << "�������ֻ���:";
	cin >> phb;
	phonenumber = phb;
	cin.clear();
	cin.ignore(10124, '\n');
	cout << "��������������:";
	getline(cin, nam);
	name = nam;
	cout << "��ϲ��ע��ɹ���" << endl;
	system("pause");
	system("cls");

	// ���ݿ����
	cout << "����Ϊ�������˻���Ϣ..." << endl;
	Insert_DB();
	Create_DB();
	cout << "���ݴ洢�ɹ���" << endl;
	cout << "�������ص�¼ҳ��..." << endl;
	system("pause");
	system("cls");

	manager_login(); // ���ص�¼ҳ��
}

void customer::Insert_DB()
{
	MYSQL mysql;
	mysql_init(&mysql); // ��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); // �����ַ����� 

	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��" << endl;
		exit(-1);
	}

	string num = to_string(phonenumber);
	string aco = to_string(account);
	string str = "insert into customer values('";
	str.append(name);
	str.append("','");
	str.append(aco);
	str.append("','");
	str.append(password);
	str.append("','");
	str.append(num);
	str.append("');");

	if (mysql_query(&mysql, str.c_str()) == 0) {
		cout << "�������ݳɹ���" << endl;
	}

	chrono::seconds duration(2);
	this_thread::sleep_for(duration);

	cout << "�����Ѹ���!" << endl;

	mysql_close(&mysql);
}
//������Ϣ��ѯ
void customer::select_information() 
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
	string queryStr = "select * from customer where name ='";
	queryStr += name;
	queryStr.append("';");
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

	cout << "��ѯ�ɹ�" << endl;
	cout << "Name\tAccount\t\tPassword\tphonember" << endl;
	for (int i = 0; i < data.size(); ++i) 
	{
		for (int j = 0; j < data[i].size(); ++j) 
		{
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
	cout << "�����ص���ҳ��" << endl;
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
	system("cls");
	control();
};
//������Ϣ�޸�(���룬�ֻ���)
void customer::revise_information() 
{
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��"<<endl;
		exit(-1);
	}
	while (true)
	{
		system("cls");
		cout << "***********************������Ϣ�޸Ľ���*******************" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                    1.�޸��ֻ���                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                    2.�޸�����                          |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                    3.������ҳ��                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "**********************************************************" << endl;
		int choice;
		cin >> choice;
		if (choice == 3)
		{
			cout << "�����ص���ҳ��" << endl;
			chrono::seconds duration(1);
			this_thread::sleep_for(duration);
			system("cls");
			control();
			break;
		}
		switch(choice)
		{
		case 1:
		{
			system("cls");
			while (true)
			{
				cout << "��������ֻ���:";
				int a;
				cin >> a;
				if (a != phonenumber)
				{
					cout << "����ֻ��Ų�ƥ�䣡"<<endl;
					chrono::seconds duration(1);
					this_thread::sleep_for(duration);
					cout << "���ٴγ��ԣ�"<<endl;
				}
				if(a==phonenumber)
				{
					cout << "���������ֻ���:";
					int b;
					cin >> b;
					phonenumber = b;
					string query = "update customer set phonenumber=";
					string pho = to_string(phonenumber);
					query.append(pho);
					query.append(" where name ='");
					query.append(name);
					query.append("';");
					if (mysql_query(&mysql, query.c_str()) != 0) 
					{
						cout << "�޸��ֻ�����ʧ��!" << endl;
						cout << "���ٴγ��ԣ�"<<endl;
					}
					else
					{
						cout << "�޸��ֻ�����ɹ�!" << endl;
						chrono::seconds duration(1);
						this_thread::sleep_for(duration);
						cout << "�����Ѹ���!" << endl;
						break;
					}
				}
			}
		}
		break;
		case 2:
		{
			system("cls");
			while (true)
			{
				cin.clear();
				cin.ignore(10124, '\n');
				cout << "�����������:";
				string pasd;
				cin >> pasd;
				if (pasd != password)
				{
					cout << "�������!";
					chrono::seconds duration(1);
					this_thread::sleep_for(duration);
					cout << "���ٴγ��ԣ�";
				}
				else
				{
					cin.clear();
					cin.ignore(10124, '\n');
					cout << "������������:";
					string npasd;
					cin >> npasd;
					password = npasd;
					string query = "update customer set password=";
					query.append(password);
					query.append(" where name ='");
					query.append(name);
					query.append("';");
					if (mysql_query(&mysql, query.c_str()) != 0) {
						cout << "�޸�����ʧ��!" << endl;
					}
					else
					{
						cout << "�޸�����ɹ�!" << endl;
						chrono::seconds duration(1);
						this_thread::sleep_for(duration);
						cout << "�����Ѹ���!" << endl;
					}
					break;
				}
			}
		}
		break;
		default:
			break;
		}
		
	}
	mysql_close(&mysql);
	
};
//��λԤԼ����
void customer::sreserve_control() 
{
	while (true)
	{
		cout << "1.���в�λԤԼ" << endl;
		cout << "2.����������" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			system("cls");
			reserve_seat();
			break;
		}
		if (a == 2)
		{
			system("cls");
			control();
			break;
		}
		
	}
};
//��λ��ѯ(�������ݿ�)(����)
void customer::select_seat() 
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
	string queryStr = "select * from seats where ԤԼ״̬='��'; ";
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

	cout << "ʣ���λ����:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");

};
//ԤԼ��λ����Ӧʵ��ѡ��ʱ��κ�֧�������ܣ�֧���������ԤԼ�ɹ�(�������û��ı��)
//����ʱ���ѡ������λ����ѡ���λ���Խ���ԤԼ��ԤԼ�����λ�����״̬
//ԤԼ��λ��������
void customer::reserve_seat() 
{
	//�ȿ�ʣ��Ĳ�λ
	select_seat();
	//����ԤԼ
	vector<vector<string>> data;
	cout << "��������ҪԤԼ��ʱ���:";
	string res;
	cin >> res;
	seattime = res;
	cout << "������ҪԤԼ�Ĳ�λ��:";
	int id,money;
	cin >> id;
	seatid = id;
	if (id < 100)
	{
		money = 50;
	}
	else
	{
		money = 100;
	}
	cout << "����Ҫ֧��" << money << "Ԫ" << endl;
	cout << "���Ƿ�ԤԼ?" << endl;
			string choice1;
			cin >> choice1;
			if (choice1 == "��")  //��ԤԼ�Ĳ�λ״̬�޸ģ�������λ�ź�ʱ���¼��������ݿ⣬�����غ���select
			{
				//�����λ��
				MYSQL mysql;
				mysql_init(&mysql);//��ʼ�����ݿ�
				mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
				if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
				{
					cout << "�����˿���Ϣ������ʧ��";
					exit(-1);
				}
				string strQuery = "insert into ";
				strQuery.append(name);
				strQuery.append("_information(Seat_ID,pre_time) values(");
				string sid = to_string(id);
				strQuery.append(sid);
				strQuery.append(",'");
				strQuery.append(res);
				strQuery.append("');");
				mysql_query(&mysql, strQuery.c_str());
				strQuery = "update seats set ԤԼ״̬='��' where ID=";
				strQuery.append(sid);
				strQuery.append(";");
				mysql_query(&mysql, strQuery.c_str());
				mysql_close(&mysql);
				cout << "ԤԼ�ɹ�!" << endl;
				system("pause");
				chrono::seconds duration(1);
				this_thread::sleep_for(duration);
				cout << "��������ԤԼ����";
				this_thread::sleep_for(duration);
				system("cls");
				sreserve_control();
				
			}
			else //���غ���select_seat() 
			{
				cout << "����ȡ��ԤԼ!"<<endl;
				system("pause");
				chrono::seconds duration(1);
				this_thread::sleep_for(duration);
				cout << "��������ԤԼ����";
				system("cls");
				sreserve_control();
			}
	
};
//��λ�޸�(�������ݿ�)(�޸�λ�û���ʱ��Σ�����ȡ��ԤԼ)*����
void customer::revise_seat() {
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	while (true)
	{
		cout << "1.�޸�Ԥ����λ" << endl;
		cout << "2.ȡ��ԤԼ" << endl;
		cout << "0.�ص�������" << endl;
		int choice;
		cin >> choice;
		if(choice==0)
		{
			control();
			break;
		}
		switch (choice)
		{
		case 1://�޸�λ��
		{
			system("cls");
			cout << "���в�λ��ԤԼ:" << endl;
			chrono::seconds duration(1);
			this_thread::sleep_for(duration);
			select_seat();
			system("pause");
			cout << "ѡ���µĲ�λ�ź�ʱ���:";
			int num;
			string time1;
			cin >> num;
			cin >> time1;
			//�޸ĸ�����Ϣ��λ��
			string strQuery = "update ";
			strQuery.append(name);
			strQuery.append("_information set Seat_ID=");
			string snum = to_string(num);
			strQuery.append(snum);
			mysql_query(&mysql, strQuery.c_str());
			//�޸ĸ�����Ϣʱ��
			 strQuery = "update ";
			strQuery.append(name);
			strQuery.append("_information set pre_time='");
			strQuery.append(time1);
			strQuery.append("';");
			if (0 == mysql_query(&mysql, strQuery.c_str()))
			{
				cout << "�޸ĳɹ�!" << endl;
			}
			//������λԤԼ״̬
			strQuery = "update seats set ԤԼ״̬='��' where ID=";
			string ssid = to_string(seatid);
			strQuery.append(ssid);
			strQuery.append(";");
			mysql_query(&mysql, strQuery.c_str());
			seatid = num;
			strQuery = "update seats set ԤԼ״̬='��' where ID=";
			strQuery.append(snum);
			strQuery.append(";");
			mysql_query(&mysql, strQuery.c_str());
			cout << "�����ص��ϸ�ҳ��" << endl;
			this_thread::sleep_for(duration);
			system("pause");
			system("cls");
		}
		break;
		case 2://ȡ��ԤԼ
		{
			int num;
			cout << "������Ҫȡ������λ��:";
			cin >> num;
			string snum = to_string(num);
			string strQuery = "delete from ";
			strQuery.append(name);
			strQuery.append("_information where Seat_ID=");
			strQuery.append(snum);
			strQuery.append(";");
			if (0 == mysql_query(&mysql, strQuery.c_str()))
			{
				cout << "ȡ���ɹ�!" << endl;
			}
			cout << "�����ص��ϸ�ҳ��" << endl;
			chrono::seconds duration(1);
			this_thread::sleep_for(duration);
			system("pause");
			system("cls");
		}
		break;
		default:
			break;
		}
	}
};
//��Ʒ��ѯ(�������ݿ�)*����
void customer::select_dish() 
{
	MYSQL mysql;
	vector<vector<string>> data;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string queryStr = "select * from dish where �Ƿ��ϼ�='��'; ";
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

	cout << "�˵���ѯ�ɹ�" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
};
//ԤԼ��Ʒ����Ӧ��ѡ��������֧�������ܣ�֧���������ԤԼ�ɹ�
void customer::reserve_dish() 
{
	//�ȿ��˵�
	select_dish();
	cin.clear();
	cin.ignore(10124, '\n');
	cout << "������ҪԤ���Ĳ���:";
	string pre_dish;
	cin >> pre_dish;
	cout << "������ҪԤ���ò˵�����:";
	int act_dish;
	cin >> act_dish;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	
	//�����Ʒ�۸�
	vector<vector<string>> data;
	string queryStr = "select price from dish where name=' ";
	queryStr.append(pre_dish);
	queryStr.append("';");
	mysql_query(&mysql, queryStr.c_str());
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
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j];
		}
		cout << endl;
	}
	int totalprice=0;//�ܼ�
	cout << "�����Ƿ�ԤԼ" << endl;
	string ans;
	cin >> ans;
	if (ans == "��")
	{
		string queryStr = "insert into ";
		queryStr.append(name);
		queryStr.append("_information (dish_name,dish_act) values(' ");
		queryStr.append(pre_dish);
		queryStr.append("',");
		string sact_dish = to_string(act_dish);
		queryStr.append(sact_dish);
		queryStr.append(");");
		mysql_query(&mysql, queryStr.c_str());//��Ʒ����Ϣ���뵽������Ϣ����
		cout << "ԤԼ�ɹ�!" << endl;
		system("pause");
		mysql_close(&mysql);
		cout << "�����ص���һ��ҳ��" << endl;
		chrono::seconds duration(1);
		this_thread::sleep_for(duration);
		system("cls");
		dreserve_control();
	}
	if (ans == "��")
	{
		mysql_close(&mysql);
		system("pause");
		cout << "�����ص���һ��ҳ��" << endl;
		chrono::seconds duration(1);
		this_thread::sleep_for(duration);
		system("cls");
		dreserve_control();
	}
};
//��ƷԤԼ����
void customer::dreserve_control()
{
	while (true)
	{
		cout << "1.���в�ƷԤԼ" << endl;
		cout << "2.����������" << endl;
		int a;
		cin >> a;
		switch (a)
		{
		case 1:
			system("cls");
			reserve_dish();
			break;
		case 2:
			system("cls");
			control();
			break;
		default:
			cout << "�������Ч����" << endl;;
			break;
		}
		if (a == 1 || a == 2)
		{
			break;
		}
	}
};
//��Ʒ�޸Ľ���
void customer::revise_dishctr() 
{
	while (true)
	{
		cout << "1.���в�Ʒ�޸�" << endl;
		cout << "2.����������" << endl;
		int a;
		cin >> a;
		switch (a)
		{
		case 1:
			revise_dish();
			break;
		case 2:
			control();
			break;
		default:
			cout << "�������Ч����" << endl;;
			break;
		}
		if (a == 1 || a == 2)
		{
			break;
		}
	}
};
//��Ʒ�޸�(�������ݿ�)(ȡ��ԤԼ���޸�����)
void customer::revise_dish() 
{
	//���ʸ���
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	while (true)
	{
		cout << "1.�޸Ĳ�Ʒ����" << endl;
		cout << "2.ȡ��ԤԼ" << endl;
		cout << "0.������һ������" << endl;
		int choice;
		cin >> choice;
		if (choice == 0)
		{
			revise_dishctr();
			break;
		}
		switch(choice)
		{
		case 1:
		{
			cout << "��������Ҫ�޸ĵĲ�Ʒ������:";
			string dish_name;
			cin >> dish_name;
			cout << "��������Ҫ�޸ĵĲ�Ʒ������:";
			int dish_account;
			cin >> dish_account;
			string queryStr = "update ";
			queryStr.append(name);
			queryStr.append("_information set dish_act=");
			string sdish_account = to_string(dish_account);
			queryStr.append(sdish_account);
			queryStr.append(" where name ='");
			if (0 == mysql_query(&mysql, queryStr.c_str()))
			{
				cout << "�޸ĳɹ�!" << endl;
			}
			system("pause");
		}
		break;
		case 2:
		{
			cout << "��������Ҫȡ���Ĳ���:";
			string dish_name;
			string queryStr = "delete from ";
			queryStr.append(name);
			queryStr.append("_information where name ='");
			queryStr.append(dish_name);
			queryStr.append("';");
			if (0 == mysql_query(&mysql, queryStr.c_str()))
			{
				cout << "ɾ���ɹ�!" << endl;
			}
			system("pause");
		}
		break;
		default:
			break;
		}
	}
};
//������ԤԼ��Ʒ
void customer::finish_dish() 
{
	vector<vector<string>>data;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string queryStr = "select dish_name,dish_act from ";
	queryStr.append(name);
	queryStr.append("_information;");;
	mysql_query(&mysql, queryStr.c_str());
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

	cout << "����ԤԼ:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
	cout << "�����ص���ҳ��" << endl;
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
	system("cls");
	control();
};
void customer::finish_seat() 
{
	vector<vector<string>>data;
	MYSQL mysql;
	mysql_init(&mysql);//��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//�����ַ����� 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��";
		exit(-1);
	}
	string queryStr = "select Seat_ID,pre_time from ";
	queryStr.append(name);
	queryStr.append("_information;");;
	mysql_query(&mysql, queryStr.c_str());
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

	cout << "����ԤԼ:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
	cout << "�����ص���ҳ��" << endl;
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
	system("cls");
	control();
};
//�������˲�λԤԼ��Ϣ��(ע���˺ŵ�ʱ���Ӧʹ��)
void customer::Create_DB()
{
	MYSQL mysql;
	mysql_init(&mysql); // ��ʼ�����ݿ�
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); // �����ַ����� 

	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "�������ݿ�", 3306, NULL, 0) == NULL)
	{
		cout << "�����˿���Ϣ������ʧ��" << endl;
		exit(-1);
	}

	string queryStr = "create table `";
	queryStr.append(name);
	queryStr.append("_information` (");
	queryStr.append("`Seat_ID` int,");
	queryStr.append("`pre_time` time,");
	queryStr.append("`dish_name` varchar(50),");
	queryStr.append("`dish_act` int);");

	if (mysql_query(&mysql, queryStr.c_str()) == 0)
	{
		cout << "��񴴽��ɹ���" << endl;
	}
	else
	{
		cout << "��񴴽�ʧ�ܣ�" << endl;
		cout << mysql_error(&mysql) << endl; // ���������Ϣ
	}

	mysql_close(&mysql);
}