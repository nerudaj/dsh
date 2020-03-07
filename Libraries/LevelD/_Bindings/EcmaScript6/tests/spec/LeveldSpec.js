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
});