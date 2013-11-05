/// <reference path="Graphos.ts" />

class MyGame extends GraphosGame
{
    public Initialize(): void
    {
        log( "Initializing" );
    }

    public Update(): void
    {
        log( "Updating" );
    }

    public Draw(): void
    {
        log( "Drawing" );
    }

    public Shutdown(): void
    {
        log( "Shutting down" );
    }
}