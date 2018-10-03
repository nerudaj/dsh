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
	
	// Render toolbar
	var buttons = [
		new ToolbarButton(TEXTS.apply, function() {
			ApplySettings(app); app.toggleView('score');
		}),
		new ToolbarButton(TEXTS.back, function() {
			app.toggleView('score');
		})
	];
	RenderToolbarTemplate(canvas, buttons, 'settings');
}

// === TOP LEVEL ===

'static'; function RenderSettingBoard(canvas, app) {
	var ROW_COUNT = 11;
	var ROW_HEIGHT = 1 / ROW_COUNT;
	var headers = [ TEXTS.plCount, TEXTS.initScore, TEXTS.plColors ];
	
	if (SYS_SETTINGS_TEXT_FONT_SIZE == null) {
		SYS_SETTINGS_TEXT_FONT_SIZE = GetOptimalFontSize(
			maxStr(headers[0], maxStr(headers[1], headers[2])),
			canvas.width,
			canvas.height * ROW_HEIGHT
		);
	}
	
	// This line applies to everything but buttons
	canvas.dom.style.fontSize = SYS_SETTINGS_TEXT_FONT_SIZE + 'px';
	
	for (var i = 0; i < headers.length; i++) {
		var header = canvas.add(0, 2 * i * ROW_HEIGHT, 1, ROW_HEIGHT);
		header.setText(headers[i]);
		header.setColor(SYSCOLOR_HEADER);
	}

	var pcount = canvas.add(0, 1 * ROW_HEIGHT, 1, ROW_HEIGHT);
	RenderFormPlayerCount(pcount, app);

	var sinit = canvas.add(0, 3 * ROW_HEIGHT, 1, ROW_HEIGHT);
	RenderFormInitScore(sinit, app);

	var cwheel = canvas.add(0, 5 * ROW_HEIGHT, 1, 6 * ROW_HEIGHT);
	RenderFormColorWheel(cwheel, app);
}

// === Second level ===

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
	var values = [ -5, -1, null, 1, 5 ];
	var btnColors = [ 'darkred', 'red', null, 'lightgreen', 'green' ];
	var classes = [ LEFT_BTN_CLASS, RIGHT_BTN_CLASS, null, LEFT_BTN_CLASS, RIGHT_BTN_CLASS ];

	if (SYS_SETTINGS_BUTTON_FONT_SIZE == null) {
		SYS_SETTINGS_BUTTON_FONT_SIZE = GetOptimalFontSize('XX', canvas.width * ITEM_WIDTH, canvas.height);
	}

	for (var i = 0; i < values.length; i++) {
		if (values[i] == null) continue;
		
		(function(p){
			var btn = canvas.add(i * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'button');
			btn.dom.addEventCallback('click', function() { ModifyInitScore(values[p], app); });
			btn.dom.className = classes[p];
			btn.dom.style.fontSize = SYS_SETTINGS_BUTTON_FONT_SIZE + 'px';
			btn.setColor(btnColors[p]);
			btn.setText(values[p]);
		}(i));
	}
	
	var display = canvas.add(2 * ITEM_WIDTH, 0, ITEM_WIDTH, 1, 'div', ID('FormInitScoreDisplay'));
	display.setText(app.context.initScore, true);
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
		for (var c = 0; c < Colors.length; c++) {
			var item = canvas.add(c * ITEM_WIDTH, i * ROW_HEIGHT, ITEM_WIDTH, ROW_HEIGHT);
			item.setColor(Colors[c]);
			
			var checked = '';
			if (app.context.colorSetup[i] == c) {
				checked = 'checked';
			}
			item.dom.innerHTML = '<input type="radio" name="' + ID('FormPlayerColor') + i + '" value="' + c + '" ' + checked + '>';
		}
	}
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