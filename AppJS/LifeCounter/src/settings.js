'static'; var MinPlayers = 2;
'static'; var MaxPlayers = 6;
var Colors = [ 'red', 'lightgreen', 'lightblue', 'yellow', 'pink', 'orange', 'grey', 'white' ];
'static'; var LEFT_BTN_CLASS = 'init_score_btn init_score_btn_left';
'static'; var RIGHT_BTN_CLASS = 'init_score_btn init_score_btn_right';

'static'; function RenderSettings() {
	var canvas = this.app.canvas;
	
	// Render header
	RenderHeaderTemplate(canvas, TEXTS.settings);
	
	// Render main
	var board = GetDrawingTemplate(canvas);
	// Render
	
	// Render toolbar
	var buttons = [
		new ButtonTemplate(TEXTS.apply, function() {
			ApplySettings(app);
			app.toggleView('score');
		}),
		new ButtonTemplate(TEXTS.back, function() {
			app.toggleView('score');
		})
	];
	RenderToolbarTemplate(canvas, buttons, ID('CacheSettingsToolbar'));
}

// *** TOP level ***

'static'; function ApplySettings(app) {
	
}