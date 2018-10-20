function ResetGame(app) {
	var ctx = app.context;
	ctx.pending = null;
	ctx.board = [
		['b-rook', 'b-knight', 'b-bishop', 'b-queen', 'b-king',  'b-bishop', 'b-knight', 'b-rook'],
		['b-pawn', 'b-pawn',   'b-pawn',   'b-pawn',  'b-pawn',  'b-pawn',   'b-pawn',   'b-pawn' ],
		[null,     null,        null,      null,      null,      null,       null,       null ],
		[null,     null,        null,      null,      null,      null,       null,       null ],
		[null,     null,        null,      null,      null,      null,       null,       null ],
		[null,     null,        null,      null,      null,      null,       null,       null ],
		['w-pawn', 'w-pawn',   'w-pawn',   'w-pawn',  'w-pawn',  'w-pawn',   'w-pawn',   'w-pawn' ],
		['w-rook', 'w-knight', 'w-bishop', 'w-king',  'w-queen', 'w-bishop', 'w-knight', 'w-rook']
	];
	ctx.turn = 'w';
	ctx.removed = { // Which pieces got removed
		'w': [],
		'b': []
	};
}

function RenderGame() {
	var w = this.app.canvas.width;
	var h = this.app.canvas.height;

	var board;
	if (w < h) {
		board = this.app.canvas.add(0, 0, 1, w / h);
	}
	else {
		board = this.app.canvas.add(0, 0, h / w, 1);
	}

	RenderBoard(this.app, board);
	RenderPieces(this.app);
	
	// TODO: Render status bar (toolbar)
}

// ------------------------

function FieldID(x, y) {
	return 'Field' + x + '_' + y;
}

function RenderBoard(app, canvas) {
	var COLORS = [ 'lightgrey', 'grey' ];
	var fontSize = null;
	
	var color = 0;
	for (var y = 0; y < 8; y++) {
		for (var x = 0; x < 8; x++) {
			(function() { // Start of closure
			var bit = canvas.add(x / 8, y / 8, 1 / 8, 1 / 8, 'button', FieldID(x, y));
			
			if (fontSize == null) {
				fontSize = GetOptimalFontSize('#', bit.width, bit.height);
			}
			
			var ix = x; // Must copy value for closure to take effect
			var iy = y;
			
			bit.dom.style.fontSize = fontSize + 'px';
			bit.dom.addEventListener('click', function() { FieldClicked(app, ix, iy); });
			bit.setColor(COLORS[color]);
			color = 1 - color; // Invert index
			}()); // Closure
		}
		color = 1 - color;
	}
}

function RenderPieces(app) {
	for (var y = 0; y < 8; y++) {
		for (var x = 0; x < 8; x++) {
			if (app.context.board[y][x] == null) {
				GetDOM(FieldID(x, y)).innerHTML = '';
			}
			else {
				GetDOM(FieldID(x, y)).innerHTML = PIECES[app.context.board[y][x]];
			}
		}
	}
}

function FieldClicked(app, x, y) {
	var ctx = app.context;
	var invert = InvertColor(ctx.turn);
	
	if (IsMyPiece(app, x, y)) { // No piece is waiting to be moved
		if (ctx.pending != null) {
			GetDOM(FieldID(ctx.pending[0], ctx.pending[1])).style.color = 'black';
		}

		ctx.pending = [x, y]; // Mark piece as pending
		GetDOM(FieldID(x, y)).style.color = 'red';
	}
	else if (ctx.pending != null) {
		var px = ctx.pending[0];
		var py = ctx.pending[1];

		if (IsValidMove(app, x, y)) {
			// If destination is not empty
			if (ctx.board[y][x] != null) {
				// Test if it is a king
				var test = invert + '-king';
				if (ctx.board[y][x] == test) {
					alert(ctx.turn + ' WINS!');
				}
				
				// Add removed piece to database of removed
				ctx.removed[invert].push(ctx.board[y][x]);
			}
			
			// Move piece
			ctx.board[y][x] = ctx.board[py][px];
			ctx.board[py][px] = null;
			ctx.pending = null;
			
			// Move performed, swap active player
			ctx.turn = invert;
			
			GetDOM(FieldID(px, py)).style.color = 'black';
		}
	}
	
	RenderPieces(app);
}

// -------------------

function IsMyPiece(app, x, y) {
	var ctx = app.context;
	
	if (ctx.board[y][x] == null) return false;
	
	return ctx.board[y][x][0] == ctx.turn; // Test first letter of piece name. It is either 'b' - black or 'w' - white. Turn is a single letter with one of these two values
}

function IsValidDestination(app, x, y) {
	var ctx = app.context;
	return ctx.board[y][x] == null || ctx.board[y][x][0] != ctx.turn;
}

function IsValidMove(app, x, y) {
	if (!IsValidDestination) return false;
	
	var ctx = app.context;
	
	// Read position of piece
	var px = ctx.pending[0];
	var py = ctx.pending[1];
	
	var pieceType = ctx.board[py][px].substring(2);
	var color = ctx.board[py][px][0];
	
	var dx = Math.abs(x - px);
	var dy = Math.abs(y - py);
	
	switch (pieceType) {
	case 'pawn':
		// Ban incorrect direction
		if (color == 'w' && y - py > 0) return false;
		if (color == 'b' && y - py < 0) return false;
	
		// Allow start jump
		if (color == 'w' && py == 6 && dx == 0) return true;
		if (color == 'b' && py == 1 && dx == 0) return true;
		
		// Allow takeout jump
		if (dx == 1 && dy == 1 && ctx.board[y][x] != null) return true;
		
		// Allow going forward by one
		if (dx == 0 && dy == 1 && ctx.board[y][x] == null) return true;
		
		return false;

	case 'rook':
		return dx == 0 || dy == 0; // Is horizontal/vertical move

	case 'knight':
		return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);

	case 'bishop':
		return dx == dy; // Is diagonal move

	case 'queen':
		// Can move diagonally
		if (dx == dy) return true;

		// Can move horizontally
		return dx == 0 || dy == 0;

	case 'king':
		return dx <= 1 && dy <= 1;
	}

	LogError('Chess', 'IsValidMove', pieceType + ' is an unknown piece type.');
}

function InvertColor(c) {
	if (c == 'w') return 'b';
	return 'w';
}