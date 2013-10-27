/// <reference path="Graphos.ts" />

class Camera1 extends GameObject {
    public Update(): void {
        if (Input.IsKeyDown(Keys.Space)) {
            //log( this.Transform.Forward.x );
            //this.Transform.Translate( this.Transform.Forward );
        }
    }
}