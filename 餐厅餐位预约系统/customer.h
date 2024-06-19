#pragma once
#include <string>
#include <iostream>
#include <vector>
#include<conio.h>//getch()函数的头文件
using namespace std;

// 实现将每个注册的信息存储到数据库中，提供权限给manager查看
class customer
{
private:
	string password;
	long long int phonenumber;
public:
	long long int account;
	int seatid;//预约的餐位号
	string seattime;//预约的时间
	string name;
	//构造函数 
	customer();
	//登陆后操作面板 
	void control();
	//个人信息查询(已完善)
	void select_information();
	//个人信息修改(已完善)
	void revise_information();
	//餐位查询(连接数据库)
	void select_seat();
	//餐位预约 
	void reserve_seat();
	//餐位修改(连接数据库)
	void revise_seat();
	//菜品查询(连接数据库)
	void select_dish();
	//菜品预约
	void reserve_dish();
	//菜品预约界面
	void dreserve_control();
	//菜品修改界面
	void revise_dishctr();
	//菜品修改(连接数据库)
	void revise_dish();
	//登录功能(需实现已有账户登录)
	void manager_login();
	//注册功能(已完善)
	void manager_register();
	//将注册的信息存储进数据库里(已完善)
	void Insert_DB();
	// 创建个人预约信息库
	void Create_DB();
	//查看已预约菜品信息
	void finish_dish();
	//查看已预约座位信息
	void finish_seat();
	//餐位预约操作界面
	void sreserve_control();
	//析构函数
	~customer();
};

