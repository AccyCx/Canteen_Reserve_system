#pragma once
#include <string>
#include <iostream>
#include <vector>
#include<conio.h>//getch()������ͷ�ļ�
using namespace std;

// ʵ�ֽ�ÿ��ע�����Ϣ�洢�����ݿ��У��ṩȨ�޸�manager�鿴
class customer
{
private:
	string password;
	long long int phonenumber;
public:
	long long int account;
	int seatid;//ԤԼ�Ĳ�λ��
	string seattime;//ԤԼ��ʱ��
	string name;
	//���캯�� 
	customer();
	//��½�������� 
	void control();
	//������Ϣ��ѯ(������)
	void select_information();
	//������Ϣ�޸�(������)
	void revise_information();
	//��λ��ѯ(�������ݿ�)
	void select_seat();
	//��λԤԼ 
	void reserve_seat();
	//��λ�޸�(�������ݿ�)
	void revise_seat();
	//��Ʒ��ѯ(�������ݿ�)
	void select_dish();
	//��ƷԤԼ
	void reserve_dish();
	//��ƷԤԼ����
	void dreserve_control();
	//��Ʒ�޸Ľ���
	void revise_dishctr();
	//��Ʒ�޸�(�������ݿ�)
	void revise_dish();
	//��¼����(��ʵ�������˻���¼)
	void manager_login();
	//ע�Ṧ��(������)
	void manager_register();
	//��ע�����Ϣ�洢�����ݿ���(������)
	void Insert_DB();
	// ��������ԤԼ��Ϣ��
	void Create_DB();
	//�鿴��ԤԼ��Ʒ��Ϣ
	void finish_dish();
	//�鿴��ԤԼ��λ��Ϣ
	void finish_seat();
	//��λԤԼ��������
	void sreserve_control();
	//��������
	~customer();
};

