#ifndef BASICTYPES_H
#define BASICTYPES_H

// C++ Libs
///////////
#include <stdexcept>
#include <string>
using namespace std;

#define	BETWEEN(X,Y,Z)		(Y >= X && Y <= Z)

#define NAME_SIZE	30 // 15
#define EMAIL_SIZE	60 // 20
#define PASS_SIZE	5

//-----------------------------------------------------------------------
// BASIC TYPES
//-----------------------------------------------------------------------

// BASE TYPE
////////////

/**
*	\brief Classe base que contém os métodos virtuais necessários para a
*	definição de tipo básico.
*	
*	Os construtores de cada classe são reponsáveis por alocar o tamanho
*	máximo do vetor que estão definidos neste cabeçalho.
**/
class BaseType {
	public:
		/**
		*	\brief Ponteiro de char para a alocação do espaço necessário
		*	a cada tipo básico.
		**/
		string value;
		
		/**
		*	\brief Recebe e valida valor.
		*	
		*	Recebe ponteiro para constante ou caracter.
		*	Avalia validez da entrada e lança exceção apropriada.
		*	@param[in]	input	Ponteiro de vetor de caracteres.
		**/
		virtual void set (char * input) throw (invalid_argument) = 0;
		virtual void set (const char * input) throw (invalid_argument) = 0;
		virtual string get () = 0;
};

// DEVELOPER NAME
/////////////////

/**
*	\brief Classe com alocação e avaliação de valores para nome de desenvolvedor.
*	
*	Avalia o nome quanto ao comprimento padrão, 15 dígitos que sejam:
*	* letras do alfabeto sem acentuação maiúsculas ou minúsculas;
*	* espaços.
**/
class dev_name : public BaseType {
		string shortname;
	public:
		void set (char *) throw (invalid_argument);
		void set (const char *) throw (invalid_argument);
		string get () { return value; }
		string getshort ();
};

// EMAIL
////////

/**
*	\brief Classe com alocação e avaliação de valores para email de desenvolvedor.
*	
*	Avalia o email ao comprimento máximo e aos padrões regulares de endereço.
**/
class email : public BaseType {
	public:
		void set (char *) throw (invalid_argument);
		void set (const char *) throw (invalid_argument);
		string get () { return value; }
};

// PASSWORD
///////////

/**
*	\brief Classe com alocação e avaliação de valores para senha de desenvolvedor.
*	
*	Avalia a senha quanto ao comprimento padrão, 5 dígitos que sejam:
*	* números e letras do alfabeto sem acentuação maiúsculas ou minúsculas;
*	* caracteres não repetentes.
**/
class password : public BaseType {
	public:
		void set (char *) throw (invalid_argument);
		void set (const char *) throw (invalid_argument);
		string get () { return value; }
};

// CODE
///////

/**
*	\brief Classe com alocação e avaliação de valores para código de produto ou defeito.
*	
*	Avalia o código quanto ao comprimento padrão, 4 dígitos que sejam:
*	* letras do alfabeto sem acentuação maiúsculas ou minúsculas.
**/
class code : public BaseType {
	public:
		void set (char *) throw (invalid_argument);
		void set (const char *) throw (invalid_argument);
		string get () { return value; }
};

// VERSION
//////////

/**
*	\brief Classe com alocação e avaliação de valores para versão de produto.
*	
*	Avalia a versão quanto ao comprimento padrão, 5 dígitos que sejam:
*	* números e letras do alfabeto sem acentuação maiúsculas ou minúsculas;
*	* o dígito do meio é um separador '.'.
**/
class version : public BaseType {
	public:
		void set (char *) throw (invalid_argument);
		void set (const char *) throw (invalid_argument);
		string get () { return value; }
};

#endif
