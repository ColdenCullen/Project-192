/// <reference path="Graphos.ts" />

class MyGame extends GraphosGame
{
    objects: GameObjectCollection;
    shootyBall: GameObject;
    ballsFired: number;

    public Initialize(): void
    {
        log( "Initializing" );

        this.ballsFired = 0;

        this.objects = new GameObjectCollection();
        this.objects.LoadObjects( "" );

        this.shootyBall = this.objects.GetObjectByName("ShootyBall");

        log( this.Camera );
    }

    public Update(): void
    {
        switch( this.CurrentState )
        {
            case GameState.Game:
                {
                    //switch to menu with F1
			        if( Input.IsKeyDown( Keys.F1 ) )
                        this.CurrentState = GameState.Menu;

                    this.UpdateGame();
                    this.objects.Update();
                    break;
                }
            case GameState.Menu:
                {
                    //switch to game with F2
			        if( Input.IsKeyDown( Keys.F2 ) )
                        this.CurrentState = GameState.Game;

                    break;
                }
        }

        // Quit game with Escape
	    if( Input.IsKeyDown( Keys.Escape ) )
		    this.Exit();

	    // Reset game with F5
	    if( Input.IsKeyDown( Keys.F5 ) )
		    this.Reset();
    }

    public Draw(): void
    {
        switch( this.CurrentState )
        {
            case GameState.Game:
                {
                    ShaderController.GetShader( "texture" ).ViewMatrix = this.Camera.ViewMatrix;
                    ShaderController.GetShader( "texture" ).ProjectionMatrix = WindowController.Get().PerspectiveMatrix;
                    ShaderController.GetShader( "light" ).ViewMatrix = this.Camera.ViewMatrix;
                    ShaderController.GetShader( "light" ).ProjectionMatrix = WindowController.Get().PerspectiveMatrix;
                    
                    this.objects.Draw();
                    break;
                }
            case GameState.Menu:
                {
                    break;
                }
        }
    }

    public UpdateGame(): void 
    {   
        // shoot a ball if space is pressed
        if ( Input.IsKeyDown( Keys.Space, true ) ) 
        {
            // delete the old ball and make a new one
            //this.objects.RemoveObjectByName("ShootyBall");
            this.objects.CreateObject( ( "ShootyBall" + this.ballsFired ), ShaderController.GetShader( "light" ) );
            this.shootyBall = this.objects.GetObjectByName( "ShootyBall" + this.ballsFired );

            // move ball to origin
            //this.shootyBall.Transform.Translate( this.shootyBall.Transform.Position.Inverse );

            // scale it
            this.shootyBall.Transform.Scale( 20.0, 20.0, 20.0 );

            // move ball to camera
            this.shootyBall.Transform.Translate( this.Camera.Owner.Transform.Position );
            this.shootyBall.Transform.Translate( 0, 0, 18 );

            // give the ball a force
            //this.shootyBall.

            // shooty the ball
            this.shootyBall.MakeShootyBall();

            log("Balls Fired: " + this.ballsFired);

            this.ballsFired++;
        }
    }

    public Shutdown(): void
    {
        log( "Shutting down" );
        this.objects.ClearObjects();
    }
}