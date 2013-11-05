/// <reference path="Graphos.ts" />

class MyGame extends GraphosGame
{
    objects: GameObjectCollection;
    box: GameObject;

    public Initialize(): void
    {
        log( "Initializing" );

        this.objects = new GameObjectCollection();

        this.objects.LoadObjects( "" );
        this.box = this.objects.GetObjectByName( "Cube2" );
    }

    public Update(): void
    {
        //log( "Updating" );
        this.box.Update();
    }

    public Draw(): void
    {
        //log( "Drawing" );
        this.box.Draw();
    }

    public Shutdown(): void
    {
        //log( "Shutting down" );
    }
}