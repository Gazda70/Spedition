#include <iostream>
#include <string>
#include <limits.h>
#include <fstream>   
#include <algorithm>
#include <cfloat>

using namespace std;
struct city;
/**struktura zawiera wska�nik do w�z�a i koszt dotarcia do niego z w�z�a macierzystego(reprezentuje kraw�d� mi�dzy w�z�ami);element listy*/
struct connect
{
	city* point = nullptr;///<wska�nik na w�ze� ko�cowy
	connect* next = nullptr;///< wska�nik na nast�pny element listy
	double dist;///< okre�la warto�� po��czenia mi�dzy w�z�ami

};
/**struktura reprezentuje w�ze� grafu;element drzewa oraz g��wnej kolejki priorytetowej*/
struct city
{
	string name;///< nazwa w�z�a
	double cost = DBL_MAX;///<koszt dotarcia do w�z�a - domy�lnie niesko�czono��
	bool vist = false;///< zmienna okre�laj�ca czy w�ze� zosta� ju� odwiedzony (czy wyznaczono do niego najkr�tsz� �cie�k�)
	city* nextL = nullptr;///<  wska�nik na lewego potomka w drzewie
	city*nextR = nullptr;///< wska�nik na prawego potomka w drzewie
	city*nextD = nullptr;///<  wska�nik na nast�pnik w kolejce priorytetowej
	city*pred = nullptr;///< wska�nik na poprzednik(�cie�ka w grafie)
	connect* poss = nullptr;///< wska�nik na g�ow� listy elementow reprezentujacych kraw�dzie w grafie 
};
/** Funkcja sczytuje dane z pliku i wywo�uje dla nich funkcje dodaj�ce do struktur danych - drzewa i listy.
Funkcja sprawdza dane i w razie ich niepoprawno�ci wy�wietla komunikat o b��dzie oraz ustawia odpowiednia zmienn� na warto�� false
@param path nazwa pliku z danymi
@param center nazwa centralnego wierzcho�ka grafu
@param pRoot wska�nik na korze� drzewa poszukiwa� binarnych
@param correct_data zmienna okre�laj�ca poprawno�� sczytywanych danych
*/
void graph_create(const string &path, const string &center, city* &pRoot, bool &correct_data);
/** Funkcja dodaje wierzcho�ek do drzewa poszukiwa� binarnych i zwraca wska�nik na niego.Drzewo jest posortowane wg kolejnosci alfabetycznej nazw wierzcho�k�w.
@param cityA nazwa wierzcho�ka do dodania
@param center nazwa wierzcho�ka reprezentuj�cego g��wny w�ze� grafu(jest inicjalizowany innymi warto�ciami
ni� domy�lne tzn. pocz�tkowy koszt dotarcia wynosi zero a nie nieskonczono�c
@param pRoot wska�nik na korze� drzewa
@return wska�nik na nowo dodany element*/
city* add_city_tree(const string &cityA, const string &center, city*&pRoot);
/** Funkcja przyjmuje wska�niki na dwa elementy dodane jeden po drugim do drzewa i do listy jednego dodaje wskaznik na drugi.
Struktury w tych listach zawieraj� tez warto�� okre�l�jac� odleg�o�� mi�dzy w�z�ami grafu reprezentowanymi przez wierzcho�ki.
@param cityA wska�nik na pierwszy w�ze�
@param cityB wska�nik na drugi w�ze�
@param val zmienna przechowuj�ca odleg�o�� mi�dzy wez�ami
*/
void two_cities(city* &ptrA, city* &ptrB, double val);
/**Funkcja okre�la kolejno�c alfabetyczn� dw�ch napis�w
@param one napis pierwszy
@param another napis drugi*/
bool alphabet(const string &one, const string &another);
/**Funkcja usuwa z pami�ci drzewo; dla ka�dego wierzcho�ka wywo�uje funkcj� usuwaj�c� list�
@param pRoot korze� drzewa*/
void tree_delete(city* &pRoot);
/**Funkcja dla kolejnych element�w drzewa wywo�uje funkcje dodaj�c� je do kolejki priorytetowej
@param pRoot korze� drzewa
@param pList wska�nik na g�ow� kolejki
*/
void search_tree(city* &pRoot, city* &pList);
/** Funkcja dodaje element do listy nale��cej do w�z�a w drzewie.
@param pHead wska�nik na g�ow� listy
@param add wska�nik  do przechowywania w  dodawanym elemencie
@param val warto�c do przechowywania w  dodawanym elemencie*/
void add_list(connect* &pHead, city* add, double val);
/**Funkcja dodaje element do kolejki priorytetowej
@param pHead wska�nik na g�ow� kolejki
@param another wska�nik na nowy element
*/
void dijkstra_queue(city* &pHead, city* &another);
/**Funkcja iteruje przez listy dla wszystkich elemnt�w kolejki priorytetowej,aktualizuje koszty doj�cia w�z��w przez nie wskazywanych ,ustawia poprzedniki
tych w�z��w oraz wywo�uje funkcje aktualizuj�ce ich pozycj� w kolejce;
tworzy rownie� list� wynikow�. Jest to najwa�niejsza funkcje w programie odpowiedzialna za g��wn� cz�� realizacji algorytmu
@param pHead wska�nik na g�ow� kolejki priorytetowej
@param out wska�nik na g�ow� listy wynikowej*/
void dijkstra(city* &pHead, city* &out);
/** Funkcja usuwa element z kolejki priorytetowej ustawiaj�c wska�nik jego poprzednika na jego nast�pnik
@param pHead wska�nik na g�ow� kolejki priorytetowej
@param elem nazwa usuwanego elementu
*/
void dijkstra_update(city* pHead, const string &elem);
/** Funkcja dodaje element do listy wynikowej i zmienia jego parametr vist na warto�� true
@param pHead wska�nik na dodawany element
@param wska�nik na g�ow� listy wynikowej*/
void output_add(city* pHead, city*&out);
/**Funkcja wypisuje elementy listy wynikowej do pliku w odpowiednim formacie
@param pOut wska�nik na g�ow� listy
@param nazwa g��wnego elementu
@param path nazwa pliku wynikowego*/
void create_routes(city* &pOut, const  string &center, const string &path);
/** Funkcja usuwa list�
@param pStart wska�nik na glowe listy
*/
void list_delete(connect* &pStart); 
