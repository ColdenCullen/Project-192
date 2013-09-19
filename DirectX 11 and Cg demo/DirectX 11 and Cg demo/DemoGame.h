
#ifndef __DEMO_GAME
#define __DEMO_GAME

#include <DirectXMath.h>
#include "DXGame.h"
#include "Texture.h"

// Include run-time memory checking in debug builds
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// For DirectX Math
using namespace DirectX;
using namespace Graphos::Core;

// Vertex struct for triangles
struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT2 TexCoord;
};


class DemoGame : public DXGame
{
public:
	DemoGame(HINSTANCE hInstance);
	~DemoGame(void);

	// Overrides for base level methods
	bool Init();
	//void OnResize();
	//void UpdateScene(float dt);
	void DrawScene(); 

private:
	void LoadCgShaders();
	void CreateVertexBuffer();
	void LoadTextures();

	Texture* ballTexture;
	
	ID3D11InputLayout* vertexLayout;
	ID3D11Buffer* vertexBuffer;

};


#endif

