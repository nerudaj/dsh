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

class MeshModule_v3 extends Module {
    constructor() {
        super();
    }

    Serialize(lvd, bout) {
        console.log("MeshModule_v2::serialize");
        bout.WriteQuadByte(lvd.mesh.tileWidth);
        bout.WriteQuadByte(lvd.mesh.tileHeight);
        bout.WriteQuadByte(lvd.mesh.layerWidth);
        bout.WriteQuadByte(lvd.mesh.layerHeight);

        bout.WriteQuadByte(lvd.mesh.layers.length);
		let layersize = lvd.mesh.layerWidth * lvd.mesh.layerHeight;

        for (let j = 0; j < lvd.mesh.layers.length; j++) {
			let dataout = [];
			for (let i = 0; i < layersize; i++) {
				let dblbyte = lvd.mesh.layers[j].tiles[i];
				dblbyte = (lvd.mesh.layers[j].blocks[i] ? 0x8000 : 0) | dblbyte ;
				dataout.push(dblbyte);
			}

			console.log(dataout);
			bout.WriteDoubleByteVector(dataout);
        }
    }

    Deserialize(bin, lvd) {
        console.log("MeshModule_v2::deserialize");
        lvd.mesh.tileWidth = bin.GetQuadByte();
        lvd.mesh.tileHeight = bin.GetQuadByte();
        lvd.mesh.layerWidth = bin.GetQuadByte();
        lvd.mesh.layerHeight = bin.GetQuadByte();

		let layerCount = bin.GetQuadByte();

		for (let i = 0; i < layerCount; i++) {
			lvd.mesh.layers.push(new LeveldTileLayer());
			let data = bin.GetDoubleByteVector();
			console.log(data);

			for (let j = 0; j < data.length; j++) {
				lvd.mesh.layers[i].tiles.push(data[j] & 0x7fff);
				lvd.mesh.layers[i].blocks.push(data[j] & 0x8000 > 0);
			}
		}
    }
};

class ThingsModule extends Module {
    constructor() {
        super();
    }

    Serialize(lvd, bout) {
        console.log("ThingsModule::serialize");

		bout.WriteQuadByte(lvd.things.length);

		for (let i = 0; i < lvd.things.length; i++) {
			bout.WriteQuadByte(lvd.things[i].id);
			bout.WriteQuadByte(lvd.things[i].tag);
			bout.WriteQuadByte(lvd.things[i].x);
			bout.WriteQuadByte(lvd.things[i].y);
			bout.WriteDoubleByte(lvd.things[i].flags);
			bout.WriteString(lvd.things[i].metadata);
		}
	}

	Deserialize(bin, lvd) {
        console.log("ThingsModule::deserialize");

		let size = bin.GetQuadByte();
		for (let i = 0; i < size; i++) {
			lvd.things.push(new LeveldThing());
			lvd.things[i].id = bin.GetQuadByte();
			lvd.things[i].tag = bin.GetQuadByte();
			lvd.things[i].x = bin.GetQuadByte();
			lvd.things[i].y = bin.GetQuadByte();
			lvd.things[i].flags = bin.GetDoubleByte();
			lvd.things[i].metadata = bin.GetString();
		}
	}
};

class TriggersModule extends Module {
	constructor() {
		super();
	}

	Serialize(lvd, bout) {
        console.log("ThingsModule::serialize");

		bout.WriteQuadByte(lvd.triggers.length);
		for (let i = 0; i < lvd.triggers.length; i++) {
			bout.WriteQuadByte(lvd.triggers[i].x);
			bout.WriteQuadByte(lvd.triggers[i].y);

			if (lvd.triggers[i].areaType == "rectangle") {
				bout.WriteByte(0);
				bout.WriteDoubleByte(lvd.triggers[i].width);
				bout.WriteDoubleByte(lvd.triggers[i].height);
			} else if (lvd.triggers[i].areaType == "circle") {
				bout.WriteByte(1);
				bout.WriteDoubleByte(lvd.triggers[i].radius);
			}

			bout.WriteQuadByte(lvd.triggers[i].id);
			bout.WriteQuadByte(lvd.triggers[i].tag);
			bout.WriteDoubleByte(lvd.triggers[i].type);
			bout.WriteQuadByte(lvd.triggers[i].a1);
			bout.WriteQuadByte(lvd.triggers[i].a2);
			bout.WriteQuadByte(lvd.triggers[i].a3);
			bout.WriteQuadByte(lvd.triggers[i].a4);
			bout.WriteQuadByte(lvd.triggers[i].a5);
		}
	}

