'static'; var TI_TMP_STORAGE = null;

// === TOP LEVEL ===

function RenderTimerSettings() {
	var canvas = this.app.canvas;
	TI_TMP_STORAGE = this.app.context.initCountdown;
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setColor(SYSCOLOR_HEADER);
	header.setText(TEXTS.settings, true);
	
	var board = canvas.add(0, 0.1, 1, 0.8);
	board.setColor('lightgrey');
	RenderTimerSettingsBoard(board, this.app);
	
	// Render toolbar
	var buttons = [
		new ButtonTemplate(TEXTS.apply, function() {
			app.context.initCountdown = TI_TMP_STORAGE; // Apply modifications to initCountdown
			app.toggleView('timer');
		}),
		new ButtonTemplate(TEXTS.back, function() {
			app.toggleView('timer');
		})
	];
	RenderToolbarTemplate(canvas, buttons, 'timer_settings');
}

// === Second level ===

'static'; function RenderTimerSettingsBoard(canvas, app) {
	// Display constants
	var DISPLAY_WIDTH = 1;
	var DISPLAY_HEIGHT = 0.4;
	
	// Refresh cache
	recomputeTimerDisplayCache(canvas, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	
	// Draw display
	var display = canvas.add(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 'div', ID('DisplayInitCountdown'));
	display.dom.style.fontSize = SYS_TIMER_DISPLAY_FONT_SIZE + 'px';
	display.setText('00:00');
	
	// Button constants
	var options = [ -10, -5, -1, 1, 5, 10 ];
	var OPTION_WIDTH = 1 / options.length;
	var OPTION_HEIGHT = 0.1;
	
	// Refresh cache
	if (SYS_TIMER_SETTINGS_BUTTON_FONT_SIZE == null) {
		SYS_TIMER_SETTINGS_BUTTON_FONT_SIZE = GetOptimalFontSize(
			'XX',
			canvas.width * OPTION_WIDTH,
			canvas.height * OPTION_HEIGHT
		);
	}
	
	// Draw buttons
	for (var i = 0; i < options.length; i++) {
		(function(p) {
			var opt = canvas.add(i * OPTION_WIDTH, DISPLAY_HEIGHT, OPTION_WIDTH, OPTION_HEIGHT, 'button');
			opt.dom.addEventCallback('click', function() {
				ModifyInitCountdown(app, options[p]);
			});
			opt.dom.style.fontSize = SYS_TIMER_SETTINGS_BUTTON_FONT_SIZE + 'px';
			opt.setText(options[p]);
		}(i));
	}
	
	// Initialize display
	ModifyInitCountdown(app, 0);
}

// === Third level ===

'static'; function ModifyInitCountdown(app, amount) {
	TI_TMP_STORAGE += amount;
	GetDOM(ID('DisplayInitCountdown')).innerHTML = IntToTimeStr(TI_TMP_STORAGE);
}