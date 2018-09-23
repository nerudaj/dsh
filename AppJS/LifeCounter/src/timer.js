function RenderTimer() {
	var canvas = this.app.canvas;
	
	var board = canvas.add(0, 0, 1, 0.9);
	board.setColor('lightgrey');
	RenderTimerBoard(board, this.app);
	
	var toolbar = canvas.add(0, 0.9, 1, 0.1);
	toolbar.dom.style.border = '1px solid black';
	toolbar.setColor('grey');
	RenderTimerToolbar(toolbar, this.app);
}

// ------------------

'static'; function RenderTimerBoard(canvas, app) {
	var context = app.context;
	
	context.countdown = context.initCountdown; // Reset countdown value
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText('Odpočet', true);
	header.setColor('#AAAAAA');
	
	var timer = canvas.add(0, 0.1, 1, 0.4, 'div', ID('CountdownDisplay'));
	timer.setText(IntToTime(context.initCountdown), true);
	
	var controls = canvas.add(0, 0.5, 1, 0.1);
	RenderTimerControls(controls, app);
	
	var notify = canvas.add(0, 0.6, 1, 0.1);
	
	var header2 = canvas.add(0, 0.7, 1, 0.1);
	header2.setText('Nastavení', true);
	header2.setColor('#AAAAAA');
	
	var settings = canvas.add(0, 0.8, 1, 0.2);
	RenderTimerSettings(settings, app);
}

'static'; function RenderTimerToolbar(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 0.5;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	var opt1 = canvas.add(0, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt1.dom.addEventCallback('click', function() { CountdownControl(app, 'stop'); });
	opt1.setText('Nastav', true);
	
	var opt2 = canvas.add(0.5, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt2.dom.addEventCallback('click', function() { app.toggleView('score'); });
	opt2.setText('Zpět', true);
}

// -------------------

'static'; function IntToTime(t) {
	var seconds = t % 60;
	var minutes = Math.floor(t / 60);
	return minutes + ':' + seconds;
}

'static'; function RenderTimerControls(canvas, app) {
	var labels = [
		['Spusť', 'play'], ['Pauza', 'pause'], ['Reset', 'stop']
	];
	var frac = 1 / labels.length;
	
	for (var i = 0; i < labels.length; i++) {
		(function() { // Closure for new lexical scope
			var p = i;
			var btn = canvas.add(p * frac, 0, frac, 1, 'button');
			btn.dom.addEventCallback('click', function() { CountdownControl(app, labels[p][1]); });
			btn.setText(labels[p][0], true);
		}());
	}
}

'static'; function RenderTimerSettings(canvas, app) {
	var minus5 = canvas.add(0, 0, 0.2, 1, 'button');
	minus5.dom.addEventCallback('click', function() { ModifyInitCountdown(app, -5) });
	minus5.dom.className = LEFT_BTN_CLASS;
	minus5.setColor('darkred');
	minus5.setText('-5', true);
	
	var minus1 = canvas.add(0.2, 0, 0.2, 1, 'button');
	minus1.dom.addEventCallback('click', function() { ModifyInitCountdown(app, -1) });
	minus1.dom.className = RIGHT_BTN_CLASS;
	minus1.setColor('red');
	minus1.setText('-1', true);
	
	var initcnt = canvas.add(0.4, 0, 0.2, 1, 'div', ID('InitCountdownDisplay'));
	initcnt.setText('XX:XX', true);
	
	var plus1 = canvas.add(0.6, 0, 0.2, 1, 'button');
	plus1.dom.addEventCallback('click', function() { ModifyInitCountdown(app, 1) });
	plus1.dom.className = LEFT_BTN_CLASS;
	plus1.setColor('lightgreen');
	plus1.setText('+1', true);
	
	var plus5 = canvas.add(0.8, 0, 0.2, 1, 'button');
	plus5.dom.addEventCallback('click', function() { ModifyInitCountdown(app, 5); });
	plus5.dom.className = RIGHT_BTN_CLASS;
	plus5.setColor('green');
	plus5.setText('+5', true);
	
	ModifyInitCountdown(app, 0);
}

'static'; function CountdownControl(app, action) {
	var context = app.context;
	
	if (action == 'play') {
		context.cntIntHndl = setInterval(function() {
			var dom = GetDOM(ID('CountdownDisplay'));
			context.countdown--;
			dom.innerHTML = IntToTime(context.countdown);
			
			if (context.countdown == 0) {
				clearInterval(context.cntIntHndl);
				dom.innerHTML = 'KONEC!';
			}
		}, 1000);
	}
	else if (action == 'pause') {
		clearInterval(context.cntIntHndl);
	}
	else if (action == 'stop') {
		clearInterval(context.cntIntHndl);
		context.countdown = context.initCountdown;
		GetDOM(ID('CountdownDisplay')).innerHTML = IntToTime(context.countdown);
	}
	else {
		LogError('Timer', 'CountdownControl', 'Invalid action name: ' + action);
	}
}

// --------------------

'static'; function ModifyInitCountdown(app, amount) {
	var context = app.context;
	
	context.initCountdown = parseInt(context.initCountdown) + parseInt(amount);
	
	GetDOM(ID('InitCountdownDisplay')).innerHTML = IntToTime(context.initCountdown);
}