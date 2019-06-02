#include "Test.hpp"

void TestMetadata::run() {
    ref.saveToFile(TMP_LVD_FILE);

    LevelD out;
    out.loadFromFile(TMP_LVD_FILE);

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
}