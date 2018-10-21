// Example program
#include <iostream>
#include <string>
#include <thread>

using namespace std;

static int var {0};

void mifunc()
{
    ++var;
}

class prueba
{
public:
    prueba() : v(var) {}
    prueba(int& _v) : v(_v) {}
    void operator()()
    { 
        cout << "ejecutando hilo...\n";
		cout << "v antes de incrementar = "<< v <<"\n";
        for(int i=0;i<1000000;++i) ++v; 
		cout << "v despues de incrementar = "<< v <<"\n";
    }
private:
    int& v;
};

void lanzahilos()
{
    cout << "comenzando lanzahilos()...\n";
    thread t1{mifunc};
    //thread t2(prueba());      //lo interpreta como declaracion de funcion con un parametro de tipo puntero a funcion
    //thread t2( (prueba()) );  //elimina la ambiguedad
    thread t2{prueba()};        // con inicializador uniforme eliminamos la ambiguedad
    for (int i=0; i<100;++i)
        cout << "lanzahilos() esta haciendo cosas...\n";
    t1.join();
    t2.join();
    cout << "terminando lanzahilos()...\n";
}

int main()
{
    cout << "comenzando main...\n";
    lanzahilos();
    cout << "terminando main...\n";
}
