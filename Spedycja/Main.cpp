
#include "Funkcje.h"
#include <cstring>
using namespace std;
int main(int argc, char* params[])
{
	const char str1[] = "-i"; ///< prze³acznik do podania przed nazwa²pliku z danymi wej´sciowymi
	const char str2[] = "-o"; ///< prze³a²cznik do podania przed nazwa²pliku z danymi wynikowymi
	const char str3[] = "-s"; ///< prze³acznik do podania przed nazwa²miasta - centrali
	string wejscie; ///< plik z danymi wejsciowymi - lista mozliwych polaczen
	string wyjscie; ///< plik z danymi wyjsciowymi - polaczenia miast z centrala
	string centrala; ///< nazwa z okresleniem centrali
	city* start = nullptr;///< wskaznik na glowe drzewa city
	city* queue = nullptr; ///< wskaznik na glowe kolejki priorytetowej(listy)
	city* output = nullptr; ///< wskaznik na glowe listy wynikowej
	bool correct_data = true;
	for (int k = 1; k < argc; k += 2)
	{
		if (!(strcmp(params[k], str1)))
		{
			wejscie = params[k + 1];
		}
		else if (!(strcmp(params[k], str2)))
		{
			wyjscie = params[k + 1];
		}
		else if (!(strcmp(params[k], str3)))
		{
			centrala = params[k + 1];
		}
	}
	if (wejscie == "" || wyjscie == "" || centrala == "")
	{
		correct_data = false;
	}
	if (correct_data)
	{
		graph_create(wejscie, centrala, start, correct_data);
		if (correct_data)
		{
			search_tree(start, queue);
			dijkstra(queue, output);
			create_routes(output, centrala, wyjscie);
		}
		tree_delete(start);
	}
	if (!correct_data)
	{
		cout << "Niepoprawne dane";
		cin.get();
		cin.get();
	}

	return(0);
}