#include <memory>
#include <DirectX/DirectXIncludes.h>

#include "DXShader.h"
#include "GraphicsController.h"
#include "AdapterController.h"
#include "OutputController.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameObject.h"

using namespace v8;
using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;
using namespace Graphos::Utility;
using namespace DirectX;

#include <d3dcompiler.inl>


// Requires the compiled shaders (.cso files)
DXShader::DXShader( string vertexPath, string fragmentPath )
{
	HRESULT result;
	ID3DBlob* shaderCompileErrors;

	// Layout description, must match layout in vertex shader
	const int numLayoutElements = 3;
	const D3D11_INPUT_ELEMENT_DESC vLayout[] =
	{
/*POS*/		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
/*UV*/		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
/*NORMAL*/	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// ---- Load Vertex Shader
	ID3DBlob* vsb;
	wstring wVertexPath( vertexPath.begin(), vertexPath.end() );
	//D3DReadFileToBlob( wVertexPath.c_str(), &vsb );
	result = D3DCompileFromFile( wVertexPath.c_str(),
								NULL,
								NULL,
								"main",
								"vs_5_0",
								D3DCOMPILE_ENABLE_STRICTNESS,
								0,
								&vsb,
								&shaderCompileErrors );

	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Error compiling vertex shader\n" + vertexPath );
		OutputController::PrintMessage( OutputType::Error, (char*)(shaderCompileErrors->GetBufferPointer()) );
	}
	
	result = AdapterController::Get()->GetDevice().dx->CreateVertexShader( vsb->GetBufferPointer(), 
																vsb->GetBufferSize(),
																NULL,
																&vertexShader );
	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Failed to create vertex shader." );
	}

	// Create Input Layout
	result = AdapterController::Get()->GetDevice().dx->CreateInputLayout( vLayout,
																numLayoutElements,//ARRAYSIZE(vertexLayout),
																vsb->GetBufferPointer(),
																vsb->GetBufferSize(),
																&vertexLayout );
	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Failed to create input layout." );
	}
	

	// ---- Load Pixel Shader
	ID3DBlob* psb;
	wstring wPixelPath( fragmentPath.begin(), fragmentPath.end() );
	//D3DReadFileToBlob( wPixelPath.c_str(), &psb );
	result = D3DCompileFromFile( wPixelPath.c_str(),
								NULL,
								NULL,
								"main",
								"ps_5_0",
								D3DCOMPILE_ENABLE_STRICTNESS,
								0,
								&psb,
								&shaderCompileErrors );

	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Error compiling fragment shader\n" + fragmentPath );
		OutputController::PrintMessage( OutputType::Error, (gChar*)(shaderCompileErrors->GetBufferPointer()) );
	}

	result = AdapterController::Get()->GetDevice().dx->CreatePixelShader( psb->GetBufferPointer(),
																psb->GetBufferSize(),
																NULL,
																&pixelShader );
	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Failed to create fragment shader." );
	}

	// get constant buffer variables
	ID3D11ShaderReflection* vsReflection = nullptr;
	D3D11Reflect( vsb->GetBufferPointer(), vsb->GetBufferSize(), &vsReflection );
	D3D11_SHADER_BUFFER_DESC vsShaderBufferDesc;
	vsReflection->GetConstantBufferByName( "uniforms" )->GetDesc( &vsShaderBufferDesc );
	vsShaderBufferDesc.Name;
	UINT numVariables = vsShaderBufferDesc.Variables;
	ID3D11ShaderReflectionVariable* var2 = vsReflection->GetConstantBufferByName( "uniforms" )->GetVariableByIndex( 2 );
	
	D3D11_SHADER_VARIABLE_DESC var2Desc;
	var2->GetDesc( &var2Desc );
	var2Desc.Name;
	var2Desc.Size;

	ID3D11ShaderReflectionType* var2Type = var2->GetType();
	var2Type->GetMemberTypeByIndex(0);
	

	

	// ---- Create Sampler State
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = AdapterController::Get()->GetDevice().dx->CreateSamplerState( &samplerDesc, &samplerState );
	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Failed to create sampler state." );
	}

	// release unneeded buffers
	ReleaseCOMobjMacro( psb );
	ReleaseCOMobjMacro( vsb );
	ReleaseCOMobjMacro( shaderCompileErrors );

	// TEMPORARY BUFFER TO BE REMOVED FROM C++ SIDE
	auto buf = new ConstBuffer;
	buf->totalSize = 0;
	buf->AddProperty( "modelViewProj", sizeof(Matrix4) );
	buf->AddProperty( "rotationMatrix", sizeof(Matrix4) );

	RegisterConstBuffer( "uniforms", buf );
	delete buf;
}

