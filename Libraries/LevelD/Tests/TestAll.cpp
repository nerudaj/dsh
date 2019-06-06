#include "Test.hpp"

void TestAll::run() {
    ref.saveToFile(TMP_LVD_FILE);

    LevelD out;
    out.loadFromFile(TMP_LVD_FILE);

    // *** METADATA ***
    LevelD::Metadata &refmeta = ref.metadata;
    LevelD::Metadata &outmeta = out.metadata;
    assume(refmeta.timestamp == outmeta.timestamp,
        "Timestamp differs! ref = " + tostr(refmeta.timestamp) + 
        ", out = " + tostr(outmeta.timestamp)
    );

    assume(refmeta.id == outmeta.id,
        "Id differs! ref = " + refmeta.id + ", out = " + outmeta.id
    );

    assume(refmeta.name == outmeta.name,
        "Name differs! ref = " + refmeta.name + ", out = " + outmeta.name
    );

    assume(refmeta.author == outmeta.author,
        "Author differs! ref = " + refmeta.author + ", out = " + outmeta.author
    );

    assume(refmeta.description == outmeta.description,
        "Description differs! ref = " + refmeta.description + ", out = " + outmeta.description
    );

    // *** MESH ***
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

    // *** PLAYERS ***
    LevelD::Players refp = ref.players;
    LevelD::Players outp = out.players;

    assume(refp.size() == outp.size(),
        "Size mismatch! Ref = " + tostr(refp.size()) + ", out = " + tostr(outp.size())
    );

    for (unsigned i = 0; i < refp.size(); i++) {
        assume(refp[i].x == outp[i].x,
            "X value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refp[i].x) + ", out = " + tostr(outp[i].x)
        );

        assume(refp[i].y == outp[i].y,
            "Y value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refp[i].y) + ", out = " + tostr(outp[i].y)
        );

        assume(refp[i].flags == outp[i].flags,
            "Flags value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refp[i].flags) + ", out = " + tostr(outp[i].flags)
        );
    }

    // *** ITEMS ***
    LevelD::Items refi = ref.items;
    LevelD::Items outi = out.items;

    assume(refi.size() == outi.size(),
        "Size mismatch! Ref = " + tostr(refi.size()) + ", out = " + tostr(outi.size())
    );

    for (unsigned i = 0; i < refi.size(); i++) {
        assume(refi[i].x == outi[i].x,
            "X value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refi[i].x) + ", out = " + tostr(outi[i].x)
        );

        assume(refi[i].y == outi[i].y,
            "Y value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refi[i].y) + ", out = " + tostr(outi[i].y)
        );

        assume(refi[i].flags == outi[i].flags,
            "Flags value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refi[i].flags) + ", out = " + tostr(outi[i].flags)
        );
    }

    // *** NPCS ***
    LevelD::Npcs refn = ref.npcs;
    LevelD::Npcs outn = out.npcs;

    assume(refn.size() == outn.size(),
        "Size mismatch! Ref = " + tostr(refn.size()) + ", out = " + tostr(outn.size())
    );

    for (unsigned i = 0; i < refn.size(); i++) {
        assume(refn[i].x == outn[i].x,
            "X value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refn[i].x) + ", out = " + tostr(outn[i].x)
        );

        assume(refn[i].y == outn[i].y,
            "Y value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refn[i].y) + ", out = " + tostr(outn[i].y)
        );

        assume(refn[i].flags == outn[i].flags,
            "Flags value mismatch at index " + tostr(i) + "! Ref = " + 
            tostr(refn[i].flags) + ", out = " + tostr(outn[i].flags)
        );
    }
}