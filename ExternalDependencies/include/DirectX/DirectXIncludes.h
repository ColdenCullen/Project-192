#if !defined( __DX_INCLUDES ) && defined( _WIN32 )
#define __DX_INCLUDES

#include <D3D11.h>

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
		MessageBox(NULL, "", "DirectX Error", MB_OK);		\
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