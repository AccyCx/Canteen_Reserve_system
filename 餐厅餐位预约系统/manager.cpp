#include "manager.h"
#include <string>
#include <iostream>
#include <vector>
#include<conio.h>//getch()函数的头文件
#include <chrono>
#include <thread>
#include <mysql.h>
#include <cstdlib>
#include <numeric>
using namespace std;
//数据初始化
manager::manager()
{
};
//析构函数
manager::~manager() {};
//管理餐位面板
void manager::smanage_seat() 
{
	while (true)
	{
		system("cls");
		cout << "1.进行餐位管理" << endl;
		cout << "2.返回主界面" << endl;
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
//餐位管理(连接数据库)
void manager::manage_seat() 
{
//先查询
	select_seat();
//再管理
	int num;//餐位号
	string zt;//预约状态
	cout << "请问您要操控的餐位号是:";
	cin >> num;
	cin.clear();
	cin.ignore(10124, '\n');
	cout << "请问您要修改预约状态为:";
	cin >> zt;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	//管理预约状态
	string strQuery = "update seats set 预约状态='";
	strQuery.append(zt);
	strQuery.append("' where ID=");
	string snum = to_string(num);
	strQuery.append(snum);
	strQuery.append(";");
	if (0 == mysql_query(&mysql, strQuery.c_str()))
	{
		cout << "操作成功!" << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	smanage_seat();
};
//餐位查询
void manager::select_seat() 
{
	vector<vector<string>> data;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string queryStr = "select * from seats; ";
	if (0 != mysql_query(&mysql, queryStr.c_str())) {
		cout << "查询失败";
	}
	MYSQL_RES* result = mysql_store_result(&mysql);//获得数据库结果集
	int row = mysql_num_rows(result);//获得结果集中的行数
	int field = mysql_num_fields(result);//获得结果集中的列数

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);
	string temp;
	while (NULL != line)
	{
		vector<string> linedata;
		for (int i = 0; i < field; i++) {//获取每一行的内容
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

	cout << "餐位如下:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
};
//管理菜品面板
void manager::smanage_dish() 
{
	system("cls");
	while (true)
	{
		//先看菜
		select_dish();
		cout << "1.修改菜价" << endl;
		cout << "2.管理菜上架情况" << endl;
		cout << "0.回到主页面" << endl;
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
//菜价管理
void manager::manage_dishprice() 
{
	string dish_name;
	double dish_price;
	cout << "请输入您想修改菜价的菜名:";
	cin >> dish_name;
	cout << "请输入您想修改的价格:";
	cin >> dish_price;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
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
		cout << "修改菜价成功!" << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	smanage_dish();

};
//上架管理
void manager::manage_dishsj() 
{
	string dish_name;
	string dish_zt;
	cout << "请输入您想上或下架的菜名:";
	cin >> dish_name;
	cout << "请问您是否想上架:";
	cin >> dish_zt;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string strQuery = "update dish set 是否上架='";
	strQuery.append(dish_zt);
	strQuery.append("' where name ='");
	strQuery.append(dish_name);
	strQuery.append("';");
	if (0 == mysql_query(&mysql, strQuery.c_str()))
	{
		cout << "上（下）架成功!" << endl;
	}
	mysql_close(&mysql);
	system("pause");
	system("cls");
	smanage_dish();
};
//菜品查询
void manager::select_dish() 
{
	vector<vector<string>> data;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string queryStr = "select * from dish; ";
	if (0 != mysql_query(&mysql, queryStr.c_str())) {
		cout << "查询失败";
	}
	MYSQL_RES* result = mysql_store_result(&mysql);//获得数据库结果集
	int row = mysql_num_rows(result);//获得结果集中的行数
	int field = mysql_num_fields(result);//获得结果集中的列数

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);
	string temp;
	while (NULL != line)
	{
		vector<string> linedata;
		for (int i = 0; i < field; i++) {//获取每一行的内容
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

	cout << "菜品如下:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
};
//查看顾客信息
void manager::select_customer() 
{
	vector<vector<string>> data;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string queryStr = "select name,account,phonenumber from customer; ";
	if (0 != mysql_query(&mysql, queryStr.c_str())) {
		cout << "查询失败";
	}
	MYSQL_RES* result = mysql_store_result(&mysql);//获得数据库结果集
	int row = mysql_num_rows(result);//获得结果集中的行数
	int field = mysql_num_fields(result);//获得结果集中的列数

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(result);
	string temp;
	while (NULL != line)
	{
		vector<string> linedata;
		for (int i = 0; i < field; i++) {//获取每一行的内容
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

	cout << "顾客信息如下:" << endl;
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
//登录功能
void manager::manager_login() 
{
		long long int act;//输入的账号或者密码
		cout << "**********************管理员登陆界面******************" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    1.账号密码登录                  |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    2.手机密码登录                  |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "******************************************************" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
			// 账号密码登录
		case 1:
		{
			system("cls");
			cout << "请输入您的账号:";
			cin >> act;
			cin.clear();
			cin.ignore(10124, '\n');
			cout << "请输入您的密码:";
			string pasd;
			cin >> pasd;
			if (act == account && pasd == password)
			{
				cout << "登入成功！" << endl;
				system("pause");
				control();
			}
			else
			{
				cout << "您的账号或密码输入错误！" << endl;
				system("pause");
				manager_login();
			}
		}
		break;
		//手机密码登录
		case 2:
		{
			system("cls");
			cout << "请输入您的手机号码:";
			cin >> act;
			cin.clear();
			cin.ignore(10124, '\n');
			cout << "请输入您的密码:";
			string pasd;
			cin >> pasd;
			if (act == phonenumber && pasd == password)
			{
				cout << "登入成功！" << endl;
				system("pause");
				control();
			}
			else
			{
				cout << "您的手机号码或密码输入错误！" << endl;
				system("pause");
				manager_login();
			}
		}
		break;
		default:
			cout << "请进行有效操作" << endl;
			system("pause");
			system("cls");
			break;
		}
};
//操作面板
void manager::control() 
{
	system("cls");
	cout << "*********************管理餐厅预约界面*****************" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    1.管理餐位状态                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    2.管理菜品状态                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    3.查询顾客信息                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    4.退出系统                      |" << endl;
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
		cout << "请输入有效操作!" << endl;
		system("pause");
		control();
	}
	break;
	}
};