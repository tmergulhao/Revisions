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

/**
*	\brief Classe virtual responsável pela persistência no banco de dados
*	
*	É um interface virtual com alocação de objeto escondida.
**/
class SQLInterface {
	/**
	*	\brief Ponteiro de instância para alocação do objeto singular.
	**/
		static SQLInterface * p_instance;
	public:
		/**
		*	\brief Métodos construtores de chamada de instância.
		**/
		SQLInterface () {}
		SQLInterface (int);
		~SQLInterface () {}
		
		// PROJECT
		//////////
		
		/**
		*	\brief Verifica se base de dados está definida.
		**/
		virtual bool Empty () = 0;
		/**
		*	\brief Inicia projeto segundo desenvolvedor administrador.
		**/
		virtual void InitProject (Developer) = 0;
		/**
		*	\brief Verifica se desenvolvedor é o administrador
		*	
		*	@param[in]	email	email de desenvolvedor padrão.
		**/
		virtual bool IsOwner (email) throw (invalid_argument) = 0;
		/**
		*	\brief Passa administração do sistema para outro desenvolvedor
		*	
		*	@param[in]	email	email de desenvolvedor padrão.
		**/
		virtual void PassOwnership (email) = 0;
		
		// DEVELOPERS
		/////////////
		/**
		*	\brief Busca se há desenvolvedor na base de dados.
		*	
		*	@param[in]	email	email de desenvolvedor.
		*	@param[out]	bool	resultado verdadeiro se há.
		**/
		virtual bool HasDeveloper (email) = 0;
		/**
		*	\brief Adiciona desenvolvedor na base de dados.
		*	
		*	@param[in]	Developer	objeto de desenvolvedor.
		**/
		virtual void AddDeveloper (Developer) throw (invalid_argument) = 0;
		/**
		*	\brief Retorna desenvolvedor da base de dados.
		*	
		*	@param[in]	email	email de desenvolvedor.
		*	@param[out]	Developer	objeto de desenvolvedor.
		**/
		virtual Developer FetchDeveloper (email) throw (invalid_argument) = 0;
		/**
		*	\brief Atualiza nome de desenvolvedor.
		*	
		*	@param[in]	Developer	objeto de desenvolvedor.
		*	@param[in]	dev_name	nome de desenvolvedor.
		**/
		virtual void UpdateDeveloperName (Developer, dev_name) throw (invalid_argument) = 0;
		/**
		*	\brief Atualiza senha de desenvolvedor.
		*	
		*	@param[in]	Developer	objeto de desenvolvedor.
		*	@param[in]	password	senha de desenvolvedor.
		**/
		virtual void UpdateDeveloperPassword (Developer, password) throw (invalid_argument) = 0;
		/**
		*	\brief Remove desenvolvedor.
		*	
		*	@param[in]	email	email de desenvolvedor.
		**/
		virtual void RemoveDeveloper (email) = 0;
		/**
		*	\brief Retona número de produtos referentes a desenvolvedor.
		*	
		*	@param[in]	email	email de desenvolvedor.
		*	@param[out]	int		número de produtos.
		**/
		virtual int DevAssignProducts (email) = 0;
		
		// PRODUCTS
		///////////
		/**
		*	\brief Procura por produto na base de dados
		*	
		*	@param[in]	code	código de produto.
		**/
		virtual bool HasProduct (code) = 0;
		/**
		*	\brief Adição de produto na base de dados
		*	
		*	@param[in]	Product	objeto de produto.
		**/
		virtual void AddProduct (Product) = 0;
		/**
		*	\brief Atualização do nome do produto
		*	
		*	@param[in]	Product	objeto de produto.
		**/
		virtual void UpdateProductName (Product) = 0;
		/**
		*	\brief Atualização da versão do produto.
		*	
		*	@param[in]	Product	objeto de produto.
		**/
		virtual void UpdateProductVersion (Product) = 0;
		/**
		*	\brief Atualização do responsável pelo produto
		*	
		*	@param[in]	Product	objeto de produto.
		*	@param[in]	Developer	objeto de desenvolvedor.
		**/
		virtual void UpdateProductDeveloper (Product, Developer) = 0;
		/**
		*	\brief Remoção de produto do banco de dados
		*	
		*	@param[out]	code	código do produto.
		**/
		virtual void RemoveProduct (code) = 0;
		/**
		*	\brief Interface de chamada de produtos em banco de dados
		*	
		*	@param[out]	list<Product>	lista dinâmica de produtos.
		**/
		virtual list<Product> ListProducts () = 0;
		
