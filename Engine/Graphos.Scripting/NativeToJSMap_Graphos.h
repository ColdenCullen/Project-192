#ifndef __NATIVE_TO_JS_MAP_GRAPHOS
#define __NATIVE_TO_JS_MAP_GRAPHOS

#include <v8/v8.h>
#include <cvv8/ClassCreator.hpp>
#include <unordered_map>

namespace cvv8
{
#if 0

	template<typename T>
	struct NativeToJSMap_Graphos : public NativeToJSMap<T>::NativeToJSImpl { };

#else

	template<typename T>
	struct NativeToJSMap_Graphos : public NativeToJSMap<T>
	{
	private:
        typedef TypeInfo<T> TI;
        typedef typename TI::Type Type;
        /**
           The native type to bind to.
        */
        typedef const Type* NativeHandle;
        /** The type for holding the JS 'this' object. */
        typedef v8::Persistent<v8::Object> JSObjHandle;
        //typedef v8::Handle<v8::Object> JSObjHandle; // Hmmm.
        typedef std::pair<NativeHandle,JSObjHandle> ObjBindT;
        typedef std::map<const void*, ObjBindT> OneOfUsT;
        /** Maps (void const *) to ObjBindT.
        
            Reminder to self: we might need to make this map a static
            non-function member to work around linking problems (at 
            least on Windows) which lead to multiple instances of 
            the returned map being created when the types being 
            bound are loaded from multiple DLLs. The out-of-class
            initialization of the member is going to require a really
            ugly set of template parameters, though.
        */
        static OneOfUsT& Map()
        {
            static OneOfUsT bob;
            return bob;
        }
    public:
        /** Maps obj as a lookup key for jself. Returns false if !obj,
         else true. */
        static bool Insert( const JSObjHandle jself, NativeHandle obj )
        {
            if( obj )
			{
				//Map().insert( std::make_pair( obj, std::make_pair( obj, jself ) ) );
				Map()[ obj ] = std::make_pair( obj, jself );
				return true;
			}
			else
			{
				return false;
			}
        }

        /**
           Removes any mapping of the given key. Returns the
           mapped native, or 0 if none is found.
        */
        static NativeHandle Remove( const void* key )
        {
            typedef typename OneOfUsT::iterator Iterator;
            OneOfUsT & map( Map() );
            Iterator it = map.find( key );
            if( map.end() == it )
            {
                return 0;
            }
            else
            {
                NativeHandle victim = it->second.first;
                map.erase(it);
                return victim;
            }
        }

        /**
           Returns the native associated (via Insert())
           with key, or 0 if none is found.
        */
        static NativeHandle GetNative( const void* key )
        {
            if( ! key ) return nullptr;
            else
            {
                typename OneOfUsT::iterator it = Map().find(key);
                return (Map().end() == it)
                    ? 0
                    : it->second.first;
            }
        }

        /**
           Returns the JS object associated with key, or
           an empty handle if !key or no object is found.
        */
        static JSObjHandle GetJSObject( const void* key )
        {
            if( !key )
				return JSObjHandle();

			auto it = Map().find(key);

            if( Map().end() == it )
				return JSObjHandle();

            else
				return it->second.second;
		}

		v8::Handle<v8::Value> operator()( const Type& val ) const
		{
			// Create new object
			v8::Handle<v8::Object>& toReturn = ClassCreator<T>::Instance().NewInstance( 0, NULL );
			// Copy values from original to new
			*static_cast<T*>( toReturn->GetPointerFromInternalField( ClassCreator_InternalFields<Type>::NativeIndex ) ) = val;
			return toReturn;
		}

		v8::Handle<v8::Value> operator()( const Type* val ) const
		{
			JSObjHandle const & rc( GetJSObject( val ) );

			if( rc.IsEmpty() )//|| !rc->IsObject() )
			{
				// If object does not exist in the JSMap, create it
				//JSObjHandle toReturn( ClassCreator<T>::Instance().NewInstance( 0, NULL ) );

				JSObjHandle toReturn =
					v8::Persistent<v8::Object>::New(
							ClassCreator<T>::Instance().NewInstance( 0, NULL ) );

				delete toReturn->GetPointerFromInternalField( ClassCreator_InternalFields<Type>::NativeIndex );
				toReturn->SetPointerInInternalField( ClassCreator_InternalFields<Type>::NativeIndex, (void*)val );
				Insert( toReturn, val );
				return toReturn;
			}
			else
			{
				return rc;
				//return v8::Null();
			}
		}
	};

#endif
}
#endif//__NATIVE_TO_JS_MAP_GRAPHOS
