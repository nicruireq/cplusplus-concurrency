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

class thread_guard
{
	thread& t;
public:
	explicit thread_guard(thread& t_) :
		t(t_) {}
	~thread_guard()
	{
		if (t.joinable())
			t.join();
	}
	thread_guard(thread_guard const&) =delete;
	thread_guard& operator=(thread_guard const&) =delete;
};

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
    int var_local = 0;		// var local
	prueba p1(var_local);	// crea instancia clase callable
	thread t1(p1);			// crea hilo con instancia de clase callable y lo lanza
    // t1.join(); no necesito poner los join en cada camino posible de salida de la funcion
	//utilizo la clase thread_guard para asegurar que se hace join antes de que la funcion 
	// local acabe y mate la variable local 
	thread_guard guard(t1);
    
	for (int i=0; i<100;++i)		// la funcion actual hace sus cosas mientras t1 se ejecuta concurrentemente
        cout << "lanzahilos() esta haciendo cosas...\n";
    /*
	 * cuando la funcion actual vaya a salir de ambito llamara los destructores de las 
	 * var. locales en orden inverso a como se instanciaron, asi lo primero que hara esta
	 * llamar al destructor de la clase thread_guard para el objeto guard 
	 * que se asegura de hace join al hilo t1 si no se hubiera hecho 
	 * actua igual si se produjera una excepcion en esta funcion 
	*/
	
    cout << "terminando lanzahilos()...\n";
}

int main()
{
    cout << "comenzando main...\n";
    lanzahilos();
    cout << "terminando main...\n";
}
