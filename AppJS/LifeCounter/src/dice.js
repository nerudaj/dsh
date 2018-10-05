function RenderDice() {
	var canvas = this.app.canvas;
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText(TEXTS.whoStarts, true);
	header.setColor('#AAAAAA');
	
	var board = canvas.add(0, 0.1, 1, 0.8, 'div', ID('ThrowResultBoard'));
	board.setColor('lightgrey');
	
	if (SYS_DICE_DISPLAY_FONT_SIZE == null) {
		SYS_DICE_DISPLAY_FONT_SIZE = GetOptimalFontSize("#######", board.width, board.height, 1000);
	}
	board.dom.style.fontSize = SYS_DICE_DISPLAY_FONT_SIZE + 'px';
	board.setText("??");
	
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