// C++ Libs
///////////
#include <string>
#include <list>
#include <exception>
using namespace std;

// ANSI C Libs
//////////////
#include <time.h>
#include <stdlib.h>

// External Libs
////////////////
#include <sqlite3.h>

// Local Libs
/////////////
#include <main.h>
#include <entities.h>
#include <persistence.h>

// SQLITE DATABASE PARSER
/////////////////////////

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
		sqlite3 *base;
		char * msg;
		
		static int SQLcallback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
			NotUsed = 0;
			ElementoResultado elemento;
			for(int i = 0; i < argc; i++){
				elemento.setNomeColuna(nomeColuna[i]);
				elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
				listaResultado.push_front(elemento);
			}
			return 0;
		}
		void Run () throw (runtime_error) {
			if (sqlite3_exec(base, command.c_str(), SQLcallback, 0, &msg) != SQLITE_OK)
				throw runtime_error("RUNTIME ERROR ON\n\t\t" + command);
		}
		
		static list<ElementoResultado> listaResultado;
		static list<Product> Products;
		static list<Defect> Defects;
		string command;
	public:
		SQLiteBase () {
			if (sqlite3_open("persistence.base", &base) != SQLITE_OK)
				throw invalid_argument("NOT ABLE TO STABLISH SQL CONNECTION");
			
			// PROJECT
			try {
				command = "SELECT * FROM project";
				Run();
			}
			catch (runtime_error error) {
				command = "CREATE TABLE project (";
				command += "title		TEXT PRIMARY KEY, ";
				command += "developer 	TEXT, ";
				command += "FOREIGN 	KEY(developer) REFERENCES developers(email) )";
				Run();
			}
			
			// DEVELOPERS
			try {
				command = "SELECT * FROM developers";
				Run();
			}
			catch (runtime_error error) {
				command = "CREATE TABLE developers (";
				command += "name 		TEXT, ";
				command += "email 		TEXT PRIMARY KEY, ";
				command += "password 	TEXT)";
				Run();
			}
			
			// PRODUCTS
			try {
				command = "SELECT * FROM products";
				Run();
			}
			catch (runtime_error error) {
				command = "CREATE TABLE products (";
				command += "name 		TEXT, ";
				command += "code 		TEXT PRIMARY KEY, ";
				command += "version 	TEXT, ";
				command += "developer 	TEXT, ";
				command += "FOREIGN 	KEY(developer) REFERENCES developers(email))";
				Run();
			}
			
			// DEFECTS
			try {
				command = "SELECT * FROM issues";
				Run();
			}
			catch (runtime_error error) {
				command = "CREATE TABLE issues (";
				command += "name			TEXT, ";
				command += "description		TEXT, ";
				command += "developer		TEXT, ";
				command += "code			TEXT, ";
				command += "votes			TEXT, ";
				command += "state			TEXT, ";
				command += "opening_date	TEXT, ";
				command += "closing_date	TEXT, ";
				command += "product			TEXT, ";
				command += "FOREIGN			KEY(developer) REFERENCES developers(email),";
				command += "FOREIGN			KEY(product) REFERENCES products(code))";
				Run();
			}
			
			// DEFECT CANDIDATES
			try {
				command = "SELECT * FROM candidates";
				Run();
			}
			catch (runtime_error error) {
				command = "CREATE TABLE candidates (";
				command += "issue			TEXT, ";
				command += "candidate		TEXT, ";
				command += "FOREIGN			KEY(issue) REFERENCES issues(code), ";
				command += "FOREIGN			KEY(candidate) REFERENCES developers(email))";
				Run();
			}
			
			listaResultado.clear();
		}
		~SQLiteBase () {
			if (sqlite3_close(base) != SQLITE_OK)
				throw invalid_argument("NOT ABLE TO KILL SQL CONNECTION");
		}
		
		// PROJECT
		//////////
		bool Empty () {
			command = "SELECT * FROM developers";
			
			Run();
			
			if (listaResultado.empty())
				return true;
				
			listaResultado.clear();
			return false;
		}
		void InitProject (Developer developer) {
			command = "INSERT INTO project VALUES (";
			command += "'owner', ";
			command += "'" + developer.email.get() + "')";
			
			Run();
			
			command = "INSERT INTO developers VALUES (";
			command += "'" + developer.name.get() + "', ";
			command += "'" + developer.email.get() + "', ";
			command += "'" + developer.password.get() + "')";
			
			Run();
		}
		bool IsOwner (email target_email) throw (invalid_argument) {
			command = "SELECT * FROM project WHERE title = 'owner'";
			
			Run();
			
			ElementoResultado resultado;
			
			if (listaResultado.empty())
				throw invalid_argument("NO OWNER EVER");
			
			listaResultado.pop_back();
			
			resultado = listaResultado.back();
			listaResultado.pop_back();
			email current_owner;
			current_owner.set(resultado.getValorColuna().c_str());
			
			if (! listaResultado.empty())
				throw invalid_argument("TOO MANY OWNERS");
			if (current_owner.get().compare(target_email.get()))
				return false;
			
			return true;
		}
		void PassOwnership (email target_email) {
			command = "UPDATE project";
			command += " SET developer = '" + target_email.get() + "'";
			command += " WHERE title = 'owner'";
			
			Run();
		}
		
		// DEVELOPERS
		/////////////
		bool HasDeveloper (email target_email) {
			command = "SELECT * FROM developers WHERE email = ";
			command += "'" + target_email.get() + "'";
			
			Run();
			
			if (listaResultado.empty())
				return false;
			
			listaResultado.clear();
			return true;
		}
		void AddDeveloper (Developer developer) throw (invalid_argument) {
			command = "INSERT INTO developers VALUES (";
			command += "'" + developer.name.get() + "', ";
			command += "'" + developer.email.get() + "', ";
			command += "'" + developer.password.get() + "')";
			
			Run();
		}
		Developer FetchDeveloper (email target_email) throw (invalid_argument) {
			command = "SELECT * FROM developers WHERE email = ";
			command += "'" + target_email.get() + "'";
			
			Run();
			
			ElementoResultado resultado;
			Developer developer;
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			developer.name.set(resultado.getValorColuna().c_str());
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			developer.email.set(resultado.getValorColuna().c_str());
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			developer.password.set(resultado.getValorColuna().c_str());
			
			if (! listaResultado.empty()) {
				listaResultado.clear();
				throw runtime_error("MORE THAN ONE ISSUE WITH SINGLE PRIMARY KEY");
			}
			
			return developer;
		}
		void UpdateDeveloperName (Developer developer, dev_name new_name) throw (invalid_argument) {
			command = "UPDATE developers ";
			command += "SET name = '" + new_name.get();
			command += "' WHERE email = '" + developer.email.get() + "'";
			
			Run();
		}
		void UpdateDeveloperPassword (Developer developer, password new_password) throw (invalid_argument) {
			if (! HasDeveloper(developer.email))
				throw invalid_argument("NO SUCH DEVELOPER");
			
	        command = "UPDATE developers ";
	        command += "SET password = '" + new_password.get();
	        command += "' WHERE email = '" + developer.email.get() + "'";
			
			Run();
		}
		void RemoveDeveloper (email target_email) {
			command = "DELETE FROM developers ";
			command += "WHERE email = '" + target_email.get() + "'";
			
			Run();
		}
		
		// PRODUCT
		//////////
		bool HasProduct (code id_code) {
			command = "SELECT * FROM products WHERE code = ";
			command += "'" + id_code.get() + "'";
			
			Run();
			
			if (listaResultado.empty())
				return false;
			
			listaResultado.clear();
			return true;
		}
		void AddProduct (Product product) {
			command = "INSERT INTO products VALUES (";
			command += "'" + product.name + "', ";
			command += "'" + product.id_code.get() + "', ";
			command += "'" + product.version.get() + "', ";
			command += "'')";
			
			Run();
		}
		void UpdateProductName (Product product) {
			command = "UPDATE products ";
			command += "SET name = '" + product.name;
			command += "' WHERE code = '" + product.id_code.get() + "'";
			
			Run();
		}
		void UpdateProductVersion (Product product) {
			command = "UPDATE products ";
			command += "SET version = '" + product.version.get();
			command += "' WHERE code = '" + product.id_code.get() + "'";
			
			Run();
		}
		void UpdateProductDeveloper (Product product, Developer developer) {
			command = "UPDATE products ";
			command += "SET developer = '" + developer.email.get();
			command += "' WHERE code = '" + product.id_code.get() + "'";
			
			Run();
		}
		int DevAssignProducts (email target) {
			command = "SELECT * FROM products WHERE developer = ";
			command += "'" + target.get() + "'";
			
			int products = 0;
			
			Run();
			
			while (! listaResultado.empty()) {
				for (int i = 0; i < 4; i++)
					listaResultado.pop_back();
				
				products++;
			}
			
			return products;
		}
		void RemoveProduct (code id_code) {
			command = "DELETE FROM products ";
			command += "WHERE code = '" + id_code.get() + "'";
			
			Run();
		}
		list<Product> ListProducts () {
			Products.clear();
			Product product;
			ElementoResultado resultado;
			
			command = "SELECT * FROM products";
			
			Run();
			
			while (! listaResultado.empty()) {
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				product.name = resultado.getValorColuna();
				
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				product.id_code.set(resultado.getValorColuna().c_str());
				
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				product.version.set(resultado.getValorColuna().c_str());
				
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				if (! resultado.getValorColuna().empty())
					product.developer.set(resultado.getValorColuna().c_str());
				else
					product.developer.value = "NULL";
				
				Products.push_front(product);
			}
			
			return Products;
		}
		
		// DEFECTS
		//////////
		bool HasDefect (code id_code) {
			command = "SELECT * FROM issues WHERE code = ";
			command += "'" + id_code.get() + "'";
			
			Run();
			
			if (listaResultado.empty())
				return false;
			
			listaResultado.clear();
			return true;
		}
		void AddDefect (Product product, Defect defect) {
			time_t rawtime;
			time (&rawtime);
			string current_time = ctime(&rawtime);
			
			command = "INSERT INTO issues VALUES (";
			command += "'" + defect.name + "', ";
			command += "'" + defect.description + "', ";
			command += "'', "; // NULL DEVELOPER
			command += "'" + product.id_code.get() + "', ";
			command += "0, ";
			command += "'NEW', ";
			command += "'" + current_time + "', ";
			command += "'NULL', ";
			command += "'" + product.id_code.get() + "' ";
			command += ")";
			
			Run();
		}
		Defect FetchDefect (code id_code) throw (invalid_argument) {
			command = "SELECT * FROM issues WHERE code = ";
			command += "'" + id_code.get() + "'";
			
			listaResultado.clear();
			
			Run();
			
			ElementoResultado resultado;
			Defect defect;
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.name = resultado.getValorColuna();
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.description = resultado.getValorColuna();
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			if (! resultado.getValorColuna().empty())
				defect.developer.set(resultado.getValorColuna().c_str());
			else
				defect.developer.value = "NULL";
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.id_code.set(resultado.getValorColuna().c_str());
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.votes = resultado.getValorColuna();
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.state = resultado.getValorColuna();
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.opening = resultado.getValorColuna();
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			if (! resultado.getValorColuna().empty())
				defect.closing = resultado.getValorColuna();
			else
				defect.closing = "NULL";
			
			if (listaResultado.empty())
				throw invalid_argument("EMPTY FIELD");
			resultado = listaResultado.back();
			listaResultado.pop_back();
			defect.product.set(resultado.getValorColuna().c_str());
			
			if (! listaResultado.empty()) {
				listaResultado.clear();
				throw runtime_error("MORE THAN ONE ISSUE WITH SINGLE PRIMARY KEY");
			}
				
			return defect;
		}
		void UpdateDefectName (Defect defect) {
			command = "UPDATE issues ";
			command += "SET name = '" + defect.name;
			command += "' WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		void UpdateDefectDescription (Defect defect) {
			command = "UPDATE issues ";
			command += "SET description = '" + defect.description;
			command += "' WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		void UpdateDefectDeveloper (Defect defect, Developer developer) {
			command = "UPDATE issues ";
			command += "SET developer = '" + developer.email.get();
			command += "' WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		void UpdateDefectVotes (Defect defect) {
			command = "UPDATE issues ";
			command += "SET votes = '" + defect.votes;
			command += "' WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		void UpdateDefectState (Defect defect) {
			command = "UPDATE issues ";
			command += "SET state = '" + defect.state;
			command += "' WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		void UpdateDefectClose (Defect defect) {
			time_t rawtime;
			time (&rawtime);
			string current_time = ctime(&rawtime);
			
			command = "UPDATE issues ";
			command += "SET closing_date = '" + current_time;
			command += "' WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		int DevAssignDefects (email target) {
			command = "SELECT * FROM issues WHERE developer = ";
			command += "'" + target.get() + "'";
			
			int issues = 0;
			
			Run();
			
			while (! listaResultado.empty()) {
				for (int i = 0; i < 9; i++)
					listaResultado.pop_back();
				
				issues++;
			}
			
			return issues;
		}
		int ProdAssignDefects (code id_code) {
			command = "SELECT * FROM issues WHERE product = ";
			command += "'" + id_code.get() + "'";
			
			int issues = 0;
			
			Run();
			
			while (! listaResultado.empty()) {
				for (int i = 0; i < 9; i++)
					listaResultado.pop_back();
				
				issues++;
			}
			
			return issues;
		}
		void RemoveDefect (Defect defect) {
			command = "DELETE FROM issues ";
			command += "WHERE code = '" + defect.id_code.get() + "'";
			
			Run();
		}
		list<Defect> ListDefects (Product product) {
			Defects.clear();
			Defect defect;
			ElementoResultado resultado;
			
			command = "SELECT * FROM issues WHERE product = ";
			command += "'" + product.id_code.get() + "'";
			
			Run();
			
			while (! listaResultado.empty()) {
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.name = resultado.getValorColuna();
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.description = resultado.getValorColuna();
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				if (! resultado.getValorColuna().empty())
					defect.developer.set(resultado.getValorColuna().c_str());
				else
					defect.developer.value = "NULL";
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.id_code.set(resultado.getValorColuna().c_str());
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.votes = resultado.getValorColuna();
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.state = resultado.getValorColuna();
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.opening = resultado.getValorColuna();
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				if (! resultado.getValorColuna().empty())
					defect.closing = resultado.getValorColuna();
				else
					defect.closing = "NULL";
			
				if (listaResultado.empty())
					throw invalid_argument("EMPTY FIELD");
				resultado = listaResultado.back();
				listaResultado.pop_back();
				defect.product.set(resultado.getValorColuna().c_str());
				
				Defects.push_front(defect);
			}
			
			return Defects;
		}
		
		// DEFECT CANDIDATES
		////////////////////
		void AddCandidade (Defect defect, Developer developer) {
			command = "INSERT INTO candidates VALUES (";
			command += "'" + defect.id_code.get() + "'";
			command += "'" + developer.email.get() + "'";
			command += ")";
			
			Run();
		}
		bool IsCandidade (Defect defect, Developer developer) {
			command = "SELECT * FROM candidates WHERE issue = ";
			command += "'" + defect.id_code.get() + "'";
			command += ")";
			
			Run();
			
			ElementoResultado resultado;
			
			while (! listaResultado.empty()) {
				listaResultado.pop_back();
				resultado = listaResultado.back();
				listaResultado.pop_back();
				
				if (developer.email.get().compare(resultado.getValorColuna()) == 0) {
					listaResultado.clear();
					return true;
				}
			}
			
			return false;
		}
		void WipeCandidades (Defect defect) {
			command = "DELETE FROM candidates ";
			command += "WHERE issue = '" + defect.id_code.get() + "'";
			command += ")";
			
			Run();
		}
};
list<ElementoResultado> SQLiteBase::listaResultado;
list<Product> SQLiteBase::Products;
list<Defect> SQLiteBase::Defects;