	Deserialize(bin, lvd) {
        console.log("TriggersModule::deserialize");

		let size = bin.GetQuadByte();
		for (let i = 0; i < size; i++) {
			lvd.triggers.push(new LeveldTrigger());
			lvd.triggers[i].x = bin.GetQuadByte();
			lvd.triggers[i].y = bin.GetQuadByte();

			let areaType = bin.GetByte();
			if (areaType == 0) {
				lvd.triggers[i].areaType = "rectangle";
				lvd.triggers[i].radius = 0;
				lvd.triggers[i].width = bin.GetDoubleByte();
				lvd.triggers[i].height = bin.GetDoubleByte();
			} else if (areaType == 1) {
				lvd.triggers[i].areaType = "circle";
				lvd.triggers[i].radius = bin.GetDoubleByte();
				lvd.triggers[i].width = 0;
				lvd.triggers[i].height = 0;
			}

			lvd.triggers[i].id = bin.GetQuadByte();
			lvd.triggers[i].tag = bin.GetQuadByte();
			lvd.triggers[i].type = bin.GetDoubleByte();
			lvd.triggers[i].a1 = bin.GetQuadByte();
			lvd.triggers[i].a2 = bin.GetQuadByte();
			lvd.triggers[i].a3 = bin.GetQuadByte();
			lvd.triggers[i].a4 = bin.GetQuadByte();
			lvd.triggers[i].a5 = bin.GetQuadByte();
		}
	}
};

const VERSION = 3;
const MODULE_CODE_META = 0x4154454D;
const MODULE_CODE_MESH = 0x4853454D;
const MODULE_CODE_THNG = 0x54484E47;
const MODULE_CODE_TRIG = 0x54524947;

function GetModule(code, version) {
    if (code == MODULE_CODE_META) {
        return new MetadataModule();
    }
    else if (code == MODULE_CODE_MESH && version == VERSION) {
        return new MeshModule_v3();
    }
    else if (code == MODULE_CODE_THNG) {
		return new ThingsModule();
    }
    else if (code == MODULE_CODE_TRIG) {
        return new TriggersModule();
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

class LeveldTileLayer {
	constructor() {
		this.tiles = [];
		this.blocks = [];
	}
};

class LeveldMesh {
    constructor() {
        this.tileWidth = 0;
        this.tileHeight = 0;
        this.layerWidth = 0;
        this.lyerHeight = 0;
        this.layers = [];
    }
};

class LeveldThing {
	constructor() {
		this.id = 0;
		this.tag = 0;
		this.x = 0;
		this.y = 0;
		this.flags = 0;
		this.metadata = "";
	}
};

class LeveldTrigger {
	constructor() {
		this.x = 0;
		this.y = 0;
		this.areaType = "rectangle"; // other choice "circle"
		this.radius = 0;
		this.width = 0;
		this.height = 0;
		this.id = 0;
		this.tag = 0;
		this.type = 0;
		this.a1 = 0;
		this.a2 = 0;
		this.a3 = 0;
		this.a4 = 0;
		this.a5 = 0;
	}
};

class LevelD {
    constructor() {
        this.metadata = new LeveldMetadata();
        this.mesh = new LeveldMesh();
		this.things = [];
		this.triggers = [];
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

        if (this.mesh.layers.length > 0) {
            let meshmod = GetModule(MODULE_CODE_MESH, VERSION);
            bout.WriteQuadByte(MODULE_CODE_MESH);
            meshmod.Serialize(this, bout);
        }

		if (this.things.length > 0) {
            let thngmod = GetModule(MODULE_CODE_THNG, VERSION);
            bout.WriteQuadByte(MODULE_CODE_THNG);
            thngmod.Serialize(this, bout);
        }

		if (this.triggers.length > 0) {
			let trigmod = GetModule(MODULE_CODE_TRIG, VERSION);
            bout.WriteQuadByte(MODULE_CODE_TRIG);
            trigmod.Serialize(this, bout);
		}

        return bout.data.slice(0, bout.usedSize);
    }
}