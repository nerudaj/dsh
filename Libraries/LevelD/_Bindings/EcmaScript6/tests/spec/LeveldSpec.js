describe ("LevelD", () => {
    var lvd;

    beforeEach(() => {
        lvd = new LevelD();
    });

    it ("should properly (de)serialize META block", () => {
        lvd.metadata.id = "DEMOID";
        lvd.metadata.timestamp = 1529644667834;
        lvd.metadata.name = "Test Name"
        lvd.metadata.author = "doomista";
        lvd.metadata.description = "Test Description for the level.";

        var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

        expect(lvd.metadata.id).toEqual(lvd2.metadata.id);
        expect(lvd.metadata.timestamp).toEqual(lvd2.metadata.timestamp);
        expect(lvd.metadata.name).toEqual(lvd2.metadata.name);
        expect(lvd.metadata.author).toEqual(lvd2.metadata.author);
        expect(lvd.metadata.description).toEqual(lvd2.metadata.description);
    });

    it ("should properly (de)serialize MESH block", () => {
        lvd.mesh.tileWidth = 16;
        lvd.mesh.tileHeight = 24;
        lvd.mesh.layerWidth = 3;
        lvd.mesh.layerHeight = 3;
		lvd.mesh.layers = [ new LeveldTileLayer() ];
        lvd.mesh.layers[0].tiles = [
            1, 1, 1,
            1, 0, 0,
            1, 2, 2
        ];
        lvd.mesh.layers[0].blocks = [
            1, 1, 1,
            1, 0, 0,
            1, 0, 0
        ];

        var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

        expect(lvd.mesh.tileWidth).toEqual(lvd2.mesh.tileWidth);
        expect(lvd.mesh.tileHeight).toEqual(lvd2.mesh.tileHeight);
        expect(lvd.mesh.layerWidth).toEqual(lvd2.mesh.layerWidth);
        expect(lvd.mesh.layerHeight).toEqual(lvd2.mesh.layerHeight);
		expect(lvd.mesh.layers.length).toEqual(lvd2.mesh.layers.length);

		for (let j = 0; j < lvd.mesh.layers.length; j++) {
			for (let i = 0; i < lvd.mesh.layerWidth * lvd.mesh.layerHeight; i++) {
				expect(lvd.mesh.layers[j].tiles[i]).toEqual(lvd2.mesh.layers[j].tiles[i]);
				expect(lvd.mesh.layers[j].blocks[i]).toEqual(lvd2.mesh.layers[j].blocks[i]);
			}
		}
    });

	it ("should properly (de)serialize THNG block", () => {
		lvd.things.push(new LeveldThing());
		lvd.things[0].id = 0;
		lvd.things[0].tag = 1;
		lvd.things[0].x = 100;
		lvd.things[0].y = 345678;
		lvd.things[0].flags = 5678;
		lvd.things[0].metadata = "test";

		var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

		expect(lvd.things.length == lvd2.things.length);

		for (let i = 0; i < lvd.things.length; i++) {
			expect(lvd.things[i].id).toEqual(lvd2.things[i].id);
			expect(lvd.things[i].tag).toEqual(lvd2.things[i].tag);
			expect(lvd.things[i].x).toEqual(lvd2.things[i].x);
			expect(lvd.things[i].y).toEqual(lvd2.things[i].y);
			expect(lvd.things[i].flags).toEqual(lvd2.things[i].flags);
			expect(lvd.things[i].metadata).toEqual(lvd2.things[i].metadata);
		}
	});

	it ("should properly (de)serialize TRIG block", () => {
		lvd.triggers.push(new LeveldTrigger());
		lvd.triggers[0].tag = 10;
		lvd.triggers[0].x = 100;
		lvd.triggers[0].y = 12345;
		lvd.triggers[0].width = 300;
		lvd.triggers[0].height = 560;
		lvd.triggers[0].type = 69;
		lvd.triggers[0].a1 = 42;
		lvd.triggers.push(new LeveldTrigger());
		lvd.triggers[1].id = 1;
		lvd.triggers[1].x = 565;
		lvd.triggers[1].y = 145;
		lvd.triggers[1].areaType = "circle";
		lvd.triggers[1].radius = 300;
		lvd.triggers[1].type = 24;
		lvd.triggers[1].a1 = 42;
		lvd.triggers[1].a1 = 42;
		lvd.triggers[1].a1 = 30;
		lvd.triggers[1].a4 = 16;
		lvd.triggers[1].a5 = 11;

		var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

		expect(lvd.triggers.length == lvd2.triggers.length);

		for (let i = 0; i < lvd.triggers.length; i++) {
			expect(lvd.triggers[i].id).toEqual(lvd2.triggers[i].id);
			expect(lvd.triggers[i].tag).toEqual(lvd2.triggers[i].tag);
			expect(lvd.triggers[i].x).toEqual(lvd2.triggers[i].x);
			expect(lvd.triggers[i].y).toEqual(lvd2.triggers[i].y);
			expect(lvd.triggers[i].areaType).toEqual(lvd2.triggers[i].areaType);
			expect(lvd.triggers[i].type).toEqual(lvd2.triggers[i].type);
			expect(lvd.triggers[i].width).toEqual(lvd2.triggers[i].width);
			expect(lvd.triggers[i].height).toEqual(lvd2.triggers[i].height);
			expect(lvd.triggers[i].radius).toEqual(lvd2.triggers[i].radius);
			expect(lvd.triggers[i].a1).toEqual(lvd2.triggers[i].a1);
			expect(lvd.triggers[i].a2).toEqual(lvd2.triggers[i].a2);
			expect(lvd.triggers[i].a3).toEqual(lvd2.triggers[i].a3);
			expect(lvd.triggers[i].a4).toEqual(lvd2.triggers[i].a4);
			expect(lvd.triggers[i].a5).toEqual(lvd2.triggers[i].a5);
		}
	});
});