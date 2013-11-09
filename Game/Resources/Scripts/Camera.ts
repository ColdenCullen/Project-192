/// <reference path="Graphos.ts" />

class Camera1 extends GraphosBehavior
{
    test: number;
    test1: GameObject;

    public OnUpdate(): void
    {
        if( Input.IsKeyDown( Keys.Space ) )
        {
            log( this.test );
            log( this.test1.Transform.Position.x );
        }

        //if( Input.IsKeyDown( Keys.W ) )
        //{
        //    this.Transform.Translate( this.Transform.Forward.Multiply( this.Speed ) );
        //}
        //if( Input.IsKeyDown( Keys.S ) )
        //{
        //    this.Transform.Translate( this.Transform.Forward.Multiply( this.Speed ).Inverse );
        //}
        //if( Input.IsKeyDown( Keys.A ) )
        //{
        //    this.Transform.Translate( this.Transform.Right.Multiply( this.Speed ).Inverse );
        //}
        //if( Input.IsKeyDown( Keys.D ) )
        //{
        //    this.Transform.Translate( this.Transform.Right.Multiply( this.Speed ) );
        //}

        //if( Input.IsKeyDown( Keys.Up ) )
        //{
        //    this.Transform.Rotate( this.RotationSpeed, 0.0, 0.0 );
        //}
        //if( Input.IsKeyDown( Keys.Down ) )
        //{
        //    this.Transform.Rotate( -this.RotationSpeed, 0.0, 0.0 );
        //}
        //if( Input.IsKeyDown( Keys.Left ) )
        //{
        //    this.Transform.Rotate( 0.0, -this.RotationSpeed, 0.0 );
        //}
        //if( Input.IsKeyDown( Keys.Right ) )
        //{
        //    this.Transform.Rotate( 0.0, this.RotationSpeed, 0.0 );
        //}
    }
}
