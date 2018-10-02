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
	
	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	toolbar.dom.style.border = '1px solid black';
	RenderToolbarDice(toolbar, this.app);
}

'static'; function RenderToolbarDice(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 1 / 3;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	if (SYS_DICE_TOOLBAR_FONT_SIZE == null) {
		SYS_DICE_TOOLBAR_FONT_SIZE = GetOptimalFontSize(
			maxStr(TEXTS.throwDice, maxStr(TEXTS.tossCoin, TEXTS.back)),
			canvas.width * TOOLBAR_BUTTON_WIDTH,
			canvas.height * TOOLBAR_BUTTON_HEIGHT
		);
	}
	
	var options = [ TEXTS.throwDice, TEXTS.tossCoin, TEXTS.back ];
	var foos = [
		function() { ThrowDice(app); },
		function() { TossCoin(app); },
		function() { app.toggleView('score'); }
	];
	
	for (var i = 0; i < options.length; i++) {
		(function(p) {
			var opt = canvas.add(i * TOOLBAR_BUTTON_WIDTH, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
			opt.dom.addEventCallback('click', foos[p]);
			opt.dom.style.fontSize = SYS_DICE_TOOLBAR_FONT_SIZE + 'px';
			opt.setText(options[p]);
		}(i));
	}
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