var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var GameObject1 = (function (_super) {
    __extends(GameObject1, _super);
    function GameObject1() {
        _super.apply(this, arguments);
    }
    GameObject1.prototype.Update = function () {
        if (Input.IsKeyDown(Keys.Space))
            log("Testing Update");
    };
    return GameObject1;
})(GameObject);
