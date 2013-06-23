/// <reference path="Graphos.ts" />

// Class
class Cube extends GameObject
{
    // Is called every frame
    Update( deltaTime: number ): void
    {
        if( Input.IsKeyDown( Keys["space"] ) )
            log( this.transform.position.x );
    }
}