#include "Test.hpp"

void TestItems::run() {
    ref.saveToFile(TMP_LVD_FILE);

    LevelD out;
    out.loadFromFile(TMP_LVD_FILE);

    LevelD::Items refi = ref.items;
    LevelD::Items outi = out.items;

    assume(refi.size() == outi.size(),
        "Size mismatch! Ref = " + tostr(refi.size()) + ", out = " + tostr(outi.size())
    );

    for (unsigned i = 0; i < refi.size(); i++) {
		assume(refi[i].id == outi[i].id,
			"ID value mismatch at index " + tostr(i) + "! Ref = " +
			tostr(refi[i].id) + ", out = " + tostr(outi[i].id)
		);

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
}