'static'; var ScoreFontSize = null;

function RenderScore() {
	var canvas = this.app.canvas;
	
	var ScoreFontSize = null; // App might be resized, reset font size
	var board = canvas.add(0, 0, 1, 0.9);
	RenderBoard(board, this.app);
	
	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.dom.style.border = '1px solid black';
	toolbar.setColor('grey');
	RenderToolbar(toolbar, this.app);
}

'static'; function RenderBoard(canvas, app) {
	var playersLength = app.context.players.length;
	
	var COL_COUNT = playersLength == 2 ? 1 : 2;
	var ROW_COUNT = Math.ceil(playersLength / COL_COUNT);
	
	var ITEM_WIDTH = 1 / COL_COUNT;
	var ITEM_HEIGHT = 1 / ROW_COUNT;
	
	var pid = 0;
	for (var y = 0; y < ROW_COUNT; y++) {
		for (var x = 0; x < COL_COUNT; x++) {
			if (playersLength % 2 == 1 && pid + 1 == playersLength) {
				ITEM_WIDTH = 1;
			}
			
			var display = canvas.add(x * ITEM_WIDTH, y * ITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT);
			display.dom.style.border = '1px solid black';
			display.setColor(app.context.players[pid].color);
			RenderDisplay(pid, display, app);
			
			pid++;
			if (playersLength == pid) return;
		}
	}
}

'static'; function RenderDisplay(id, canvas, app) {
	if (ScoreFontSize == null) {
		ScoreFontSize = GetOptimalFontSize('XX', canvas.width * 0.25, canvas.height);
	}
	
	var score = canvas.add(0.25, 0, 0.5, 1, 'div', ID('DisplayScore') + id);
	score.dom.style.fontSize = ScoreFontSize + 'px';
	
	var minus = canvas.add(0, 0, 0.25, 1, 'button');
	minus.setText('−', false, ScoreFontSize);
	minus.dom.addEventCallback('click', function() { ModifyScore(app.context.players, id, -1); });
	minus.dom.className = 'score_btn';
	
	var plus = canvas.add(0.75, 0, 0.25, 1, 'button');
	plus.setText('+', false, ScoreFontSize);
	plus.dom.addEventCallback('click', function() { ModifyScore(app.context.players, id, 1); });
	plus.dom.className = 'score_btn';
	
	ModifyScore(app.context.players, id, app.context.players[id].score, true);
}

'static'; function ModifyScore(players, id, amount, forceAssign) {
	var forceAssign = DefaultArgument(forceAssign, false);
	
	players[id].score = (forceAssign ? 0 : parseInt(players[id].score)) + amount;
	
	GetDOM(ID('DisplayScore') + id).innerHTML = players[id].score;
}

'static'; function RenderToolbar(canvas, app) {
	var opt1 = canvas.add(0, 0, 1 / 3, 1, 'button', ID('TBtnToDice'));
	var optimFontSize = GetOptimalFontSize('Nastavení', opt1.width, opt1.height);
	opt1.dom.style.fontSize = optimFontSize + 'px';
	opt1.setText('Kdo začne?');
	opt1.dom.addEventCallback('click', function() { app.toggleView('dice'); });
	
	var opt2 = canvas.add(1 / 3, 0, 1 / 3, 1, 'button');
	opt2.dom.style.fontSize = optimFontSize + 'px';
	opt2.setText('Nezdržuj');
	opt2.dom.addEventCallback('click', function() { app.toggleView('timer'); });
	
	var opt3 = canvas.add(2 / 3, 0, 1 / 3, 1, 'button', ID('TBtnToSettings'));
	opt3.dom.style.fontSize = optimFontSize + 'px';
	opt3.setText('Nastavení');
	opt3.dom.addEventCallback('click', function() { app.toggleView('settings'); });
}