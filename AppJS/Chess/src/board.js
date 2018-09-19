function RenderBoard(app, canvas) {
	var COLORS = [ 'lightgrey', 'grey' ];
	
	var color = 0;
	for (var y = 0; y < 8; y++) {
		for (var x = 0; x < 8; x++) {
			var bit = canvas.add(x / 8, y / 8, 1 / 8, 1 / 8);
			bit.setColor(COLORS[color]);
			color = 1 - color; // Invert index
		}
		color = 1 - color;
	}
}