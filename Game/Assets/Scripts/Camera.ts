/// <reference path="Graphos.ts" />

class Camera1 extends GameObject
{
    Speed: number;
    //RotationSpeed: number;

    public OnUpdate(): void
    {
        // This moves the camera around on a 2D plane
        if( Input.IsKeyDown( Keys.W ) )
        {
            this.Transform.Translate( this.Transform.Up.Multiply( this.Speed ) );
        }
        if( Input.IsKeyDown( Keys.S ) )
        {
            this.Transform.Translate( this.Transform.Up.Multiply( this.Speed ).Inverse );
        }
        if( Input.IsKeyDown( Keys.A ) )
        {
            this.Transform.Translate( this.Transform.Right.Multiply( this.Speed ).Inverse );
        }
        if( Input.IsKeyDown( Keys.D ) )
        {
            this.Transform.Translate( this.Transform.Right.Multiply( this.Speed ) );
        }

        /*
        if( Input.IsKeyDown( Keys.Up ) )
        {
            this.Transform.Rotate( this.RotationSpeed, 0.0, 0.0 );
        }
        if( Input.IsKeyDown( Keys.Down ) )
        {
            this.Transform.Rotate( -this.RotationSpeed, 0.0, 0.0 );
        }
        if( Input.IsKeyDown( Keys.Left ) )
        {
            this.Transform.Rotate( 0.0, this.RotationSpeed, 0.0 );
        }
        if( Input.IsKeyDown( Keys.Right ) )
        {
            this.Transform.Rotate( 0.0, -this.RotationSpeed, 0.0 );
        }
        */
    }
}
