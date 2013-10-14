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
        if (Input.IsKeyDown(Keys.Space))
        {
            log(this.Transform.Rotation.x);
            //this.Transform.Translate(new Vector3(1.0, 1.0, 0.0));
            this.Transform.Rotate( 0.1, 0.1, 0.0 );
            //log(this.Transform.Rotation.x);
        }

        if (Input.IsKeyDown(Keys.W)) {
            this.Transform.Translate(0.0, 0.001, 0.0);
        }

        if (Input.IsKeyDown(Keys.S)) {
            this.Transform.Translate(0.0, -0.001, 0.0);
        }

        if (Input.IsKeyDown(Keys.A)) {
            this.Transform.Translate(-0.001, 0.0, 0.0);
        }

        if (Input.IsKeyDown(Keys.D)) {
            this.Transform.Translate(0.001, 0.0, 0.0);
        }
    }
}