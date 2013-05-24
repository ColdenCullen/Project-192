#include "Collider.h"

using namespace Graphos;
using namespace Graphos::Content;

Collider::Collider( ColliderType colliderType, GameObject* owner ) : type( colliderType ), centerOffset( 0.0f, 0.0f, 0.0f ), bounce( 1.0f ), Ingredient( owner ) { }