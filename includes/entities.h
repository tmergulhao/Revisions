#ifndef ENTITIES_H
#define ENTITIES_H

// Local Libs
/////////////
#include <basetypes.h>

//-----------------------------------------------------------------------
// ENTITIES
//-----------------------------------------------------------------------

// DEVELOPER
////////////

/**
*	\brief Classe de entidade desenvolvedor
**/
class Developer {
	public:
		/**
		*	\brief Valor de email de desenvolvedor com validador
		**/
		class email email;
		/**
		*	\brief Valor de nome de desenvolvedor com validador
		**/
		class dev_name name;
		/**
		*	\brief Valor de senha de desenvolvedor com validador
		**/
		class password password;
		
		Developer () {}
		/**
		*	\brief Construtor com argumentos
		*	
		*	@param[in]	const char	Valor constante de nome.
		*	@param[in]	const char	Valor constante de email.
		*	@param[in]	const char	Valor constante de senha.
		**/
		Developer (const char *, const char *, const char *);
};

// DEFECT
/////////

/**
*	\brief Classe de entidade defeito
**/
class Defect {
	public:
		/**
		*	\brief Valor de nome de defeito
		**/
		string name;
		/**
		*	\brief Descrição de defeito em 30 caracteres
		**/
		string description;
		/**
		*	\brief Email de desenvolvedor com validador
		**/
		email developer;
		/**
		*	\brief Código de defeito com validador
		**/
		code id_code;
		/**
		*	\brief Votos de defeito de 0 a 100
		**/
		string votes;
		/**
		*	\brief Estados do defeito
		*
		*	Novo, confirmado, em reparo, reparado, fechado
		**/
		string state;
		/**
		*	\brief Data de abertura em texto
		**/
		string opening;
		/**
		*	\brief Data de fechamento em texto
		**/
		string closing;
		/**
		*	\brief Código de produto referente com validador
		**/
		code product;
};

// PRODUCT
//////////

/**
*	\brief Classe de entidade produto
**/
class Product {
	public:
		/**
		*	\brief Valor de nome do produto
		**/
		string name;
		/**
		*	\brief Código de produto com validador
		**/
		code id_code;
		/**
		*	\brief Versão do produto com validador
		**/
		version version;
		/**
		*	\brief Email de desenvolvedor com validador
		**/
		email developer;
};

#endif
