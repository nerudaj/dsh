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
'static'; var GLOBAL_FONT_SIZE_CACHE = {};

'static'; function ClearOptimizationCache() {
	GLOBAL_FONT_SIZE_CACHE = {};
}

/**
 *  @brief Get value of cached value from \ref GLOBAL_FONT_SIZE_CACHE
 *  
 *  @param [in] canvas Parent canvas for timer display
 *  @param [in] width Width of display element within \p canvas
 *  @param [in] height Height of display element within \p canvas
 *  @param [in] label Text label used for computing cache
 *  @param [in] cacheID ID of the cache to access
 *  @param [in] hint Optional value hinting start size for heuristics
 *  @return Cache value
 *  
 *  @details If the cache is empty, new cache value is computed and stored
 */
'static'; function ReadFontSizeCache(canvas, width, height, label, cacheID, hint) {
	var hintedFontSize = DefaultArgument(hint, 100);
	
	if (GLOBAL_FONT_SIZE_CACHE[cacheID] == null) {
		GLOBAL_FONT_SIZE_CACHE[cacheID] = GetOptimalFontSize(
			label,
			canvas.width * width,
			canvas.height * height,
			hintedFontSize
		);
	}
	return GLOBAL_FONT_SIZE_CACHE[cacheID];
}