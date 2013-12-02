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

/**
*	\brief Classe virtual responsável pela controladora de negócios
*	
*	É um interface virtual com alocação de objeto escondida.
**/
class CNTRLInterface {
		/**
		*	\brief Ponteiro de instância para alocação do objeto singular.
		**/
	static CNTRLInterface * p_instance;
public:
	/**
	*	\brief Métodos construtores de chamada de instância.
	**/
	CNTRLInterface () {}
	CNTRLInterface (int FLAGS);
	~CNTRLInterface () {}
	
	/**
	*	\brief Verificador de início de banco de dados.
	*	
	*	@param[out]	bool	verdadeiro caso iniciado
	**/
	virtual bool Initialize() = 0;
	/**
	*	\brief Inicializador de banco de dados.
	*	
	*	@param[in]	Developer	desenvolvedor padrão.
	**/
	virtual void Initialize (Developer) = 0;
	/**
	*	\brief Assinala o novo administrador do sistema.
	*	
	*	@param[in]	email	novo administrador.
	**/
	virtual void ProjectAssign (email) = 0;
	
	/**
	*	\brief Verificador de existência de usuários.
	*	
	*	@param[out]	bool	verdadeiro caso usuário exista
	**/
	virtual bool User () = 0;
	/**
	*	\brief Interface de login na ferramenta.
	*	
	*	@param[in]	Developer	desenvolvedor do login.
	**/
	virtual void User (Developer) throw (invalid_argument) = 0;
	/**
	*	\brief Interface de logout da ferramenta.
	**/
	virtual void Logout () = 0;
	/**
	*	\brief Camada de verificação e passagem de desenvolvedor
	*	para banco de dados.
	*	
	*	@param[in]	Developer	desenvolvedor adicionado.
	**/
	virtual void AddDeveloper (Developer) = 0;
	/**
	*	\brief Camada de verificação e passagem de nome de 
	*	desenvolvedor para banco de dados.
	*	
	*	@param[in]	dev_name	nome de desenvolvedor.
	**/
	virtual void EditDevName (dev_name) = 0;
	/**
	*	\brief Camada de verificação e passagem de senha de 
	*	desenvolvedor para banco de dados.
	*	
	*	@param[in]	password	senha de desenvolvedor.
	**/
	virtual void EditDevPassword (password) = 0;
	/**
	*	\brief Interface de exclusão de conta de desenvolvedor
	*	com validação
	*	
	*	@param[in]	email	email de desenvolvedor.
	**/
	virtual void RemoveDeveloper (email) = 0;
	
	/**
	*	\brief Adição de produto em objeto
	*	
	*	@param[in]	Product	produto a ser adicionado.
	**/
	virtual void AddProduct (Product) = 0;
	/**
	*	\brief Edição de nome de produto em objeto
	*	
	*	@param[in]	Product	nova versão de produto a ser editado.
	**/
	virtual void EditProductName (Product) = 0;
	/**
	*	\brief Edição de versão de produto em objeto
	*	
	*	@param[in]	Product	nova versão de produto a ser editado.
	**/
	virtual void EditProductVersion (Product) = 0;
	/**
	*	\brief Edição de administrador de produto
	*	
	*	@param[in]	Developer	desenvolvedor a administrar produto.
	*	@param[in]	Product	produto a ser administrado.
	**/
	virtual void AssignDevProduct (Developer, Product) = 0;
	/**
	*	\brief Interface de exclusão de produto
	*	com validação
	*	
	*	@param[in]	Product	produto a ser removido.
	**/
	virtual void RemoveProduct (Product) = 0;
	/**
	*	\brief Interface de chamada de produtos em banco de dados
	*	
	*	@param[out]	list<Product>	lista dinâmica de produtos.
	**/
	virtual list<Product> ListProducts () = 0;
	
	/**
	*	\brief Adição de defeito em objeto
	*	
	*	@param[in]	Product	produto onde defeito será adicionado.
	*	@param[in]	Defect	defeito a ser adicionado.
	**/
	virtual void AddDefect (Product, Defect) = 0;
	/**
	*	\brief Captação de defeito
	*	
	*	@param[in]	Defect	defeito a ser buscado.
	*	@param[out]	Defect	defeito a ser retornado.
	**/
	virtual Defect FetchDefect (Defect) = 0;
	/**
	*	\brief Edição de nome de defeito
	*	
	*	@param[in]	Defect	defeito a ser buscado.
	**/
	virtual void EditDefectName (Defect) = 0;
	/**
	*	\brief Edição de descrição de defeito
	*	
	*	@param[in]	Defect	defeito a ser buscado.
	**/
	virtual void EditDefectDescription (Defect) = 0;
	/**
	*	\brief Edição de estado de defeito
	*	
	*	@param[in]	Defect	defeito a ser buscado.
	**/
	virtual void EditDefectState (Defect) = 0;
	/**
	*	\brief Edição de votos do defeito
	*	
	*	@param[in]	Defect	defeito a ser buscado.
	**/
	virtual void EditDefectVotes (Defect) = 0;
	/**
	*	\brief Adição de responsável por defeito
	*	
	*	@param[in]	Developer	desenvolvedor responsável.
	*	@param[in]	Defect	defeito a ser buscado.
	**/
	virtual void AssignDevDefect (Developer, Defect) = 0;
	/**
	*	\brief Fechamento de defeito
	*	
	*	@param[in]	Defect	defeito a ser buscado.
	**/
	virtual void CloseDefect (Defect) = 0;
	/**
	*	\brief Interface de chamada de defeitos de produto em banco de dados
	*	
	*	@param[in]	Product			produto referente.
	*	@param[out]	list<Defect>	lista dinâmica de defeitos.
	**/
	virtual list<Defect> ListDefects (Product) = 0;
	
	/**
	*	\brief Adição de desenvolvedor atual na tabela de candidatos
	*	ao defeito
	*	
	*	@param[in]	Defect			defeito referente.
	**/
	virtual void OfferAsCandidate (Defect) = 0;
	
	/**
	*	\brief Retorna escopo de execução. No caso nome curto de desenvolvedor.
	*	
	*	@param[out]	string	retorna escopo.
	**/
	virtual string Scope () = 0;
	
	/**
	*	\brief Métodos de chamada de instância com sinalizadores de
	*	modo.
	*	@param[in]	int	Sinalizador de modo de execução.
	**/
	static CNTRLInterface * instance (int) throw (invalid_argument);
	static CNTRLInterface * instance () throw (invalid_argument);
};typedef class CNTRLInterface CONTROLLER;

#endif
