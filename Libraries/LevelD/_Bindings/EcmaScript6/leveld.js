function ByteStreamIn(inputData = null, inputIsString = false) {
    this.data = inputData;
    if (inputIsString) this.data = new TextEncoder().encode(inputData);

    this.index = 0;
}

ByteStreamIn.prototype.MakeRequest = function(url) {
    return new Promise(function (resolve, reject) {
        let xhr = new XMLHttpRequest();
        xhr.open("GET", url);
        xhr.onload = function () {
            if (this.status >= 200 && this.status < 300) {
                resolve(xhr.response);
            } else {
                reject({
                    status: this.status,
                    statusText: xhr.statusText
                });
            }
        };
        xhr.onerror = function () {
            reject({
                status: this.status,
                statusText: xhr.statusText
            });
        };
        xhr.send();
    });
}

ByteStreamIn.prototype.LoadFromFile = async function(url) {
    let response = await this.MakeRequest(url);
    console.log(response);
    this.data = new Uint8Array(response);
/*    var xhr = new XMLHttpRequest();
    xhr.open('GET', url);
    xhr.responseType = 'arraybuffer';

    xhr.send(null);

    if (request.status !== 200) {
        throw "Could not fetch the data";
    }

    var arraydata = stringTo
    return new Uint8Array(this.response);*/
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