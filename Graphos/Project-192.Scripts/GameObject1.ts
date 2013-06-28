/// <reference path="Graphos.ts" />

// Interface
class GameObject1 extends GameObject
{
    public Update(): void
    {
        if( Input.IsKeyDown( Keys.Space ) )
            log("Testing Update");
    }
}