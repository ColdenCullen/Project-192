var __extends = this.__extends || function (d, b) {
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
/// <reference path="Graphos.ts" />
include("Resources/Scripts/Graphos.js");
// Class
var Cube = (function (_super) {
    __extends(Cube, _super);
    function Cube() {
        _super.apply(this, arguments);

    }
    Cube.prototype.Update = // Is called every frame
    function (deltaTime) {
        if(Input.IsKeyDown(Keys["space"])) {
            log(this.transform.position.x);
        }
    };
    return Cube;
})(GameObject);
//@ sourceMappingURL=Cube.js.map
