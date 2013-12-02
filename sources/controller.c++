// C++ Libs
///////////
#include <string>
#include <list>
#include <stdexcept>
using namespace std;

// ANSI C Libs
//////////////
#include <string.h>
#include <stdio.h>

// Local Libs
/////////////
#include <main.h>
#include <entities.h>
#include <persistence.h>
#include <controller.h>

class Controller : public CNTRLInterface {
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
		
		bool Initialize() {
			return SQLINTERFACE::instance()->Empty() ? false : true;
		}
		void Initialize (Developer developer) {
			SQLINTERFACE::instance()->InitProject(developer);
		}
		void ProjectAssign (email target_email) {
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN ASSING NEW OWNER");
			if (! SQLINTERFACE::instance()->HasDeveloper(target_email))
				throw invalid_argument("NO SUCH USER");
			if (SQLINTERFACE::instance()->DevAssignProducts(target_email))
				throw invalid_argument ("TOO MANY ASSETS ON ACCOUNT");
			if (SQLINTERFACE::instance()->DevAssignDefects(target_email))
				throw invalid_argument ("TOO MANY ASSETS ON ACCOUNT");
	
			SQLINTERFACE::instance()->PassOwnership(target_email);
		}
		
		bool User () { return login; }
		void User (Developer developer) throw (invalid_argument) {
			scope_user = SQLINTERFACE::instance()->FetchDeveloper(developer.email);

			if (developer.password.get().compare(scope_user.password.get()) == 0)
				login = true;
		}
		void Logout () { login = false; }
		void AddDeveloper (Developer developer) {
			if (SQLINTERFACE::instance()->HasDeveloper(developer.email))
				throw invalid_argument("EMAIL IN USE");
	
			SQLINTERFACE::instance()->AddDeveloper(developer);
		}
		void EditDevName (dev_name new_name) {
			SQLINTERFACE::instance()->UpdateDeveloperName(scope_user, new_name);
			scope_user = SQLINTERFACE::instance()->FetchDeveloper(scope_user.email);
		}
		void EditDevPassword (password new_password) {
			SQLINTERFACE::instance()->UpdateDeveloperPassword(scope_user, new_password);
		}
		void RemoveDeveloper (email target_email) {
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN REMOVE USER");
			if (! SQLINTERFACE::instance()->HasDeveloper(target_email))
				throw invalid_argument("NO SUCH USER");
			if (SQLINTERFACE::instance()->IsOwner(target_email) ||
				SQLINTERFACE::instance()->DevAssignProducts(target_email) ||
				SQLINTERFACE::instance()->DevAssignDefects(target_email))
				throw invalid_argument("USER HAS DEPENDENCIES");
	
			SQLINTERFACE::instance()->RemoveDeveloper(target_email);
			// remove from candidate table
		}
		
		void AddProduct (Product product) {
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN ADD PRODUCT");
			if (SQLINTERFACE::instance()->HasProduct(product.id_code))
				throw invalid_argument ("PRODUCT ID ALREADY IN USE");
	
			SQLINTERFACE::instance()->AddProduct(product);
		}
		void EditProductName (Product product) {
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN EDIT PRODUCT");
			if (! SQLINTERFACE::instance()->HasProduct(product.id_code))
				throw invalid_argument ("NO SUCH PRODUCT");
	
			SQLINTERFACE::instance()->UpdateProductName(product);
		}
		void EditProductVersion (Product product) {
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN EDIT PRODUCT");
			if (! SQLINTERFACE::instance()->HasProduct(product.id_code))
				throw invalid_argument ("NO SUCH PRODUCT");
	
			SQLINTERFACE::instance()->UpdateProductVersion(product);
		}
		void AssignDevProduct (Developer developer, Product product) {
			if (! SQLINTERFACE::instance()->HasDeveloper(developer.email))
				throw invalid_argument("NO SUCH DEVELOPER");
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN EDIT PRODUCT");
			if (SQLINTERFACE::instance()->IsOwner(developer.email))
				throw invalid_argument ("NO ADMIN CAN OWN PRODUCT");
			if (SQLINTERFACE::instance()->DevAssignProducts(developer.email) == 2)
				throw invalid_argument ("TOO MANY ASSETS ON ACCOUNT");
			if (SQLINTERFACE::instance()->DevAssignDefects(developer.email))
				throw invalid_argument ("TOO MANY ASSETS ON ACCOUNT");
			if (! SQLINTERFACE::instance()->HasProduct(product.id_code))
				throw invalid_argument ("NO SUCH PRODUCT");
	
			SQLINTERFACE::instance()->UpdateProductDeveloper(product, developer);
		}
		void RemoveProduct (Product product) {
			if (! SQLINTERFACE::instance()->IsOwner(scope_user.email))
				throw invalid_argument ("ONLY ADMIN CAN REMOVE PRODUCT");
			if (! SQLINTERFACE::instance()->HasProduct(product.id_code))
				throw invalid_argument ("NO SUCH PRODUCT");
			if (SQLINTERFACE::instance()->ProdAssignDefects(product.id_code))
				throw invalid_argument ("PRODUCT HAS ISSUES");
	
			SQLINTERFACE::instance()->RemoveProduct(product.id_code);
		}
		list<Product> ListProducts () {
			return SQLINTERFACE::instance()->ListProducts();
		}
		
