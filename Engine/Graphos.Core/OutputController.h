#ifndef __OUTPUT_MANAGER
#define __OUTPUT_MANAGER

#include "IController.h"
#include "ISingleton.h"

#include <string>
#include <iostream>

namespace Graphos
{
	namespace Core
	{
		enum class				OutputType { OT_INFO, OT_WARNING, OT_ERROR };

		class OutputController : public IController
		{
		public:
			void				PrintMessage( OutputType type, std::string message );
			template<typename T>
			void				PrintValue( OutputType type, std::string varName, T value )
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

			std::string			GetOutputHeader( OutputType type );
			bool				GetWhetherPrint( OutputType type );

			friend class		ISingleton<OutputController>;
		};
	}
}

#endif//__OUTPUT_MANAGER