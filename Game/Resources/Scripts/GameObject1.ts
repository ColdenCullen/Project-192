/// <reference path="Graphos.ts" />

class GameObject1 extends GameObject
{
    public Update(): void
    {
        if( Input.IsKeyDown( Keys.W ) )
        {
            //this.Transform.Translate( this.Transform.Forward );
        }
    }
}