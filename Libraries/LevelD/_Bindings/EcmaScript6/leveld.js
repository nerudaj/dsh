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
    this.ALLOC_CHUNK_SIZE = 256;
    this.data = new Uint8Array(this.ALLOC_CHUNK_SIZE);
    this.usedSize = 0;
}

ByteStreamOut.prototype._ResizeBuffer = function(newSize) {
    var oldBuffer = this.data.buffer;
    var newBuffer = new ArrayBuffer(newSize);
    this.data = new Uint8Array(newBuffer);
    this.data.set(oldBuffer);
}

ByteStreamOut.prototype.WriteByte = function(data) {
    this.data[this.usedSize] = data;
    this.usedSize++;

    if (this.usedSize == this.data.length) {
        this._ResizeBuffer(usedSize + this.ALLOC_CHUNK_SIZE);
    }
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
    constructor() {}

    Serialize(lvd, bout) {}
    Deserialize(bin, lvd) {}
}

class MetadataModule extends Module {
    constructor() {
        super();
    }

    Serialize(lvd, bout) {
        console.log("MetadataModule::serialize");

        bout.WriteQuadByte(parseInt(lvd.metadata.timestamp / 0x0100000000));
        bout.WriteQuadByte(lvd.metadata.timestamp % 0x0100000000);

        bout.WriteString(lvd.metadata.id);
        bout.WriteString(lvd.metadata.name);
        bout.WriteString(lvd.metadata.author);
        bout.WriteString(lvd.metadata.description);
    }

    Deserialize(bin, lvd) {
        console.log("MetadataModule::deserialize");

        lvd.metadata.timestamp = (bin.GetQuadByte() * 0x0100000000) + bin.GetQuadByte();

        lvd.metadata.id = bin.GetString();
        lvd.metadata.name = bin.GetString();
        lvd.metadata.author = bin.GetString();
        lvd.metadata.description = bin.GetString();
    }
};

class MeshModule_v2 extends Module {
    constructor() {
        super();
    }

    Serialize(lvd, bout) {
        console.log("MeshModule_v2::serialize");
        bout.WriteQuadByte(lvd.mesh.tileWidth);
        bout.WriteQuadByte(lvd.mesh.tileHeight);
        bout.WriteQuadByte(lvd.mesh.width);

        let dataSize = lvd.mesh.width * lvd.mesh.height;
        bout.WriteQuadByte(dataSize);

        for (let i = 0; i < dataSize; i++) {
            let dblbyte = lvd.mesh.tiles[i];
            dblbyte = (lvd.mesh.blocks[i] ? 0x8000 : 0) | dblbyte ;
            bout.WriteDoubleByte(dblbyte);
        }
    }

    Deserialize(bin, lvd) {
        console.log("MeshModule_v2::deserialize");
        lvd.mesh.tileWidth = bin.GetQuadByte();
        lvd.mesh.tileHeight = bin.GetQuadByte();
        lvd.mesh.width = bin.GetQuadByte();

        let data = bin.GetDoubleByteVector();

        lvd.mesh.height = data.length / lvd.mesh.width;
        lvd.mesh.tiles = [];
        lvd.mesh.blocks = [];

        for (let i = 0; i < data.length; i++) {
            lvd.mesh.tiles.push(data[i] & 0x7fff);
            lvd.mesh.blocks.push(data[i] & 0x8000 > 0);
        }
    }
};

class ActorsModule extends Module {
    constructor() {
        super();
        this.actorType = "none";
    }

    Serialize(lvd, bout) {
        bout.WriteQuadByte(lvd[this.actorType].length);

        for (let i = 0; i < lvd[this.actorType].length; i++) {
            bout.WriteQuadByte(lvd[this.actorType][i].id);
            bout.WriteQuadByte(lvd[this.actorType][i].x);
            bout.WriteQuadByte(lvd[this.actorType][i].y);
            bout.WriteDoubleByte(lvd[this.actorType][i].flags);
        }
    }

    Deserialize(bin, lvd) {
        let count = bin.GetQuadByte();

        for (let i = 0; i < count; i++) {
            lvd[this.actorType].push(new LeveldActor());
            lvd[this.actorType][i].id = bin.GetQuadByte();
            lvd[this.actorType][i].x = bin.GetQuadByte();
            lvd[this.actorType][i].y = bin.GetQuadByte();
            lvd[this.actorType][i].flags = bin.GetDoubleByte();
        }
    }
};

class PlayersModule extends ActorsModule {
    constructor() {
        super();
        this.actorType = "players";
    }
};

class NpcsModule extends ActorsModule {
    constructor() {
        super();
        this.actorType = "npcs";
    }
};

class ItemsModule extends ActorsModule {
    constructor() {
        super();
        this.actorType = "items";
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
    else if (code == MODULE_CODE_MESH && version == VERSION) {
        return new MeshModule_v2();
    }
    else if (code == MODULE_CODE_PLRS) {
        return new PlayersModule();
    }
    else if (code == MODULE_CODE_ITEM) {
        return new ItemsModule();
    }
    else if (code == MODULE_CODE_NPCS) {
        return new NpcsModule();
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

class LeveldMesh {
    constructor() {
        this.tileWidth = 0;
        this.tileHeight = 0;
        this.width = 0;
        this.height = 0;
        this.tiles = [];
        this.blocks = [];
    }
};

class LeveldActor {
    constructor(id = 0, x = 0, y = 0, flags = 0) {
        this.id = id;
        this.x = x;
        this.y = y;
        this.flags = flags;
    }
};

class LevelD {
    constructor() {
        this.metadata = new LeveldMetadata();
        this.mesh = new LeveldMesh();
        this.players = [];
        this.npcs = [];
        this.items = [];
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

    GetSerializedToUint8Array() {
        let bout = new ByteStreamOut();

        bout.WriteDoubleByte(VERSION);

        let metamod = GetModule(MODULE_CODE_META, VERSION);
        bout.WriteQuadByte(MODULE_CODE_META);
        metamod.Serialize(this, bout);

        if (this.mesh.width * this.mesh.height > 0) {
            let meshmod = GetModule(MODULE_CODE_MESH, VERSION);
            bout.WriteQuadByte(MODULE_CODE_MESH);
            meshmod.Serialize(this, bout);
        }

        if (this.players.length > 0) {
            let module = GetModule(MODULE_CODE_PLRS, VERSION);
            bout.WriteQuadByte(MODULE_CODE_PLRS);
            module.Serialize(this, bout);
        }

        if (this.items.length > 0) {
            let module = GetModule(MODULE_CODE_ITEM, VERSION);
            bout.WriteQuadByte(MODULE_CODE_ITEM);
            module.Serialize(this, bout);
        }

        if (this.npcs.length > 0) {
            let module = GetModule(MODULE_CODE_NPCS, VERSION);
            bout.WriteQuadByte(MODULE_CODE_NPCS);
            module.Serialize(this, bout);
        }

        return bout.data.slice(0, bout.usedSize);
    }
}