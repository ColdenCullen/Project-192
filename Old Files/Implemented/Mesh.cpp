#include "Mesh.h"

#include <sstream>
#include <vector>

#define _USE_READ_FILE
#include <Helpers.h>

using namespace std;
using namespace Graphos::Math;
using namespace Graphos::Content;

bool Mesh::LoadFromFile( string filePath )
{
	vector<Vector3> vertices;
	vector<Vector2> uvs;
	vector<Vector3> normals;

	vector<GLfloat>	outputData;

	istringstream file( Helpers::ReadFile( filePath ) );
	string line;

	if( !file )
		return false;

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

	numElements = outputData.size() / 8;

	unsigned int* indices = new unsigned int[ numElements ];

	for( unsigned int ii = 0; ii < numElements; ++ii )
		indices[ ii ] = ii;

	// make and bind the VAO
	glGenVertexArrays( 1, &vertexArrayObject );
	glBindVertexArray( vertexArrayObject );

	// make and bind the VBO
	glGenBuffers( 1, &vertexBufferObject );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );

	// Buffer the data
	glBufferData( GL_ARRAY_BUFFER, outputData.size() * sizeof(GLfloat), &outputData[ 0 ], GL_STATIC_DRAW );

	// Connect the position to the inputPosition attribute of the vertex shader
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL );
	// Connect color to the textureCoordinate attribute of the vertex shader
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (unsigned char*)NULL + ( sizeof(GLfloat) * 3 ) );
	// Connect color to the shaderPosition attribute of the vertex shader
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (unsigned char*)NULL + ( sizeof(GLfloat) * 5 ) );

	// Generate index buffer
	glGenBuffers( 1, &indexBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );

	// Buffer index data
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numElements, &indices[ 0 ], GL_STATIC_DRAW );

	// unbind the VBO and VAO
	glBindBuffer( GL_ARRAY_BUFFER, NULL );
	glBindVertexArray( NULL );

	delete[] indices;

	return true;
}

void Mesh::Draw( void )
{
	// Bind all of the buffers
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBindVertexArray( vertexArrayObject );

	// Draw
	glDrawElements( GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0 );
}

void Mesh::Shutdown( void )
{
	glDeleteBuffers( 1, &vertexBufferObject );
	glDeleteBuffers( 1, &vertexArrayObject );
}