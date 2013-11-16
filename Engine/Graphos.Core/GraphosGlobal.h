#ifndef __GRAPHOS_GLOBAL
#define __GRAPHOS_GLOBAL
// Code that can be accessed from anywhere

typedef	char gByte;

/// <summary>
/// Titanic_casts the specified pointer.
/// </summary>
/// <remarks>SHUT THE FUCK UP C++ I KNOW WHAT I'M DOING</remarks>
/// <param name="start">The pointer to cast.</param>
/// <returns>The casted pointer</returns>
template<typename TEnd, typename TStart>
TEnd* titanic_cast( TStart* start )
{
	return static_cast<TEnd*>( static_cast<void*>( start ) );
}

/// <summary>
/// Safely deletes the specified pointer.
/// </summary>
/// <param name="ptr">The pointer to delete.</param>
template<typename T>
void delete_s( T*& ptr )
{
	if( ptr )
	{
		delete ptr;
		ptr = nullptr;
	}
}

#endif//__GRAPHOS_GLOBAL