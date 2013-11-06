/// <reference path="Graphos.ts" />

class GameObject1 extends GraphosBehavior
{
    public OnUpdate(): void
    {
        if( Input.IsKeyDown( Keys.Space ) )
        {
            //log( this.Transform.Forward.Multiply( 3 ) );
        }
    }
}