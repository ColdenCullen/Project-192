#include "Mesh.h"
#include "GraphicsController.h"
#include "File.h"
#include "Vector2.h"
#include "Vector3.h"
#include "AdapterController.h"

#include <sstream>
#include <vector>
#define POSITION_ATTRIBUTE 0
#define UV_ATTRIBUTE 1
#define NORMAL_ATTRIBUTE 2

using namespace Graphos::Math;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace DirectX;
using namespace OpenGL;

#include <DirectX/DirectXIncludes.h>

void Mesh::LoadFromFile( std::string filePath )
{
	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;

	std::vector<float>	outputData;

	std::istringstream file( File::ReadFile( filePath ) );
	std::string line;

	if( !file )
		throw std::exception( std::string( "Failed to read object file " + filePath + "." ).c_str() );

	while( getline( file, line ) )
	{
		if( line.substr( 0, 2 ) == "v " )
		{
			Vector3 vertex;

			sscanf( line.c_str(), "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z );

			vertices.push_back( vertex );
		}
		else if( line.substr( 0, 2 ) == "vt" )
		{
			Vector2 uv;

			sscanf( line.c_str(), "vt %f %f\n", &uv.x, &uv.y );

			uvs.push_back( uv );
		}
		else if( line.substr( 0, 2 ) == "vn" )
		{
			Vector3 normal;

			sscanf( line.c_str(), "vn %f %f %f\n", &normal.x, &normal.y, &normal.z );

			normals.push_back( normal );
		}
		else if( line.substr( 0, 2 ) == "f " )
		{
			unsigned int vertexIndex[ 3 ];
			unsigned int uvIndex[ 3 ];
			unsigned int normalIndex[ 3 ];

			sscanf( line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[ 0 ], &uvIndex[0], &normalIndex[0], &vertexIndex[ 1 ], &uvIndex[1], &normalIndex[1], &vertexIndex[ 2 ], &uvIndex[2], &normalIndex[2] );

			for( int ii = 0; ii < 3; ++ii )
			{
				outputData.push_back( vertices[ vertexIndex[ ii ] - 1 ].x );
				outputData.push_back( vertices[ vertexIndex[ ii ] - 1 ].y );
				outputData.push_back( vertices[ vertexIndex[ ii ] - 1 ].z );

				outputData.push_back( uvs[ uvIndex[ ii ] - 1 ].x );
				outputData.push_back( uvs[ uvIndex[ ii ] - 1 ].y );

				outputData.push_back( normals[ normalIndex[ ii ] - 1 ].x );
				outputData.push_back( normals[ normalIndex[ ii ] - 1 ].y );
				outputData.push_back( normals[ normalIndex[ ii ] - 1 ].z );
			}
		}
	}

	numVertices = outputData.size() / 8;  // 8 is num floats per vertex

	unsigned int* indices = new unsigned int[ numVertices ];

	for( unsigned int ii = 0; ii < numVertices; ++ii )
		indices[ ii ] = ii;

	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		// make and bind the VAO
		glGenVertexArrays( 1, &vertexArrayObject );
		glBindVertexArray( vertexArrayObject );

		// make and bind the VBO
		glGenBuffers( 1, &vertexBufferObject );
		glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );

		// Buffer the data
		glBufferData( GL_ARRAY_BUFFER, outputData.size() * sizeof(GLfloat), &outputData[ 0 ], GL_STATIC_DRAW );

		// Connect the position to the inputPosition attribute of the vertex shader
		glEnableVertexAttribArray( POSITION_ATTRIBUTE );
		glVertexAttribPointer( POSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL );
		// Connect uv to the textureCoordinate attribute of the vertex shader
		glEnableVertexAttribArray( UV_ATTRIBUTE );
		glVertexAttribPointer( UV_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (unsigned char*)NULL + ( sizeof(GLfloat) * 3 ) );
		// Connect color to the shaderPosition attribute of the vertex shader
		glEnableVertexAttribArray( NORMAL_ATTRIBUTE );
		glVertexAttribPointer( NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (unsigned char*)NULL + ( sizeof(GLfloat) * 5 ) );

		// Generate index buffer
		glGenBuffers( 1, &indexBuffer );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );

		// Buffer index data
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numVertices, &indices[ 0 ], GL_STATIC_DRAW );

		// unbind the VBO and VAO
		glBindBuffer( GL_ARRAY_BUFFER, NULL );
		glBindVertexArray( NULL );
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		// Create the vertex buffer
		D3D11_BUFFER_DESC vbDesc;
		vbDesc.ByteWidth		= sizeof(float) * outputData.size();
		vbDesc.Usage			= D3D11_USAGE_IMMUTABLE;
		vbDesc.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags   = 0;
		vbDesc.MiscFlags		= 0;

		D3D11_SUBRESOURCE_DATA initialVertexData;
		ZeroMemory( &initialVertexData, sizeof( D3D11_SUBRESOURCE_DATA ) );
		initialVertexData.pSysMem = &outputData[0];
		AdapterController::Get()->GetDevice().dxDevice->CreateBuffer( &vbDesc, &initialVertexData, &vertexBuffer );
	}
#endif//_WIN32
	delete[] indices;
}

// Meshes can be shared between objects, objects may have different shaders
void Mesh::Draw( IShader* shader )
{
	shader->Draw( *this );
}

void Mesh::Shutdown( void )
{
	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		glDeleteBuffers( 1, &vertexBufferObject );
		glDeleteBuffers( 1, &vertexArrayObject );
	}
#ifdef _WIN32
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		ReleaseCOMobjMacro( vertexBuffer );
	}
#endif//_WIN32
	
}