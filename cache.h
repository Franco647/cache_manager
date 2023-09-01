#ifndef CACHE
#define CACHE
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

string RELATIVE_PATH = "/Users/franc/Escritorio/Cache_Manager/data.txt";

template<class T>
class CacheManager {
//members (private)
    map <string, pair<T, int>> cache_data; //<Clave , <Obj, Indice de Uso>>
    int capacity;
    int MRU = 10;

    public:
        CacheManager(int); //recibe la capacidad en el int

        void insert(string key, T obj);
        void show_cache();
        bool write_file();
        T get(string key);

        // Agregar todas las funciones necesarias

        bool esClaveExistente(string);
        bool estaLleno();
        string obtenerLRU();
        void listaValoresUsoFrec();
};

// Constructor clase
template <class T>
CacheManager <T> :: CacheManager(int cap) {
    capacity = cap;
}

// Esta parte hace referencia a que se imprime la informacion mas relevante por la pantalla
template <class T>
void CacheManager <T> :: show_cache() {
    for (auto x : cache_data) {
        int valor_actual = x.second.second;

        cout << "El elemento con key \"" << x.first << "\""
             << "\n\tPosee un valor de uso frecuente = " << valor_actual << endl;
        cout << "\tNombre: " << x.second.first.getData()
             << "\n\tID: " << x.second.first.getId() << '\n' << endl;
    }
}

// Checkear a partir de la key si en necesario escribir la 'ram'
template <class T>
bool CacheManager <T> :: write_file() {
    ofstream miArchivo;
    miArchivo.open(RELATIVE_PATH, ios::out);

    if (miArchivo.fail()) {
        cout << "Error: no se pudo acceder al archivo.";
        exit(1);
    }
    for (auto x : cache_data) {
        miArchivo << x.first << " "
               << x.second.first.getId() << " "
               << x.second.first.getData() << " "
               << x.second.first.getValue() << endl;
    }
    miArchivo.close();
    return true;
}

//INSERT
// A partir de la key inserto un objeto en la cache y si es necesario escribir en la 'ram'
template <class T>
void CacheManager <T> :: insert(string key, T obj) {
    if (cache_data.empty()) {
        cache_data.insert(make_pair(key, make_pair(obj, MRU)));

        write_file()
            ? cout << "Exitoso: La informacion fue guardada correctamente." << endl
            : cout << "Error: Hubo un error al intentar guardar la informacion en la 'ram'." << endl;

    } else {
        if (esClaveExistente(key))  {
            cache_data.at(key).first = obj;
            cache_data.at(key).second = ++MRU;

            write_file()
                ? cout << "Exitoso: La informacion fue guardada correctamente." << endl
                : cout << "Error: Hubo un error al intentar guardar la informacion en la 'ram'" << endl;

        } else if (estaLleno()) {
            string key = obtenerLRU();
            cache_data.at(key).first = obj;
            cache_data.at(key).second = ++MRU;

// Despues, reescribimos el archivo para que la informacion sea consistente.
            write_file()
                ? cout << "Exitoso: La informacion fue guardada correctamente." << endl
                : cout << "Error: Hubo un error al intentar guardar la informacion en la 'ram'" << endl;

        } else {
            cache_data.insert(make_pair(key, make_pair(obj, ++MRU)));

            write_file()
                ? cout << "Exitoso: La informacion fue guardada correctamente." << endl
                : cout << "Error: Hubo un error al intentar guardar la informacion en la 'ram'" << endl;
        }
    }
}

// Aqui, a partir de la key obtengo un objeto de la cache o de la 'ram'.
template <class T>
T CacheManager <T> :: get(string key) {
    if (!esClaveExistente(key)) {
        throw  std::invalid_argument("Error: Key invalida.");
    }

    cache_data.at(key).second = ++MRU;
    return cache_data.at(key).first;
}

// Devuelvo la key del elemento almacenado en la cache que tiene el valor de uso mas bajito.
template <class T>
string CacheManager <T> :: obtenerLRU() {
    string lru_key = "";
    int LRU = MRU;

    for (auto x : cache_data) {
        auto pair_elemento = x.second;

        if (LRU > pair_elemento.second) {
            lru_key = x.first;
            LRU = pair_elemento.second;
        }
    }
    return lru_key;
}

// Lista por pantalla los elementos de la cache y sus respectivos valores de uso.
template <class T>
void CacheManager <T> :: listaValoresUsoFrec() {
    for (auto x : cache_data) {
        int valor_actual = x.second.second;
        cout << "Elemento " << x.first
             << " Posee un valor de uso frecuente = " << valor_actual << endl;
    }
    cout << "\n" << endl;
}

// Checkea si la clave corresponde a un objeto ya almacenado en la cache.
template <class T>
bool CacheManager <T> :: esClaveExistente(string key) {
    for (auto x : cache_data) {
        if (key == x.first) {
            return true;
        }
    }
    return false;
}

// Por ulitmo, checkea si la cache esta llena o no.
template <class T>
bool CacheManager <T> :: estaLleno() {
    return (int)cache_data.size() == capacity;
}

#endif
