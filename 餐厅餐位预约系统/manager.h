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
	//���캯��
	manager();
	//��������
	~manager();
	//�����λ���
	void smanage_seat();
	//��λ����(�������ݿ�)
	void manage_seat();
	//��λ��ѯ
	void select_seat();
	//�����Ʒ���
	void smanage_dish();
	//�˼۹���
	void manage_dishprice();
	//�ϼܹ���
	void manage_dishsj();
	//��Ʒ��ѯ
	void select_dish();
	//�鿴�˿���Ϣ
	void select_customer();
	//��¼����
	void manager_login();
	//�������
	void control();

};

