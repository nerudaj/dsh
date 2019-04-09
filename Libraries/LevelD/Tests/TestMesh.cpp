#include "Test.hpp"

void TestMesh::run() {
    ref.saveToFile(TMP_LVD_FILE);

    LevelD out;
    out.loadFromFile(TMP_LVD_FILE);

    LevelD::Mesh &refm = ref.mesh;
    LevelD::Mesh &outm = out.mesh;
    assume(refm.width == outm.width, 
        "Width mismatch! Ref = " + tostr(refm.width) + ", out = " + tostr(outm.width)
    );

    assume(refm.height == outm.height, 
        "Height mismatch! Ref = " + tostr(refm.height) + ", out = " + tostr(outm.height)
    );

    assume(outm.width * outm.height == outm.tiles.size(),
        "Tiles dimension mismatch! W*H = " + tostr(outm.width * outm.height) + 
        ", tiles = " + tostr(outm.tiles.size())
    );

    assume(outm.width * outm.height == outm.blocks.size(),
        "Blocks dimension mismatch! W*H = " + tostr(outm.width * outm.height) + 
        ", blocks = " + tostr(outm.blocks.size())
    );

    for (unsigned i = 0; i < refm.tiles.size(); i++) {
        assume(refm.tiles[i] == outm.tiles[i], 
            "Tile mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refm.tiles[i]) + ", out = " + tostr(outm.tiles[i])
        );

        assume(refm.blocks[i] == outm.blocks[i], 
            "Block mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refm.blocks[i]) + ", out = " + tostr(outm.blocks[i])
        );
    }
}