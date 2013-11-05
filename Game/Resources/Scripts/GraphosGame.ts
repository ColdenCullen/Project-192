/// <reference path="Graphos.ts" />

class MyGame extends GraphosGame
{
    objects: GameObjectCollection;

    public Initialize(): void
    {
        log( "Initializing" );

        this.objects = new GameObjectCollection();

        this.objects.LoadObjects( "" );
    }

    public Update(): void
    {
        this.objects.Update();
    }

    public Draw(): void
    {
        this.objects.Draw();
    }

    public Shutdown(): void
    {
        log( "Shutting down" );
        this.objects.ClearObjects();
    }
}