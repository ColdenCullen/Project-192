
#if !defined( __DX_INCLUDES ) && defined( _WIN32 )
#define __DX_INCLUDES

#ifndef NO_NAMESPACE
namespace DirectX
{
#endif//NO_NAMESPACE

	#include <d3d11.h>

#ifndef NO_NAMESPACE
}
#endif//NO_NAMESPACE

#ifndef ReleaseCOMobjMacro
 #define ReleaseCOMobjMacro( x ) { if( x ){  x->Release(); x = nullptr; } }
#endif

// Macro for popping up a text box based
// on a failed HRESULT and then quitting (only in debug builds)
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)												\
{															\
	HRESULT hr = (x);										\
	if(FAILED(hr))											\
	{														\
		MessageBox(NULL, L"", L"DirectX Error", MB_OK);		\
		PostQuitMessage(0);									\
	}														\
}														
#endif
#else
 #ifndef HR
  #define HR(x) (x)
 #endif
#endif

#endif//__DX_INCLUDES/_WIN32