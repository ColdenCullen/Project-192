#include "Texture.h"


using namespace std;
using namespace Graphos::Core;
using namespace DirectX;

void Texture::LoadFromFile( std::string filePath,ID3D11Device* device )
{
	std::wstring wFilePath( filePath.begin(), filePath.end() );
	
	
	TexMetadata metaData;
	GetMetadataFromWICFile( wFilePath.c_str(), NULL, metaData );
	
	ScratchImage scratchImg;
	LoadFromWICFile( wFilePath.c_str(), WIC_FLAGS_NONE, &metaData, scratchImg );

	const Image* img = scratchImg.GetImage( 0, 0, 0 );
	CreateTexture( device, img, 1, metaData, &myDecalTexture );
	
}

void Texture::Draw( CGprogram* myCgFragmentProgram )
{
	myCgFragmentParam_decal = cgGetNamedParameter(*myCgFragmentProgram, "decal");

    cgD3D11SetTextureParameter( myCgFragmentParam_decal, myDecalTexture );
    cgD3D11SetSamplerStateParameter( myCgFragmentParam_decal, NULL ); // NULL == default states
}

void Texture::Shutdown( void )
{
	ReleaseCOMobjMacro( myDecalTexture );
}