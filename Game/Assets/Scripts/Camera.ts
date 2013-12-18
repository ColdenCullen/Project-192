/// <reference path="Graphos.ts" />

class Camera1 extends Camera
{
    Speed: number;
    RotationSpeed: number;

    public OnUpdate(): void
    {
	//*
        if( Input.IsKeyDown( Keys.W ) )
        {
            this.Transform.Translate( this.Transform.Forward.Multiply( this.Speed ) );
        }
        if( Input.IsKeyDown( Keys.S ) )
        {
            this.Transform.Translate( this.Transform.Forward.Multiply( this.Speed ).Inverse );
        }
        if( Input.IsKeyDown( Keys.A ) )
        {
            this.Transform.Translate( this.Transform.Right.Multiply( this.Speed ).Inverse );
        }
        if( Input.IsKeyDown( Keys.D ) )
        {
            this.Transform.Translate( this.Transform.Right.Multiply( this.Speed ) );
        }

        if( Input.IsKeyDown( Keys.Up ) )
        {
            //this.Transform.Rotate( this.RotationSpeed, 0.0, 0.0 );
			this.Transform.Rotate( 1.0, 0.0, 0.0, this.RotationSpeed, false );
        }
        if( Input.IsKeyDown( Keys.Down ) )
        {
            //this.Transform.Rotate( -this.RotationSpeed, 0.0, 0.0 );
			this.Transform.Rotate( 1.0, 0.0, 0.0, -this.RotationSpeed, false );
        }
        if( Input.IsKeyDown( Keys.Left ) )
        {
            //this.Transform.Rotate( 0.0, this.RotationSpeed, 0.0 );
			this.Transform.Rotate( 0.0, 1.0, 0.0, this.RotationSpeed, true );
        }
        if( Input.IsKeyDown( Keys.Right ) )
        {
            //this.Transform.Rotate( 0.0, -this.RotationSpeed, 0.0 );
            this.Transform.Rotate( 0.0, 1.0, 0.0, -this.RotationSpeed, true );
        }
	//*/
    }
}

class RotatyThing extends GameObject
{
	/*
    Speed: number;
    RotationSpeed: number;

    public OnUpdate(): void
    {
        if( Input.IsKeyDown( Keys.Up ) )
        {
            //this.Transform.Rotate( this.RotationSpeed, 0.0, 0.0 );
			this.Transform.Rotate( 1.0, 0.0, 0.0, -this.RotationSpeed, false );
        }
        if( Input.IsKeyDown( Keys.Down ) )
        {
            //this.Transform.Rotate( -this.RotationSpeed, 0.0, 0.0 );
			this.Transform.Rotate( 1.0, 0.0, 0.0, this.RotationSpeed, false );
        }
        if( Input.IsKeyDown( Keys.Left ) )
        {
            //this.Transform.Rotate( 0.0, this.RotationSpeed, 0.0 );
			this.Transform.Rotate( 0.0, 1.0, 0.0, this.RotationSpeed, true );
        }
        if( Input.IsKeyDown( Keys.Right ) )
        {
            //this.Transform.Rotate( 0.0, -this.RotationSpeed, 0.0 );
			this.Transform.Rotate( 0.0, 1.0, 0.0, -this.RotationSpeed, true );
        }
    }
	//*/
}

