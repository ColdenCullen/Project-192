#ifndef __NATIVE_TO_JS_MAP_GRAPHOS
#define __NATIVE_TO_JS_MAP_GRAPHOS

#include <v8/v8.h>
#include <cvv8/ClassCreator.hpp>
#include <unordered_map>

namespace cvv8
{
	template<typename T>
	struct NativeToJSMap_Graphos : public NativeToJSMap<T>
	{
	public:
		v8::Handle<v8::Value> operator()( T const& val ) const
		{
			v8::Handle<v8::Value> const & toReturn( GetObject( &val ) );

			if( toReturn.IsEmpty() )
			{
				// If object does not exist in the JSMap, create it
				v8::Handle<v8::Object> newToReturn = ClassCreator<T>::Instance().NewInstance( 0, NULL );
				delete newToReturn->GetPointerFromInternalField( ClassCreator_InternalFields<T>::NativeIndex );
				newToReturn->SetPointerInInternalField( ClassCreator_InternalFields<T>::NativeIndex, (void*)&val );
				AddObject( &val, newToReturn );
				return newToReturn;
			}

			return toReturn;
		}

	private:
		typedef std::unordered_map<T const *, v8::Handle<v8::Object>> HandleMap;

		static
		HandleMap& Map()
		{
			static HandleMap instance;
			return instance;
		}

		static
		v8::Handle<v8::Object> GetObject( T const * ptr )
		{
			/*
			auto obj = Map().find( ptr );

			if( obj == Map().end() )
				return v8::Handle<v8::Object>();
			else
				return obj->second;
			/*/
			return v8::Handle<v8::Object>();
			//*/
		}
		static
		void AddObject( T const * ptr, v8::Handle<v8::Object> obj )
		{
			Map()[ ptr ] = obj;
		}
	};
}

#endif//__NATIVE_TO_JS_MAP_GRAPHOS