/*
// STUB SQLITE EMULATOR
///////////////////////
class StubBase: public SQLInterface {
	public:
		Developer FetchUser (email) throw (invalid_argument);
		
		StubBase () {}
		~StubBase () {}
};

Developer StubBase::FetchUser (email target_email) throw (invalid_argument) {
	string email = target_email.get();
	
	if (email.compare("me@tmergulhao.com") == 0) {
		return Developer (	"Tiago Mergulhao",
							"me@tmergulhao.com",
							"12345");
	}
	else if (email.compare("usr1@doma.in") == 0) {
		return Developer (	"Dummy One",
							"usr1@doma.in",
							"54321");
	}
	else if (email.compare("usr2@doma.in") == 0) {
		return Developer (	"Dummy Two",
							"usr2@doma.in",
							"54321");
	}
	else if (email.compare("usr3@doma.in") == 0) {
		return Developer (	"Dummy Three",
							"usr3@doma.in",
							"54321");
	} else if (email.compare("admin@doma.in") == 0) {
		return Developer (	"Admin Love",
							"admin@doma.in",
							"54321");
	} else
		throw invalid_argument("NO SUCH USER");
}
*/
// SINGLETON STATEMENTS
///////////////////////
SQLInterface * SQLInterface::p_instance = 0;

SQLInterface * SQLInterface::instance (int FLAGS) throw (invalid_argument) {
	if (!p_instance) {
		try {
			p_instance = new class SQLiteBase;
		}
		catch (invalid_argument error) {
			//p_instance = new class StubBase;
		}
	}
	return p_instance;
}

SQLInterface * SQLInterface::instance () throw (invalid_argument) {
	if (p_instance) return p_instance;
	return instance (0);
}
