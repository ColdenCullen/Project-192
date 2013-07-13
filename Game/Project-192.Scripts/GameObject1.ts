/// <reference path="Graphos.ts" />

// Interface
class GameObject1 extends GameObject
{
    vec1: Vector3;
    vec2: Vector3;

    constructor()
    {
        super();

        this.vec1 = new Vector3();
        this.vec1.x = 5.0;

        this.vec2 = new Vector3();
        this.vec2.y = 5.0;
    }

    public Update(): void
    {
        //log("Update");

        if (Input.IsKeyDown(Keys.Space))
            log("Vec.z: " + this.vec1.Cross(this.vec2).z);
    }
}