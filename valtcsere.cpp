#include <iostream>

using namespace std;

int main()
{
	int a = 1;
	int b = 2;
	cout << "Alap valtozok:" << endl;
	cout << " a: " << a << " b: " << b << endl;

	//Változók felcserélése
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	cout << "Cserelve: " << endl;
	cout << " a: " << a << " b: " << b << endl;
	
	//Visszacsere
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	cout << "Visszacsere: " << endl;
	cout << " a: " << a << " b: " << b << endl;

	return 0;
}
