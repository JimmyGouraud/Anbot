

function init()
{
    $.support.cors = true;
    $.ajax({
	url: 'localhost:8080/bouh.txt',
	success: function (data, textStatus, jqXHR)
	{
	    alert("success : " + textStatus + " " + data);
	},
	error: function (error)
	{
	    //alert("Errors : " + error);
	    console.log("Errors : " + error);
	}
    });
}

window.addEventListener("load", init, false);

/*
var adressServer = "ws://jimmy.gouraud.emi.u-bordeaux.fr/";

var output;

function init()
{
    output = document.getElementById("output");
    initWebSocket();
}


function initWebSocket()
{
    websocket = new WebSocket(adressServer);
    websocket.onopen = function(evt) { onOpen(evt) };
    websocket.onclose = function(evt) { onClose(evt) };
    websocket.onmessage = function(evt) { onMessage(evt) };
    websocket.onerror = function(evt) { onError(evt) };
}

function onOpen(evt)
{
    doSend("init");
}

function onClose(evt)
{
    writeToScreen("DISCONNECTED");
}

function onMessage(evt)
{
    
}

function onError(evt)
{
    
    writeToScreen('<span style="color: red;">ERROR:</span> ' + evt.data);
    
}

function doSend(message)
{
    websocket.send(message);
}

function writeToScreen(message)
{
    var pre = document.createElement("p");
    pre.style.wordWrap = "break-word";
    pre.innerHTML = message;
    output.appendChild(pre);
}
*/
