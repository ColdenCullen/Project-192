var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var Cube = (function (_super) {
    __extends(Cube, _super);
    function Cube() {
        _super.apply(this, arguments);
    }
    Cube.prototype.Update = function (deltaTime) {
        if (Input.IsKeyDown(Keys["space"]))
            log(this.transform.position.x);
    };
    return Cube;
})(GameObject);
