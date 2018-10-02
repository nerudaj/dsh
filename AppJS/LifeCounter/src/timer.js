function RenderTimer() {
	var canvas = this.app.canvas;
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText(TEXTS.countdown, true);
	header.setColor(SYSCOLOR_HEADER);
	
	var board = canvas.add(0, 0.1, 1, 0.8);
	board.setColor(SYSCOLOR_CONTENT);
	RenderTimerBoard(board, this.app);
	
	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.dom.style.border = '1px solid black';
	toolbar.setColor(SYSCOLOR_TOOLBAR);
	RenderTimerToolbar(toolbar, this.app);
}

// === TOP LEVEL ===

'static'; function RenderTimerBoard(canvas, app) {
	var context = app.context;
	
	// Reset countdown value
	context.countdown = context.initCountdown;

	var countdownDisplay = canvas.add(0, 0, 1, 0.3, 'div', ID('CountdownDisplay'));
	countdownDisplay.setText(IntToTimeStr(context.initCountdown), true);

	// Render controls
	var labels = [ TEXTS.run, TEXTS.pause, TEXTS.stop, TEXTS.restart ];
	var actions = [ 'play', 'pause', 'stop', 'restart' ];
	var count = labels.length;
	
	for (var i = 0; i < count; i++) {
		(function(p){
		var opt = canvas.add(i * (1 / count), 0.4, (1 / count), 0.2, 'button');
		opt.dom.addEventCallback('click', function() { CountdownControl(app, actions[p]); });
		opt.setText(labels[i], true);
		}(i));
	}
}

'static'; function RenderTimerToolbar(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 0.5;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	var labels = [ TEXTS.settings, TEXTS.back ];
	var foos = [
		function() { CountdownControl(app, 'stop'); app.toggleView('timer_settings'); },
		function() { app.toggleView('score') }
	];

	for (var i = 0; i < labels.length; i++) {
		var opt = canvas.add(i * TOOLBAR_BUTTON_WIDTH, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
		opt.dom.addEventCallback('click', foos[i]);
		opt.setText(labels[i], true);
	}
}

// === Second level ===

'static'; function CountdownControl(app, action) {
	var context = app.context;
	
	if (action == 'play') {
		context.cntIntHndl = setInterval(function() {
			var dom = GetDOM(ID('CountdownDisplay'));
			context.countdown--;
			dom.innerHTML = IntToTimeStr(context.countdown);
			
			if (context.countdown == 0) {
				clearInterval(context.cntIntHndl);
				dom.innerHTML = TEXTS.end;
			}
		}, 1000);
	}
	else if (action == 'pause') {
		clearInterval(context.cntIntHndl);
	}
	else if (action == 'stop') {
		clearInterval(context.cntIntHndl);
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