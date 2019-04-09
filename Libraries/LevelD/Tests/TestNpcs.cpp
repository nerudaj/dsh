#include "Test.hpp"

void TestNpcs::run() {
    ref.saveToFile(TMP_LVD_FILE);

    LevelD out;
    out.loadFromFile(TMP_LVD_FILE);

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