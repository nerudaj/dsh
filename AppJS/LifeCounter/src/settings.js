var MIN_PLAYERS = 2;
var MAX_PLAYERS = 6;
var COLORS = [ 'red', 'lightgreen', 'lightblue', 'yellow', 'pink', 'orange', 'grey', 'white' ];

function RenderSettings() {
	var board = this.app.canvas.add(0, 0, 1, 0.9);
	board.setColor('lightgrey');
	RenderSettingBoard(board, this.app);

	var toolbar = this.app.canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	RenderSettingsToolbar(toolbar, this.app);
}

function RenderSettingBoard(canvas, app) {
	var ROW_COUNT = 11;
	var ROW_HEIGHT = 1 / ROW_COUNT;
	canvas.dom.style.fontSize = GetOptimalFontSize('Počáteční skóre', canvas.width, canvas.height * ROW_HEIGHT) + 'px';

	var header1 = canvas.add(0, 0, 1, ROW_HEIGHT);
	header1.setText('Počet hráčů:', false);

	var pcount = canvas.add(0, 1 * ROW_HEIGHT, 1, ROW_HEIGHT);
	RenderFormPlayerCount(pcount, app);

	var header2 = canvas.add(0, 2 * ROW_HEIGHT, 1, ROW_HEIGHT);
	header2.setText('Počáteční skóre:', false);

	var sinit = canvas.add(0, 3 * ROW_HEIGHT, 1, ROW_HEIGHT);
	RenderFormInitScore(sinit, app);

	var header3 = canvas.add(0, 4 * ROW_HEIGHT, 1, ROW_HEIGHT);
	header3.setText('Barvy hráčů:', false);
	
	var cwheel = canvas.add(0, 5 * ROW_HEIGHT, 1, 6 * ROW_HEIGHT);
	RenderFormColorWheel(cwheel, app);
}

function RenderFormPlayerCount(canvas, app) {
	var ITEM_WIDTH = 1 / (MAX_PLAYERS - MIN_PLAYERS + 1);

	for (var i = MIN_PLAYERS; i <= MAX_PLAYERS; i++) {
		var opt = canvas.add((i - MIN_PLAYERS) * ITEM_WIDTH, 0, ITEM_WIDTH, 1);
		var checked = '';
		if (i == app.context.numOfPlayers) checked = 'checked';
		opt.dom.innerHTML = '<input type="radio" name="FormPlayerCount" value="' + i + '" ' + checked + '>' + i + '</radio>';
	}
}

function RenderFormInitScore(canvas, app) {
	var ITEM_WIDTH = 1/ 5;
	
	var minus5 = canvas.add(0, 0, ITEM_WIDTH, 1, 'button');
	minus5.dom.addEventListener('click', function() { ModifyInitScore(-5, app); });
	minus5.setColor('darkred');
	minus5.setText('-5');
	
	var minus1 = canvas.add(1 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
	minus1.dom.addEventListener('click', function() { ModifyInitScore(-1, app); });
	minus1.setColor('red');
	minus1.setText('-1');
	
	var display = canvas.add(2 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'div', 'FormInitScoreDisplay');
	display.setText(app.context.initScore);
	
	var plus1 = canvas.add(3 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
	plus1.dom.addEventListener('click', function() { ModifyInitScore(1, app); });
	plus1.setColor('lightgreen');
	plus1.setText('1');
	
	var plus5 = canvas.add(4 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
	plus5.dom.addEventListener('click', function() { ModifyInitScore(5, app); });
	plus5.setColor('green');
	plus5.setText('5');
}

function ModifyInitScore(amount, app) {
	var dom = GetDOM('FormInitScoreDisplay');
	
	app.context.initScore = parseInt(dom.innerHTML) + amount;
	
	dom.innerHTML = app.context.initScore;
}

function RenderFormColorWheel(canvas, app) {
	var ROW_HEIGHT = 1 / MAX_PLAYERS;
	var ITEM_WIDTH = 1 / COLORS.length;
	
	for (var i = 0; i < MAX_PLAYERS; i++) {
		var row = canvas.add(0, i * ROW_HEIGHT, 1, ROW_HEIGHT);
		
		for (var c = 0; c < COLORS.length; c++) {
			var item = row.add(c * ITEM_WIDTH, 0, ITEM_WIDTH, 1);
			item.setColor(COLORS[c]);
			
			var checked = '';
			if (app.context.colorSetup[i] == c) {
				checked = 'checked';
			}
			item.dom.innerHTML = '<input type="radio" name="FormPlayerColor' + i + '" value="' + c + '" ' + checked + '>';
		}
	}
}

function RenderSettingsToolbar(canvas, app) {
	var opt1 = canvas.add(0, 0, 0.5, 1, 'button');
	opt1.dom.addEventListener('click', function() { ApplySettings(app); app.toggleView('score'); });
	opt1.setText('Použít', true);

	var opt2 = canvas.add(0.5, 0, 0.5, 1, 'button');
	opt2.dom.addEventListener('click', function() { app.toggleView('score'); });
	opt2.setText('Zpět', true);
}

function ApplySettings(app) {
	var form_pcount = document.getElementsByName('FormPlayerCount');
	for (var i = 0; i < form_pcount.length; i++) {
		if (form_pcount[i].checked) {
			app.context.numOfPlayers = form_pcount[i].value;
			break;
		}
	}
	
	var context = app.context;
	while (context.numOfPlayers < context.players.length) context.players.pop();
	while (context.numOfPlayers > context.players.length) context.players.push(new Player());
	
	for (var p = 0; p < context.players.length; p++) {
		var form_color = document.getElementsByName('FormPlayerColor' + p);

		for (var i = 0; i < form_color.length; i++) {
			if (form_color[i].checked) {
				context.colorSetup[p] = i;
				break;
			}
		}
		
		context.players[p].color = COLORS[context.colorSetup[p]];
		context.players[p].score = context.initScore;
	}
}