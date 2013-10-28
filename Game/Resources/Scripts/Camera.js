/// <reference path="Graphos.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var Camera1 = (function (_super) {
    __extends(Camera1, _super);
    function Camera1() {
        _super.apply(this, arguments);
    }
    Camera1.prototype.Update = function () {
        if (Input.IsKeyDown(Keys.Space)) {
            //log( this.Transform.Forward.x );
            //this.Transform.Translate( this.Transform.Forward );
        }
    };
    return Camera1;
})(GameObject);
