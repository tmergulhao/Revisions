#ifndef PERSISTENCE_H
#define PERSISTENCE_H

class SQLInterface {
	private:
		developer* active_developer;
		product* active_product;
	public:
		// USER
		// VALIDATE DEVELOPER LOGIN
		virtual bool Login (* developer) = 0;
		// CHANGES DEVELOPER DATA
		virtual bool ChangeUser (* developer) = 0;
		
		// PRODUCT
		// STARTS NEW PRODUCT
		virtual bool NewProduct (* product) = 0;
		// SWITCHES PRODUCT STATE
		virtual bool ChangeState (methaproduct_state) = 0;
		
		// ISSUE
		// STARTS NEW ISSUE
		virtual bool NewIssue (* product, * issue) = 0;
		// SWITCHES ISSUE STATE
		virtual bool ChangeState (* product, methaproduct_state) = 0;
		
		// SWITCHES ISSUE STATE
		virtual bool ChangeState (* issue, methaproduct_state) = 0;
		
};

class SQLiteBase: public SQLInterface {
	private:
	public:
		SQLiteBase () {}
		~SQLiteBase () {}
};
bool SQLiteBase::Login (* developer) { return true; }

class StubBase: public SQLInterface {
	private:
	public:
		StubBase () {}
		~StubBase () {}
};
bool StubBase::Login (* developer) {
	if (strcmp(developer->email, "me@tmergulhao.com") == 0 && strcmp(developer->email, "12345") == 0) return true;
	return false;
}

#endif
