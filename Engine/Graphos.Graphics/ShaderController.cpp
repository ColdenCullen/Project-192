#include "StdAfx.h"
#include "ShaderController.h"
#include "WindowController.h"
#include "GraphicsController.h"
#include "GlShader.h"
#include "DXShader.h"
#include "File.h"
#include "OutputController.h"
#include "ScriptController.h"

#define SHADER_PATH string("Resources\\Shaders\\")

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

void ShaderController::Initialize( void )
{
	auto shaderFiles = File::ScanDir( SHADER_PATH );

	for( auto file : shaderFiles )
	{
		string fileName = file.GetFileName();

		if( fileName.size() < 8 )
			OutputController::PrintMessage( OutputType::OT_WARNING, "File not valid shader file: " + file.GetFileName() );

		string shaderName = fileName.substr( 0, fileName.size() - 8 );

		IShader* shader;

		if( fileName.substr( fileName.size() - 8 ) == ".fs.glsl" &&
			GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
		{
			shader = new GlShader(
				file.GetFullPath().substr( 0, file.GetFullPath().size() - 8 ) + ".vs.glsl",
				file.GetFullPath() );
		}
		else if( fileName.substr( fileName.size() - 8 ) == ".fs.hlsl" &&
			GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
		{
			shader = new DXShader(
				file.GetFullPath().substr( 0, file.GetFullPath().size() - 8 ) + ".vs.hlsl",
				file.GetFullPath() );
		}
		else
		{
			continue;
		}

		shader->script = ScriptController::Get().CreateObjectInstance( shaderName, shader );

		shaders[ shaderName ] = shader;
	}
}

IShader* ShaderController::GetShader( string shaderName )
{
	return shaders.at( shaderName );
}

void ShaderController::Shutdown( void )
{
	for( auto shader : shaders )
	{
		shader.second->Shutdown();
		delete shader.second;
	}
	shaders.clear();
}

unordered_map<string, IShader*> ShaderController::shaders;
