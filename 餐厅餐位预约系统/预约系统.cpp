#include "customer.h"
#include <string>
#include <iostream>
#include <vector>
#include<conio.h>
#include <chrono>
#include <thread>
#include <mysql.h>
#include <cstdlib>
#include <numeric>
#include "manager.h"
using namespace std;
int main()
{
	customer c;
	manager m;
	while (true)
	{
		system("cls");
		cout << "***************��ӭ����XX������ʳԤԼϵͳ*************" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    1.�˿͵�¼                      |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    2.����Ա��¼                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                    3.�˳�ϵͳ                      |" << endl;
		cout << "|                                                    |" << endl;
		cout << "|                                                    |" << endl;
		cout << "******************************************************" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			c.manager_login();
			break;
		case 2:
			system("cls");
			m.manager_login();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout << "�������Ч����!" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}