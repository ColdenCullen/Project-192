#include "stdafx.h"
#include "CgShader.h"
#include "Matrix4.h"
#include "Mesh.h"
#include "OutputController.h"
#include "Texture.h"
#include "GraphicsController.h"
#include "AdapterController.h"


#include <GL\glincludes.h>
using namespace OpenGL;
using namespace DirectX;
#include <Cg\cgGL.h>
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
		cgD3D11SetDevice( cgContext, AdapterController::Get()->GetDevice().dxDevice );
		cgVertexProfile = cgD3D11GetLatestVertexProfile();
		cgFragmentProfile = cgD3D11GetLatestPixelProfile();

	}
#endif//_WIN32
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
		cgD3D11LoadProgram( cgVertexProgram, NULL );
		cgD3D11LoadProgram( cgFragmentProgram, NULL );

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
/*POS*/		{ "ATTR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
/*UV*/		{ "ATTR", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
/*NORMAL*/	{ "ATTR", 2, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		ID3DBlob* vertexShaderBuffer = cgD3D11GetCompiledProgram( cgVertexProgram );
		AdapterController::Get()->GetDevice().dxDevice->
			CreateInputLayout( layout, 3, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &vertexLayout );


	}
#endif//_WIN32
}

void CgShader::ShutdownCg( void )
{
#ifdef _WIN32
	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		cgD3D11SetDevice( cgContext, NULL );
	}
#endif
	cgDestroyContext( cgContext );
}

void CgShader::Shutdown( void )
{
	
	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		cgGLUnloadProgram( cgVertexProgram );
		cgGLUnloadProgram( cgFragmentProgram);
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		ReleaseCOMobjMacro( vertexLayout );
		cgD3D11UnloadProgram( cgVertexProgram );
		cgD3D11UnloadProgram( cgFragmentProgram );
	}
#endif//_WIN32
	cgDestroyProgram( cgVertexProgram );
	cgDestroyProgram( cgFragmentProgram );
	
	
}

void CgShader::Draw( const Mesh& mesh ) const
{
	CGparameter cgFragmentParam_decal = cgGetNamedParameter( cgFragmentProgram, "decal" );

	SetUniform( "modelViewProjection", modelViewProjection );

	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
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
		glDrawElements( GL_TRIANGLES, mesh.GetNumVertices(), GL_UNSIGNED_INT, NULL );

		// Disable profiles
		cgGLDisableProfile(cgVertexProfile);
		cgGLDisableProfile(cgFragmentProfile);
	
		cgGLDisableTextureParameter(cgFragmentParam_decal);
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		UINT strides[1] = { mesh.GetVertexSize() };
		UINT offsets[1] = { 0 };
		ID3D11Buffer* buffers[1] = { mesh.GetVertexBuffer() };
		auto deviceContext = AdapterController::Get()->GetDeviceContext().dxDeviceContext;
    
		deviceContext->IASetVertexBuffers( 0, 1, buffers, strides, offsets );
		deviceContext->IASetInputLayout( vertexLayout );    
		deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );   

		cgD3D11BindProgram( cgVertexProgram );
		cgD3D11BindProgram( cgFragmentProgram );

		cgD3D11SetSamplerStateParameter( cgFragmentParam_decal, NULL ); // NULL == default states

		deviceContext->Draw( mesh.GetNumVertices(), 0 );

		cgD3D11UnbindProgram( cgVertexProgram );
		cgD3D11UnbindProgram( cgFragmentProgram );
		
	}
#endif//_WIN32
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
		cgD3D11SetTextureParameter( cgGetNamedParameter( cgFragmentProgram, "decal" ), text.GetDxTextureId() );
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