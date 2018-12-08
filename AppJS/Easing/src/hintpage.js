'static'; function RenderHintPage() {
	var canvas = this.app.canvas;
	
	RenderHeaderTemplate(canvas, "Hints");
	
	var board = GetDrawingTemplate(canvas);
	board.setText('TODO: hints');
	
	var buttons = [
		new ButtonTemplate('Back', function() {
			app.toggleView('mainpage');
		})
	];
	RenderToolbarTemplate(canvas, buttons, ID('toolbar_button_cache'));
}