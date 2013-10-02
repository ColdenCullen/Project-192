#include "stdafx.h"
#include "CgShader.h"
#include "Matrix4.h"
#include "Mesh.h"
#include "OutputController.h"
#include "Texture.h"
#include "GraphicsController.h"

#include <GL/glincludes.h>
#include <Cg/cgGL.h>
#ifdef _WIN32
#include <Cg/cgD3D11.h>
#endif//_WIN32

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
	cgSetErrorHandler( &CgErrorHandler, NULL );

	cgContext = cgCreateContext();

	cgSetParameterSettingMode( cgContext, CG_DEFERRED_PARAMETER_SETTING );

	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
#ifndef _DEBUG
		cgGLSetDebugMode( CG_FALSE );
#else
		cgGLSetDebugMode( CG_TRUE );
#endif

		cgVertexProfile = cgGLGetLatestProfile( CG_GL_VERTEX );
		cgGLSetOptimalOptions( cgVertexProfile );
		cgGLEnableProfile( cgVertexProfile );

		cgFragmentProfile = cgGLGetLatestProfile( CG_GL_FRAGMENT );
		cgGLSetOptimalOptions( cgFragmentProfile );
		cgGLEnableProfile( cgFragmentProfile );
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{

	}
#endif//_WIN32
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

	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		cgGLLoadProgram( cgVertexProgram );
		cgGLLoadProgram( cgFragmentProgram );
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{

	}
#endif//_WIN32
}

void CgShader::Draw( const Mesh& mesh ) const
{
	CGparameter cgFragmentParam_decal = cgGetNamedParameter( cgFragmentProgram, "decal" );

	SetUniform( "modelViewProjection", modelViewProjection );

	// Bind programs and profiles
	cgGLBindProgram( cgVertexProgram );
	cgGLEnableProfile( cgVertexProfile );
	cgGLBindProgram( cgFragmentProgram );
	cgGLEnableProfile( cgFragmentProfile );
	
	// Enable the texture parameter
	cgGLEnableTextureParameter( cgFragmentParam_decal );

	// Bind the mesh elements
	glBindVertexArray( mesh.GetVAO() );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer() );

	// Draw the elements
	glDrawElements( GL_TRIANGLES, mesh.GetNumElements(), GL_UNSIGNED_INT, NULL );

	// Disable profiles
	cgGLDisableProfile(cgVertexProfile);
	cgGLDisableProfile(cgFragmentProfile);
	
	cgGLDisableTextureParameter(cgFragmentParam_decal);
}

void CgShader::BindTexture( const Texture& text ) const
{
	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		cgGLSetTextureParameter( cgGetNamedParameter( cgFragmentProgram, "decal" ), text.GetGlTextureId() );
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{

	}
#endif//_WIN32
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
	cgSetParameterValuefc( cgGetNamedParameter( cgVertexProgram, name.c_str() ), 16, value.dataArray );
}

CGcontext CgShader::cgContext;
CGprofile CgShader::cgVertexProfile;
CGprofile CgShader::cgFragmentProfile;