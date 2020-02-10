function ByteStreamIn() {
    this.data = null;
}

ByteStreamIn.prototype.FetchDataSynchronous = function (url) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, false);
    xhr.responseType = 'arraybuffer';

    xhr.send(null);

    if (request.status !== 200) {
        throw "Could not fetch the data";
    }

    return new Uint8Array(this.response);
}

ByteStreamIn.prototype.GetByte = function() {
    return data.shift();
}

/*ByteStreamIn.prototype.GetDoubleByte = function() {
    // TODO: Slice and convert
    return 256 * this.GetByte() + this.GetByte();
}

ByteStreamIn.prototype.GetQuadByte = function() {
    // TODO: Slice and convert
    var sum = 0;
    var exp = 256 * 256 * 256;

    for (let i = 0; i < 4; i++) {
        sum += exp * this.GetByte();
        exp /= 256;
    }

    return sum;
}

ByteStreamIn.prototype.GetString = function() {
    var result = "";
    var length = this.GetByte();

    // TODO: slice and convert
    for (let i = 0; i < length; i++) {
        result += this.GetByte();
    }
}

ByteStreamIn.prototype.GetDoubleByteVector = function() {
    // TODO: slice and convert
}*/

function LevelMetadata() {
    this.time = 0;
    this.id = "";
    this.name = "";
    this.author = "";
    this.description = "";
}

function LevelMesh() {
    this.tileWidth = 0;
    this.tileHeight = 0;
    this.width = 0;
    this.height = 0;
    this.tiles = [];
    this.blocks = [];
}

function LevelD() {
    this.metadata = new LevelMetadata();
    this.mesh = new LevelMesh();
}

LevelD.prototype.loadFromFile = function(filename) {
    var data = FetchDataSynchronous(filename);
}