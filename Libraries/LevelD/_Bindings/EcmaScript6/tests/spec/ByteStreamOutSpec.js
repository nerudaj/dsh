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
});