/// <reference path="Graphos.ts" />

// Interface
class GameObject1 extends GameObject
{
    vec: Vector3;

    constructor()
    {
        super();

        this.vec = new Vector3();
        this.vec.x = 5.0;
    }

    public Update(): void
    {
        if( Input.IsKeyDown( Keys.Space ) )
            log( "Vec.x: " + this.vec.x );
    }
}