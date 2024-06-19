#pragma once
#include <string>
#include <mysql.h>
#include <vector>
#include <iostream>
using namespace std;
class manager
{
private:
	const int account=123456;
	const string password="abc123";
public:
	const string name="admin";
	const int phonenumber=123456;
	string ID;
	//构造函数
	manager();
	//析构函数
	~manager();
	//管理餐位面板
	void smanage_seat();
	//餐位管理(连接数据库)
	void manage_seat();
	//餐位查询
	void select_seat();
	//管理菜品面板
	void smanage_dish();
	//菜价管理
	void manage_dishprice();
	//上架管理
	void manage_dishsj();
	//菜品查询
	void select_dish();
	//查看顾客信息
	void select_customer();
	//登录功能
	void manager_login();
	//操作面板
	void control();

};

