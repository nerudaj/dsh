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
        lvd.mesh.width = 3;
        lvd.mesh.height = 3;
        lvd.mesh.tiles = [
            1, 1, 1,
            1, 0, 0,
            1, 2, 2
        ];
        lvd.mesh.blocks = [
            1, 1, 1,
            1, 0, 0,
            1, 0, 0
        ];

        var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

        expect(lvd.mesh.tileWidth).toEqual(lvd2.mesh.tileWidth);
        expect(lvd.mesh.tileHeight).toEqual(lvd2.mesh.tileHeight);
        expect(lvd.mesh.width).toEqual(lvd2.mesh.width);
        expect(lvd.mesh.height).toEqual(lvd2.mesh.height);

        for (let i = 0; i < lvd.mesh.width * lvd.mesh.height; i++) {
            expect(lvd.mesh.tiles[i]).toEqual(lvd2.mesh.tiles[i]);
            expect(lvd.mesh.blocks[i]).toEqual(lvd2.mesh.blocks[i]);
        }
    });

    it ("should properly (de)serialize PLRS block", () => {
        lvd.players.push(new LeveldActor(0, 100, 20, 15));
        lvd.players.push(new LeveldActor(1, 15, 39, 2));

        var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

        expect(lvd.players.length).toEqual(lvd2.players.length);

        for (let i = 0; i < lvd.players.length; i++) {
            expect(lvd.players[i].id).toEqual(lvd2.players[i].id);
            expect(lvd.players[i].x).toEqual(lvd2.players[i].x);
            expect(lvd.players[i].y).toEqual(lvd2.players[i].y);
            expect(lvd.players[i].flags).toEqual(lvd2.players[i].flags);
        }
    });

    it ("should properly (de)serialize ITEM block", () => {
        lvd.items.push(new LeveldActor(0, 100, 20, 15));
        lvd.items.push(new LeveldActor(1, 15, 39, 2));

        var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

        expect(lvd.items.length).toEqual(lvd2.items.length);

        for (let i = 0; i < lvd.items.length; i++) {
            expect(lvd.items[i].id).toEqual(lvd2.items[i].id);
            expect(lvd.items[i].x).toEqual(lvd2.items[i].x);
            expect(lvd.items[i].y).toEqual(lvd2.items[i].y);
            expect(lvd.items[i].flags).toEqual(lvd2.items[i].flags);
        }
    });

    it ("should properly (de)serialize NPCS block", () => {
        lvd.npcs.push(new LeveldActor(0, 100, 20, 15));
        lvd.npcs.push(new LeveldActor(1, 15, 39, 2));

        var rawData = lvd.GetSerializedToUint8Array();
        var lvd2 = new LevelD();
        lvd2.LoadFromUint8Array(rawData);

        expect(lvd.npcs.length).toEqual(lvd2.npcs.length);

        for (let i = 0; i < lvd.npcs.length; i++) {
            expect(lvd.npcs[i].id).toEqual(lvd2.npcs[i].id);
            expect(lvd.npcs[i].x).toEqual(lvd2.npcs[i].x);
            expect(lvd.npcs[i].y).toEqual(lvd2.npcs[i].y);
            expect(lvd.npcs[i].flags).toEqual(lvd2.npcs[i].flags);
        }
    });
});