'static'; function RenderTimer() {
	var canvas = this.app.canvas;
	
	RenderViewHeaderTemplate(canvas, TEXTS.countdown);
	
	var board = GetDrawingCanvas(canvas);
	RenderTimerBoard(board, this.app);
	
	// Render toolbar
	var buttons = [
		new ButtonTemplate(TEXTS.settings, function() {
			CountdownControl(app, 'stop');
			app.toggleView('timer_settings');
		}),
		new ButtonTemplate(TEXTS.back, function() {
			CountdownControl(app, 'stop');
			app.toggleView('score');
		})
	];
	RenderToolbarTemplate(canvas, buttons, ID('timer'));
}

// === TOP LEVEL ===
'static'; function RenderTimerBoard(canvas, app) {
	var context = app.context;
	var DISPLAY_WIDTH = 1;
	var DISPLAY_HEIGHT = 0.4;
	
	// Reset countdown value
	context.countdown = context.initCountdown;

	var DISPLAY_FONT_SIZE = ReadFontSizeCache(canvas, DISPLAY_WIDTH, DISPLAY_HEIGHT, 'XX:XX', ID('timer_display'), 250);
	
	var countdownDisplay = canvas.add(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 'div', ID('CountdownDisplay'));
	countdownDisplay.dom.style.fontSize = DISPLAY_FONT_SIZE + 'px';
	countdownDisplay.setText(IntToTimeStr(context.initCountdown));

	// Render controls
	var buttons = [
		new ButtonTemplate(TEXTS.play, function() {
			CountdownControl(app, 'play');
		}),
		new ButtonTemplate(TEXTS.pause, function() {
			CountdownControl(app, 'pause');
		}),
		new ButtonTemplate(TEXTS.stop, function() {
			CountdownControl(app, 'stop');
		}),
		new ButtonTemplate(TEXTS.restart, function() {
			CountdownControl(app, 'restart');
		})
	];
	RenderButtonArray(canvas, buttons, 0, 0.4, 1, 0.1, ID('timer_buttons'));
}

// === Second level ===

'static'; function CountdownControl(app, action) {
	var context = app.context;
	
	if (action == 'play') {
		if (context.cntIntHndl != null) return;
		context.cntIntHndl = setInterval(function() {
			var dom = GetDOM(ID('CountdownDisplay'));
			context.countdown--;
			dom.innerHTML = IntToTimeStr(context.countdown);
			
			if (context.countdown == 0) {
				context.cntIntHndl = ReallyClearInterval(context.cntIntHndl);
				dom.innerHTML = TEXTS.end;
			}
		}, 1000);
	}
	else if (action == 'pause') {
		context.cntIntHndl = ReallyClearInterval(context.cntIntHndl);
	}
	else if (action == 'stop') {
		context.cntIntHndl = ReallyClearInterval(context.cntIntHndl);
		context.countdown = context.initCountdown;
		GetDOM(ID('CountdownDisplay')).innerHTML = IntToTimeStr(context.countdown);
	}
	else if (action == 'restart') {
		CountdownControl(app, 'stop');
		CountdownControl(app, 'play');
	}
	else {
		LogError('Timer', 'CountdownControl', 'Invalid action name: ' + action);
	}
}