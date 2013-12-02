#ifndef CONSTROLLER_H
#define CONSTROLLER_H

// C++ Libs
///////////
#include <stdexcept>
#include <string>
using namespace std;

// Local Libs
/////////////
#include <entities.h>
#include <persistence.h>

class Controller {
		static Controller * p_instance;
		Developer scope_user;
		bool login;
	public:
		Controller (int FLAGS) throw (invalid_argument) {
			login = false;
			SQLINTERFACE::instance(FLAGS);
		}
		~Controller () {
			delete SQLINTERFACE::instance();
		}
		
		bool Initialize();
		void Initialize (Developer);
		void ProjectAssign (email);
		
		bool User () { return login; }
		void User (Developer) throw (invalid_argument);
		void Logout () { login = false; }
		void AddDeveloper (Developer);
		void EditDevName (dev_name);
		void EditDevPassword (password);
		void RemoveDeveloper (email);
		
		void AddProduct (Product);
		void EditProductName (Product);
		void EditProductVersion (Product);
		void AssignDevProduct (Developer, Product);
		void RemoveProduct (Product);
		list<Product> ListProducts ();
		
		void AddDefect (Product product, Defect defect);
		Defect FetchDefect (Defect defect);
		void EditDefectName (Defect defect);
		void EditDefectDescription (Defect defect);
		void EditDefectState (Defect defect);
		void EditDefectVotes (Defect defect);
		void AssignDevDefect (Developer developer, Defect defect);
		void CloseDefect (Defect defect);
		list<Defect> ListDefects (Product product);
		
		void OfferAsCandidate (Defect);
		
		string Scope ();
		
		static Controller * instance (int) throw (invalid_argument);
		static Controller * instance () throw (invalid_argument);
};typedef class Controller CONTROLLER;

#endif
