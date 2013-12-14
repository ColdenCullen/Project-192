#ifndef __POINT_LIGHT
#define __POINT_LIGHT

#include "AmbientLight.h"

namespace Graphos
{
	namespace Core
	{

		class PointLight : public AmbientLight
		{
		public:
								// w of initPos should be 1 for position
								PointLight( std::string name, 
											Math::Vector4 initPos,
											gFloat initRange,
											gFloat initConstAttenuation,
											gFloat initLinearAttenuation,
											gFloat initQuadAttenuation,
											Math::Vector4 initColor,
											GameObject* owner = nullptr);
								~PointLight( void ) { }

			// Must be duplicated due to static size
			void				Draw( Graphics::IShader* shader ) override;

			Math::Vector4		GetPosition( void ) { return position; }
			void				SetPosition( const Math::Vector4& value ) { dirty = true; position = value; }
			gFloat				GetRange( void ) { return range; }
			void				SetRange( const gFloat value ) { dirty = true; range = value; }
			gFloat				GetConstAttenuation( void ) { return constAttenuation; }
			void				SetConstAttenuation( const gFloat value ) { dirty = true; constAttenuation = value; }
			gFloat				GetLinearAttenuation( void ) { return linearAttenuation; }
			void				SetLinearAttenuation( const gFloat value ) { dirty = true; linearAttenuation = value; }
			gFloat				GetQuadAttenuation( void ) { return quadAttenuation; }
			void				SetQuadAttenuation( const gFloat value ) { dirty = true; quadAttenuation = value; }
			

			const static gSize size;
			
		protected:

			virtual void		UpdateBuffer( void ) override;
			Math::Vector4		position;
			// x = constant
			// y = linear
			// z =  quadratic
			// w = range
			Math::Vector4		attenuation;
			gFloat&				constAttenuation;
			gFloat&				linearAttenuation;
			gFloat&				quadAttenuation;
			gFloat&				range;
		};
	}

}
#endif
