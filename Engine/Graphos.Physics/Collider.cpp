#include "Collider.h"

using namespace Graphos::Core;
using namespace Graphos::Physics;

Collider::Collider( ColliderType colliderType, GameObject* owner ) : type( colliderType ), centerOffset( 0.0f, 0.0f, 0.0f ), bounce( 1.0f ), IComponent( owner ) { }