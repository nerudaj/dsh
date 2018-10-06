/**
 *  @brief Constructor of player data storage
 *  
 *  @return Player object
 */
'static'; function ClassPlayer() {
	this.score = 0;
	this.subscore = 0;
	this.color = "red";
}

/**
 *  @brief Convert integer time in seconds to string MM:SS reprezentation
 *  
 *  @param [in] t Time in seconds
 *  @return String in format MM:SS
 */
'static'; function IntToTimeStr(t) {
	var seconds = '0' + String(t % 60);
	var minutes = '0' + String(Math.floor(t / 60));
	return minutes.slice(-2) + ':' + seconds.slice(-2);
}

/**
 *  @brief Return longest of two strings
 *  
 *  @param [in] str1 First string
 *  @param [in] str2 Second string
 *  @return Longer of both strings
 */
'static'; function maxStr(str1, str2) {
	if (str1.length > str2.length) return str1;
	return str2;
}

/**
 *  @brief Clear interval and return NULL as a new value for handle
 *  
 *  @param [in] handle Interval ID handle
 *  @return NULL
 */
'static'; function ReallyClearInterval(handle) {
	clearInterval(handle);
	return null;
}

/////////////////////////
// Optimization values //
/////////////////////////
/**
 *  \brief Cache for speeding up text-fit computations
 */
'static'; var GLOBAL_FONT_SIZE_CACHE = {}

'static'; var SYS_SCORE_DISPLAY_FONT_SIZE = null; // todo: use score display optim
'static'; var SYS_DICE_DISPLAY_FONT_SIZE = null; // used
'static'; var SYS_SETTINGS_TEXT_FONT_SIZE = null; // used
'static'; var SYS_SETTINGS_BUTTON_FONT_SIZE = null; // used
'static'; var SYS_TIMER_BUTTON_FONT_SIZE = null; // used
'static'; var SYS_TIMER_DISPLAY_FONT_SIZE = null; // used
'static'; var SYS_TIMER_SETTINGS_BUTTON_FONT_SIZE = null; // todo: use timer settings toolbar optim
'static'; var SYS_TIMER_SETTINGS_TOOLBAR_FONT_SIZE = null; // todo: use timer settings toolbar optim

'static'; function clearOptimizationCache() {
	SYS_SCORE_DISPLAY_FONT_SIZE = null;
	SYS_DICE_DISPLAY_FONT_SIZE = null;
	SYS_SETTINGS_TEXT_FONT_SIZE = null;;
	SYS_SETTINGS_BUTTON_FONT_SIZE = null;
	SYS_TIMER_BUTTON_FONT_SIZE = null;
	SYS_TIMER_DISPLAY_FONT_SIZE = null;
	SYS_TIMER_SETTINGS_BUTTON_FONT_SIZE = null;
	GLOBAL_FONT_SIZE_CACHE = {};
}

'static'; function recomputeTimerDisplayCache(canvas, width, height) {
	if (SYS_TIMER_DISPLAY_FONT_SIZE == null) {
		SYS_TIMER_DISPLAY_FONT_SIZE = GetOptimalFontSize(
			'XX:XX',
			canvas.width * width,
			canvas.height * height,
			250
		);
	}
}