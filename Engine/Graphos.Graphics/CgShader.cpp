#include "stdafx.h"
#include "CgShader.h"

#include <Cg\cgGL.h>
#ifdef _WIN32
#include <Cg\cgD3D11.h>
#endif//_WIN32

using namespace std;
using namespace Graphos::Graphics;

CgShader& CgShader::Initialize( std::string filePath )
{
	InitializeForGl( filePath );
#if _WIN32
	//InitializeForDx( name );
#endif

	return *this;
}

void Graphos::Graphics::CgShader::InitializeForGl( std::string filePath )
{
	if( !( cgContext = cgCreateContext() ) )
		throw exception( "Error creating CG Context" );

	if( ( cgVertexProfile = cgGLGetLatestProfile( CG_GL_VERTEX ) ) == CG_PROFILE_UNKNOWN )
		throw exception( "Error getting CG GL profile" );

	if( !( cgProgram = cgCreateProgramFromFile( cgContext, CG_SOURCE, filePath.c_str(), cgVertexProfile, "main", 0 ) ) )
		throw exception( "Error creating CG program." );

	cgGLLoadProgram( cgProgram );
}

#ifdef _WIN32
void CgShader::InitializeForDx( std::string filePath )
{
	if( !( cgContext = cgCreateContext() ) )
		throw exception( "Error creating CG Context" );

	if( ( cgVertexProfile = cgGLGetLatestProfile( CG_GL_VERTEX ) ) == CG_PROFILE_UNKNOWN )
		throw exception( "Error getting CG GL profile" );

	if( !( cgProgram = cgCreateProgramFromFile( cgContext, CG_SOURCE, filePath.c_str(), cgVertexProfile, "main", 0 ) ) )
		throw exception( "Error creating CG program." );

	//( cgProgram );
}
#endif//_WIN32