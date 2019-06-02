#include "Test.hpp"

void TestPlayers::run() {
    ref.saveToFile(TMP_LVD_FILE);

    LevelD out;
    out.loadFromFile(TMP_LVD_FILE);

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
}