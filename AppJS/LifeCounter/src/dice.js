'static'; function RenderDice() {
	var canvas = this.app.canvas;

	RenderViewHeaderTemplate(canvas, TEXTS.whoStarts);
	
	var board = GetDrawingCanvas(canvas, true);
	RenderThrowDisplay(board);
	
	// Render toolbar
	var buttons = [
		new ButtonTemplate(TEXTS.throwDice, function() {
			ThrowDice(app);
		}),
		new ButtonTemplate(TEXTS.tossCoin, function() {
			TossCoin(app);
		}),
		new ButtonTemplate(TEXTS.back, function() {
			app.toggleView('score');
		})
	];
	RenderToolbarTemplate(canvas, buttons, ID('dice'));
}

'static'; function RenderThrowDisplay(canvas) {
	var display = canvas.add(0, 0, 1, 1, 'div', ID('ThrowResultBoard'));
	
	var FONT_SIZE = ReadFontSizeCache(display, 1, 1, '#######', ID('throw_result'), 1000);
	display.setText("??", false, FONT_SIZE);
}

'static'; function ThrowDice(app) {
	var DICE_SIDES = ['⚀', '⚁', '⚂', '⚃', '⚄', '⚅'];

	var dom = GetDOM(ID('ThrowResultBoard'));
	dom.innerHTML = '';
	for (var i = 0; i < 3; i++) {
		dom.innerHTML += DICE_SIDES[(Random(1, 6) - 1)] + ' ';
	}
}

'static'; function TossCoin(app) {
	var COIN_SIDES = [TEXTS.coin1, TEXTS.coin2];
	
	var dom = GetDOM(ID('ThrowResultBoard'));
	dom.innerHTML = COIN_SIDES[Random(1, 2) - 1];
}