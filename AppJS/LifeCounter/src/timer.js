'static'; function RenderTimer() {
	var canvas = this.app.canvas;
	
	RenderViewHeaderTemplate(canvas, TEXTS.countdown);
	
	var board = GetDrawingCanvas(canvas, true);
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
	RenderToolbarTemplate(canvas, buttons, 'timer');
}

// === TOP LEVEL ===
'static'; function RenderTimerBoard(canvas, app) {
	var context = app.context;
	var DISPLAY_WIDTH = 1;
	var DISPLAY_HEIGHT = 0.4;
	
	// Reset countdown value
	context.countdown = context.initCountdown;

	recomputeTimerDisplayCache(canvas, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	
	var countdownDisplay = canvas.add(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 'div', ID('CountdownDisplay'));
	countdownDisplay.dom.style.fontSize = SYS_TIMER_DISPLAY_FONT_SIZE + 'px';
	countdownDisplay.setText(IntToTimeStr(context.initCountdown));

	// Render controls
	var BUTTON_WIDTH = 0.25;
	var BUTTON_HEIGHT = 0.1;
	
	var labels = [ TEXTS.run, TEXTS.pause, TEXTS.stop, TEXTS.restart ];
	var actions = [ 'play', 'pause', 'stop', 'restart' ];
	
	if (SYS_TIMER_BUTTON_FONT_SIZE == null) {
		SYS_TIMER_BUTTON_FONT_SIZE = GetOptimalFontSize(
			maxStr(maxStr(labels[0], labels[1]), maxStr(labels[2], labels[3])),
			canvas.width * BUTTON_WIDTH,
			canvas.height * BUTTON_HEIGHT
		);
	}
	
	for (var i = 0; i < labels.length; i++) {
		(function(p){
		var opt = canvas.add(i * BUTTON_WIDTH, 0.4, BUTTON_WIDTH, BUTTON_HEIGHT, 'button');
		opt.dom.addEventCallback('click', function() { CountdownControl(app, actions[p]); });
		opt.dom.style.fontSize = SYS_TIMER_BUTTON_FONT_SIZE + 'px';
		opt.setText(labels[i]);
		}(i));
	}
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