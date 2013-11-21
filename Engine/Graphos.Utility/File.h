#ifndef __FILE
#define __FILE

#include <string>
#include <vector>

namespace Graphos
{
	namespace Utility
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

			const std::string	GetExtension( void ) const	{ return extension; }
			const std::string	GetFileName( void )	const	{ return fileName; }
			const std::string	GetFullPath( void ) const	{ return fullPath; }
			const std::string	GetDirectory( void ) const	{ return directory; }
			const std::string	GetLocalPath( void ) const	{ return localPath; }
			const std::string	GetContents( void ) const	{ return File::ReadFile( GetFullPath() ); }

		private:
			std::string			extension;
			std::string			fileName;
			std::string			fullPath;
			std::string			directory;
			std::string			localPath;
#pragma endregion
		};
	}
}

#endif//__FILE