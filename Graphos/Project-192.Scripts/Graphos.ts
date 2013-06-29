// Interface for Vectors
interface Vector3
{
    x: Number;
    y: Number;
    z: Number;
}

// Interface for object transforms
interface Transform
{
    position: Vector3;
    rotation: Vector3;
    scale: Vector3;
}

// Class with variables and functions
class GameObject
{
    // ID of owner object
    public id: string;

    // Transform object
    public transform: Transform;

    // Abstract method for updating object
    public Update( deltaTime: number ): void
    {
        throw new Error( "Implement your own damn Update!" );
    }
}

// Interface that allows GameObjects to check for input
interface Input
{
    IsKeyDown( key: number ): bool;
}
declare var Input: Input;

// Print function
declare function log(toPrint: any): void;

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