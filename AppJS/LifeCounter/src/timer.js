"use strict";

function RenderTimer() {
	var board = this.app.canvas.add(0, 0, 1, 0.9);
	board.setColor('lightgrey');
	RenderTimerBoard(board, this.app);
	
	var toolbar = this.app.canvas.add(0, 0.9, 1, 0.1);
	toolbar.dom.style.border = '1px solid black';
	toolbar.setColor('grey');
	RenderTimerToolbar(toolbar, this.app);
}

// ------------------

function RenderTimerBoard(canvas, app) {
	app.context.countdown = app.context.initCountdown; // Reset countdown value
	
	var header = canvas.add(0, 0, 1, 0.1);
	header.setText('Odpočet', true);
	header.setColor('#AAAAAA');
	
	var timer = canvas.add(0, 0.1, 1, 0.4, 'div', 'CountdownDisplay');
	timer.setText(IntToTime(app.context.initCountdown), true);
	
	var controls = canvas.add(0, 0.5, 1, 0.1);
	RenderTimerControls(controls, app);
	
	var notify = canvas.add(0, 0.6, 1, 0.1);
	
	var header2 = canvas.add(0, 0.7, 1, 0.1);
	header2.setText('Nastavení', true);
	header2.setColor('#AAAAAA');
	
	var settings = canvas.add(0, 0.8, 1, 0.2);
	RenderTimerSettings(settings, app);
}

function RenderTimerToolbar(canvas, app) {
	var TOOLBAR_BUTTON_WIDTH = 0.5;
	var TOOLBAR_BUTTON_HEIGHT = 1;
	
	var opt1 = canvas.add(0, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt1.dom.addEventListener('click', function() { CountdownControl(app, 'stop'); });
	opt1.setText('Nastav', true);
	
	var opt2 = canvas.add(0.5, 0, TOOLBAR_BUTTON_WIDTH, TOOLBAR_BUTTON_HEIGHT, 'button');
	opt2.dom.addEventListener('click', function() { app.toggleView('score'); });
	opt2.setText('Zpět', true);
}

// -------------------

function IntToTime(t) {
	var seconds = t % 60;
	var minutes = Math.floor(t / 60);
	return minutes + ':' + seconds;
}

function RenderTimerControls(canvas, app) {
	var btnPlay = canvas.add(0, 0, 1 / 3, 1, 'button');
	btnPlay.dom.addEventListener('click', function() { CountdownControl(app, 'play'); });
	btnPlay.setText('Spusť', true);
	
	var btnPause = canvas.add(1 / 3, 0, 1 / 3, 1, 'button');
	btnPause.dom.addEventListener('click', function() { CountdownControl(app, 'pause'); });
	btnPause.setText('Pauza', true);
	
	var btnStop = canvas.add(2 / 3, 0, 1 / 3, 1, 'button');
	btnStop.dom.addEventListener('click', function() { CountdownControl(app, 'stop'); });
	btnStop.setText('Reset', true);
}

function RenderTimerSettings(canvas, app) {
	var minus5 = canvas.add(0, 0, 0.2, 1, 'button');
	minus5.dom.addEventListener('click', function() { ModifyInitCountdown(app, -5) });
	minus5.dom.className = 'init_score_btn init_score_btn_left';
	minus5.setColor('darkred');
	minus5.setText('-5', true);
	
	var minus1 = canvas.add(0.2, 0, 0.2, 1, 'button');
	minus1.dom.addEventListener('click', function() { ModifyInitCountdown(app, -1) });
	minus1.dom.className = 'init_score_btn init_score_btn_right';
	minus1.setColor('red');
	minus1.setText('-1', true);
	
	var initcnt = canvas.add(0.4, 0, 0.2, 1, 'div', 'InitCountdownDisplay');
	initcnt.setText('XX:XX', true);
	
	var plus1 = canvas.add(0.6, 0, 0.2, 1, 'button');
	plus1.dom.addEventListener('click', function() { ModifyInitCountdown(app, 1) });
	plus1.dom.className = 'init_score_btn init_score_btn_left';
	plus1.setColor('lightgreen');
	plus1.setText('+1', true);
	
	var plus5 = canvas.add(0.8, 0, 0.2, 1, 'button');
	plus5.dom.addEventListener('click', function() { ModifyInitCountdown(app, 5); });
	plus5.dom.className = 'init_score_btn init_score_btn_right';
	plus5.setColor('green');
	plus5.setText('+5', true);
	
	ModifyInitCountdown(app, 0);
}

function CountdownControl(app, action) {
	if (action == 'play') {
		app.context.cntIntHndl = setInterval(function() {
			var dom = GetDOM('CountdownDisplay');
			app.context.countdown--;
			dom.innerHTML = IntToTime(app.context.countdown);
			
			if (app.context.countdown == 0) {
				clearInterval(app.context.cntIntHndl);
				dom.innerHTML = 'KONEC!';
			}
		}, 1000);
	}
	else if (action == 'pause') {
		clearInterval(app.context.cntIntHndl);
	}
	else if (action == 'stop') {
		clearInterval(app.context.cntIntHndl);
		app.context.countdown = app.context.initCountdown;
		GetDOM('CountdownDisplay').innerHTML = IntToTime(app.context.countdown);
	}
	else {
		LogError('Timer', 'CountdownControl', 'Invalid action name: ' + action);
	}
}

// --------------------

function ModifyInitCountdown(app, amount) {
	app.context.initCountdown = parseInt(app.context.initCountdown) + parseInt(amount);
	
	GetDOM('InitCountdownDisplay').innerHTML = IntToTime(app.context.initCountdown);
}