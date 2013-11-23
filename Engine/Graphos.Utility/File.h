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
			/**
			 * @typedef	std::vector<File> FileList
			 *
			 * @brief	A list of files found in a directory.
			 */
			typedef std::vector<File> FileList;

			/**
			 * @fn	static std::string ReadFile( std::string filePath );
			 *
			 * @brief	Reads a file for its contents.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	filePath	Full pathname of the file.
			 *
			 * @return	The file contents.
			 */
			static std::string	ReadFile( std::string filePath );

			/**
			 * @fn	static FileList ScanDir( std::string dirPath );
			 *
			 * @brief	Scans a directory for files.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	dirPath	Pathname of the directory.
			 *
			 * @return	A FileList of files returned.
			 */
			static FileList		ScanDir( std::string dirPath );
#pragma endregion

#pragma region Not Static Stuff
		public:
								File( std::string filePath );
								File( std::string fullPath, std::string name );
								File( std::string path, std::string localPath, std::string name );

			/**
			 * @fn	const std::string GetExtension( void ) const
			 *
			 * @brief	Gets the extension of the file.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The extension of the file.
			 */
			const std::string	GetExtension( void ) const	{ return fileName.substr( fileName.find_last_of( '.' ) ); }

			/**
			 * @fn	const std::string GetFileName( void ) const
			 *
			 * @brief	Gets file name.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The file name of the file.
			 */
			const std::string	GetFileName( void )	const	{ return fileName; }

			/**
			 * @fn	const std::string GetFullPath( void ) const
			 *
			 * @brief	Gets full path of the file.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The full path of the file.
			 */
			const std::string	GetFullPath( void ) const	{ return fullPath + fileName; }

			/**
			 * @fn	const std::string GetLocalPath( void ) const
			 *
			 * @brief	Gets local path of the file.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The local path of the file.
			 */
			const std::string	GetLocalPath( void ) const	{ return localPath; }

			/**
			 * @fn	const std::string GetContents( void ) const
			 *
			 * @brief	Gets the contents of the file.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The contents of the file.
			 */
			const std::string	GetContents( void ) const	{ return File::ReadFile( GetFullPath() ); }

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