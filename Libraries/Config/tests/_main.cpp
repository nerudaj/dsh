#include <iostream>
#include <Test.hpp>
#include <cstdio>
#include "../Config.hpp"
#include <typeinfo>
#include <fstream>
#include <vector>

using std::string;
using std::vector;

template<typename T>
class ItemInitTest : public Test {
private:
	T input;
	string ref;

public:
	virtual void run() final override {
		cfg::Item item(input);

		assertEqual(item.asString(), ref, item.asString(), ref);
	}

	virtual string name() const {
		return "ItemInitTest<" + std::string(typeid(T).name()) + ">";
	}

	ItemInitTest(T input, const string &ref) : input(input), ref(ref) {}
};

template<typename T>
class ItemAssignTest : public Test {
private:
	T input;
	string ref;

public:
	virtual void run() final override {
		cfg::Item item;
		item = input;

		assertEqual(item.asString(), ref, item.asString(), ref);
	}

	virtual string name() const {
		return "ItemAssignTest<" + std::string(typeid(T).name()) + ">";
	}

	ItemAssignTest(T input, const string &ref) : input(input), ref(ref) {}
};

template<typename T, typename U>
class ItemEqualTest : public Test {
private:
	T input;
	U ref;

public:
	virtual void run() final override {
		cfg::Item item(input);

		assertTrue(item == ref);
	}

	virtual string name() const {
		return "ItemEqualTest<" + std::string(typeid(T).name()) + ", " + std::string(typeid(U).name()) + ">";
	}

	ItemEqualTest(T input, U ref) : input(input), ref(ref) {}
};

void compareIniToReferenceMap(const cfg::Ini &ini, const std::map<string, cfg::IniSection> &ref) {
	for (auto &sec : ref) {
		assertTrue(ini.hasSection(sec.first));

		auto &section = ini[sec.first];
		for (auto &keyval : sec.second) {
			assertTrue(section.hasKey(keyval.first));
			assertEqual(keyval.second, section.at(keyval.first), keyval.second.asString(), section.at(keyval.first).asString());
		}
	}
}

class IniManualInitTest : public Test {
private:
	std::map<string, cfg::IniSection> ref;

public:
	virtual void run() final override {
		cfg::Ini ini;

		// Initialize from ref
		for (auto &sec : ref) {
			auto &section = ini[sec.first];

			for (auto &keyval : sec.second) {
				section[keyval.first] = keyval.second;
			}
		}

		compareIniToReferenceMap(ini, ref);
	}
	
	virtual string name() const {
		return "IniManualInitTest";
	}
	
	IniManualInitTest(const std::map<string, cfg::IniSection> &ref) : ref(ref) {}
};

class IniLoadFromFileTest : public Test {
private:
	string filename;
	std::map<string, cfg::IniSection> ref;

public:
	virtual void run() final override {
		cfg::Ini ini;
		assertNotException({
			ini.loadFromFile(filename);
		});
		
		compareIniToReferenceMap(ini, ref);
	}
	
	virtual string name() const {
		return "IniLoadFromFileTest(" + filename + ")";
	}
	
	IniLoadFromFileTest(const std::string &filename, const std::map<string, cfg::IniSection> &ref) : filename(filename), ref(ref) {}
};

class IniLoadFromFileFailTest : public Test {
private:
	string filename;

public:
	virtual void run() final override {
		cfg::Ini ini;
		assertException({
			ini.loadFromFile(filename);
		}, cfg::IniException);
	}

	virtual string name() const {
		return "IniLoadFromFileFailTest(" + filename + ")";
	}

	IniLoadFromFileFailTest(const std::string &filename) : filename(filename) {}
};

string loadFile(const string &filename) {
	string result;

	try {
		std::ifstream load(filename);

		load.seekg(0, load.end);
		unsigned size = load.tellg();
		load.seekg(0, load.beg);

		result.resize(size);
		load.read((char*)(result.data()), size);

		load.close();
		load.clear();
	} catch (std::exception &e) {
		throw std::runtime_error(string(e.what()));
	}

	return result;
}

void compareFiles(const string &ref, const string &file) {
	auto fileRef = loadFile(ref);
	auto fileTest = loadFile(file);

	assertEqual(fileRef.size(), fileTest.size(), 
		std::to_string(fileRef.size()), std::to_string(fileTest.size())
	);
	for (unsigned i = 0; i < fileRef.size(); i++) {
		inLoop(assertEqual(
			fileRef[i], fileTest[i], fileRef[i], fileTest[i]
		), i);
	}
}

