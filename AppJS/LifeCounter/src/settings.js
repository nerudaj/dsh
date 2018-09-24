'static'; var MinPlayers = 2;
'static'; var MaxPlayers = 6;
var Colors = [ 'red', 'lightgreen', 'lightblue', 'yellow', 'pink', 'orange', 'grey', 'white' ];
'static'; var LEFT_BTN_CLASS = 'init_score_btn init_score_btn_left';
'static'; var RIGHT_BTN_CLASS = 'init_score_btn init_score_btn_right';

function RenderSettings() {
	var canvas = this.app.canvas;
	
	var board = canvas.add(0, 0, 1, 0.9);
	board.setColor('lightgrey');
	RenderSettingBoard(board, this.app);

	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.dom.style.border = '1px solid black';
	toolbar.setColor('grey');
	RenderSettingsToolbar(toolbar, this.app);
}

'static'; function RenderSettingBoard(canvas, app) {
	var ROW_COUNT = 11;
	var ROW_HEIGHT = 1 / ROW_COUNT;
	canvas.dom.style.fontSize = GetOptimalFontSize(TEXTS.initScore, canvas.width, canvas.height * ROW_HEIGHT) + 'px';

	var header1 = canvas.add(0, 0, 1, ROW_HEIGHT);
	header1.setText(TEXTS.plCount, false);
	header1.setColor('#AAAAAA');

	var pcount = canvas.add(0, 1 * ROW_HEIGHT, 1, ROW_HEIGHT);
	RenderFormPlayerCount(pcount, app);

	var header2 = canvas.add(0, 2 * ROW_HEIGHT, 1, ROW_HEIGHT);
	header2.setText(TEXTS.initScore, false);
	header2.setColor('#AAAAAA');

	var sinit = canvas.add(0, 3 * ROW_HEIGHT, 1, ROW_HEIGHT);
	RenderFormInitScore(sinit, app);

	var header3 = canvas.add(0, 4 * ROW_HEIGHT, 1, ROW_HEIGHT);
	header3.setText(TEXTS.plColors, false);
	header3.setColor('#AAAAAA');
	
	var cwheel = canvas.add(0, 5 * ROW_HEIGHT, 1, 6 * ROW_HEIGHT);
	RenderFormColorWheel(cwheel, app);
}

'static'; function RenderFormPlayerCount(canvas, app) {
	var ITEM_WIDTH = 1 / (MaxPlayers - MinPlayers + 1);

	for (var i = MinPlayers; i <= MaxPlayers; i++) {
		var opt = canvas.add((i - MinPlayers) * ITEM_WIDTH, 0, ITEM_WIDTH, 1);
		var checked = '';
		if (i == app.context.numOfPlayers) checked = 'checked';
		opt.dom.innerHTML = '<input type="radio" name="' + ID('FormPlayerCount') + '" value="' + i + '" ' + checked + '>' + i + '</radio>';
	}
}

'static'; function RenderFormInitScore(canvas, app) {
	var ITEM_WIDTH = 1/ 5;
	
	var minus5 = canvas.add(0, 0, ITEM_WIDTH, 1, 'button');
	minus5.dom.addEventCallback('click', function() { ModifyInitScore(-5, app); });
	minus5.dom.className = LEFT_BTN_CLASS;
	minus5.setColor('darkred');
	minus5.setText('-5', true);
	
	var minus1 = canvas.add(1 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
	minus1.dom.addEventCallback('click', function() { ModifyInitScore(-1, app); });
	minus1.dom.className = RIGHT_BTN_CLASS;
	minus1.setColor('red');
	minus1.setText('-1', true);
	
	var display = canvas.add(2 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'div', ID('FormInitScoreDisplay'));
	display.setText(app.context.initScore, true);
	
	var plus1 = canvas.add(3 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
	plus1.dom.addEventCallback('click', function() { ModifyInitScore(1, app); });
	plus1.dom.className = LEFT_BTN_CLASS;
	plus1.setColor('lightgreen');
	plus1.setText('1', true);
	
	var plus5 = canvas.add(4 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
	plus5.dom.addEventCallback('click', function() { ModifyInitScore(5, app); });
	plus5.dom.className = RIGHT_BTN_CLASS;
	plus5.setColor('green');
	plus5.setText('5', true);
}

'static'; function ModifyInitScore(amount, app) {
	var dom = GetDOM(ID('FormInitScoreDisplay'));
	
	app.context.initScore = parseInt(dom.innerHTML) + amount;
	
	dom.innerHTML = app.context.initScore;
}

'static'; function RenderFormColorWheel(canvas, app) {
	var ROW_HEIGHT = 1 / MaxPlayers;
	var ITEM_WIDTH = 1 / Colors.length;
	
	for (var i = 0; i < MaxPlayers; i++) {
		var row = canvas.add(0, i * ROW_HEIGHT, 1, ROW_HEIGHT);
		row.dom.style.border = "1px solid black";
		
		for (var c = 0; c < Colors.length; c++) {
			var item = row.add(c * ITEM_WIDTH, 0, ITEM_WIDTH, 1);
			item.setColor(Colors[c]);
			
			var checked = '';
			if (app.context.colorSetup[i] == c) {
				checked = 'checked';
			}
			item.dom.innerHTML = '<input type="radio" name="' + ID('FormPlayerColor') + i + '" value="' + c + '" ' + checked + '>';
		}
	}
}

'static'; function RenderSettingsToolbar(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 0.5;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	var opt1 = canvas.add(0, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt1.dom.addEventCallback('click', function() { ApplySettings(app); app.toggleView('score'); });
	opt1.setText(TEXTS.apply, true);

	var opt2 = canvas.add(0.5, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt2.dom.addEventCallback('click', function() { app.toggleView('score'); });
	opt2.setText(TEXTS.back, true);
}

'static'; function ApplySettings(app) {
	var context = app.context;
	var players = context.players;
	
	var form_pcount = GetElementsByName(ID('FormPlayerCount'));
	for (var i = 0; i < form_pcount.length; i++) {
		if (form_pcount[i].checked) {
			context.numOfPlayers = form_pcount[i].value;
			break;
		}
	}
	
	while (context.numOfPlayers < players.length) players.pop();
	while (context.numOfPlayers > players.length) players.push(new Player());
	
	for (var p = 0; p < players.length; p++) {
		var form_color = GetElementsByName(ID('FormPlayerColor') + p);

		for (var i = 0; i < form_color.length; i++) {
			if (form_color[i].checked) {
				context.colorSetup[p] = i;
				break;
			}
		}
		
		players[p].color = Colors[context.colorSetup[p]];
		players[p].score = context.initScore;
	}
}