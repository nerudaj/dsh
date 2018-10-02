'static'; var TI_TMP_STORAGE = null;

// === TOP LEVEL ===

function RenderTimerSettings() {
	var canvas = this.app.canvas;
	TI_TMP_STORAGE = this.app.context.initCountdown;
	
	var board = canvas.add(0, 0, 1, 0.9);
	board.setColor('lightgrey');
	RenderTimerSettingsBoard(board, this.app);
	
	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.setColor('grey');
	RenderTimerSettingsToolbar(toolbar, this.app);
}

// === Second level ===

'static'; function RenderTimerSettingsBoard(canvas, app) {
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText(TEXTS.settings, true);
	header.setColor('#AAAAAA');
	
	var options = [ -10, -5, -1, null, +1, +5, +10 ];
	var yoffsets = [ 0, 0, 0, null, 7, 7, 7 ];
	var xoffsets = [ 0, 1, 2, null, 0, 1, 2 ];
	var BUTTON_HEIGHT = 0.9 / options.length;
	for (var i = 0; i < options.length; i++) {
		if (options[i] == null) continue;
		(function(p) {
			var opt = canvas.add(xoffsets[p] * 1 / 3, 0.1 + yoffsets[p] * 0.1, 1 / 3, 0.2, 'button');
			opt.setText(options[p], true);
			opt.dom.addEventCallback('click', function() { ModifyInitCountdown(app, options[p]); });
		}(i));
	}
	
	// TODO: init countdown display
	var display = canvas.add(0, 3 * 0.1, 1, 0.5,'div', ID('DisplayInitCountdown'));
	display.setText('00:00', true);
	
	ModifyInitCountdown(app, 0);
}

'static'; function RenderTimerSettingsToolbar(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 0.5;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	var labels = [ TEXTS.apply, TEXTS.back ];
	var foos = [
		function() { app.context.initCountdown = TI_TMP_STORAGE; app.toggleView('timer'); }, 
		function() { app.toggleView('timer'); }
	];
	
	for (var i = 0; i < labels.length; i++) {
		(function(p) {
		var opt = canvas.add(p * TOOLBAR_BUTTON_WIDTH, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
		opt.setText(labels[p], true);
		opt.dom.addEventCallback('click', foos[p]);
		}(i));
	}
}

// === Third level ===

'static'; function ModifyInitCountdown(app, amount) {
	TI_TMP_STORAGE += amount;
	GetDOM(ID('DisplayInitCountdown')).innerHTML = IntToTimeStr(TI_TMP_STORAGE);
}