#include <string.h>

#include <entities.h>
#include <persistence.h>
#include <main.h>

#include <list>
#include <iostream>
#include <string>
using namespace std;

// SQLITE INTERFACE
///////////////////

/*
list<ElementoResultado> SQLiteBase::listaResultado;

class ElementoResultado {
	private:
	        string nomeColuna;
	        string valorColuna;
	public:
		void ElementoResultado::setNomeColuna(const string& nomeColuna) {
		        this->nomeColuna = nomeColuna;
		}
		void ElementoResultado::setValorColuna(const string& valorColuna){
		        this->valorColuna = valorColuna;
		}
		inline string ElementoResultado::getNomeColuna() const {
		        return nomeColuna;
		}
	
		inline string ElementoResultado::getValorColuna() const {
		        return valorColuna;
		}
};
*/
class SQLiteBase: public SQLInterface {
	private:
		sqlite3 *base;
		int rc;
	protected:
		//static list<ElementoResultado> listaResultado;
		//string comandoSQL;
	public:
		bool Login (Developer *);
		SQLiteBase () {
			//rc = sqlite3_open("revisionsdb", &base);
			// if (sqlite3_open(nomeBancoDados, &bd) != SQLITE_OK)
			//if (rc != SQLITE_OK)
			//	throw CONNECT;
		}
		~SQLiteBase () {
			//rc = sqlite3_close(base);
			// if (sqlite3_close(bd) != SQLITE_OK)
			//if (rc != SQLITE_OK)
			//	throw DISCONNECT;
		}
		/*
		void Run () {
			rc = sqlite3_exec(base, comandoSQL.c_str(), callback, 0, &mensagem);
			// if (sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem) != SQLITE_OK)
			if (rc != SQLITE_OK)
				throw RUNTIME;
		}
		
		int callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
			NotUsed=0;
			ElementoResultado elemento;
			for(int i = 0; i < argc; i++){
				elemento.setNomeColuna(nomeColuna[i]);
				elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
				listaResultado.push_front(elemento);
			}
			return 0;
		}
		*/
};

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
