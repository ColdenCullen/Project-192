#ifndef __OUTPUT_MANAGER
#define __OUTPUT_MANAGER

#include <string>
#include <iostream>

namespace Graphos
{
	namespace Core
	{
		enum class				OutputType { OT_INFO, OT_WARNING, OT_ERROR };

		class OutputController
		{
		public:
			static void			PrintMessage( OutputType type, std::string message );
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
			static bool			GetWhetherPrint( OutputType type );
		};
	}
}

#endif//__OUTPUT_MANAGER
