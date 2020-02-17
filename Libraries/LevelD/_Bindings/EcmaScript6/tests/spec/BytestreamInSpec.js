describe("Bytestream In", () => {
    var bin;

    beforeEach(() => {
        bin = new ByteStreamIn();
    });

    it ("should throw when not initialized and getter is called", () => {
        expect(() => {
            bin.GetByte();
        }).toThrowError();
    });

    it ("should return first byte when initialized", () => {
        bin = new ByteStreamIn(new Uint8Array([1, 2, 3, 4, 5]));

        expect(bin.GetByte()).toEqual(1);
        expect(bin.GetByte()).toEqual(2);
        expect(bin.GetByte()).toEqual(3);
        expect(bin.GetByte()).toEqual(4);
        expect(bin.GetByte()).toEqual(5);
        expect(bin.Eof()).toEqual(true);
    });

    it ("should return double byte when initialized", () => {
        bin = new ByteStreamIn(new Uint8Array([1, 2, 3, 4]));

        expect(bin.GetDoubleByte()).toEqual(258);
        expect(bin.GetDoubleByte()).toEqual(772);
        expect(bin.Eof()).toEqual(true);
    });

    it ("should return quad byte when initialized", () => {
        bin = new ByteStreamIn(new Uint8Array([1, 2, 3, 4, 1, 2, 3, 5]));

        expect(bin.GetQuadByte()).toEqual(16909060);
        expect(bin.GetQuadByte()).toEqual(16909061);
        expect(bin.Eof()).toEqual(true);
    });

    it ("should return UTF-8 string when initialized", () => {
        bin = new ByteStreamIn(new Uint8Array([6, 97, 98, 97, 99, 100, 101]));

        expect(bin.GetString()).toEqual("abacde");
        expect(bin.Eof()).toEqual(true);
    });

    it ("should return uint16 vector when initialized", () => {
        bin = new ByteStreamIn(new Uint8Array([0, 0, 0, 4, 0, 1, 0, 2, 1, 2, 1, 3]));

        expect(bin.GetDoubleByteVector()).toEqual([1, 2, 258, 259]);
        expect(bin.Eof()).toEqual(true);
    });

    it ("should work after loading from file", () => {
        bin = new ByteStreamIn("a hello world this is message abcd0", true);

        expect(bin.GetByte()).toEqual(97);
        expect(bin.GetString()).toEqual("hello world this is message abcd");
        expect(bin.GetByte()).toEqual(48);
        expect(bin.Eof()).toEqual(true);
    });
});