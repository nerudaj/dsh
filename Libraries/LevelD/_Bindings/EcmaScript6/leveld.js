/** BYTESTREAM IN **/
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

ByteStreamIn.prototype.Eof = function() {
    return this.index == this.data.length;
}

/** BYTESTREAM OUT **/

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

/* Modules */

class Module {
    constructor() {
/*        this.Serialize(lvd, bout);
        this.Deserialize(bin, lvd);*/
    }

    Serialize(lvd, bout) {}
    Deserialize(bin, lvd) {}
}

class MetadataModule extends Module {
    constructor() {
        super();
    }

    Serialize(lvd, bout) {
        console.log("MetadataModule::serialize");

        // TODO: timestamp
        bout.WriteQuadByte(0);
        bout.WriteQuadByte(0);

        bout.WriteString(lvd.metadata.id);
        bout.WriteString(lvd.metadata.name);
        bout.WriteString(lvd.metadata.author);
        bout.WriteString(lvd.metadata.description);
    }

    Deserialize(bin, lvd) {
        console.log("MetadataModule::deserialize");

        // TODO: timestamp
        lvd.metadata.timestamp = 0;

        lvd.metadata.id = bin.GetString();
        lvd.metadata.name = bin.GetString();
        lvd.metadata.author = bin.GetString();
        lvd.metadata.description = bin.GetString();
    }
};

const VERSION = 2;
const MODULE_CODE_META = 0x4154454D;
const MODULE_CODE_MESH = 0x4853454D;
const MODULE_CODE_PLRS = 0x53524C50;
const MODULE_CODE_NPCS = 0x5343504E;
const MODULE_CODE_ITEM = 0x4D455449;

function GetModule(code, version) {
    if (code == MODULE_CODE_META) {
        return new MetadataModule();
    }

    throw new Error("Module code '" + code + "' is not recognized!");
}

class LeveldMetadata {
    constructor() {
        this.time = 0;
        this.id = "";
        this.name = "";
        this.author = "";
        this.description = "";
    }
};

class Leveld {
    constructor() {
        this.metadata = new LeveldMetadata();
    }

    LoadFromUint8Array(arr) {
        let bin = new ByteStreamIn(arr);
        let version = bin.GetDoubleByte();

        if (version > VERSION) {
            throw new Error("Unsupported version: " + version);
        }

        while (!bin.Eof()) {
            let code = bin.GetQuadByte();
            let module = GetModule(code, version);

            module.Deserialize(bin, this);
        }
    }

    SaveToUint8Array() {
        let bout = new ByteStreamOut();

        let metamod = GetModule(MODULE_CODE_META, VERSION);
        metamot.Serialize(this, bout);
    }
}