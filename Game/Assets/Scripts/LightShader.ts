/// <reference path="Graphos.ts" />

class light extends IShader
{
    thing: number;

    Draw(): void
    {
        this.SetUniform( "uShaderTexture", 0 );
        this.SetUniformMatrix( "uModelViewProjection", this.ModelViewProjectionMatrix );
        this.SetUniformMatrix( "uModelMatrix", this.ModelMatrix );
    }
}

class texture extends IShader
{
    thang: number;

    Draw(): void
    {
        this.SetUniform( "uShaderTexture", 0 );
        this.SetUniformMatrix( "uModelViewProjection", this.ModelViewProjectionMatrix );
    }
}
