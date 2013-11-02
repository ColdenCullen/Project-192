#include <memory>
#include <DirectX/DirectXIncludes.h>

#include "DXShader.h"
#include "GraphicsController.h"
#include "AdapterController.h"
#include "OutputController.h"

using namespace v8;
using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace DirectX;

// Requires the compiled shaders (.cso files)
DXShader::DXShader( string vertexPath, string fragmentPath )
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
	wstring wVertexPath( vertexPath.begin(), vertexPath.end() );
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
	wstring wPixelPath( fragmentPath.begin(), fragmentPath.end() );
	D3DReadFileToBlob( wPixelPath.c_str(), &psb );
	AdapterController::Get()->GetDevice().dxDevice->CreatePixelShader( psb->GetBufferPointer(),
																		psb->GetBufferSize(),
																		NULL,
																		&pixelShader );
	ReleaseCOMobjMacro( psb );
}

void DXShader::RegisterConstBuffer( string name, ConstBuffer* buf )
{
	buffer = buf;

	// ---- Constant Buffer
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.ByteWidth			= buf->size;
	cBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags		= 0;
	cBufferDesc.MiscFlags			= 0;
	cBufferDesc.StructureByteStride = 0;
	HR(AdapterController::Get()->GetDevice().dxDevice->CreateBuffer(
		&cBufferDesc,
		NULL,
		&buffer->vsConsantBuffer));
}

DXShader::~DXShader(void)
{
	Shutdown();
}

void DXShader::Shutdown( void )
{
	delete buffer;
	ReleaseCOMobjMacro( vertexShader );
	ReleaseCOMobjMacro( pixelShader );
	ReleaseCOMobjMacro( vertexLayout );
}

void DXShader::Draw( const Mesh& mesh ) const 
{

}

void DXShader::BindTexture( const Texture& text ) const 
{

}

void DXShader::BuildConstBuffer( v8::Arguments args )
{
	auto BuildStruct = [&]( Handle<Object> obj )
	{
		// Total size of the struct
		size_t totalSize = 0;
		ConstBuffer* buf = new ConstBuffer();

		for( unsigned int ii = 0; ii < obj->GetPropertyNames()->Length(); ++ii )
		{
			// Get the property
			auto prop = obj->GetPropertyNames()->Get( ii );

			// Get size of object
			size_t size;
			if( prop->IsBoolean() )
			{
				size = 1;
			}
			else if( prop->IsArray() )
			{
				size = 4 * Handle<Array>::Cast( prop )->Length();
			}
			else if( prop->IsObject() )
			{
				size = 4 * prop->ToObject()->GetPropertyNames()->Length();
			}
			else
			{
				size = 4;
			}

			// Get the name of the property
			string name = string( *String::AsciiValue( prop ) );

			// Store the property's offset and size
			buf->meta[ name ] = pair<unsigned int, size_t>( totalSize, size );

			// Update current offset
			totalSize += size;
		}

		// Allocate buffer space
		buf->data = new char[ totalSize ];
		buf->size = totalSize;

		return buf;
	};

	if( args.Data()->IsArray() )
	{
		auto obj = Handle<Array>::Cast( args.Data() );

		for( unsigned int ii = 0; ii < obj->Length(); ++ii )
		{
			RegisterConstBuffer( "", BuildStruct( obj->Get( ii )->ToObject() ) );
		}
	}
	else
	{
		RegisterConstBuffer( "", BuildStruct( args.Data()->ToObject() ) );
	}
	
}

#pragma region SetUniforms
void DXShader::SetUniform( string name, const float value, ShaderType type ) const
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid name in SetUniform" );
	if( it->second.second == sizeof( value ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Data size mismatch in SetUniform(float)" );

	memcpy( buffer->data + it->second.first, &value, it->second.second );
}

void DXShader::SetUniform( string name, const int value, ShaderType type ) const 
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid name in SetUniform" );
	if( it->second.second == sizeof( value ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Data size mismatch in SetUniform(int)" );

	memcpy( buffer->data + it->second.first, &value, it->second.second );
}

void DXShader::SetUniformArray( string name, const float* value, const int size, ShaderType type ) const 
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid name in SetUniform" );
	if( it->second.second == sizeof( *value )*size )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Data size mismatch in SetUniformArray(float)" );
	
	memcpy( buffer->data + it->second.first, value, it->second.second );
}

void DXShader::SetUniformArray( string name, const int* value, const int size, ShaderType type ) const 
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid name in SetUniform" );
	if( it->second.second == sizeof( *value )*size )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Data size mismatch in SetUniformArray(int)" );
	
	memcpy( buffer->data + it->second.first, value, it->second.second );
}
#pragma endregion
