/// <reference path="Graphos.ts" />

class MyGame extends GraphosGame
{
    objects: GameObjectCollection;

    public Initialize(): void
    {
        log( "Initializing" );

        this.objects = new GameObjectCollection();

        this.objects.LoadObjects( "" );

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
        ShaderController.GetShader( "texture" ).ViewMatrix = this.Camera.ViewMatrix;
        ShaderController.GetShader( "texture" ).ProjectionMatrix = WindowController.Get().PerspectiveMatrix;
        ShaderController.GetShader( "light" ).ViewMatrix = this.Camera.ViewMatrix;
        ShaderController.GetShader( "light" ).ProjectionMatrix = WindowController.Get().PerspectiveMatrix;

        switch( this.CurrentState )
        {
            case GameState.Game:
                {
                    this.objects.Draw();
                    break;
                }
            case GameState.Menu:
                {
                    break;
                }
        }
    }

    public Shutdown(): void
    {
        log( "Shutting down" );
        this.objects.ClearObjects();
    }
}