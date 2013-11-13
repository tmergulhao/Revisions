#ifndef PERSISTENCE_H
#define PERSISTENCE_H

class SQLInterface {
		static SQLInterface * p_instance;
	public:
		virtual string GetPassword (string) {
			string NULL_STR = "NULL";
			return NULL_STR;
		}
		
		SQLInterface () {}
		SQLInterface (int);
		
		virtual ~SQLInterface () {}
		
		static SQLInterface * instance (int);
		static SQLInterface * instance ();
};typedef class SQLInterface SQLINTERFACE;

#endif