		// DEFECTS
		//////////
		/**
		*	\brief Busca se há defeito referente a código.
		*	
		*	@param[in]	code	código de defeito.
		**/
		virtual bool HasDefect (code) = 0;
		/**
		*	\brief Adiciona defeito ao banco de dados.
		*	
		*	@param[in]	Product	produto referente.
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void AddDefect (Product, Defect) = 0;
		/**
		*	\brief Retorna defeito referente a código
		*	
		*	@param[in]	code	código de defeito.
		**/
		virtual Defect FetchDefect (code) throw (invalid_argument) = 0;
		/**
		*	\brief Atualiza nome de defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void UpdateDefectName (Defect) = 0;
		/**
		*	\brief Atualiza descrição de defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void UpdateDefectDescription (Defect) = 0;
		/**
		*	\brief Assinala defeito a desenvolvedor.
		*	
		*	@param[in]	Defect		objeto de defeito.
		*	@param[in]	Developer	objeto de desenvolvedor.
		**/
		virtual void UpdateDefectDeveloper (Defect, Developer) = 0;
		/**
		*	\brief Atualiza votos de defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void UpdateDefectVotes (Defect) = 0;
		/**
		*	\brief Atualiza estado de defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void UpdateDefectState (Defect) = 0;
		/**
		*	\brief Adiciona data de fechamento a defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void UpdateDefectClose (Defect) = 0;
		/**
		*	\brief Conta número de defeitos em desenvolvedor.
		*	
		*	@param[in]	email	email do desenvolvedor.
		*	@param[out]	int		número de defeitos.
		**/
		virtual int DevAssignDefects (email) = 0;
		/**
		*	\brief Conta número de defeitos abertos no projeto.
		*	
		*	@param[in]	code	código do projeto.
		*	@param[out]	int		número de defeitos.
		**/
		virtual int ProdAssignDefects (code) = 0;
		/**
		*	\brief Remove defeito do banco de dados.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void RemoveDefect (Defect) = 0;
		/**
		*	\brief Interface de chamada de defeitos de produto em banco de dados
		*	
		*	@param[in]	Product			produto referente.
		*	@param[out]	list<Defect>	lista dinâmica de defeitos.
		**/
		virtual list<Defect> ListDefects (Product) = 0;
		
		// DEFECT CANDIDATES
		////////////////////
		/**
		*	\brief Adiciona candidato a tabela do defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		*	@param[in]	Developer	objeto de desenvolvedor.
		**/
		virtual void AddCandidade (Defect, Developer) = 0;
		/**
		*	\brief Checa se desenvolvedor é candidato a defeito.
		*	
		*	@param[in]	Defect	objeto de defeito.
		*	@param[in]	Developer	objeto de desenvolvedor.
		**/
		virtual bool IsCandidade (Defect, Developer) = 0;
		/**
		*	\brief Remove todos os candidatos a defeito da tabela.
		*	
		*	@param[in]	Defect	objeto de defeito.
		**/
		virtual void WipeCandidades (Defect) = 0;
		
		/**
		*	\brief Métodos de chamada de instância com sinalizadores de
		*	modo.
		*	@param[in]	int	Sinalizador de modo de execução.
		**/
		static SQLInterface * instance (int) throw (invalid_argument);
		static SQLInterface * instance () throw (invalid_argument);
};typedef class SQLInterface SQLINTERFACE;

#endif
