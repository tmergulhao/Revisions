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

class CNTRLInterface {
	static CNTRLInterface * p_instance;
public:
	CNTRLInterface () {}
	CNTRLInterface (int FLAGS);
	~CNTRLInterface () {}
	
	virtual bool Initialize() = 0;
	virtual void Initialize (Developer) = 0;
	virtual void ProjectAssign (email) = 0;
	
	virtual bool User () = 0;
	virtual void User (Developer) throw (invalid_argument) = 0;
	virtual void Logout () = 0;
	virtual void AddDeveloper (Developer) = 0;
	virtual void EditDevName (dev_name) = 0;
	virtual void EditDevPassword (password) = 0;
	virtual void RemoveDeveloper (email) = 0;
	
	virtual void AddProduct (Product) = 0;
	virtual void EditProductName (Product) = 0;
	virtual void EditProductVersion (Product) = 0;
	virtual void AssignDevProduct (Developer, Product) = 0;
	virtual void RemoveProduct (Product) = 0;
	virtual list<Product> ListProducts () = 0;
	
	virtual void AddDefect (Product product, Defect defect) = 0;
	virtual Defect FetchDefect (Defect defect) = 0;
	virtual void EditDefectName (Defect defect) = 0;
	virtual void EditDefectDescription (Defect defect) = 0;
	virtual void EditDefectState (Defect defect) = 0;
	virtual void EditDefectVotes (Defect defect) = 0;
	virtual void AssignDevDefect (Developer developer, Defect defect) = 0;
	virtual void CloseDefect (Defect defect) = 0;
	virtual list<Defect> ListDefects (Product product) = 0;
	
	virtual void OfferAsCandidate (Defect) = 0;
	
	virtual string Scope () = 0;
	
	static CNTRLInterface * instance (int) throw (invalid_argument);
	static CNTRLInterface * instance () throw (invalid_argument);
};typedef class CNTRLInterface CONTROLLER;

#endif