void DXShader::RegisterConstBuffer( string name, ConstBuffer* buf )
{
	buffer = new DxConstBuffer();
	buffer->meta = buf->meta;
	buffer->totalSize = buf->totalSize;
	buffer->data = new gByte[ buffer->totalSize ];

	// ---- Constant Buffer
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.ByteWidth			= buf->totalSize; // must be multiple of 16 if a CONSTANT_BUFFER
	cBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags		= 0;
	cBufferDesc.MiscFlags			= 0;
	cBufferDesc.StructureByteStride = 0;
	HRESULT result = AdapterController::Get()->GetDevice().dx->CreateBuffer( &cBufferDesc,
																NULL,
																&buffer->vsConstantBuffer);
	if( FAILED(result) )
	{
		OutputController::PrintMessage( OutputType::Error, "Failed to create constant buffer " + name );
	}

}

DXShader::~DXShader(void)
{
	Shutdown();
}

void DXShader::Shutdown( void )
{
	IShader::Shutdown();
	delete buffer;
	ReleaseCOMobjMacro( vertexShader );
	ReleaseCOMobjMacro( pixelShader );
	ReleaseCOMobjMacro( vertexLayout );
	ReleaseCOMobjMacro( samplerState );
}

void DXShader::Draw( Mesh& mesh ) const 
{
	auto deviceContext = AdapterController::Get()->GetDeviceContext().dx;

	SetUniformMatrix( "modelViewProj", *modelViewProjection );
//	SetUniformMatrix( "modelMatrix", mesh.Owner()->transform->RotationMatrix() );

	// update constant buffer on the GPU
	deviceContext->UpdateSubresource( buffer->vsConstantBuffer,
									0,
									NULL,
									buffer->data,
									0,
									0 );
	//deviceContext->Map( buffer->vsConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,

	// set up input assembler
	deviceContext->IASetInputLayout( vertexLayout );
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	UINT strides[1] = { mesh.GetVertexSize() };
	UINT offsets[1] = { 0 };
	ID3D11Buffer* buffers[1] = { mesh.GetVertexBuffer().dx };
	
	// set buffers 
	deviceContext->IASetVertexBuffers( 0, 1, buffers, strides, offsets );
	deviceContext->IASetInputLayout( vertexLayout );    
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ); 
	deviceContext->IASetIndexBuffer( mesh.GetIndexBuffer().dx, DXGI_FORMAT_R32_UINT, 0 );
	
	// set shaders
	deviceContext->VSSetShader( vertexShader, NULL, 0 );
	deviceContext->VSSetConstantBuffers( 0, 1, &buffer->vsConstantBuffer );
	deviceContext->PSSetShader( pixelShader, NULL, 0 );

	// set sampler state
	deviceContext->PSSetSamplers( 0, 1, &samplerState );

	// draw
	deviceContext->DrawIndexed( mesh.GetNumIndices(), 0, 0 );

}

void DXShader::BindTexture( Texture& text ) const 
{
	// set the texture in the shader
	AdapterController::Get()->GetDeviceContext().dx->PSSetShaderResources( 0, 1, &text.GetTextureId().dx );
}

#pragma region SetUniforms 
//
// For DirectX, these should only update the data on the CPU side
// Draw should update once on the GPU
//

void DXShader::SetUniform( string name, const gFloat value ) const
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::Error, "Invalid name in SetUniform" );
	if( it->second.second != sizeof( value ) )
		OutputController::PrintMessage( OutputType::Error, "Data size mismatch in SetUniform(gFloat)" );

	memcpy( buffer->data + it->second.first, &value, it->second.second );
}

void DXShader::SetUniform( string name, const int value ) const 
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::Error, "Invalid name in SetUniform" );
	if( it->second.second != sizeof( value ) )
		OutputController::PrintMessage( OutputType::Error, "Data size mismatch in SetUniform(int)" );

	memcpy( buffer->data + it->second.first, &value, it->second.second );
}

void DXShader::SetUniformArray( string name, const gFloat* value, const int size ) const 
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::Error, "Invalid name in SetUniform" );
	if( it->second.second != sizeof( *value )*size )
		OutputController::PrintMessage( OutputType::Error, "Data size mismatch in SetUniformArray(gFloat)" );
	
	memcpy( buffer->data + it->second.first, value, it->second.second );
}

void DXShader::SetUniformArray( string name, const int* value, const int size ) const 
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::Error, "Invalid name in SetUniform" );
	if( it->second.second != sizeof( *value )*size )
		OutputController::PrintMessage( OutputType::Error, "Data size mismatch in SetUniformArray(int)" );
	
	memcpy( buffer->data + it->second.first, value, it->second.second );
}

void DXShader::SetUniformBuffer( string name, const gByte* value, const size_t size) const
{
	auto it = buffer->meta.find( name );

	if( it == end( buffer->meta ) )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid name in SetUniform" );
	if( it->second.second != sizeof( *value )*size )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Data size mismatch in SetUniformBuffer" );
	
	memcpy( buffer->data + it->second.first, value, it->second.second );
}

void DXShader::SetUniformMatrix( std::string name, const Matrix4& matrix ) const 
{
	SetUniformArray( name, matrix.dataArray, 16 );
}

#pragma endregion
