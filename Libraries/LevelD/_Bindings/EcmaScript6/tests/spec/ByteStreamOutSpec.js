describe("ByteStreamOut", () => {
    let bout;

    beforeEach(() => {
        bout = new ByteStreamOut();
    });

    it ("should write byte", () => {
        bout.WriteByte(10);
        bout.WriteByte(257);

        expect(bout.data[0]).toEqual(10);
        expect(bout.data[1]).toEqual(1);
        expect(bout.data[2]).toEqual(0);
        expect(bout.usedSize).toEqual(2);
    });

    it ("should write double byte", () => {
        bout.WriteDoubleByte(34567);

        expect(bout.data[0]).toEqual(135);
        expect(bout.data[1]).toEqual(7);
        expect(bout.usedSize).toEqual(2);
    });

    it ("should write quad byte", () => {
        bout.WriteQuadByte(16909060);


        expect(bout.data[0]).toEqual(1);
        expect(bout.data[1]).toEqual(2);
        expect(bout.data[2]).toEqual(3);
        expect(bout.data[3]).toEqual(4);
        expect(bout.data[4]).toEqual(0);
        expect(bout.usedSize).toEqual(4);
    });

    it ("should write ascii string", () => {
        bout.WriteString("hello world");

        expect(bout.data[0]).toEqual(11);
        expect(bout.data[1]).toEqual(104);
        expect(bout.data[2]).toEqual(101);
        expect(bout.data[3]).toEqual(108);
        expect(bout.data[4]).toEqual(108);
        expect(bout.data[5]).toEqual(111);
        expect(bout.data[6]).toEqual(32);
        expect(bout.data[7]).toEqual(119);
        expect(bout.data[8]).toEqual(111);
        expect(bout.data[9]).toEqual(114);
        expect(bout.data[10]).toEqual(108);
        expect(bout.data[11]).toEqual(100);
    });

    it ("should throw when string is too long", () => {
        expect(() => { bout.WriteString("a".repeat(300)) }).toThrow(Error("String is too long"));
    });

    it ("should write double byte vector", () => {
        bout.WriteDoubleByteVector([512, 16, 21, 65535]);

        expect(bout.data[0]).toEqual(0);
        expect(bout.data[1]).toEqual(0);
        expect(bout.data[2]).toEqual(0);
        expect(bout.data[3]).toEqual(4);
        expect(bout.data[4]).toEqual(2);
        expect(bout.data[5]).toEqual(0);
        expect(bout.data[6]).toEqual(0);
        expect(bout.data[7]).toEqual(16);
        expect(bout.data[8]).toEqual(0);
        expect(bout.data[9]).toEqual(21);
        expect(bout.data[10]).toEqual(255);
        expect(bout.data[11]).toEqual(255);
    });
});