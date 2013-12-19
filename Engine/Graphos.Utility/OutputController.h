#ifndef __OUTPUT_MANAGER
#define __OUTPUT_MANAGER

#include <string>
#include <iostream>

namespace Graphos
{
	namespace Utility
	{
		/**
		 * @enum	
		 *
		 * @brief	Values that represent the types of output.
		 */
		enum class				OutputType { Info, Warning, Error };

		/**
		 * @class	OutputController
		 *
		 * @brief	A controller for handling output.
		 *
		 * @author	Colden Cullen
		 */
		class OutputController
		{
		public:
			/**
			 * @fn	static void OutputController::PrintMessage( OutputType type, std::string message );
			 *
			 * @brief	Print a message.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	type   	The type of message.
			 * @param	message	The message.
			 */
			static void			PrintMessage( OutputType type, std::string message );
			
			/**
			 * @fn	static void OutputController::PrintValue( OutputType type, std::string varName, T value )
			 *
			 * @brief	Print a Variable.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	type   	The type of message.
			 * @param	varName	Name of the variable.
			 * @param	value  	The variable.
			 */
			template<typename T>
			static void			PrintValue( OutputType type, std::string varName, T value )
			{
				if( GetWhetherPrint( type ) )
				{
					std::cout << GetOutputHeader( type ) << " " << varName << ": " << value << std::endl;
				}
			}

		private:
								OutputController( void ) { }
								OutputController( const OutputController& );
			OutputController&	operator=( const OutputController& );
			
			static std::string	GetOutputHeader( OutputType type );
			static gBool		GetWhetherPrint( OutputType type );
		};
	}
}

#endif//__OUTPUT_MANAGER
