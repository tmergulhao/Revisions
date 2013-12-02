#ifndef COMMAND_H
#define COMMAND_H

//-----------------------------------------------------------------------
// USER INTERFACE METHACLASS
//-----------------------------------------------------------------------

/**
*	\brief Classe virtual responsável pela ferramenta de linha de comando 
*	e pela alocação de recursos em camada via o flag de instância.
*	
*	É um interface virtual com alocação de objeto escondida.
**/
class MethaUI {
		/**
		*	\brief Ponteiro de instância para alocação do objeto singular.
		**/
		static MethaUI * p_instance;
	public:
		/**
		*	\brief Método de execução do ambiente de linha de comando.
		**/
		virtual void Run () {}
		
		/**
		*	\brief Métodos construtores de chamada de instância.
		**/
		MethaUI () {}
		MethaUI (int);
		
		virtual ~MethaUI () {}
		
		/**
		*	\brief Métodos de chamada de instância com sinalizadores de
		*	modo.
		*	@param[in]	int	Sinalizador de modo de execução.
		**/
		static MethaUI * instance (int);
		static MethaUI * instance ();
};typedef class MethaUI USRINTERFACE;

#endif
