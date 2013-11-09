/// <reference path="Graphos.ts" />

class light extends IShader
{
    thing: number;

    Draw(): void
    {
        this.SetUniform( "shaderTexture", 0 );
        this.SetUniformMatrix( "modelViewProjection", this.ModelViewProjectionMatrix );
        this.SetUniformMatrix( "modelMatrix", this.ModelMatrix );
    }
}

class texture extends IShader
{
    thang: number;

    Draw(): void
    {
        this.SetUniform( "shaderTexture", 0 );
        this.SetUniformMatrix( "modelViewProjection", this.ModelViewProjectionMatrix );
    }
}
