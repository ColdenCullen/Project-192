#include "DXShader.h"
#include "GraphicsController.h"
#include "AdapterController.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace DirectX;

// Requires the compiled shaders (.cso files)
DXShader::DXShader( std::string vertexPath, std::string fragmentPath )
{
	// Layout description, must match layout in vertex shader
	const int numLayoutElements = 3;
	const D3D11_INPUT_ELEMENT_DESC vLayout[] =
	{
/*POS*/		{ "ATTR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
/*UV*/		{ "ATTR", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
/*NORMAL*/	{ "ATTR", 2, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// ---- Load Vertex Shader
	ID3DBlob* vsb;
	std::wstring wVertexPath( vertexPath.begin(), vertexPath.end() );
	D3DReadFileToBlob( wVertexPath.c_str(), &vsb );

	AdapterController::Get()->GetDevice().dxDevice->CreateVertexShader( vsb->GetBufferPointer(), 
																		vsb->GetBufferSize(),
																		NULL,
																		&vertexShader );
	AdapterController::Get()->GetDevice().dxDevice->CreateInputLayout( vLayout,
																		numLayoutElements,//ARRAYSIZE(vertexLayout),
																		vsb->GetBufferPointer(),
																		vsb->GetBufferSize(),
																		&vertexLayout );

	ReleaseCOMobjMacro( vsb );

	// ---- Load Pixel Shader
	ID3DBlob* psb;
	std::wstring wPixelPath( fragmentPath.begin(), fragmentPath.end() );
	D3DReadFileToBlob( wPixelPath.c_str(), &psb );
	AdapterController::Get()->GetDevice().dxDevice->CreatePixelShader( psb->GetBufferPointer(),
																		psb->GetBufferSize(),
																		NULL,
																		&pixelShader );
	ReleaseCOMobjMacro( psb );

	// ---- Constant Buffer
	D3D11_BUFFER_DESC cBufferDesc;

																		
	
	

}

void DXShader::RegisterConstBuffer( Arguments args )
{
	/*
	auto RegisterStruct = [&]( Handle<Object> obj )
	{
		unsigned int totalSize = 0;
		ConstBuffer buf;

		for( int ii = 0; ii < obj->GetPropertyNames()->Length(); ++ii )
		{
			auto prop = obj->GetPropertyNames()->Get( ii );

			

			std::string name = std::string( *String::AsciiValue( prop ) );

			buf.meta[ name ] = std::pair<unsigned int, std::size_t>( totalSize, 4 );
		}
	};

	if( args.Data()->IsArray() )
	{
		auto vals = Handle<Array>::Cast( args.Data() );

		for( int ii = 0; ii < vals->Length(); ++ii )
		{
			RegisterStruct( vals->Get( ii )->ToObject() );
		}
	}
	else
	{
		RegisterStruct( args.Data() );
	}
	*/
}

DXShader::~DXShader(void)
{

}

void DXShader::Shutdown( void )
{

}

void DXShader::Draw( const Mesh& mesh ) const 
{

}

void DXShader::BindTexture( const Texture& text ) const 
{

}

void DXShader::SetUniform( std::string name, const float value, ShaderType type ) const
{

}

void DXShader::SetUniform( std::string name, const int value, ShaderType type ) const 
{

}

void DXShader::SetUniformArray( std::string name, const float* value, const int size, ShaderType type ) const 
{

}

void DXShader::SetUniformArray( std::string name, const int* value, const int size, ShaderType type ) const 
{

}