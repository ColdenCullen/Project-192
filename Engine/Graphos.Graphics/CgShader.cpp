#include "stdafx.h"
#include "CgShader.h"

#define USE_GL
//#define USE_DX

#include "Matrix4.h"
#include "Mesh.h"

#if defined( USE_GL )
#include <GL\glincludes.h>
#include <Cg\cgGL.h>
#elif defined( USE_DX )
#include <Cg\cgD3D11.h>
#endif//USE_GL/USE_DX

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
			strError = string( "Compile Error:\n" ) + cgGetLastListing( context );
		}
		else
		{	// If not compiler error, print error
			strError = cgGetErrorString( error );
		}

		ISingleton<OutputController>::Get().PrintMessage( OutputType::OT_ERROR, string( "Cg Error: " ) + strError );
	}
}

void CgShader::InitCg( void )
{
//	cgGLRegisterStates( cgContext );
//	cgGLSetManageTextureParameters( cgContext, CG_TRUE );

	cgSetErrorHandler( &CgErrorHandler, NULL );

	cgContext = cgCreateContext();
	cgSetParameterSettingMode( cgContext, CG_DEFERRED_PARAMETER_SETTING );
	//cgSetContextBehavior( cgContext, CG_BEHAVIOR_3100 );

#if defined( USE_GL )

	//cgGLRegisterStates( cgContext );
	//cgGLSetManageTextureParameters( cgContext, CG_TRUE );

	cgVertexProfile = cgGLGetLatestProfile( CG_GL_VERTEX );
	cgGLSetOptimalOptions( cgVertexProfile );

	cgFragmentProfile = cgGLGetLatestProfile( CG_GL_FRAGMENT );
	cgGLSetOptimalOptions( cgFragmentProfile );

	cgGLEnableProfile( cgVertexProfile );
	cgGLEnableProfile( cgFragmentProfile );

#elif defined( USE_DX )



#endif//USE_GL/USE_DX
}

CgShader::CgShader( string effectPath )
{
	cgEffect = cgCreateEffectFromFile( cgContext, effectPath.c_str(), NULL );
	cgTechnique = cgGetFirstTechnique( cgEffect );

	while( ( cgTechnique && cgValidateTechnique( cgTechnique ) ) == CG_FALSE )
	{
		if( !cgTechnique )
		{
			ISingleton<OutputController>::Get().PrintMessage(
				OutputType::OT_ERROR,
				string( "No valid techniques found." )
				);

			break;
		}

		if( cgValidateTechnique( cgTechnique ) == CG_FALSE )
		{
			ISingleton<OutputController>::Get().PrintMessage(
				OutputType::OT_WARNING,
				string( "Technique " ) + string( cgGetTechniqueName( cgTechnique ) ) + string( " did not validate. Skipping." )
				);

			cgTechnique = cgGetNextTechnique( cgTechnique );
		}
	}
}

CgShader::CgShader( string vertexPath, string fragmentPath )
{
	cgVertexProgram = cgCreateProgramFromFile(
		cgContext,
		CG_SOURCE,
		vertexPath.c_str(),
		cgVertexProfile,
		"main",
		NULL );

	cgFragmentProgram = cgCreateProgramFromFile(
		cgContext,
		CG_SOURCE,
		fragmentPath.c_str(),
		cgFragmentProfile,
		"main",
		NULL );

#if defined( USE_GL )

	cgGLLoadProgram( cgVertexProgram );
	cgGLLoadProgram( cgFragmentProgram );

#elif defined( USE_DX )



#endif//USE_GL/USE_DX
}

void CgShader::Draw( const Mesh& mesh ) const
{
	CGparameter cgFragmentParam_decal = cgGetNamedParameter( cgFragmentProgram, "texture" );

	cgGLBindProgram( cgVertexProgram );
	
	cgGLEnableProfile( cgVertexProfile );
	
	cgGLBindProgram( cgFragmentProgram );
	
	cgGLEnableProfile( cgFragmentProfile );
	
	cgGLEnableTextureParameter(cgFragmentParam_decal);

	glBindVertexArray( mesh.GetVAO() );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer() );

	//CGpass pass = cgGetFirstPass( cgTechnique );
	//while( pass )
	//{
	//	cgSetPassState( pass );
		glDrawElements( GL_TRIANGLES, mesh.GetNumElements(), GL_UNSIGNED_INT, NULL );
	//	cgResetPassState( pass );

	//	pass = cgGetNextPass( pass );
	//}

	cgGLDisableProfile(cgVertexProfile);
	
	cgGLDisableProfile(cgFragmentProfile);
	
	cgGLDisableTextureParameter(cgFragmentParam_decal);
}

void CgShader::SetUniform( string name, int value ) const 
{
	//cgSetParameter1i( cgGetNamedEffectParameter( cgEffect, name.c_str() ), value );
}

void CgShader::SetUniform( string name, float value ) const 
{
	//cgSetParameter1f( cgGetNamedEffectParameter( cgEffect, name.c_str() ), value );
}

void CgShader::SetUniform( string name, const Matrix4& value ) const 
{
	//cgSetParameterValuefc( cgGetNamedEffectParameter( cgEffect, name.c_str() ), 16, value.dataArray );
}

CGcontext CgShader::cgContext;
CGprofile CgShader::cgVertexProfile;
CGprofile CgShader::cgFragmentProfile;