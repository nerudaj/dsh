function ByteStreamIn(inputData = null, inputIsString = false) {
    this.data = inputData;
    if (inputIsString) this.data = new TextEncoder().encode(inputData);

    this.index = 0;
}

ByteStreamIn.prototype.GetByte = function() {
    return this.data[this.index++];
}

ByteStreamIn.prototype.GetDoubleByte = function() {
    return 256 * this.GetByte() + this.GetByte();
}

ByteStreamIn.prototype.GetQuadByte = function() {
    return this.GetDoubleByte() * 256 * 256 + this.GetDoubleByte();
}

ByteStreamIn.prototype.GetString = function() {
    var length = this.GetByte();
    var rawStr = this.data.slice(this.index, this.index + length);
    this.index += length;
    return new TextDecoder("utf-8").decode(rawStr);
}

ByteStreamIn.prototype.GetDoubleByteVector = function() {
    var length = this.GetQuadByte();
    var result = [];

    for (let i = 0; i < length; i++) {
        result.push(this.GetDoubleByte());
    }

    return result;
}

function ByteStreamOut() {
    this.data = new Uint8Array(256);
    this.usedSize = 0;
}

ByteStreamOut.prototype.WriteByte = function(data) {
    this.data[this.usedSize] = data;
    this.usedSize++;
}

ByteStreamOut.prototype.WriteDoubleByte = function(data) {
    this.WriteByte(parseInt(data / 256));
    this.WriteByte(data % 256);
}

ByteStreamOut.prototype.WriteQuadByte = function(data) {
    let upper = parseInt(data / (256 * 256));
    let lower = parseInt(data % (256 * 256));

    this.WriteDoubleByte(upper);
    this.WriteDoubleByte(lower);
}

ByteStreamOut.prototype.WriteString = function(data) {
    if (data.length > 255) throw new Error("String is too long");

    this.WriteByte(data.length);

    for (let i = 0; i < data.length; i++) {
        this.WriteByte(data.charCodeAt(i));
    }
}

ByteStreamOut.prototype.WriteDoubleByteVector = function(data) {
    this.WriteQuadByte(data.length);

    for (let i = 0; i < data.length; i++) {
        this.WriteDoubleByte(data[i]);
    }
}

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