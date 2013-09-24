
#include "DemoGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	DemoGame game(hInstance);

	if( !game.Init() )
		return 0;
	
	return game.run();

}

DemoGame::DemoGame(HINSTANCE hInstance) : DXGame(hInstance)
{
	windowWidth = 800;
	windowHeight = 600;
}


DemoGame::~DemoGame(void)
{
	ReleaseCOMobjMacro( vertexLayout );
	ReleaseCOMobjMacro( vertexBuffer );
	ballTexture->Shutdown();
	delete ballTexture;
}

bool DemoGame::Init()
{
	if( !DXGame::Init() )
		return false;
	LoadCgShaders();
	LoadTextures();
	CreateVertexBuffer();
	return true;
}

void DemoGame::LoadCgShaders()
{
	ID3DBlob* pVSBuf = nullptr;
	ID3DBlob* pPSBuf = nullptr;
	ID3DBlob* pErrBuf = nullptr;
	const char ** profileOpts = nullptr;

	/* Determine the best profile once a device to be set. */
    myCgVertexProfile = cgD3D11GetLatestVertexProfile();
    checkForCgError("getting latest profile");

    profileOpts = cgD3D11GetOptimalOptions(myCgVertexProfile);
    checkForCgError("getting latest profile options");

	 myCgVertexProgram =
        cgCreateProgramFromFile(
            myCgContext,              /* Cg runtime context */
            CG_SOURCE,                /* Program in human-readable form */
            "demo.vs.cg",			  /* Name of file containing program */
            myCgVertexProfile,        /* Profile */
            "demo",					  /* Entry function name */
            profileOpts);             /* Pass optimal compiler options */
    checkForCgError("creating vertex program from file");

	cgD3D11LoadProgram( myCgVertexProgram, 0 );
    checkForCgError("loading vertex program");

	 // Create vertex input layout
    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    pVSBuf = cgD3D11GetCompiledProgram( myCgVertexProgram );

    HR( device->CreateInputLayout( layout, 2, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &vertexLayout ) ); 
   
  
    myCgFragmentProfile = cgD3D11GetLatestPixelProfile();

    profileOpts = cgD3D11GetOptimalOptions(myCgFragmentProfile);
    checkForCgError("getting latest profile options");

    myCgFragmentProgram = 
        cgCreateProgramFromFile(
            myCgContext,                /* Cg runtime context */
            CG_SOURCE,                  /* Program in human-readable form */
            "demo.fs.cg",				/* Name of file containing program */
            myCgFragmentProfile,        /* Profile */
            "demo",						/* Entry function name */
            profileOpts);               /* Pass optimal compiler options */
    checkForCgError("creating fragment program from file");

    cgD3D11LoadProgram( myCgFragmentProgram, 0 );
    checkForCgError("loading fragment program");

	

}

void DemoGame::CreateVertexBuffer()
{

//	XMFLOAT4 red	= XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
//	XMFLOAT4 green	= XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
//	XMFLOAT4 blue	= XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex triangleVertices[] = 
	{
		{ XMFLOAT3(-0.8f, +0.8f, +0.0f), XMFLOAT2(+0.0f, +0.0f) },
		{ XMFLOAT3(+0.8f, +0.8f, +0.0f), XMFLOAT2(+1.0f, +0.0f) },
		{ XMFLOAT3(+0.0f, -0.8f, +0.0f), XMFLOAT2(+0.5f, +1.0f) },
	};

	// Create the vertex buffer
	D3D11_BUFFER_DESC vbDesc;
	vbDesc.ByteWidth		= sizeof(Vertex) * 3;
	vbDesc.Usage			= D3D11_USAGE_IMMUTABLE;
	vbDesc.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags   = 0;
    vbDesc.MiscFlags		= 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	ZeroMemory( &initialVertexData, sizeof( D3D11_SUBRESOURCE_DATA ) );
	initialVertexData.pSysMem = triangleVertices;
	HR( device->CreateBuffer( &vbDesc, &initialVertexData, &vertexBuffer ) );
}

void DemoGame::LoadTextures()
{
	ballTexture = new Texture( "balls.jpg", device, myCgFragmentProgram );
}

void DemoGame::DrawScene()
{
	UINT strides[1] = { sizeof( Vertex ) };
    UINT offsets[1] = { 0 };
    ID3D11Buffer* buffers[1] = { vertexBuffer };

	float ClearColor[4] = { 100.0f/255.0f, 149.0f/255.0f, 237.0f/255.0f, 1.0f }; // RGBA
    // Clear the back buffer        
    deviceContext->ClearRenderTargetView( renderTargetView, ClearColor );
    deviceContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0 );

   // deviceContext->OMSetBlendState( myBlendState_NoBlend, 0, 0xffffffff );
   // deviceContext->RSSetState( myRasterizerState_NoCull );  
    
    deviceContext->IASetVertexBuffers( 0, 1, buffers, strides, offsets );
    deviceContext->IASetInputLayout( vertexLayout );    
    deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );   

    cgD3D11BindProgram( myCgVertexProgram );
    cgD3D11BindProgram( myCgFragmentProgram );

	ballTexture->Draw();

    deviceContext->Draw( 3, 0 ); // numVertices, startVertex
     
    swapChain->Present( 0, 0 );
}