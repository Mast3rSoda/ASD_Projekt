#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <set>
#define maxInt 200000000

using namespace std;

map <string, vector<pair<string, int>>> lista;

ifstream plikWe("plik.txt");
ofstream plikWy("wynik.txt");
typedef pair<string, int> PSI;
struct bst //basic bst structure
{
	string miasto = "";
	bst* left = NULL;
	bst* right = NULL;
	bool odw = false;
};

struct bst* newBst(string data) //creates new bst node
{
	struct bst* newNode = new bst;
	newNode->miasto = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

struct bst* findNast(struct bst* tree) //finds the successor to given node
{
	struct bst* el = tree;
	while (el->left != NULL && el)
		el = el->left;
	return el;
}

struct bst* insert(string data, struct bst* tree) //adds city
{
	if (tree == NULL) //is first city
	{
		return newBst(data);
	}
	else if (data == tree->miasto)
	{
		return tree;
	}
	else if (data < tree->miasto)
	{
		tree->left = insert(data, tree->left);
	}
	else if (data > tree->miasto)
	{
		tree->right = insert(data, tree->right);
	}
	return tree; //returns address
}

struct bst* del(string data, struct bst* tree) //deletes city
{
	if (tree == NULL)
		return tree;
	if (data < tree->miasto)
	{
		tree->left = del(data, tree->left);
	}
	else if (data > tree->miasto)
	{
		tree->right = del(data, tree->right);
	}
	else //if city found
	{
		if (tree->right == NULL) //if has no right child
		{
			struct bst* el = tree->left;
			free(tree);
			return el;
		}
		else if (tree->left == NULL) //if has no left child
		{
			struct bst* el = tree->right;
			free(tree);
			return el;
		}
		struct bst* el = findNast(tree->right); //if has both children
		tree->miasto = el->miasto;
		tree->right = del(el->miasto, tree->right);
	}
	return tree;
}

struct bst* findMiasto(string data, struct bst* tree)
{
	if (data < tree->miasto)
	{
		if (tree->left == NULL)
		{
			plikWy << "NIE\n";
			return tree;
		}
		findMiasto(data, tree->left);
	}
	else if (data > tree->miasto)
	{
		if (tree->right == NULL)
		{
			plikWy << "NIE\n";
			return tree;
		}
		findMiasto(data, tree->right);
	}
	else if (data == tree->miasto)
	{
		plikWy << "TAK\n";
		return tree;
	}
}

int miastoCount;
struct bst* findPrefMiasta(string data, struct bst* tree) //count cities with given prefix
{
	if (tree->miasto.rfind(data, 0) == 0)
	{
		miastoCount++;
		if (tree->left == NULL && tree->right == NULL)
			return tree;
		if (tree->left != NULL)
			findPrefMiasta(data, tree->left);
		if (tree->right != NULL)
			findPrefMiasta(data, tree->right);
	}
	if (tree->miasto.compare(0, data.size(), data) > 0)
	{
		if (tree->left != NULL)
			findPrefMiasta(data, tree->left);
	}
	if (tree->miasto.compare(0, data.size(), data) < 0)
	{
		if (tree->right != NULL)
			findPrefMiasta(data, tree->right);
	}
}

void printTree(bst* tree, int spacja)
{
	if (tree == NULL)
		return;
	spacja += 8;
	printTree(tree->right, spacja);
	cout << endl;
	for (int i = 8; i < spacja; i++)
		cout << " ";
	if (tree->odw == false)
	{
		cout << tree->miasto << endl;
		tree->odw = true;
	}
	printTree(tree->left, spacja);
}
//void printTree(bst* tree)
//{
//	if (tree == NULL)
//		return;
//	printTree(tree->left);
//	cout << tree->miasto <<" ";
//	printTree(tree->right);
//}

void UD(string miasto, string miasto2)
{
	int i = 0;
	for (auto& vect : lista[miasto])
	{
		if (vect.first == miasto2)
		{
			lista[miasto].erase(lista[miasto].begin() + i);
			break;
		}
		else
			i++;
	}
	i = 0;
	for (auto& vect : lista[miasto2])
	{
		if (vect.first == miasto)
		{
			lista[miasto2].erase(lista[miasto2].begin() + i);
			break;
		}
		else
			i++;
	}
}

void dijkstra(string miasto, string miasto2, map<string, int>& odleglosc)
{
	set<pair<int, string>> q;
	q.insert(make_pair(0, miasto));
	for (auto iterator : lista)
	{
		if (iterator.first != miasto)
		{
			odleglosc[iterator.first] = maxInt;
			q.insert(make_pair(maxInt, iterator.first));
		}
	}
	odleglosc[miasto] = 0;
	while (!q.empty())
	{
		pair<int, string> i = *(q.begin());
		string it = i.second;
		q.erase(q.begin());
		for (auto vect : lista[it])
		{
			if (odleglosc[it] + vect.second < odleglosc[vect.first])
			{
				q.erase(make_pair(odleglosc[vect.first], vect.first));
				int at = odleglosc[it] + vect.second;
				odleglosc[vect.first] = at;
				q.insert(make_pair(odleglosc[vect.first], vect.first));
			}
		}
	}
	if (miasto2 != "")
	{
		if (odleglosc[miasto2] != maxInt)
			plikWy << odleglosc[miasto2] << endl;
		else
			plikWy << "NIE\n";
	}
}
int main() //driver code
{
	if (!plikWe)
		return 0;
	struct bst* root = NULL;
	string input, miasto, miasto2, miasto3;
	int dlugosc;
	while (!plikWe.eof())
	{
		plikWe >> input;
		if (input == "DM")
		{
			plikWe >> miasto;
			root = insert(miasto, root);
			lista[miasto].begin();
		}
		else if (input == "UM")
		{
			plikWe >> miasto;
			root = del(miasto, root);
			if (lista.count(miasto) > 0)
				lista.erase(miasto);
		}
		else if (input == "WM")
		{
			plikWe >> miasto;
			findMiasto(miasto, root);
		}
		else if (input == "LM")
		{
			miastoCount = 0;
			plikWe >> miasto;
			findPrefMiasta(miasto, root);
			plikWy << miastoCount << "\n";
		}
		else if (input == "WY")
		{
			printTree(root, 0);
		}
		else if (input == "DD")
		{
			plikWe >> miasto >> miasto2 >> dlugosc;
			if (lista.count(miasto) > 0 && lista.count(miasto2) > 0)
			{
				lista[miasto].push_back(make_pair(miasto2, dlugosc));
				lista[miasto2].push_back(make_pair(miasto, dlugosc));
			}
		}
		else if (input == "UD")
		{
			plikWe >> miasto >> miasto2;
			UD(miasto, miasto2);
		}
		else if (input == "ND")
		{
			plikWe >> miasto >> miasto2;
			map<string, int> odleglosc;
			dijkstra(miasto, miasto2, odleglosc);
		}
		else if (input == "IS")
		{
			int skrot = 0;
			plikWe >> miasto >> miasto2 >> miasto3 >> dlugosc;
			map<string, int> odleglosc;
			map<string, int> odleglosc2;
			dijkstra(miasto, "", odleglosc);
			lista[miasto2].push_back(make_pair(miasto3, dlugosc));
			lista[miasto3].push_back(make_pair(miasto2, dlugosc));
			dijkstra(miasto, "", odleglosc2);
			UD(miasto2, miasto3);
			typename map<string, int>::iterator i, y;
			for (i = odleglosc.begin(), y = odleglosc2.begin(); i != odleglosc.end(); i++, y++)
			{
				if (i->second != y->second)
					skrot++;
				if (skrot > 100)
				{
					plikWy << "100+" << endl;
					break;
				}
			}
			if (skrot <= 100)
				plikWy << skrot << endl;
		}
		//for (const auto& iterator : lista)
		//{
		//	cout << iterator.first << " = "; // keys
		//	for (const auto& vect : iterator.second)  // values vec
		//		cout << vect.first << "-" << vect.second << "\t";
		//	cout << std::endl;
		//}
	}
	plikWe.close();
	plikWy.close();
}