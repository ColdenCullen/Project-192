/// <reference path="Graphos.ts" />

// Interface
class GameObject1 extends GameObject
{
    constructor()
    {
        super();

        //this.vec1 = new Vector3();
        //this.vec1.x = 5.0;

        //this.vec2 = new Vector3();
        //this.vec2.y = 5.0;
    }

    public Update(): void
    {
        //log("Update");

        if (Input.IsKeyDown(Keys.Space))
        {
            //log(Time.DeltaTime);
            //this.Transform.Translate(new Vector3(1.0, 1.0, 0.0));
            this.Transform.Translate( 1.0, 1.0, 1.0 );
            log(this.Transform.Position.x);
        }
    }
}