		void AddDefect (Product product, Defect defect) {
			if (SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("DEFECT ID ALREADY IN USE");
	
			SQLINTERFACE::instance()->AddDefect(product, defect);
		}
		Defect FetchDefect (Defect defect) {
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
	
			return SQLINTERFACE::instance()->FetchDefect(defect.id_code);
		}
		void EditDefectName (Defect defect) {
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
	
			SQLINTERFACE::instance()->UpdateDefectName(defect);
		}
		void EditDefectDescription (Defect defect) {
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
	
			SQLINTERFACE::instance()->UpdateDefectDescription(defect);
		}
		void EditDefectState (Defect defect) {
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
			Defect curr_defect = SQLINTERFACE::instance()->FetchDefect(defect.id_code);
	
			// APPLY LOGICS
	
			/*
		typedef enum {
			UNCONFIRMED = 0, 	// ALL CAN ADD A DEFECT IN ALL ENVIROMENTS
			CONFIRMED,
			REPAIRING,
			REPARED,
			DONE // ASSIGN CLOSING DATE
			// REPARED->DONE AND REPARED->CONFIRMED IS THE ONLY, AND ONLY, FOR MANAGERS
		} defect_state;
			*/
	
			SQLINTERFACE::instance()->UpdateDefectState(defect);
		}
		void EditDefectVotes (Defect defect) {
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
			Defect curr_defect = SQLINTERFACE::instance()->FetchDefect(defect.id_code);
	
			// APPLY LOGICS
	
			SQLINTERFACE::instance()->UpdateDefectVotes(defect);
		}
		void AssignDevDefect (Developer developer, Defect defect) {
			if (! SQLINTERFACE::instance()->HasDeveloper(developer.email))
				throw invalid_argument("NO SUCH DEVELOPER");
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
			if (SQLINTERFACE::instance()->IsOwner(developer.email))
				throw invalid_argument ("NO ADMIN CAN DEVELOP");
			if (SQLINTERFACE::instance()->DevAssignProducts(developer.email))
				throw invalid_argument ("NO MANAGER CAN DEVELOP");
			if (SQLINTERFACE::instance()->DevAssignDefects(developer.email) == 5)
				throw invalid_argument ("TOO MANY ASSETS ON ACCOUNT");
			if (! SQLINTERFACE::instance()->IsCandidade(defect, developer))
				throw invalid_argument ("ONLY CANDIDATES CAN BECOME DEVELOPERS");
	
			SQLINTERFACE::instance()->UpdateDefectDeveloper(defect, developer);
	
			SQLINTERFACE::instance()->WipeCandidades(defect);
		}
		void CloseDefect (Defect defect) {
			if (! SQLINTERFACE::instance()->HasDefect(defect.id_code))
				throw invalid_argument ("NO SUCH DEFECT");
	
			SQLINTERFACE::instance()->UpdateDefectClose(defect);
		}
		list<Defect> ListDefects (Product product) {
			return SQLINTERFACE::instance()->ListDefects(product);
		}
		
		void OfferAsCandidate (Defect defect) {
			if (SQLINTERFACE::instance()->IsCandidade(defect, scope_user))
				throw invalid_argument ("ALREADY CANDIDATE");
	
			SQLINTERFACE::instance()->AddCandidade(defect, scope_user);
		}
		
		string Scope () {
			string return_str;
	
			if (login) return return_str = scope_user.name.getshort() + " > ";
	
			return return_str = "> ";
		}
		
		static Controller * instance (int) throw (invalid_argument);
		static Controller * instance () throw (invalid_argument);
};

// SINGLETON STATEMENTS
///////////////////////

CNTRLInterface * CNTRLInterface::p_instance = 0;

CNTRLInterface * CNTRLInterface::instance (int FLAGS) throw (invalid_argument) {
	if (!p_instance) p_instance = new class Controller (FLAGS);
	return p_instance;
}

CNTRLInterface * CNTRLInterface::instance () throw (invalid_argument) {
	if (p_instance) return p_instance;
	return instance (0);
}
