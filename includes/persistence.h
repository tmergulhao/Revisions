#ifndef PERSISTENCE_H
#define PERSISTENCE_H

typedef enum {
	CONNECT,	// < Erro de conexão
	DISCONNECT,	// < Erro de desconexão
	RUNTIME		// < Erro na execução
} sql_error;

class SQLInterface {
		static SQLInterface * p_instance;
	public:
		// virtual Develper * Find (Develper *);
		// virtual void Add (Develper *);
		// virtual void Update (Develper *);
		// virtual void Remove (Develper *);
		
		SQLInterface () {}
		SQLInterface (int);
		
		virtual ~SQLInterface () {}
		
		static SQLInterface * instance (int);
		static SQLInterface * instance ();
};typedef class SQLInterface SQLINTERFACE;

#endif
