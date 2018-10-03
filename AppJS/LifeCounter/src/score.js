'static'; var ScoreFontSize = null;

function RenderScore() {
	var canvas = this.app.canvas;
	
	var ScoreFontSize = null; // App might be resized, reset font size
	var board = canvas.add(0, 0, 1, 0.9);
	RenderBoard(board, this.app);
	
	//RenderToolbar(toolbar, this.app);
	var buttons = [
		new ToolbarButton(TEXTS.whoStarts, function() { app.toggleView('dice'); }),
		new ToolbarButton(TEXTS.timer, function() { app.toggleView('timer'); }),
		new ToolbarButton(TEXTS.settings, function() { app.toggleView('settings'); })
	];
	RenderToolbarTemplate(canvas, buttons, 'score');
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