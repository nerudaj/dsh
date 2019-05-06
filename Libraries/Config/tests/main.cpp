#include <iostream>
#include <Test.hpp>
#include "../Config.hpp"
#include <typeinfo>

using std::string;

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
		assertTrue(ini.loadFromFile(filename));
		
		compareIniToReferenceMap(ini, ref);
	}
	
	virtual string name() const {
		return "IniLoadFromFileTest(" + filename + ")";
	}
	
	IniLoadFromFileTest(const std::string &filename, const std::map<string, cfg::IniSection> &ref) : filename(filename), ref(ref) {}
};

};

int main() {
	/*std::vector<TestCase*> cases = {
		new TestLoadValidCSV("tests/test0.csv"),
		new TestLoadValidCSV("tests/test1.csv"),
		new TestLoadValidCSV("tests/test2.csv"),
		new TestLoadValidCSV("tests/test3.csv"),
		new TestLoadValidCSV("tests/test4.csv"),
		new TestLoadValidCSV("tests/test5.csv"),
		new TestLoadValidCSV("tests/test6.csv"),
		new TestLoadValidCSV("tests/test7.csv"),
		new TestValidCSVData("tests/test0.csv", {
			{"aaa", "bbb", "ccc"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test1.csv", {
			{"aaa", "bbb", "ccc"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test2.csv", {
			{"aaa", "bbb", "cc\nc"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test3.csv", {
			{"aaa", "bbb", "cc,c"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test4.csv", {
			{"aaa", "bbb", "cc\"c"}, { "ddd", "eee", "fff" }
		}),
		new TestLoadValidIni("tests/test0.ini"),
		new TestLoadInvalidIni("tests/test1.ini"),
		new TestLoadInvalidIni("tests/test2.ini"),
		new TestLoadInvalidIni("tests/test4.ini"),
		new TestValidIniData("tests/test0.ini", {
			{ "root", {
				{ "key1", "value1" }
			}},
			{ "section", {
				{ "key2", "value2"},
				{ "key3", "10" },
				{ "key4", "false" }
			}}
		}),
		new TestValidIniData("tests/test3.ini", {
			{ "root", {
				{ "key1", "" }
			}}
		})
	};*/

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
		new IniLoadFromFileTest("../tests/iniOk0.ini", {
			{"root", cfg::IniSection({
				{"key1", cfg::Item("value1")}
			})},
			{"section", cfg::IniSection({
				{"key2", cfg::Item("value2")},
				{"key3", cfg::Item(10)},
				{"key4", cfg::Item("false")}
			})}
		}),
		new IniLoadFromFileTest("../tests/iniOk1.ini", {
			{"root", cfg::IniSection({
				{"key", cfg::Item()}
			})}
		}),
	});

	return runner.evaluateTestcases(true);
}