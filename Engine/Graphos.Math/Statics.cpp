#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"

using namespace Graphos::Math;

const Quaternion Quaternion::Identity = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );

const Vector3 Vector3::Zero = Vector3( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::Right = Vector3( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::Up = Vector3( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::Forward = Vector3( 0.0f, 0.0f, 1.0f );

const Vector4 Vector4::Zero = Vector4( 0.0f, 0.0f, 0.0f, 1.0f );
const Vector4 Vector4::Right = Vector4( 1.0f, 0.0f, 0.0f, 1.0f );
const Vector4 Vector4::Up = Vector4( 0.0f, 1.0f, 0.0f, 1.0f );
const Vector4 Vector4::Forward = Vector4( 0.0f, 0.0f, 1.0f, 1.0f );