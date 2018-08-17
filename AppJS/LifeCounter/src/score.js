var SCORE_FONT_SIZE = null;

function RenderScore() {
	var SCORE_FONT_SIZE = null; // App might be resized, reset font size
	var board = this.app.canvas.add(0, 0, 1, 0.9);
	RenderBoard(board, this.app);
	
	var toolbar = this.app.canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	RenderToolbar(toolbar, this.app);
}

function RenderBoard(canvas, app) {
	var players_length = app.context.players.length;
	
	var COL_COUNT = players_length == 2 ? 1 : 2;
	var ROW_COUNT = Math.ceil(players_length / COL_COUNT);
	
	var ITEM_WIDTH = 1 / COL_COUNT;
	var ITEM_HEIGHT = 1 / ROW_COUNT;
	
	var pid = 0;
	for (var y = 0; y < ROW_COUNT; y++) {
		for (var x = 0; x < COL_COUNT; x++) {
			if (players_length % 2 == 1 && pid + 1 == players_length) {
				ITEM_WIDTH = 1;
			}
			
			var display = canvas.add(x * ITEM_WIDTH, y * ITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT);
			display.setColor(app.context.players[pid].color);
			RenderDisplay(pid, display, app);
			
			pid++;
			if (players_length == pid) return;
		}
	}
}

function RenderDisplay(id, canvas, app) {
	if (SCORE_FONT_SIZE == null) {
		SCORE_FONT_SIZE = GetOptimalFontSize('XX', canvas.width * 0.25, canvas.height);
	}
	
	var score = canvas.add(0.25, 0, 0.5, 1, 'div', 'DisplayScore' + id);
	score.dom.style.fontSize = SCORE_FONT_SIZE + "px";
	
	var minus = canvas.add(0, 0, 0.25, 1, 'button');
	minus.setText('−', false, SCORE_FONT_SIZE);
	minus.dom.addEventListener('click', function() { ModifyScore(app.context.players, id, -1); });
	minus.dom.className = 'score_btn';
	
	var plus = canvas.add(0.75, 0, 0.25, 1, 'button');
	plus.setText('+', false, SCORE_FONT_SIZE);
	plus.dom.addEventListener('click', function() { ModifyScore(app.context.players, id, 1); });
	plus.dom.className = 'score_btn';
	
	ModifyScore(app.context.players, id, app.context.players[id].score, true);
}

function ModifyScore(players, id, amount, forceAssign) {
	var forceAssign = DefaultArgument(forceAssign, false);
	
	players[id].score = (forceAssign ? 0 : parseInt(players[id].score)) + amount;
	
	GetDOM('DisplayScore' + id).innerHTML = players[id].score;
}

function RenderToolbar(canvas, app) {
	var opt1 = canvas.add(0.05, 0.05, 0.425, 0.9, 'button', 'TBtnToDice');
	opt1.setText('Kdo začne?', true);
	opt1.dom.addEventListener('click', function() { app.toggleView('dice'); });
	
	var opt2 = canvas.add(0.525, 0.05, 0.425, 0.9, 'button', 'TBtnToSettings');
	opt2.setText('Nastavení', true);
	opt2.dom.addEventListener('click', function() { app.toggleView('settings'); });
}