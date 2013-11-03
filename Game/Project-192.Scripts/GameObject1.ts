/// <reference path="Graphos.ts" />

class GameObject1 extends GameObject
{
    public Update(): void
    {
        if( Input.IsKeyDown( Keys.Space ) )
        {
            //log( this.Transform.Forward.Multiply( 3 ) );
        }
    }
}