class IniSaveToFileTest : public Test {
private:
	string filename;

public:
	virtual void run() final override {
		cfg::Ini ini;
		assertNotException({ini.loadFromFile(filename);});
		assertNotException({ini.saveToFile(filename + ".test");});

		cfg::Ini ini2;
		assertNotException({ini2.loadFromFile(filename + ".test");});

		// TODO: there should be a comparison of the two
	}

	virtual string name() const final override {
		return "IniSaveToFileTest(" + filename + ")";
	}

	IniSaveToFileTest(const string &filename) : filename(filename) {}

	~IniSaveToFileTest() {
		remove(string(filename + ".test").c_str());
	}
};

class ArgsSetupArgumentsTest : public Test {
private:
	string setup;

public:
	virtual void run() final override {
		cfg::Args args;

		assertNotException(args.setupArguments(setup));
	}

	virtual string name() const final override {
		return "ArgsSetupArgumentsTest(" + setup + ")";
	}

	ArgsSetupArgumentsTest(const string &setup) : setup(setup) {}
};

class ArgsSetupArgumentsFailTest : public Test {
private:
	string setup;

public:
	virtual void run() final override {
		cfg::Args args;

		assertException(args.setupArguments(setup), cfg::ArgsException);
	}

	virtual string name() const final override {
		return "ArgsSetupArgumentsFailTest(" + setup + ")";
	}

	ArgsSetupArgumentsFailTest(const string &setup) : setup(setup) {}
};

class ArgsParseTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;

public:
	virtual void run() final override {
		cfg::Args args(setup);

		assertNotException(args.parse(inArgs.size(), inArgs.data()));
	}

	virtual string name() const final override {
		return "ArgsParseTest(" + setup + ", " + std::to_string(inArgs.size()) + ")";
	}

	ArgsParseTest(const string &setup, const vector<const char*> &inArgs) : setup(setup), inArgs(inArgs) {}
};

class ArgsParseFailTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;

public:
	virtual void run() final override {
		cfg::Args args(setup);

		assertException(args.parse(inArgs.size(), inArgs.data()), cfg::ArgsException);
	}

	virtual string name() const final override {
		return "ArgsParseFailTest(" + setup + ", " + std::to_string(inArgs.size()) + ")";
	}

	ArgsParseFailTest(const string &setup, const vector<const char*> &inArgs) : setup(setup), inArgs(inArgs) {}
};

class ArgsIsSetTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;
	vector<char> queries;

public:
	virtual void run() final override {
		cfg::Args args(setup);
		
		assertNotException(args.parse(inArgs.size(), inArgs.data()));

		for (auto query : queries) {
			assertTrue(args.isSet(query));
		}
	}

	virtual string name() const final override {
		return "ArgsIsSetTest(" + setup + ")";
	}

	ArgsIsSetTest(const string &setup, const vector<const char*> &inArgs, const vector<char> &queries) : setup(setup), inArgs(inArgs), queries(queries) {}
};

class ArgsIsSetFailTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;
	vector<char> queries;

public:
	virtual void run() final override {
		cfg::Args args(setup);
		
		assertNotException(args.parse(inArgs.size(), inArgs.data()));

		for (auto query : queries) {
			assertFalse(args.isSet(query));
		}
	}

	virtual string name() const final override {
		return "ArgsIsSetFailTest(" + setup + ")";
	}

	ArgsIsSetFailTest(const string &setup, const vector<const char*> &inArgs, const vector<char> &queries) : setup(setup), inArgs(inArgs), queries(queries) {}
};

class ArgsGetPositionalArgsTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;
	vector<string> ref;

public:
	virtual void run() final override {
		cfg::Args args(setup);
		assertNotException(args.parse(inArgs.size(), inArgs.data()));

		auto out = args.getPositionalArguments();
		assertEqual(out.size(), ref.size(), std::to_string(out.size()), std::to_string(ref.size()));

		for (unsigned i = 0; i < out.size(); i++) {
			inLoop(assertEqual(out[i], ref[i], out[i], ref[i]), i);
		}
	}

	virtual string name() const final override {
		return "ArgsGetPositionalArgsTest(" + setup + ")";
	}

	ArgsGetPositionalArgsTest(const string &setup, const vector<const char*> &inArgs, const vector<string> &ref) : setup(setup), inArgs(inArgs), ref(ref) {}
};

class ArgsGetArgValueTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;
	char query;
	cfg::Item ref;

public:
	virtual void run() final override {
		cfg::Args args(setup);
		assertNotException(args.parse(inArgs.size(), inArgs.data()));

		assertTrue(args.isSet(query));
		
		auto item = args.getArgumentValue(query);
		assertEqual(item, ref, item.asString(), ref.asString());
	}

	virtual string name() const final override {
		return "ArgsGetArgValueTest(" + setup + ")";
	}

	ArgsGetArgValueTest(const string &setup, const vector<const char*> &inArgs, char query, const cfg::Item &ref) : setup(setup), inArgs(inArgs), query(query), ref(ref) {}
};

class ArgsGetArgValueFailTest : public Test {
private:
	string setup;
	vector<const char*> inArgs;
	char query;

public:
	virtual void run() final override {
		cfg::Args args(setup);
		assertNotException(args.parse(inArgs.size(), inArgs.data()));

		assertFalse(args.isSet(query));
	}

	virtual string name() const final override {
		return "ArgsGetArgValueFailTest(" + setup + ")";
	}

	ArgsGetArgValueFailTest(const string &setup, const vector<const char*> &inArgs, char query, const cfg::Item &ref) : setup(setup), inArgs(inArgs), query(query) {}
};

void assertCsvsEqual(const vector<vector<cfg::Item>> &out, const vector<vector<cfg::Item>> &ref) {
	assertEqual(out.size(), ref.size(), std::to_string(out.size()), std::to_string(ref.size()));
	for (unsigned i = 0; i < out.size(); i++) {
		inLoop(assertEqual(out[i].size(), ref[i].size(), std::to_string(out[i].size()), std::to_string(ref[i].size())), i);

		for (unsigned p = 0; p < out[i].size(); p++) {
			auto outi = out[i][p];
			auto refi = ref[i][p];

			inLoop(inLoop(assertEqual(outi, refi, outi.asString(), refi.asString()), p), i);
		}
	}
}

class CsvLoadFromFileTest : public Test {
private:
	string in;
	vector<vector<cfg::Item>> ref;

public:
	virtual void run() final override {
		vector<vector<cfg::Item>> out;
		assertNotException({
			out = cfg::Csv::loadFromFile(in);
		});

		assertCsvsEqual(out, ref);
	}

	virtual string name() const final override {
		return "CsvLoadFromFileTest(" + in + ")";
	}

	CsvLoadFromFileTest(const string &in, const vector<vector<cfg::Item>> &ref) : in(in), ref(ref) {}
};

class CsvLoadFromFileFailTest : public Test {
private:
	string in;
	string ref;

public:
	virtual void run() final override {
		assertExceptionWithMessage({
			auto csv = cfg::Csv::loadFromFile(in);
		}, cfg::CsvException, ref);
	}

	virtual string name() const final override {
		return "CsvLoadFromFileFailTest(" + in + ")";
	}

	CsvLoadFromFileFailTest(const string &in, const string &ref) : in(in), ref(ref) {}
};

class CsvLoadFromFilePedanticTest : public Test {
private:
	string in;
	vector<vector<cfg::Item>> ref;

public:
	virtual void run() final override {
		vector<vector<cfg::Item>> out;
		assertNotException({
			out = cfg::Csv::loadFromFile(in, true);
		});

		assertCsvsEqual(out, ref);
	}

	virtual string name() const final override {
		return "CsvLoadFromFilePedanticTest(" + in + ")";
	}

	CsvLoadFromFilePedanticTest(const string &in, const vector<vector<cfg::Item>> &ref) : in(in), ref(ref) {}
};

class CsvLoadFromFilePedanticFailTest : public Test {
private:
	string in;
	string ref;


public:
	virtual void run() final override {
		assertExceptionWithMessage({
			auto csv = cfg::Csv::loadFromFile(in, true);
		}, cfg::CsvException, ref);
	}

	virtual string name() const final override {
		return "CsvLoadFromFilePedanticFailTest(" + in + ")";
	}

	CsvLoadFromFilePedanticFailTest(const string &in, const string &ref) : in(in), ref(ref) {}
};

