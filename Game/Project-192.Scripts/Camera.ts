/// <reference path="Graphos.ts" />

class Camera extends GameObject
{
    public Update(): void
    {
        // Movement
        if (Input.IsKeyDown(Keys.W))
        {
            this.Transform.Translate(0.0, 0.0, 0.001);
        }
        if (Input.IsKeyDown(Keys.A))
        {
            this.Transform.Translate(-0.001, 0.0, 0.0);
        }
        if (Input.IsKeyDown(Keys.S))
        {
            this.Transform.Translate(0.0, 0.0, -0.001);
        }
        if (Input.IsKeyDown(Keys.D))
        {
            this.Transform.Translate(0.001, 0.0, 0.0);
        }

        // Rotation
        if (Input.IsKeyDown(Keys.Up))
        {
            this.Transform.Rotate(0.001, 0.0, 0.0);
        }
        if (Input.IsKeyDown(Keys.Down))
        {
            this.Transform.Rotate(-0.001, 0.0, 0.0);
        }
        if (Input.IsKeyDown(Keys.Left))
        {
            this.Transform.Rotate(0.0, -0.001, 0.0);
        }
        if (Input.IsKeyDown(Keys.Right))
        {
            this.Transform.Rotate(0.0, 0.001, 0.0);
        }
    }
}