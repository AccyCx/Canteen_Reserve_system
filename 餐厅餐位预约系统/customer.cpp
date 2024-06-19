#include "customer.h"
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
customer::customer() 
{
	
};
//析构函数
customer::~customer() {};
//登录功能(待完善)
void customer::manager_login() 
{
	long long int act;//输入的账号或者密码
	vector <char>vec1;//输入的密码
	char ch;//无回显输入
	system("cls");
	cout << "***********************顾客登陆界面*******************" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    1.账号密码登录                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    2.手机密码登录                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    3.注册                          |" << endl;
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
		case 3:
		{
			system("cls");
			manager_register();
		}
		break;
		default:
			cout << "请进行有效操作" << endl;
			system("pause");
			system("cls");
			break;
		}
};
//登陆后操作面板 
void customer::control() 
{
	system("cls");
	cout << "***********************餐厅预约界面*******************" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    1.预约餐位                      |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    2.预约菜品                      |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    3.查询已预约餐位                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    4.查询已预约菜品                |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    5.账户信息查询                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    6.账户信息修改                  |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                    7.退出系统                      |" << endl;
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
			cout << "请输入有效操作!" << endl;
			system("pause");
			control();
		}
		break;
	}
};
//注册功能
void customer::manager_register()
{
	long long int act; // 输入的账号
	string nam ; // 输入的姓名
	long long int phb; // 输入的电话号码
	string pasd;//输入的密码
	cout << "请输入账号:";
	cin >> act;
	account = act;
	string pasd1;
	// 输入密码
	cout << "请输入密码:";
	cin.clear();
	cin.ignore(10124, '\n');
	cin >> pasd;
	password = pasd;
	// 输入手机号码和姓名
	cout << "请输入手机号:";
	cin >> phb;
	phonenumber = phb;
	cin.clear();
	cin.ignore(10124, '\n');
	cout << "请输入您的姓名:";
	getline(cin, nam);
	name = nam;
	cout << "恭喜您注册成功！" << endl;
	system("pause");
	system("cls");

	// 数据库操作
	cout << "正在为您储存账户信息..." << endl;
	Insert_DB();
	Create_DB();
	cout << "数据存储成功！" << endl;
	cout << "即将返回登录页面..." << endl;
	system("pause");
	system("cls");

	manager_login(); // 返回登录页面
}

