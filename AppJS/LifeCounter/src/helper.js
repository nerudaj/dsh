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

'static'; function maxStr(str1, str2) {
	if (str1.length > str2.length) return str1;
	return str2;
}

'static'; var SYSCOLOR_HEADER = '#AAAAAA';
'static'; var SYSCOLOR_CONTENT = 'lightgrey';
'static'; var SYSCOLOR_TOOLBAR = 'grey';

// Optimization values
'static'; var SYS_SCORE_TOOLBAR_FONT_SIZE = null; // used
'static'; var SYS_SCORE_DISPLAY_FONT_SIZE = null; // todo: use score display optim
'static'; var SYS_DICE_TOOLBAR_FONT_SIZE = null; // used
'static'; var SYS_DICE_DISPLAY_FONT_SIZE = null; // used
'static'; var SYS_SETTINGS_TOOLBAR_FONT_SIZE = null; // todo: use settings toolbar optim
'static'; var SYS_TIMER_TOOLBAR_FONT_SIZE = null; // todo: use timer toolbar optim
'static'; var SYS_TIMER_SETTINGS_TOOLBAR_FONT_SIZE = null; // todo: use timer settings toolbar optim

'static'; function clearOptimizationCache() {
	SYS_SCORE_TOOLBAR_FONT_SIZE = null;
	SYS_SCORE_DISPLAY_FONT_SIZE = null;
	SYS_DICE_TOOLBAR_FONT_SIZE = null;
	SYS_DICE_DISPLAY_FONT_SIZE = null;
	SYS_SETTINGS_TOOLBAR_FONT_SIZE = null;
	SYS_TIMER_TOOLBAR_FONT_SIZE = null;
	SYS_TIMER_SETTINGS_TOOLBAR_FONT_SIZE = null;
}