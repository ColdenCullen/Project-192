// Class with variables and functions
var GameObject = (function () {
    function GameObject() {
    }
    // Abstract method for updating object
    GameObject.prototype.Update = function (deltaTime) {
    };
    return GameObject;
})();

var Keys;
(function (Keys) {
    Keys[Keys["Backspace"] = 8] = "Backspace";
    Keys[Keys["Tab"] = 9] = "Tab";
    Keys[Keys["Enter"] = 13] = "Enter";
    Keys[Keys["Shift"] = 16] = "Shift";
    Keys[Keys["Control"] = 17] = "Control";
    Keys[Keys["Alt"] = 18] = "Alt";
    Keys[Keys["PauseBreak"] = 19] = "PauseBreak";
    Keys[Keys["CapsLock"] = 20] = "CapsLock";
    Keys[Keys["Escape"] = 27] = "Escape";
    Keys[Keys["Space"] = 32] = "Space";
    Keys[Keys["PageUp"] = 33] = "PageUp";
    Keys[Keys["PageDown"] = 34] = "PageDown";
    Keys[Keys["End"] = 35] = "End";
    Keys[Keys["Home"] = 36] = "Home";
    Keys[Keys["Left"] = 37] = "Left";
    Keys[Keys["Up"] = 38] = "Up";
    Keys[Keys["Right"] = 39] = "Right";
    Keys[Keys["Down"] = 40] = "Down";
    Keys[Keys["PlusSign"] = 43] = "PlusSign";
    Keys[Keys["printscreen"] = 44] = "printscreen";
    Keys[Keys["Insert"] = 45] = "Insert";
    Keys[Keys["Delete"] = 46] = "Delete";
    Keys[Keys["Main0"] = 48] = "Main0";
    Keys[Keys["Main1"] = 49] = "Main1";
    Keys[Keys["Main2"] = 50] = "Main2";
    Keys[Keys["Main3"] = 51] = "Main3";
    Keys[Keys["Main4"] = 52] = "Main4";
    Keys[Keys["Main5"] = 53] = "Main5";
    Keys[Keys["Main6"] = 54] = "Main6";
    Keys[Keys["Main7"] = 55] = "Main7";
    Keys[Keys["Main8"] = 56] = "Main8";
    Keys[Keys["Main9"] = 57] = "Main9";
    Keys[Keys["A"] = 65] = "A";
    Keys[Keys["B"] = 66] = "B";
    Keys[Keys["C"] = 67] = "C";
    Keys[Keys["D"] = 68] = "D";
    Keys[Keys["E"] = 69] = "E";
    Keys[Keys["F"] = 70] = "F";
    Keys[Keys["G"] = 71] = "G";
    Keys[Keys["H"] = 72] = "H";
    Keys[Keys["I"] = 73] = "I";
    Keys[Keys["J"] = 74] = "J";
    Keys[Keys["K"] = 75] = "K";
    Keys[Keys["L"] = 76] = "L";
    Keys[Keys["M"] = 77] = "M";
    Keys[Keys["N"] = 78] = "N";
    Keys[Keys["O"] = 79] = "O";
    Keys[Keys["P"] = 80] = "P";
    Keys[Keys["Q"] = 81] = "Q";
    Keys[Keys["R"] = 82] = "R";
    Keys[Keys["S"] = 83] = "S";
    Keys[Keys["T"] = 84] = "T";
    Keys[Keys["U"] = 85] = "U";
    Keys[Keys["V"] = 86] = "V";
    Keys[Keys["W"] = 87] = "W";
    Keys[Keys["X"] = 88] = "X";
    Keys[Keys["Y"] = 89] = "Y";
    Keys[Keys["Z"] = 90] = "Z";
    Keys[Keys["Numpad0"] = 96] = "Numpad0";
    Keys[Keys["Numpad1"] = 97] = "Numpad1";
    Keys[Keys["Numpad2"] = 98] = "Numpad2";
    Keys[Keys["Numpad3"] = 99] = "Numpad3";
    Keys[Keys["Numpad4"] = 100] = "Numpad4";
    Keys[Keys["Numpad5"] = 101] = "Numpad5";
    Keys[Keys["Numpad6"] = 102] = "Numpad6";
    Keys[Keys["Numpad7"] = 103] = "Numpad7";
    Keys[Keys["Numpad8"] = 104] = "Numpad8";
    Keys[Keys["Numpad9"] = 105] = "Numpad9";
    Keys[Keys["NumpadAsterisk"] = 106] = "NumpadAsterisk";
    Keys[Keys["NumpadPlusSign"] = 107] = "NumpadPlusSign";
    Keys[Keys["NumpadEqualSign"] = 109] = "NumpadEqualSign";
    Keys[Keys["NumpadPeriod"] = 110] = "NumpadPeriod";
    Keys[Keys["NumpadForwardSlash"] = 111] = "NumpadForwardSlash";
    Keys[Keys["F1"] = 112] = "F1";
    Keys[Keys["F2"] = 113] = "F2";
    Keys[Keys["F3"] = 114] = "F3";
    Keys[Keys["F4"] = 115] = "F4";
    Keys[Keys["F5"] = 116] = "F5";
    Keys[Keys["F6"] = 117] = "F6";
    Keys[Keys["F7"] = 118] = "F7";
    Keys[Keys["F8"] = 119] = "F8";
    Keys[Keys["F9"] = 120] = "F9";
    Keys[Keys["F10"] = 121] = "F10";
    Keys[Keys["F11"] = 122] = "F11";
    Keys[Keys["F12"] = 123] = "F12";
    Keys[Keys["NumLock"] = 144] = "NumLock";
    Keys[Keys["ScrollLock"] = 145] = "ScrollLock";
    Keys[Keys["SemiColon"] = 186] = "SemiColon";
    Keys[Keys["EqualSign"] = 187] = "EqualSign";
    Keys[Keys["Colon"] = 188] = "Colon";
    Keys[Keys["Hyphen"] = 189] = "Hyphen";
    Keys[Keys["Period"] = 190] = "Period";
    Keys[Keys["ForwardSlash"] = 191] = "ForwardSlash";
    Keys[Keys["BackTick"] = 192] = "BackTick";
    Keys[Keys["OpenSquareBrace"] = 219] = "OpenSquareBrace";
    Keys[Keys["BackSlash"] = 220] = "BackSlash";
    Keys[Keys["CloseSquareBrace"] = 221] = "CloseSquareBrace";

    Keys[Keys["SingleQuote"] = 222] = "SingleQuote";
})(Keys || (Keys = {}));
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
/// <reference path="Graphos.ts" />
// Interface
var GameObject1 = (function (_super) {
    __extends(GameObject1, _super);
    function GameObject1() {
        _super.call(this);
    }
    GameObject1.prototype.Update = function () {
        if (Input.IsKeyDown(Keys.Space)) {
            log(Time.DeltaTime);
        }
    };
    return GameObject1;
})(GameObject);
//@ sourceMappingURL=__output.js.map
