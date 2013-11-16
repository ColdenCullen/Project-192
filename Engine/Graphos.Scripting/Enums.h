#include <cvv8/ClassCreator.hpp>

#include "GraphosGame.h"

#define WRAP_ENUM(ENUM)														\
template<> struct cvv8::JSToNative<ENUM> : public cvv8::JSToNative<int> {};	\
template<> struct cvv8::NativeToJS<ENUM> : public cvv8::NativeToJS<int> {};

using namespace Graphos::Core;

WRAP_ENUM(GameState)
