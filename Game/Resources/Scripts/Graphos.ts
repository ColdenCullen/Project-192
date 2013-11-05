// Interface for Vectors
declare class Vector3
{
    public x: Number;
    public y: Number;
    public z: Number;
    public Inverse: Vector3;

    constructor();
    constructor( x: number, y: number, z: number );
    constructor( other: Vector3 );

    public Equals( other: Vector3 ): boolean;
    public Dot( other: Vector3 ): number;
    public Cross( other: Vector3 ): Vector3;
    public Add( other: Vector3 ): Vector3;
    public Multiply( other: number ): Vector3;

    public static TripleProduct( a: Vector3, b: Vector3, c: Vector3 ): Vector3;
}

declare class Matrix4
{
    public Mul( other: Vector3 ): Vector3;
    public Mul( other: Matrix4 ): Matrix4;
    public Add( other: Matrix4 ): Matrix4;
    public Equals( other: Matrix4 ): boolean;
}

// Interface for object transforms
declare class Transform
{
    public Position: Vector3;
    public Rotation: Vector3;
    //public Scale: Vector3;
    public Right: Vector3;
    public Up: Vector3;
    public Forward: Vector3;

    public Rotate(rotation: Vector3): void;
    public Rotate(x: number, y: number, z: number): void;
    public Translate(displacement: Vector3): void;
    public Translate(x: number, y: number, z: number): void;
    public Scale(scale: Vector3): void;
    public Scale(x: number, y: number, z: number): void;
}

declare class Camera
{
    public GetViewMatrix(): Matrix4;
}

class IShader
{
    public ModelMatrix: Matrix4;
    public ViewMatrix: Matrix4;
    public ProjectionMatrix: Matrix4;
    public ModelViewProjectionMatrix: Matrix4;
    public RegisterConstBuffer( buffer: any ): void { }

    public SetUniform( name: string, value: number ): void { }
    public SetUniformMatrix( name: string, value: Matrix4 ): void { }
}

declare class Mesh
{
    public Draw( shader: IShader ): void;
}

declare class Texture
{
    public Draw( shader: IShader ): void;
}

// Class with variables and functions
class GameObject
{
    // Transform object
    public Transform: Transform;

    // Abstract method for updating object
    public Update(): void { }
    public Draw(): void { }
}

declare class GameObjectCollection
{
    public LoadObjects( path: string ): void;
    public ClearObjects(): void;
    public CreateObject( name: string, shader: IShader ): number;
    public GetObjectById( id: number ): GameObject;
    public GetObjectByName( name: string ): GameObject;
    public RemoveObjectById( id: number ): void;
    public RemoveObjectByName( name: string ): void;
}

class GraphosGame
{
    public CurrentState: GameState;

    // DO NOT OVERRIDE
    public Reset(): void { }
    public Exit(): void { }

    // To be overridden
    public Initialize(): void { }
    public Update(): void { }
    public Draw(): void { }
    public Shutdown(): void { }
}

enum GameState
{
    Menu = 0,
    Game = 1
}

declare class Time
{
    public static DeltaTime: number;
    public static TotalTime: number;
}

// Interface that allows GameObjects to check for input
declare class Input
{
    public static IsKeyDown( key: number ): boolean;
}

// Print function
declare function log( toPrint: any ): void;

enum Keys
{
    Backspace = 8,
    Tab = 9,
    Enter = 13,
    Shift = 16,
    Control = 17,
    Alt = 18,
    PauseBreak = 19,
    CapsLock = 20,
    Escape = 27,
    Space = 32,
    PageUp = 33,
    PageDown = 34,
    End = 35,
    Home = 36,
    Left = 37,
    Up = 38,
    Right = 39,
    Down = 40,
    PlusSign = 43,
    printscreen = 44,
    Insert = 45,
    Delete = 46,
    Main0 = 48,
    Main1 = 49,
    Main2 = 50,
    Main3 = 51,
    Main4 = 52,
    Main5 = 53,
    Main6 = 54,
    Main7 = 55,
    Main8 = 56,
    Main9 = 57,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    Numpad0 = 96,
    Numpad1 = 97,
    Numpad2 = 98,
    Numpad3 = 99,
    Numpad4 = 100,
    Numpad5 = 101,
    Numpad6 = 102,
    Numpad7 = 103,
    Numpad8 = 104,
    Numpad9 = 105,
    NumpadAsterisk = 106,
    NumpadPlusSign = 107,
    NumpadEqualSign = 109,
    NumpadPeriod = 110,
    NumpadForwardSlash = 111,
    F1 = 112,
    F2 = 113,
    F3 = 114,
    F4 = 115,
    F5 = 116,
    F6 = 117,
    F7 = 118,
    F8 = 119,
    F9 = 120,
    F10 = 121,
    F11 = 122,
    F12 = 123,
    NumLock = 144,
    ScrollLock = 145,
    SemiColon = 186,
    EqualSign = 187,
    Colon = 188,
    Hyphen = 189,
    Period = 190,
    ForwardSlash = 191,
    BackTick = 192,
    OpenSquareBrace = 219,
    BackSlash = 220,
    CloseSquareBrace = 221,
    SingleQuote = 222
}