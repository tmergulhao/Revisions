#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <stdbool.h>
#include <time.h>

#define	BETWEEN(X,Y,Z)		(Y >= X && Y <= Z)

#define NAME_SIZE	30
#define EMAIL_SIZE	60
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
		char * value;
		
		/**
		*	\brief Recebe e valida valor.
		*	
		*	Recebe ponteiro para constante ou caracter.
		*	Avalia validez da entrada e lança exceção apropriada.
		*	@param[in]	input	Ponteiro de vetor de caracteres.
		**/
		virtual void set (char * input) = 0;
		virtual void set (const char * input) = 0;
};

// DEVELOPER NAME
/////////////////

/**
* Erros de validação de nome
**/
typedef enum {
	NUMBERS,	// < Uso de números
	NULL_NAME,	// < Vazio
	TOO_BIG		// < Maior que tamanho definido
} dev_name_error;
/**
*	\brief Classe com alocação e avaliação de valores para nome de desenvolvedor.
*	
*	Avalia o nome quanto ao comprimento padrão, 15 dígitos que sejam:
*	* letras do alfabeto sem acentuação maiúsculas ou minúsculas;
*	* espaços.
**/
class dev_name : public BaseType {
	public:
		dev_name () {
			value = new char [NAME_SIZE+1];
		}
		~dev_name () {
			delete [] value;
		}
		
		void set (char *);
		void set (const char *);
};

// EMAIL
////////

/**
* Erros de validação de email
**/
typedef enum {
	STD_INVALID	// < Email invalido
} email_error;
/**
*	\brief Classe com alocação e avaliação de valores para email de desenvolvedor.
*	
*	Avalia o email ao comprimento máximo e aos padrões regulares de endereço.
**/
class email : public BaseType {
	public:
		email () {
			value = new char [EMAIL_SIZE+1];
		}
		~email () {
			delete [] value;
		}
		
		void set (char *);
		void set (const char *);
};

// PASSWORD
///////////

/**
* Erros de validação de senha
**/
typedef enum {
	INVALID_SIZE,	// < Tamanho inválido
	EQUAL_CHARS		// < Caracteres coincidentes
} password_error;
/**
*	\brief Classe com alocação e avaliação de valores para senha de desenvolvedor.
*	
*	Avalia a senha quanto ao comprimento padrão, 5 dígitos que sejam:
*	* números e letras do alfabeto sem acentuação maiúsculas ou minúsculas;
*	* caracteres não repetentes.
**/
class password : public BaseType {
	public:
		password () {
 			value = new char [PASS_SIZE+1];
 		}
 		~password () {
 			delete [] value;
 		}
		
		void set (char *);
		void set (const char *);
};

#endif
