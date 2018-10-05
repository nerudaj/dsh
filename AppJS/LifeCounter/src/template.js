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

'static'; function RenderToolbarTemplate(parentCanvas, buttons, cacheID) {
	var canvas = parentCanvas.add(0, 0.9, 1, 0.1);
	canvas.setColor(SYSCOLOR_TOOLBAR);
	
	var BUTTON_WIDTH = 1 / buttons.length;
	
	if (TOOLBAR_TEMPLATE_FONT_SIZE_CACHE[cacheID] == null) {
		var longestStr = '';
		for (var i = 0; i < buttons.length; i++) {
			longestStr = maxStr(longestStr, buttons[i].label);
		}
		
		TOOLBAR_TEMPLATE_FONT_SIZE_CACHE[cacheID] = GetOptimalFontSize(
			longestStr,
			canvas.width * BUTTON_WIDTH,
			canvas.height
		);
	}
	
	for (var i = 0; i < buttons.length; i++) {
		(function(p) {
			var opt = canvas.add(i * BUTTON_WIDTH, 0, BUTTON_WIDTH, 1, 'button');
			opt.dom.addEventCallback('click', buttons[p].action);
			opt.dom.style.fontSize = TOOLBAR_TEMPLATE_FONT_SIZE_CACHE[cacheID] + 'px';
			opt.setText(buttons[p].label);
		}(i));
	}
}

'static'; function GetDrawingCanvas(core, hasHeader) {
	var HEADER_OFFSET = hasHeader ? TEMPLATE_HEADER_HEIGHT : 0;
	var result = core.add(0, HEADER_OFFSET, 1, 1 - HEADER_OFFSET - TEMPLATE_TOOLBAR_HEIGHT);
	result.setColor(SYSCOLOR_CONTENT);
	return result;
}