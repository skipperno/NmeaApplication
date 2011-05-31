var t;
	var timer_is_on = 0;
	var xmlhttp;
	
	var canvasDoubleBuffElement;
	var canvasDoubleBuffer2Dcontext;
	var canvasDoubleBuff_1pixData;
	
	var colorArray = new Array();
	var nCanvasWidth = 900; // 900 px
	var nCanasHeight = 400;
	var dataParameter = 1;
	
	

	var colors_R = new Array(40, 80, 40, 0, 0, 0, 0, 0, 40, 120, 200, 240, 252,
			224, 180, 160, 120, 80, 40);
	var colors_G = new Array(252, 220, 140, 80, 40, 0, 80, 120, 160, 200, 200,
			240, 200, 120, 80, 0, 0, 0, 0);
	var colors_B = new Array(252, 220, 192, 168, 160, 128, 64, 40, 0, 0, 0, 0,
			0, 0, 0, 20, 40, 20, 0);
	
	function echoPainter_init() {
		canvasDoubleBuffElement = document.createElement('canvas');
		canvasDoubleBuffElement.width = nCanvasWidth + 20; //20 pix if painting 20 times in one sec.(sleep 50ms)
		canvasDoubleBuffElement.height = nCanasHeight;
		
		canvasDoubleBuffer2Dcontext = canvasDoubleBuffElement.getContext('2d');
		canvasDoubleBuff_1pixData = canvasDoubleBuffer2Dcontext.createImageData(1, nCanasHeight);
		
		startDataProviderTimer();
		startPaintingCanvasTimer();
	}
	
	
	function echoPainter_PaintCanvas() {
		canvasDoubleBuffer2Dcontext.drawImage(canvasDoubleBuffElement, -1, 0);
		//var canvasBufferContext = canvasBuffer.getContext('2d');
		//canvasBufferContext.drawImage(document.getElementById('echoCanvas'), -1, 0);
		//TODO: if "createImageData" is not supported by browser, use: "getImageData"
		//var imageData = canvasDoubleBuffer2Dcontext.createImageData(1, nCanasHeight);

		for ( var i = 0; i < colorArray.length; i++) {
			var colorIndex = parseInt((colorArray[i] * 19) / 255);
			canvasDoubleBuff_1pixData.data[i * 4] = colors_R[colorIndex];
			canvasDoubleBuff_1pixData.data[i * 4 + 1] = colors_G[colorIndex];
			canvasDoubleBuff_1pixData.data[i * 4 + 2] = colors_B[colorIndex];

			canvasDoubleBuff_1pixData.data[i * 4 + 3] = 0xff; // opaque
		}

		canvasDoubleBuffer2Dcontext.putImageData(canvasDoubleBuff_1pixData, nCanvasWidth -1, 0);

		document.getElementById('echoCanvas').getContext('2d').drawImage(canvasDoubleBuffElement,
				0, 0);

		////////////////////////////////////////
		startPaintingCanvasTimer();
	}
	
	function echoPainter_getData() {
		///////////////////////////////////////////////
		// Get data using jquery function "get"
		///////////////////////////////////////////////
		$.get("dataProvider.php", // calling php
		{
			index : dataParameter
		}, // parameter to send
		function(data) { // callback function
			var temp = "";
			var colorArray = data.split(",");

			//$('#timeval').html(data); // don't remove. It displays received message
		}

		); // end of "$get"

		///////////////////////////////////////////////
		// Don't remove: The same using jquery function "load"
		///////////////////////////////////////////////
		//$('#timeval').load('dataProvider.php?randval='+ Math.random());
		startDataProviderTimer();
	}
	