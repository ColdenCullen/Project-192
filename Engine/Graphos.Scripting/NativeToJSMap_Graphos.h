#ifndef __NATIVE_TO_JS_MAP_GRAPHOS
#define __NATIVE_TO_JS_MAP_GRAPHOS

#include <v8\v8.h>

#include "cvv8\ClassCreator.hpp"

namespace cvv8
{
	template<typename T>
	struct NativeToJSMap_Graphos : NativeToJSMap<T>
	{
		v8::Handle<v8::Value> operator()( const T& val ) const
		{
			v8::Handle<v8::Object> toReturn;

			if( ( toReturn = GetJSObject( (void*)&val ) ).IsEmpty() )
			{	// If object does not exist in the JSMap, create it
				toReturn = ClassCreator<T>::Instance().NewInstance( 0, NULL )->ToObject();
				toReturn->SetInternalField( ClassCreator_InternalFields<T>::NativeIndex, External::New( (void*)&val ) );
			}

			return toReturn;
		}
	};
}

#endif//__NATIVE_TO_JS_MAP_GRAPHOS
