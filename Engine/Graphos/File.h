#ifndef __FILE
#define __FILE

#include <string>
#include <vector>

namespace Graphos
{
	namespace Core
	{
		struct File
		{
#pragma region Static Stuff
		public:
			// Typedefs
			typedef std::vector<File> FileList;

			// Readers
			static std::string	ReadFile( std::string filePath );
			static FileList		ScanDir( std::string dirPath );
#pragma endregion

#pragma region Not Static Stuff
		public:
			std::string			location;
			std::string			localPath;
			std::string			name;

								File( std::string filePath );
								File( std::string path, std::string name );

			const std::string	GetFullPath( void ) const;
			const std::string	GetContents( void ) const;

		private:
			void				Initialize( std::string p, std::string n );
#pragma endregion
		};
	}
}

#endif//__FILE