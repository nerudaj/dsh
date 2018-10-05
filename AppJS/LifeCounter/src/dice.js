'static'; function RenderDice() {
	var canvas = this.app.canvas;
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText(TEXTS.whoStarts, true);
	header.setColor('#AAAAAA');
	
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
	RenderToolbarTemplate(canvas, buttons, 'dice');
}

'static'; function RenderThrowDisplay(canvas) {
	var display = canvas.add(0, 0, 1, 1, 'div', ID('ThrowResultBoard'));
	
	if (SYS_DICE_DISPLAY_FONT_SIZE == null) {
		SYS_DICE_DISPLAY_FONT_SIZE = GetOptimalFontSize("#######", display.width, display.height, 1000);
	}
	display.dom.style.fontSize = SYS_DICE_DISPLAY_FONT_SIZE + 'px';
	display.setText("??");
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