void customer::Insert_DB()
{
	MYSQL mysql;
	mysql_init(&mysql); // 初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); // 设置字符编码 

	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败" << endl;
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
		cout << "插入数据成功！" << endl;
	}

	chrono::seconds duration(2);
	this_thread::sleep_for(duration);

	cout << "数据已更新!" << endl;

	mysql_close(&mysql);
}
//个人信息查询
void customer::select_information() 
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
	string queryStr = "select * from customer where name ='";
	queryStr += name;
	queryStr.append("';");
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

	cout << "查询成功" << endl;
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
	cout << "即将回到主页面" << endl;
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
	system("cls");
	control();
};
//个人信息修改(密码，手机号)
void customer::revise_information() 
{
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败"<<endl;
		exit(-1);
	}
	while (true)
	{
		system("cls");
		cout << "***********************个人信息修改界面*******************" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                    1.修改手机号                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                    2.修改密码                          |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                    3.返回主页面                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "|                                                        |" << endl;
		cout << "**********************************************************" << endl;
		int choice;
		cin >> choice;
		if (choice == 3)
		{
			cout << "即将回到主页面" << endl;
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
				cout << "请输入旧手机号:";
				int a;
				cin >> a;
				if (a != phonenumber)
				{
					cout << "与旧手机号不匹配！"<<endl;
					chrono::seconds duration(1);
					this_thread::sleep_for(duration);
					cout << "请再次尝试！"<<endl;
				}
				if(a==phonenumber)
				{
					cout << "请输入新手机号:";
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
						cout << "修改手机号码失败!" << endl;
						cout << "请再次尝试！"<<endl;
					}
					else
					{
						cout << "修改手机号码成功!" << endl;
						chrono::seconds duration(1);
						this_thread::sleep_for(duration);
						cout << "数据已更新!" << endl;
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
				cout << "请输入旧密码:";
				string pasd;
				cin >> pasd;
				if (pasd != password)
				{
					cout << "密码错误!";
					chrono::seconds duration(1);
					this_thread::sleep_for(duration);
					cout << "请再次尝试！";
				}
				else
				{
					cin.clear();
					cin.ignore(10124, '\n');
					cout << "请输入新密码:";
					string npasd;
					cin >> npasd;
					password = npasd;
					string query = "update customer set password=";
					query.append(password);
					query.append(" where name ='");
					query.append(name);
					query.append("';");
					if (mysql_query(&mysql, query.c_str()) != 0) {
						cout << "修改密码失败!" << endl;
					}
					else
					{
						cout << "修改密码成功!" << endl;
						chrono::seconds duration(1);
						this_thread::sleep_for(duration);
						cout << "数据已更新!" << endl;
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
//餐位预约界面
void customer::sreserve_control() 
{
	while (true)
	{
		cout << "1.进行餐位预约" << endl;
		cout << "2.返回主界面" << endl;
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
//餐位查询(连接数据库)(完善)
void customer::select_seat() 
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
	string queryStr = "select * from seats where 预约状态='否'; ";
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

	cout << "剩余餐位如下:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");

};
//预约餐位界面应实现选择时间段和支付定金功能，支付定金才算预约成功(创立该用户的表格)
//根据时间段选择空余餐位，再选择餐位号以进行预约，预约后的座位需更新状态
//预约座位功能完善
void customer::reserve_seat() 
{
	//先看剩余的餐位
	select_seat();
	//进行预约
	vector<vector<string>> data;
	cout << "请输入您要预约的时间段:";
	string res;
	cin >> res;
	seattime = res;
	cout << "输入您要预约的餐位号:";
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
	cout << "您需要支付" << money << "元" << endl;
	cout << "您是否预约?" << endl;
			string choice1;
			cin >> choice1;
			if (choice1 == "是")  //将预约的餐位状态修改，并将餐位号和时间段录入个人数据库，并返回函数select
			{
				//插入餐位号
				MYSQL mysql;
				mysql_init(&mysql);//初始化数据库
				mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
				if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
				{
					cout << "餐厅顾客信息库连接失败";
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
				strQuery = "update seats set 预约状态='是' where ID=";
				strQuery.append(sid);
				strQuery.append(";");
				mysql_query(&mysql, strQuery.c_str());
				mysql_close(&mysql);
				cout << "预约成功!" << endl;
				system("pause");
				chrono::seconds duration(1);
				this_thread::sleep_for(duration);
				cout << "即将返回预约界面";
				this_thread::sleep_for(duration);
				system("cls");
				sreserve_control();
				
			}
			else //返回函数select_seat() 
			{
				cout << "您已取消预约!"<<endl;
				system("pause");
				chrono::seconds duration(1);
				this_thread::sleep_for(duration);
				cout << "即将返回预约界面";
				system("cls");
				sreserve_control();
			}
	
};
//餐位修改(连接数据库)(修改位置或者时间段，或者取消预约)*完善
void customer::revise_seat() {
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	while (true)
	{
		cout << "1.修改预定餐位" << endl;
		cout << "2.取消预约" << endl;
		cout << "0.回到主界面" << endl;
		int choice;
		cin >> choice;
		if(choice==0)
		{
			control();
			break;
		}
		switch (choice)
		{
		case 1://修改位置
		{
			system("cls");
			cout << "下列餐位可预约:" << endl;
			chrono::seconds duration(1);
			this_thread::sleep_for(duration);
			select_seat();
			system("pause");
			cout << "选择新的餐位号和时间段:";
			int num;
			string time1;
			cin >> num;
			cin >> time1;
			//修改个人信息座位号
			string strQuery = "update ";
			strQuery.append(name);
			strQuery.append("_information set Seat_ID=");
			string snum = to_string(num);
			strQuery.append(snum);
			mysql_query(&mysql, strQuery.c_str());
			//修改个人信息时间
			 strQuery = "update ";
			strQuery.append(name);
			strQuery.append("_information set pre_time='");
			strQuery.append(time1);
			strQuery.append("';");
			if (0 == mysql_query(&mysql, strQuery.c_str()))
			{
				cout << "修改成功!" << endl;
			}
			//更改座位预约状态
			strQuery = "update seats set 预约状态='否' where ID=";
			string ssid = to_string(seatid);
			strQuery.append(ssid);
			strQuery.append(";");
			mysql_query(&mysql, strQuery.c_str());
			seatid = num;
			strQuery = "update seats set 预约状态='是' where ID=";
			strQuery.append(snum);
			strQuery.append(";");
			mysql_query(&mysql, strQuery.c_str());
			cout << "即将回到上个页面" << endl;
			this_thread::sleep_for(duration);
			system("pause");
			system("cls");
		}
		break;
		case 2://取消预约
		{
			int num;
			cout << "输入您要取消的座位号:";
			cin >> num;
			string snum = to_string(num);
			string strQuery = "delete from ";
			strQuery.append(name);
			strQuery.append("_information where Seat_ID=");
			strQuery.append(snum);
			strQuery.append(";");
			if (0 == mysql_query(&mysql, strQuery.c_str()))
			{
				cout << "取消成功!" << endl;
			}
			cout << "即将回到上个页面" << endl;
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
//菜品查询(连接数据库)*完善
void customer::select_dish() 
{
	MYSQL mysql;
	vector<vector<string>> data;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string queryStr = "select * from dish where 是否上架='是'; ";
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

	cout << "菜单查询成功" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
};
//预约菜品界面应有选择数量和支付定金功能，支付定金才算预约成功
void customer::reserve_dish() 
{
	//先看菜单
	select_dish();
	cin.clear();
	cin.ignore(10124, '\n');
	cout << "输入您要预定的菜名:";
	string pre_dish;
	cin >> pre_dish;
	cout << "输入您要预定该菜的数量:";
	int act_dish;
	cin >> act_dish;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	
	//计算菜品价格
	vector<vector<string>> data;
	string queryStr = "select price from dish where name=' ";
	queryStr.append(pre_dish);
	queryStr.append("';");
	mysql_query(&mysql, queryStr.c_str());
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
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j];
		}
		cout << endl;
	}
	int totalprice=0;//总价
	cout << "请问是否预约" << endl;
	string ans;
	cin >> ans;
	if (ans == "是")
	{
		string queryStr = "insert into ";
		queryStr.append(name);
		queryStr.append("_information (dish_name,dish_act) values(' ");
		queryStr.append(pre_dish);
		queryStr.append("',");
		string sact_dish = to_string(act_dish);
		queryStr.append(sact_dish);
		queryStr.append(");");
		mysql_query(&mysql, queryStr.c_str());//菜品的信息插入到个人信息库里
		cout << "预约成功!" << endl;
		system("pause");
		mysql_close(&mysql);
		cout << "即将回到上一个页面" << endl;
		chrono::seconds duration(1);
		this_thread::sleep_for(duration);
		system("cls");
		dreserve_control();
	}
	if (ans == "否")
	{
		mysql_close(&mysql);
		system("pause");
		cout << "即将回到上一个页面" << endl;
		chrono::seconds duration(1);
		this_thread::sleep_for(duration);
		system("cls");
		dreserve_control();
	}
};
//菜品预约界面
void customer::dreserve_control()
{
	while (true)
	{
		cout << "1.进行菜品预约" << endl;
		cout << "2.返回主界面" << endl;
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
			cout << "请进行有效操作" << endl;;
			break;
		}
		if (a == 1 || a == 2)
		{
			break;
		}
	}
};
//菜品修改界面
void customer::revise_dishctr() 
{
	while (true)
	{
		cout << "1.进行菜品修改" << endl;
		cout << "2.返回主界面" << endl;
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
			cout << "请进行有效操作" << endl;;
			break;
		}
		if (a == 1 || a == 2)
		{
			break;
		}
	}
};
//菜品修改(连接数据库)(取消预约或修改数量)
void customer::revise_dish() 
{
	//访问个体
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	while (true)
	{
		cout << "1.修改菜品数量" << endl;
		cout << "2.取消预约" << endl;
		cout << "0.返回上一个界面" << endl;
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
			cout << "请输入您要修改的菜品的名字:";
			string dish_name;
			cin >> dish_name;
			cout << "请输入您要修改的菜品的数量:";
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
				cout << "修改成功!" << endl;
			}
			system("pause");
		}
		break;
		case 2:
		{
			cout << "请输入您要取消的菜名:";
			string dish_name;
			string queryStr = "delete from ";
			queryStr.append(name);
			queryStr.append("_information where name ='");
			queryStr.append(dish_name);
			queryStr.append("';");
			if (0 == mysql_query(&mysql, queryStr.c_str()))
			{
				cout << "删除成功!" << endl;
			}
			system("pause");
		}
		break;
		default:
			break;
		}
	}
};
//访问已预约菜品
void customer::finish_dish() 
{
	vector<vector<string>>data;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string queryStr = "select dish_name,dish_act from ";
	queryStr.append(name);
	queryStr.append("_information;");;
	mysql_query(&mysql, queryStr.c_str());
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

	cout << "您已预约:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
	cout << "即将回到主页面" << endl;
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
	system("cls");
	control();
};
void customer::finish_seat() 
{
	vector<vector<string>>data;
	MYSQL mysql;
	mysql_init(&mysql);//初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置字符编码 
	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败";
		exit(-1);
	}
	string queryStr = "select Seat_ID,pre_time from ";
	queryStr.append(name);
	queryStr.append("_information;");;
	mysql_query(&mysql, queryStr.c_str());
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

	cout << "您已预约:" << endl;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
	mysql_close(&mysql);
	system("pause");
	cout << "即将回到主页面" << endl;
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
	system("cls");
	control();
};
//创建个人餐位预约信息库(注册账号的时候就应使用)
void customer::Create_DB()
{
	MYSQL mysql;
	mysql_init(&mysql); // 初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); // 设置字符编码 

	if (mysql_real_connect(&mysql, "127.0.0.1", "AccyCx", "ycy0050307", "餐厅数据库", 3306, NULL, 0) == NULL)
	{
		cout << "餐厅顾客信息库连接失败" << endl;
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
		cout << "表格创建成功！" << endl;
	}
	else
	{
		cout << "表格创建失败！" << endl;
		cout << mysql_error(&mysql) << endl; // 输出错误信息
	}

	mysql_close(&mysql);
}