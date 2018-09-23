function RenderDice() {
	var canvas = this.app.canvas;
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText('Kdo začne?', true);
	header.setColor('#AAAAAA');
	
	var board = canvas.add(0, 0.1, 1, 0.8, 'div', ID('ThrowResultBoard'));
	board.setColor('lightgrey');
	var optimFontSize = GetOptimalFontSize("#######", board.width, board.height, 1000);
	board.dom.style.fontSize = optimFontSize + 'px';
	board.setText("??");
	
	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	toolbar.dom.style.border = '1px solid black';
	RenderToolbarDice(toolbar, this.app);
}

'static'; function RenderToolbarDice(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 1 / 3;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	var opt1 = canvas.add(0.0, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	var optimFontSize = GetOptimalFontSize('Hoď kostkami', opt1.width, opt1.height);
	opt1.dom.addEventCallback('click', function() { ThrowDice(app); });
	opt1.dom.style.fontSize = optimFontSize + 'px';
	opt1.setText('Hoď kostkami');
	
	var opt2 = canvas.add(1 / 3, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt2.dom.addEventCallback('click', function() { TossCoin(app); });
	opt2.dom.style.fontSize = optimFontSize + 'px';
	opt2.setText('Hoď mincí');
	
	var opt3 = canvas.add(2 / 3, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt3.dom.addEventCallback('click', function() { app.toggleView('score'); });
	opt3.dom.style.fontSize = optimFontSize + 'px';
	opt3.setText('Zpět');
}

'static'; function ThrowDice(app) {
	var DICE_SIDES = ['⚀', '⚁', '⚂', '⚃', '⚄', '⚅'];
	
	var d1 = Random(1, 6) - 1;
	var d2 = Random(1, 6) - 1;
	var d3 = Random(1, 6) - 1;
	
	var dom = GetDOM(ID('ThrowResultBoard'));
	dom.innerHTML = DICE_SIDES[d1] + ' ' + DICE_SIDES[d2] + ' ' + DICE_SIDES[d3];
}

'static'; function TossCoin(app) {
	var COIN_SIDES = ['hlava', 'orel'];
	
	var dom = GetDOM(ID('ThrowResultBoard'));
	dom.innerHTML = COIN_SIDES[Random(1, 2) - 1];
}