var DICE_FONT_SIZE = null;

function RenderDice() {
	var header = this.app.canvas.add(0, 0, 1, 0.1);
	header.setText('Kdo začne?', true);
	header.setColor('lightgrey');
	
	var board = this.app.canvas.add(0, 0.1, 1, 0.8);
	RenderDiceRows(board, this.app)
	
	var toolbar = this.app.canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	RenderToolbarDice(toolbar, this.app);
}

function RenderDiceRows(canvas, app) {
	var ROW_HEIGHT = 1 / app.context.players.length;
	DICE_FONT_SIZE = GetOptimalFontSize('Hráč XX hodil: XXX', canvas.width, canvas.height * ROW_HEIGHT);
	
	for (var i = 0; i < app.context.players.length; i++) {
		var row = canvas.add(0, i * ROW_HEIGHT, 1, ROW_HEIGHT, 'div', 'DiceRow' + i);
		row.dom.style.fontSize = DICE_FONT_SIZE + 'px';
		row.setText('Hráč ' + (i+1) + ' hodil: ??', false, DICE_FONT_SIZE);
		row.setColor(app.context.players[i].color);
	}
}

function RenderToolbarDice(canvas, app) {
	var opt1 = canvas.add(0.05, 0.05, 0.425, 0.9, 'button');
	opt1.dom.addEventListener('click', function() { ThrowDice(app); });
	opt1.setText('Hoď kostkami', true);
	
	var opt2 = canvas.add(0.525, 0.05, 0.425, 0.9, 'button');
	opt2.dom.addEventListener('click', function() { app.toggleView('score'); });
	opt2.setText('Zpět', true);
}

function ThrowDice(app) {
	for (var i = 0; i < app.context.players.length; i++) {
		var row = GetDOM('DiceRow' + i);
		var value = Random(1, 20);
		row.innerHTML = 'Hráč ' + (i+1) + ' hodil: ' + value;
	}
}