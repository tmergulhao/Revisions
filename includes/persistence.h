#ifndef PERSISTENCE_H
#define PERSISTENCE_H

// C++ Libs
///////////
#include <stdexcept>
#include <list>

// Local Libs
/////////////
#include <basetypes.h>
#include <entities.h>

class SQLInterface {
		static SQLInterface * p_instance;
	public:
		SQLInterface () {}
		SQLInterface (int);
		~SQLInterface () {}
		
		// PROJECT
		//////////
		virtual bool Empty () = 0;
		virtual void InitProject (Developer) = 0;
		virtual bool IsOwner (email) throw (invalid_argument) = 0;
		virtual void PassOwnership (email) = 0;
		
		// DEVELOPERS
		/////////////
		virtual bool HasDeveloper (email target_email) = 0;
		virtual void AddDeveloper (Developer developer) throw (invalid_argument) = 0;
		virtual Developer FetchDeveloper (email target_email) throw (invalid_argument) = 0;
		virtual void UpdateDeveloperName (Developer developer, dev_name new_name) throw (invalid_argument) = 0;
		virtual void UpdateDeveloperPassword (Developer developer, password new_password) throw (invalid_argument) = 0;
		virtual void RemoveDeveloper (email target_email) = 0;
		virtual int DevAssignProducts (email) = 0;
		
		// PRODUCTS
		///////////
		virtual bool HasProduct (code id_code) = 0;
		virtual void AddProduct (Product product) = 0;
		virtual void UpdateProductName (Product) = 0;
		virtual void UpdateProductVersion (Product) = 0;
		virtual void UpdateProductDeveloper (Product, Developer) = 0;
		virtual void RemoveProduct (code) = 0;
		virtual list<Product> ListProducts () = 0;
		
		// DEFECTS
		//////////
		virtual bool HasDefect (code id_code) = 0;
		virtual void AddDefect (Product product, Defect defect) = 0;
		virtual Defect FetchDefect (code id_code) throw (invalid_argument) = 0;
		virtual void UpdateDefectName (Defect defect) = 0;
		virtual void UpdateDefectDescription (Defect defect) = 0;
		virtual void UpdateDefectDeveloper (Defect defect, Developer developer) = 0;
		virtual void UpdateDefectVotes (Defect defect) = 0;
		virtual void UpdateDefectState (Defect defect) = 0;
		virtual void UpdateDefectClose (Defect defect) = 0;
		virtual int DevAssignDefects (email target) = 0;
		virtual int ProdAssignDefects (code id_code) = 0;
		virtual void RemoveDefect (Defect defect) = 0;
		virtual list<Defect> ListDefects (Product product) = 0;
		
		// DEFECT CANDIDATES
		////////////////////
		virtual void AddCandidade (Defect defect, Developer developer) = 0;
		virtual bool IsCandidade (Defect defect, Developer developer) = 0;
		virtual void WipeCandidades (Defect defect) = 0;
		
		static SQLInterface * instance (int) throw (invalid_argument);
		static SQLInterface * instance () throw (invalid_argument);
};typedef class SQLInterface SQLINTERFACE;

#endif
