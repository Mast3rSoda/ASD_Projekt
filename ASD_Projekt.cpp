#include <iostream>
using namespace std;

struct two3
{
	string miasto1, miasto2, miasto3;
	two3* root = NULL;
	two3* left = NULL;
	two3* middle = NULL;
	two3* right = NULL;
};
void insert(string data)
{


}

int main()
{
	two3 drzewo;
	int input;
	string miasto;
	cout << "Wybierz:\n1) Aby dodac\n2) Aby usunac\n3) Aby znalezc\n4) Aby znalezc liczbe\n";
	cin >> input;
	if (input == 1)
	{
		cout << "Podaj nazwe miasta\n";
			cin >> miasto;
	}
	else if (input == 2)
	{
		cout << "Podaj nazwe miasta do usuniecia\n";
		cin >> miasto;
	}
	else if (input == 3)
	{
		cout << "Podaj nazwe miasta\n";
		cin >> miasto;
	}
	else if (input == 4)
	{
		cout << "Podaj prefiks\n";
		cin >> miasto;
	}
}