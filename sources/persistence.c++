// C++ Libs
///////////
#include <list>
#include <iostream>
#include <string>
using namespace std;

// ANSI C Libs
//////////////
#include <string.h>

// External Libs
////////////////
#include <sqlite3.h>

// Local Libs
/////////////
#include <main.h>
#include <entities.h>
#include <persistence.h>

// SQLITE INTERFACE
///////////////////

class ElementoResultado {
	private:
	        string nomeColuna;
	        string valorColuna;
	public:
		void setNomeColuna(const string& nomeColuna) {
		        this->nomeColuna = nomeColuna;
		}
		void setValorColuna(const string& valorColuna){
		        this->valorColuna = valorColuna;
		}
		inline string getNomeColuna() const {
		        return nomeColuna;
		}
	
		inline string getValorColuna() const {
		        return valorColuna;
		}
};

class SQLiteBase: public SQLInterface {
	private:
		sqlite3 *base;
		int rc;
		char * msg;
	protected:
		static list<ElementoResultado> listaResultado;
		string command;
	public:
		bool Login (Developer *);
		
		SQLiteBase () {
			rc = sqlite3_open("revisionsdb", &base);
			// if (sqlite3_open(nomeBancoDados, &bd) != SQLITE_OK)
			if (rc != SQLITE_OK)
				throw invalid_argument("NOT ABLE TO STABLISH SQL CONNECTION");
		}
		
		~SQLiteBase () {
			rc = sqlite3_close(base);
			// if (sqlite3_close(bd) != SQLITE_OK)
			if (rc != SQLITE_OK)
				throw invalid_argument("NOT ABLE TO KILL SQL CONNECTION");
		}
		
		void Run () {
			cout << "PROCEDURE 1";
			
			rc = sqlite3_exec(base, command.c_str(), SQLcallback, 0, &msg);
			// if (sqlite3_exec(base, command.c_str(), SQLcallback, 0, &msg) != SQLITE_OK)
			if (rc != SQLITE_OK)
				throw invalid_argument("RUNTIME ERROR ON SQL");
		}
		
		static int SQLcallback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
			NotUsed=0;
			ElementoResultado elemento;
			for(int i = 0; i < argc; i++){
				elemento.setNomeColuna(nomeColuna[i]);
				elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
				listaResultado.push_front(elemento);
			}
			return 0;
		}
		
		string GetPassword (string email) {
			string password;
			ElementoResultado resultado;
			
			command = "SELECT password FROM developers WHERE email = ";
			command += email;
			
			Run();
			
			cout << "PROCEDURE 2";
	        if (listaResultado.empty())
	                throw invalid_argument("EMPTY LIST");
	        resultado = listaResultado.back();
	        listaResultado.pop_back();
	        password = resultado.getValorColuna();
			
			return password;
		}
}; list<ElementoResultado> SQLiteBase::listaResultado;

// SINGLETON STATEMENTS
///////////////////////

SQLInterface * SQLInterface::p_instance = 0;

SQLInterface * SQLInterface::instance (int FLAGS) {
	if (p_instance) delete p_instance;
	
	while (true) {
		try {
			//if (FLAGS & FILEBASE)
			//	p_instance = new class FileBase;
			//else
			p_instance = new SQLiteBase;
		
			break;
		}
		catch (sql_error error) {
			cout << "ERRO!";
		}
	}
	
	
	return p_instance;
}

SQLInterface * SQLInterface::instance () {
	if (p_instance) return p_instance;
	return instance (0);
}
