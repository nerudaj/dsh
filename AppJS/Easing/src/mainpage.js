'static'; function IsWidescreen(canvas) {
	return canvas.width > canvas.height;
}

'static'; function RenderMainPage() {
	var canvas = this.app.canvas;
	
	var board = GetDrawingTemplate(canvas, false); // No header
	
	if (IsWidescreen(board)) {
		RenderPortraitscreenSetup(this.app, board);
	}
	else {
		RenderPortraitscreenSetup(this.app, board);
	}
	
	var buttons = [
		new ButtonTemplate('Apply', function() {}),
		new ButtonTemplate('Hints', function() { app.toggleView('hints'); })
	];
	RenderToolbarTemplate(canvas, buttons, ID('toolbar_button_cache'));
}

'static'; function RenderWidescreenSetup(app, canvas) {
	
}

'static'; function RenderPortraitscreenSetup(app, canvas) {
	
}
