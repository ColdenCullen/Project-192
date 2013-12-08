var configOptions;

function getConfig()
{
    jQuery.getJSON( '../Config/Config.json', function( json, textStatus )
    {
        configOptions = json;
        $("#adapterName").html("(Using " + configOptions.graphics.Adapter + ")");
        $("#screenWidth").val(configOptions.display.width);
        $("#screenHeight").val(configOptions.display.height);
        $("#fullscreen").prop('checked', configOptions.display.fullscreen);
        $("#vsync").prop('checked', configOptions.graphics.vsync);
        fullscreenChecked();
        //$("#uiScaleValue").val(configOptions.ui.scale.x);
        //$("#uiScaleSlider").val(configOptions.ui.scale.x);
    } );
}

function updateConfig()
{
    setConfig();
}

function setConfig()
{
    GraphosGame.SetConfig( 'display.width', parseInt( $("#screenWidth").val() ) );
    GraphosGame.SetConfig( 'display.height', parseInt( $("#screenHeight").val() ) );
    GraphosGame.SetConfig( 'display.fullscreen', $('#fullscreen').is(':checked') );
    GraphosGame.SetConfig( 'graphics.vsync', $('#vsync').is(':checked') );
    //GraphosGame.SetConfig( 'ui.scale.x', parseFloat( $("#uiScaleValue").val() ) );
    //GraphosGame.SetConfig( 'ui.scale.y', parseFloat( $("#uiScaleValue").val() ) );
    GraphosGame.Reset();
}

$( document ).ready(function() 
{
        getConfig();
});