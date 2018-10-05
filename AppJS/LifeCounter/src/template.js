/**
 *  \brief Cache for speeding up text-fit computations
 */
'static'; var TOOLBAR_TEMPLATE_FONT_SIZE_CACHE = {
	'score': null,
	'dice': null,
	'timer': null,
	'settings': null,
	'timer_settings': null
}

/**
 *  @brief Create button for templater
 *  
 *  @param [in] label Label written on the button
 *  @param [in] action Function callback of the button
 */
'static'; function ButtonTemplate(label, action) {
	this.label = label;
	this.action = action;
}

'static'; function RenderButtonArray(canvas, buttons, x, y, w, h, cacheID) {
	var BUTTON_WIDTH = w / buttons.length;

	if (GLOBAL_FONT_SIZE_CACHE[cacheID] == null) {
		var longestStr = '';
		for (var i = 0; i < buttons.length; i++) {
			longestStr = maxStr(longestStr, buttons[i].label);
		}

		GLOBAL_FONT_SIZE_CACHE[cacheID] = GetOptimalFontSize(
			longestStr,
			canvas.width * BUTTON_WIDTH,
			canvas.height * h
		);
	}

	for (var i = 0; i < buttons.length; i++) {
		if (buttons[i] == null) continue;
		(function(p) {
			var opt = canvas.add(x + i * BUTTON_WIDTH, y, BUTTON_WIDTH, h, 'button');
			opt.dom.addEventCallback('click', buttons[p].action);
			opt.dom.style.fontSize = GLOBAL_FONT_SIZE_CACHE[cacheID] + 'px';
			opt.setText(buttons[p].label);
		}(i));
	}
}

'static'; function RenderToolbarTemplate(parentCanvas, buttons, cacheID) {
	var canvas = parentCanvas.add(0, 1 - TEMPLATE_TOOLBAR_HEIGHT, 1, TEMPLATE_TOOLBAR_HEIGHT);
	canvas.setColor(SYSCOLOR_TOOLBAR);
	
	RenderButtonArray(canvas, buttons, 0, 0, 1, 1, cacheID);
}
'static'; function GetDrawingCanvas(core, hasHeader) {
	var HEADER_OFFSET = hasHeader ? TEMPLATE_HEADER_HEIGHT : 0;
	var result = core.add(0, HEADER_OFFSET, 1, 1 - HEADER_OFFSET - TEMPLATE_TOOLBAR_HEIGHT);
	result.setColor(SYSCOLOR_CONTENT);
	return result;
}