var testDb = [];

function Test(testName, testCallback) {
    testDb.push({name: testName, callback: testCallback});
}

function RunTests() {
    for (let i = 0; i < testDb.length; i++) {
        try {
            testDb[i].callback();
            document.write(testDb[i].name + ": OK");
        } catch (e) {
            document.write(testDb[i].name + ": ERROR<br>Reason: " + e.message);
        } finally {
            document.write("<br><br>");
        }
    }
}

/* ------- */

Test("TestOk", () => {});
Test("TestFail", () => { throw Error("TestError"); });