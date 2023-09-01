#include "cache.h"

class Student
{
    int id;
    int value;
    const char *data;

public:
    static const string class_name; //Cada clase tiene un static llamado: class_name

    Student(int _key, int _value, const char *_data):
        id(_key), value(_value), data(_data) {}

    void print() {
        cout << "Student Object: " <<
        id << ", " << value << ", " << data << endl;
    }

    const char * getData() {
        return data;
    }

    int getValue() {
        return value;
    }

    int getId (){
        return id;
    }

    ~Student(){};
};
const string Student :: class_name = "StudentClass";

int main(){
    int cache_cap = 4;

    CacheManager<Student> my_cache(cache_cap);

    // Agregamos dos Students
    cout << "		----		INSERT 	----		" << endl;
    cout << "Se agregaran los dos primeros elementos a la cache." << '\n' << endl;
    my_cache.insert("1", Student(0, 22, "Franco Thobokholt."));
    my_cache.insert("2", Student(1, 25, "Tamara S."));
    cout << endl;

    // Checkeamos que los valores sean los esperados
    cout << "Mostramos contenido actual... " << endl;
    my_cache.show_cache();

    // Accedemos el elemento "0" por lo tanto queda con el MRU mas alto
    cout << "		----		GET 	----		" << endl;
    cout << "Se accede a uno de los students en la cache." << '\n' << endl;
    auto objFromClass = my_cache.get("1"); //not in cache but in filesystem
    cout << "Nombre del student: " << objFromClass.getData() << '\n' << endl;

    // Checkeamos nuevamente los valores y corroboramos lo anterior hecho
    cout << "Mostramos contenido actual... " << endl;
    my_cache.show_cache();

    // Agregamos dos estudiantes mas y colmamos la cache
    cout << "		----		INSERT 	----		" << endl;
    cout << "Se agregaran otros dos elementos a la cache." << '\n' << endl;
    my_cache.insert("3", Student(2, 17, "Nadia Moreno."));
    my_cache.insert("4", Student(3, 3, "Raquel Morales."));
    cout << endl;

    cout << "Mostramos contenido actual... " << endl;
    my_cache.show_cache();

    // Este quinto elemento necesariamente debe eliminar uno de los students anteriores
    cout << "		----		UPDATE 	----		" << endl;
    cout << "Un quinto elemento sera introducido a la cache de capacidad. 4" << '\n'
         << "por lo tanto el elemento menos usado fue reemplazado." << '\n' << endl;
    my_cache.insert("5", Student(4, 8, "Lionel Messi."));
    cout << endl;

    // Vemos que student fue eliminado para poder almacenar a Maria Rodriguez
    cout << "Mostramos contenido actual... " << endl;
    my_cache.show_cache();

    cout << "		----		UPDATE 	----		" << endl;
    cout << "Ingresamos otro elemento con una key existente" << '\n'
         << "por lo tanto habra una actualizacion." << '\n' << endl;
    my_cache.insert("4", Student(4, 8, "Angel DiMaria."));
    cout << endl;

    // Y, Vemos que el ultimo elemento ("3") fue actualizado
    cout << "Mostramos contenido actual... " << endl;
    my_cache.show_cache();

    return 0;
}