class CsvSaveToFileTest : public Test {
private:
	vector<vector<cfg::Item>> in;

public:
	virtual void run() final override {
		assertNotException({
			cfg::Csv::saveToFile(in, "tmp.csv");
		});
		
		vector<vector<cfg::Item>> out;
		assertNotException({
			out = cfg::Csv::loadFromFile("tmp.csv", true);
		});

		assertCsvsEqual(out, in);
	}

	virtual string name() const final override {
		return "CsvSaveToFileTest";
	}

	CsvSaveToFileTest(const vector<vector<cfg::Item>> &in) : in(in) {}
};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "ERROR: pathPrefix unspecified!" << std::endl;
		return 1;
	}
	
	std::string pathPrefix = argv[1];
	
	Testrunner runner({
		new ItemInitTest<const char*>(std::string("hello world").c_str(), "hello world"),
		new ItemInitTest<std::string>("hello world", "hello world"),
		new ItemInitTest<bool>(true, "1"),
		new ItemInitTest<bool>(false, "0"),
		new ItemInitTest<int>(268374, "268374"),
		new ItemInitTest<long>(2061728394, "2061728394"),
		new ItemInitTest<float>(42.69f, "42.689999"),
		new ItemAssignTest<const char*>(std::string("hello world").c_str(), "hello world"),
		new ItemAssignTest<std::string>("hello world", "hello world"),
		new ItemAssignTest<bool>(true, "1"),
		new ItemAssignTest<bool>(false, "0"),
		new ItemAssignTest<int>(268374, "268374"),
		new ItemAssignTest<long>(2061728394, "2061728394"),
		new ItemAssignTest<float>(42.69f, "42.689999"),
		// const char * | anything
		new ItemEqualTest<const char*, const char*>(std::string("hello world").c_str(), std::string("hello world").c_str()),
		new ItemEqualTest<const char*, std::string>(std::string("hello world").c_str(), "hello world"),
		new ItemEqualTest<const char*, bool>(std::string("").c_str(), false),
		new ItemEqualTest<const char*, bool>(std::string("0").c_str(), false),
		new ItemEqualTest<const char*, bool>(std::string("false").c_str(), false),
		new ItemEqualTest<const char*, bool>(std::string("False").c_str(), false),
		new ItemEqualTest<const char*, bool>(std::string("FALSE").c_str(), false),
		new ItemEqualTest<const char*, bool>(std::string("anything").c_str(), true),
		new ItemEqualTest<const char*, int>(std::string("123456").c_str(), 123456),
		new ItemEqualTest<const char*, long>(std::string("2061728394").c_str(), 2061728394L),
		new ItemEqualTest<const char*, float>(std::string("42.689999").c_str(), 42.69f),
		// std::string | anything
		new ItemEqualTest<std::string, const char*>("hello world", std::string("hello world").c_str()),
		new ItemEqualTest<std::string, std::string>("hello world", "hello world"),
		new ItemEqualTest<std::string, bool>("", false),
		new ItemEqualTest<std::string, bool>("0", false),
		new ItemEqualTest<std::string, bool>("false", false),
		new ItemEqualTest<std::string, bool>("False", false),
		new ItemEqualTest<std::string, bool>("FALSE", false),
		new ItemEqualTest<std::string, bool>("anything", true),
		new ItemEqualTest<std::string, int>("123456", 123456),
		new ItemEqualTest<std::string, long>("2061728394", 2061728394L),
		new ItemEqualTest<std::string, float>("42.689999", 42.69f),
		// bool | anything
		new ItemEqualTest<bool, const char *>(true, std::string("1").c_str()),
		new ItemEqualTest<bool, const char *>(false, std::string("0").c_str()),
		new ItemEqualTest<bool, std::string>(true, "1"),
		new ItemEqualTest<bool, std::string>(false, "0"),
		new ItemEqualTest<bool, bool>(true, true),
		new ItemEqualTest<bool, bool>(false, false),
		new ItemEqualTest<bool, int>(true, 1),
		new ItemEqualTest<bool, int>(false, 0),
		new ItemEqualTest<bool, long>(true, 1),
		new ItemEqualTest<bool, long>(false, 0),
		new ItemEqualTest<bool, float>(true, 1.f),
		new ItemEqualTest<bool, float>(false, 0.f),
		// int | anything
		new ItemEqualTest<int, const char*>(123456, std::string("123456").c_str()),
		new ItemEqualTest<int, std::string>(123456, "123456"),
		new ItemEqualTest<int, bool>(10, true),
		new ItemEqualTest<int, bool>(0, false),
		new ItemEqualTest<int, int>(123456, 123456),
		new ItemEqualTest<int, long>(123456, 123456),
		new ItemEqualTest<int, float>(123456, 123456.0f),
		// long | anything
		new ItemEqualTest<long, const char*>(123456, std::string("123456").c_str()),
		new ItemEqualTest<long, std::string>(123456, "123456"),
		new ItemEqualTest<long, bool>(10, true),
		new ItemEqualTest<long, bool>(0, false),
		new ItemEqualTest<long, int>(123456, 123456),
		new ItemEqualTest<long, long>(123456, 123456),
		new ItemEqualTest<long, float>(123456, 123456.0f),
		// float | anything
		new ItemEqualTest<float, const char*>(42.69f, std::string("42.689999").c_str()),
		new ItemEqualTest<float, std::string>(42.69f, "42.689999"),
		new ItemEqualTest<float, bool>(42.69f, true),
		new ItemEqualTest<float, bool>(0.f, false),
		new ItemEqualTest<float, int>(2.2f, 2),
		new ItemEqualTest<float, long>(2061728394.2f, 2061728384L),
		new ItemEqualTest<float, float>(2061728394.2f, 2061728394.2f),
		// IniManualInitTest
		new IniManualInitTest({}),
		new IniManualInitTest({
			{"root", cfg::IniSection()}
		}),
		new IniManualInitTest({
			{"root", cfg::IniSection({
				{"key", cfg::Item("value")}
			})}
		}),
		new IniManualInitTest({
			{"root", cfg::IniSection({
				{"key", cfg::Item("value")},
				{"key2", cfg::Item("value2")},
			})},
			{"otherSection", cfg::IniSection({
				{"key", cfg::Item(3)},
				{"key3", cfg::Item(false)},
			})}
		}),
		// IniLoadFromFileTest
		new IniLoadFromFileTest(pathPrefix + "/iniOk0.ini", {
			{"root", cfg::IniSection({
				{"key1", cfg::Item("value1")}
			})},
			{"section", cfg::IniSection({
				{"key2", cfg::Item("value2")},
				{"key3", cfg::Item(10)},
				{"key4", cfg::Item("false")}
			})}
		}),
		new IniLoadFromFileTest(pathPrefix + "/iniOk1.ini", {
			{"root", cfg::IniSection({
				{"key1", cfg::Item()}
			})}
		}),
		new IniLoadFromFileFailTest(pathPrefix + "/iniFail0.ini"),
		new IniLoadFromFileFailTest(pathPrefix + "/iniFail1.ini"),
		new IniLoadFromFileFailTest(pathPrefix + "/iniFail2.ini"),
		// IniSaveToFileTest
		new IniSaveToFileTest(pathPrefix + "/iniOk0.ini"),
		new IniSaveToFileTest(pathPrefix + "/iniOk1.ini"),
		// ArgsSetupArgumentsTest
		new ArgsSetupArgumentsTest("h"),
		new ArgsSetupArgumentsTest("h:"),
		new ArgsSetupArgumentsTest("h!"),
		new ArgsSetupArgumentsTest("hg"),
		new ArgsSetupArgumentsTest("h:g:"),
		new ArgsSetupArgumentsTest("h!g!"),
		new ArgsSetupArgumentsTest("hg:i!"),
		// ArgsSetupArgumentsFailTest
		new ArgsSetupArgumentsFailTest("h?"),
		new ArgsSetupArgumentsFailTest(""),
		// ArgsParseTest
		new ArgsParseTest("h", {"progname"}),
		new ArgsParseTest("hc:", {"progname"}),
		new ArgsParseTest("hc:", {"progname", "-h"}),
		new ArgsParseTest("hc:", {"progname", "-c", "value"}),
		new ArgsParseTest("m!", {"progname", "-m", "value"}),
		new ArgsParseTest("m!vc:", {"progname", "-m", "value"}),
		new ArgsParseTest("m!vc:", {"progname", "-m", "value", "-c", "value2"}),
		// ArgsParseFailTest
		new ArgsParseFailTest("c:", {"progname", "-c"}),
		new ArgsParseFailTest("m!", {"progname"}),
		new ArgsParseFailTest("h", {"progname", "-c"}),
		// ArgsIsSetTest
		new ArgsIsSetTest("h", {"progname", "-h"}, {'h'}),
		new ArgsIsSetTest("hc:", {"progname", "-h"}, {'h'}),
		new ArgsIsSetTest("hc:", {"progname", "-c", "value", "-h"}, {'h', 'c'}),
		new ArgsIsSetTest("m!", {"progname", "-m", "value"}, {'m'}),
		// ArgsIsSetFailTest
		new ArgsIsSetFailTest("m!", {"progname", "-m", "value"}, {'h'}),
		new ArgsIsSetFailTest("hc:", {"progname", "-c", "value", "-h"}, {'H', 'C'}),
		// ArgsGetPositionalArgumentsTest
		new ArgsGetPositionalArgsTest("h", {"progname", "-h"}, {}),
		new ArgsGetPositionalArgsTest("p", {"progname", "-p", "ehlo"}, {"ehlo"}),
		new ArgsGetPositionalArgsTest("h:", {"progname", "-h", "ehlo"}, {}),
		new ArgsGetPositionalArgsTest("h:", {"progname", "-h", "ehlo", "helo"}, {"helo"}),
		new ArgsGetPositionalArgsTest("h:", {"progname", "helo", "-h", "ehlo"}, {"helo"}),
		// ArgsGetArgValueTest
		new ArgsGetArgValueTest("h:", {"progname", "-h", "10"}, 'h', 10),
		new ArgsGetArgValueTest("d!", {"progname", "-d", "ehlo"}, 'd', "ehlo"),
		// ArgsGetArgValueFailTest
		new ArgsGetArgValueFailTest("h:", {"progname"}, 'h', 10),
		// CsvLoadFromFileTest
		new CsvLoadFromFileTest(pathPrefix + "/test0.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test1.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test2.csv", {
			{"aaa", "bbb", "cc\nc"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test3.csv", {
			{"aaa", "bbb", "cc,c"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test4.csv", {
			{"aaa", "bbb", "cc\"c"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test5.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"},
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test6.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee"}
		}),
		new CsvLoadFromFileTest(pathPrefix + "/test7.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff", "ggg"}
		}),
		// CsvLoadFromFileFailTest
		new CsvLoadFromFileFailTest(pathPrefix + "/test8.csv", "Invalid '\"' character at position: 6"),
		new CsvLoadFromFileFailTest(pathPrefix + "/test9.csv", "Invalid non-delimiter, non-newline character followed after closing quote at position: 9"),
		// CsvLoadFromFilePedanticTest
		new CsvLoadFromFilePedanticTest(pathPrefix + "/test0.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFilePedanticTest(pathPrefix + "/test1.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFilePedanticTest(pathPrefix + "/test2.csv", {
			{"aaa", "bbb", "cc\nc"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFilePedanticTest(pathPrefix + "/test3.csv", {
			{"aaa", "bbb", "cc,c"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFilePedanticTest(pathPrefix + "/test4.csv", {
			{"aaa", "bbb", "cc\"c"}, {"ddd", "eee", "fff"}
		}),
		new CsvLoadFromFilePedanticTest(pathPrefix + "/test5.csv", {
			{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"}
		}),
		// CsvLoadFromFilePedanticFailTest
		new CsvLoadFromFilePedanticFailTest(pathPrefix + "/test6.csv", "loadFromFile: Rows do not have the same number of columns and pedantic flag has been set"),
		new CsvLoadFromFilePedanticFailTest(pathPrefix + "/test7.csv", "loadFromFile: Rows do not have the same number of columns and pedantic flag has been set"),
		// CsvSaveToFileTest
		new CsvSaveToFileTest({{"aaa", "bbb", "ccc"}, {"ddd", "eee", "fff"}}),
		new CsvSaveToFileTest({{"aaa", "bbb", "cc\nc"}, {"ddd", "eee", "fff"}}),
		new CsvSaveToFileTest({{"aaa", "bbb", "cc,c"}, {"ddd", "eee", "fff"}}),
		new CsvSaveToFileTest({{"aaa", "bbb", "cc\"c"}, {"ddd", "eee", "fff"}}),
	});

	return runner.evaluateTestcases(true, true);
}