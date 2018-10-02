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

'static'; var SYSCOLOR_HEADER = '#AAAAAA';
'static'; var SYSCOLOR_CONTENT = 'lightgrey';
'static'; var SYSCOLOR_TOOLBAR = 'grey';
