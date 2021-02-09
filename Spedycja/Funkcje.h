#include <iostream>
#include <string>
#include <limits.h>
#include <fstream>   
#include <algorithm>
#include <cfloat>

using namespace std;
struct city;
/**struktura zawiera wskaŸnik do wêz³a i koszt dotarcia do niego z wêz³a macierzystego(reprezentuje krawêdŸ miêdzy wêz³ami);element listy*/
struct connect
{
	city* point = nullptr;///<wskaŸnik na wêze³ koñcowy
	connect* next = nullptr;///< wskaŸnik na nastêpny element listy
	double dist;///< okreœla wartoœæ po³¹czenia miêdzy wêz³ami

};
/**struktura reprezentuje wêze³ grafu;element drzewa oraz g³ównej kolejki priorytetowej*/
struct city
{
	string name;///< nazwa wêz³a
	double cost = DBL_MAX;///<koszt dotarcia do wêz³a - domyœlnie nieskoñczonoœæ
	bool vist = false;///< zmienna okreœlaj¹ca czy wêze³ zosta³ ju¿ odwiedzony (czy wyznaczono do niego najkrótsz¹ œcie¿kê)
	city* nextL = nullptr;///<  wskaŸnik na lewego potomka w drzewie
	city*nextR = nullptr;///< wskaŸnik na prawego potomka w drzewie
	city*nextD = nullptr;///<  wskaŸnik na nastêpnik w kolejce priorytetowej
	city*pred = nullptr;///< wskaŸnik na poprzednik(œcie¿ka w grafie)
	connect* poss = nullptr;///< wskaŸnik na g³owê listy elementow reprezentujacych krawêdzie w grafie 
};
/** Funkcja sczytuje dane z pliku i wywo³uje dla nich funkcje dodaj¹ce do struktur danych - drzewa i listy.
Funkcja sprawdza dane i w razie ich niepoprawnoœci wyœwietla komunikat o b³êdzie oraz ustawia odpowiednia zmienn¹ na wartoœæ false
@param path nazwa pliku z danymi
@param center nazwa centralnego wierzcho³ka grafu
@param pRoot wskaŸnik na korzeñ drzewa poszukiwañ binarnych
@param correct_data zmienna okreœlaj¹ca poprawnoœæ sczytywanych danych
*/
void graph_create(const string &path, const string &center, city* &pRoot, bool &correct_data);
/** Funkcja dodaje wierzcho³ek do drzewa poszukiwañ binarnych i zwraca wskaŸnik na niego.Drzewo jest posortowane wg kolejnosci alfabetycznej nazw wierzcho³ków.
@param cityA nazwa wierzcho³ka do dodania
@param center nazwa wierzcho³ka reprezentuj¹cego g³ówny wêze³ grafu(jest inicjalizowany innymi wartoœciami
ni¿ domyœlne tzn. pocz¹tkowy koszt dotarcia wynosi zero a nie nieskonczonoœc
@param pRoot wskaŸnik na korzeñ drzewa
@return wskaŸnik na nowo dodany element*/
city* add_city_tree(const string &cityA, const string &center, city*&pRoot);
/** Funkcja przyjmuje wskaŸniki na dwa elementy dodane jeden po drugim do drzewa i do listy jednego dodaje wskaznik na drugi.
Struktury w tych listach zawieraj¹ tez wartoœæ okreœl¹jac¹ odleg³oœæ miêdzy wêz³ami grafu reprezentowanymi przez wierzcho³ki.
@param cityA wskaŸnik na pierwszy wêze³
@param cityB wskaŸnik na drugi wêze³
@param val zmienna przechowuj¹ca odleg³oœæ miêdzy wez³ami
*/
void two_cities(city* &ptrA, city* &ptrB, double val);
/**Funkcja okreœla kolejnoœc alfabetyczn¹ dwóch napisów
@param one napis pierwszy
@param another napis drugi*/
bool alphabet(const string &one, const string &another);
/**Funkcja usuwa z pamiêci drzewo; dla ka¿dego wierzcho³ka wywo³uje funkcjê usuwaj¹c¹ listê
@param pRoot korzeñ drzewa*/
void tree_delete(city* &pRoot);
/**Funkcja dla kolejnych elementów drzewa wywo³uje funkcje dodaj¹c¹ je do kolejki priorytetowej
@param pRoot korzeñ drzewa
@param pList wskaŸnik na g³owê kolejki
*/
void search_tree(city* &pRoot, city* &pList);
/** Funkcja dodaje element do listy nale¿¹cej do wêz³a w drzewie.
@param pHead wskaŸnik na g³owê listy
@param add wskaŸnik  do przechowywania w  dodawanym elemencie
@param val wartoœc do przechowywania w  dodawanym elemencie*/
void add_list(connect* &pHead, city* add, double val);
/**Funkcja dodaje element do kolejki priorytetowej
@param pHead wskaŸnik na g³owê kolejki
@param another wskaŸnik na nowy element
*/
void dijkstra_queue(city* &pHead, city* &another);
/**Funkcja iteruje przez listy dla wszystkich elemntów kolejki priorytetowej,aktualizuje koszty dojœcia wêz³ów przez nie wskazywanych ,ustawia poprzedniki
tych wêz³ów oraz wywo³uje funkcje aktualizuj¹ce ich pozycjê w kolejce;
tworzy rownie¿ listê wynikow¹. Jest to najwa¿niejsza funkcje w programie odpowiedzialna za g³ówn¹ czêœæ realizacji algorytmu
@param pHead wskaŸnik na g³owê kolejki priorytetowej
@param out wskaŸnik na g³owê listy wynikowej*/
void dijkstra(city* &pHead, city* &out);
/** Funkcja usuwa element z kolejki priorytetowej ustawiaj¹c wskaŸnik jego poprzednika na jego nastêpnik
@param pHead wskaŸnik na g³owê kolejki priorytetowej
@param elem nazwa usuwanego elementu
*/
void dijkstra_update(city* pHead, const string &elem);
/** Funkcja dodaje element do listy wynikowej i zmienia jego parametr vist na wartoœæ true
@param pHead wskaŸnik na dodawany element
@param wskaŸnik na g³owê listy wynikowej*/
void output_add(city* pHead, city*&out);
/**Funkcja wypisuje elementy listy wynikowej do pliku w odpowiednim formacie
@param pOut wskaŸnik na g³owê listy
@param nazwa g³ównego elementu
@param path nazwa pliku wynikowego*/
void create_routes(city* &pOut, const  string &center, const string &path);
/** Funkcja usuwa listê
@param pStart wskaŸnik na glowe listy
*/
void list_delete(connect* &pStart); 
