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
								File( std::string filePath );
								File( std::string fullPath, std::string name );
								File( std::string path, std::string localPath, std::string name );

			const std::string	GetFileName( void ) const { return fileName; }
			const std::string	GetFullPath( void ) const { return fullPath + fileName; }
			const std::string	GetLocalPath( void )const { return localPath; }
			const std::string	GetContents( void ) const { return File::ReadFile( GetFullPath() ); }

		private:
			std::string			fullPath;
			std::string			localPath;
			std::string			fileName;

			void				Initialize( std::string p, std::string lp, std::string n );
#pragma endregion
		};
	}
}

#endif//__FILE