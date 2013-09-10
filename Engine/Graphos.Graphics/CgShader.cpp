#include "stdafx.h"
#include "CgShader.h"

#include "Matrix4.h"

#include <Cg\cgGL.h>
#ifdef _WIN32
#include <Cg\cgD3D11.h>
#endif//_WIN32
#include <sstream>
#include "ISingleton.h"
#include "OutputController.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

void CgErrorHandler( CGcontext context, CGerror error, void* appData )
{
	if( error != CG_NO_ERROR )
	{	// If there is an error, print it
		string strError;

		if( error == CG_COMPILER_ERROR )
		{	// If error is a compiler error, output it
			strError = cgGetLastListing( context );
		}
		else
		{	// If not compiler error, print error
			strError = cgGetErrorString( error );
		}

		ISingleton<OutputController>::Get().PrintMessage( OutputType::OT_ERROR, string( "Cg Error: \n" ) + strError );
	}
}

CgShader& CgShader::Initialize( std::string filePath )
{
	//cgSetErrorHandler( &CgErrorHandler, NULL );

	if( !cgContext )
	{
		cgContext = cgCreateContext();

		InitializeForGl( filePath );

		cgSetErrorHandler( &CgErrorHandler, NULL );
	}

	cgEffect = cgCreateEffectFromFile( cgContext, filePath.c_str(), NULL );

	cgTechnique = cgGetFirstTechnique( cgEffect );

#if _WIN32
	//InitializeForDx( name );
#endif

	return *this;
}

void CgShader::InitializeForGl( std::string filePath )
{
	cgGLRegisterStates( cgContext );
	cgGLSetManageTextureParameters( cgContext, CG_TRUE );
}

#ifdef _WIN32
void CgShader::InitializeForDx( std::string filePath )
{

}
#endif//_WIN32

void CgShader::Use( void ) const 
{

}

void CgShader::SetUniform( string name, int value ) const 
{
	cgSetParameter1i( cgGetNamedEffectParameter( cgEffect, name.c_str() ), value );
}

void CgShader::SetUniform( string name, float value ) const 
{
	cgSetParameter1f( cgGetNamedEffectParameter( cgEffect, name.c_str() ), value );
}

void CgShader::SetUniform( string name, const Matrix4& value ) const 
{
	cgSetParameterValuefc( cgGetNamedEffectParameter( cgEffect, name.c_str() ), 16, value.dataArray );
}

CGcontext CgShader::cgContext;