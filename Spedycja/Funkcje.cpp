#include "Funkcje.h"
using namespace std;
void graph_create(const string &path, const string &center, city* &pRoot, bool &correct_data)
{
	string cityA, cityB;
	double distance;
	city* temp1, *temp2;
	ifstream plik(path);
	if (plik)
	{
		while (!plik.eof() && correct_data)
		{

			plik >> cityA >> cityB >> distance;
			if (plik.fail() && !plik.eof())
			{
				correct_data = false;
			}
			if (distance <= 0)
			{
				correct_data = false;
			}
			temp1 = add_city_tree(cityA, center, pRoot);
			temp2 = add_city_tree(cityB, center, pRoot);
			two_cities(temp1, temp2, distance);

		}
		plik.close();
	}

}
city* add_city_tree(const string &cityA, const string &center, city* &pRoot)
{
	if (pRoot == nullptr)
	{
		if (cityA == center)
			pRoot = new city{ cityA,0,false,nullptr,nullptr };
		else
			pRoot = new city{ cityA,DBL_MAX,false,nullptr,nullptr };
		return pRoot;

	}
	if (pRoot->name == cityA)
	{
		return pRoot;
	}
	else
	{
		if (alphabet(cityA, pRoot->name))
			return add_city_tree(cityA, center, pRoot->nextR);
		else
			return	add_city_tree(cityA, center, pRoot->nextL);

	}
}
void two_cities(city* &ptrA, city* &ptrB, double val)
{
	add_list(ptrA->poss, ptrB, val);
	add_list(ptrB->poss, ptrA, val);
}
void add_list(connect* &pHead, city* add, double val)
{
	pHead = new connect{ add,pHead,val };
}
bool alphabet(const string &one, const string &another)
{
	int k = 0;
	while ((one[k] == another[k]) && (k < min(one.length(), another.length())))
		k++;
	if (one[k] > another[k])
		return true;
	return false;
}
void tree_delete(city* &pRoot)
{
	if (pRoot)
	{
		list_delete(pRoot->poss);
		tree_delete(pRoot->nextL);
		tree_delete(pRoot->nextR);
		delete pRoot;
		pRoot = nullptr;
	}
}
void list_delete(connect* &pStart)
{
	connect* temp = nullptr;
	while (pStart != nullptr)
	{
		temp = pStart;
		pStart = pStart->next;
		delete temp;
	}
}
void search_tree(city* &pRoot, city* &pList)
{
	if (pRoot)
	{
		dijkstra_queue(pList, pRoot);
		search_tree(pRoot->nextL, pList);
		search_tree(pRoot->nextR, pList);

	}
}
void dijkstra_queue(city* &pHead, city* &another)
{
	city* temp = pHead, *prev = NULL;
	while (temp && temp->cost < another->cost)
	{
		prev = temp;
		temp = temp->nextD;
	}
	another->nextD = temp;
	if (prev != nullptr)
		prev->nextD = another;
	else
		pHead = another;
}
void dijkstra(city* &pHead, city* &out)
{
	connect* temp1 = nullptr;
	city* outg = nullptr;
	while (pHead)
	{
		temp1 = pHead->poss;
		while (temp1 != nullptr)
		{

			if ((temp1->point->cost > pHead->cost + temp1->dist) && (!temp1->point->vist))
			{
				temp1->point->cost = temp1->dist + pHead->cost;
				temp1->point->pred = pHead;
				dijkstra_update(pHead, temp1->point->name);
				dijkstra_queue(pHead, temp1->point);

			}
			temp1 = temp1->next;
		}

		outg = pHead;
		pHead = pHead->nextD;
		output_add(outg, out);
	}
}
void dijkstra_update(city* temp2, const string &elem)
{
	city*prev = nullptr;
	city*help = nullptr;

	while (temp2&&temp2->name != elem)
	{
		prev = temp2;
		temp2 = temp2->nextD;
	}
	if (temp2 != nullptr)
		prev->nextD = temp2->nextD;
	else
		prev->nextD = nullptr;

}
void output_add(city* pHead, city*&out)
{
	pHead->vist = true;
	city* help = out;
	out = pHead;
	out->nextD = help;
}
void create_routes(city* &pOut, const string  &center, const string &path)
{
	ofstream output(path);
	while (pOut&&pOut->name != center)
	{
		city *iEnd = nullptr;
		city* move = pOut, *prev = nullptr;

		while (iEnd != pOut)
		{
			while (move != iEnd)
			{
				prev = move;
				move = move->pred;
			}
			output << prev->name;
			if (prev->name != pOut->name)
				output << " -> ";
			move = pOut;
			iEnd = prev;
		}
		output << ":" << " " << pOut->cost;
		output << endl;
		pOut = pOut->nextD;
	}
	output.close();
}