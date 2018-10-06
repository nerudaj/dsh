'static'; function RenderDice() {
	var canvas = this.app.canvas;

	RenderViewHeaderTemplate(canvas, TEXTS.whoStarts);
	
	var board = GetDrawingCanvas(canvas, true);
	RenderThrowDisplay(board);
	
	// Render toolbar
	var buttons = [
		new ButtonTemplate(TEXTS.throwDice, function() {
			ThrowDice();
		}),
		new ButtonTemplate(TEXTS.tossCoin, function() {
			TossCoin();
		}),
		new ButtonTemplate(TEXTS.back, function() {
			app.toggleView('score');
		})
	];
	RenderToolbarTemplate(canvas, buttons, ID('CacheDiceToolbar'));
}

'static'; function RenderThrowDisplay(canvas) {
	var display = canvas.add(0, 0, 1, 1, 'div', ID('DOMThrowResultBoard'));
	
	var FONT_SIZE = ReadFontSizeCache(display, 1, 1, '#######', ID('CacheThrowDisplay'), 1000);
	display.setText("??", false, FONT_SIZE);
}

'static'; function ThrowDice() {
	var DICE_SIDES = ['⚀', '⚁', '⚂', '⚃', '⚄', '⚅'];

	var dom = GetDOM(ID('DOMThrowResultBoard'));
	dom.innerHTML = '';
	for (var i = 0; i < 3; i++) {
		dom.innerHTML += DICE_SIDES[(Random(1, 6) - 1)] + ' ';
	}
}

'static'; function TossCoin() {
	var COIN_SIDES = [TEXTS.coin1, TEXTS.coin2];
	
	var dom = GetDOM(ID('DOMThrowResultBoard'));
	dom.innerHTML = COIN_SIDES[Random(1, 2) - 1];
}