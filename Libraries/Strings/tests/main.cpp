#include <Test.hpp>
#include "../Strings.hpp"

using std::string;
using std::vector;

#define tostr(s) std::to_string(s)

class TestStringSplit : public Test {
private:
	char delim;
	string in;
	vector<string> ref;

public:
	virtual void run() final override {
		auto out = Strings::split(delim, in);

		assertTrue(ref.size() == out.size(), 
			"Size mismatch! Ref " + tostr(ref.size()) + 
			", out = " + tostr(out.size())
		);

		for (unsigned i = 0; i < out.size(); i++) {
			assertTrue(ref[i] == out[i],
				"Value mismatch at index " + tostr(i) + "! Ref = " + ref[i] + 
				", out = " + out[i]
			);
		}
	}

	virtual string name() const final override {
		return "TestStringSplit";
	}

	TestStringSplit(char delim, const string &in, const vector<string> &ref) : delim(delim), in(in), ref(ref) {}
};

class TestStringReplaceAll : public Test {
private:
	string in;
	string from;
	string to;
	string ref;

public:
	virtual void run() final override {
		auto out = Strings::replaceAllCopy(in, from, to);

		assertTrue(out == ref, 
			"Value mismatch!, Ref = " + ref + ", out = " + out
		);
	}

	virtual string name() const final override {
		return "TestStringReplaceAll";
	}

	TestStringReplaceAll(const string &in, const string &from, const string &to, const string &ref) : in(in), from(from), to(to), ref(ref) {}
};

class TestStringTrim : public Test {
private:
	string in;
	string ref;

public:
	virtual void run() final override {
		auto out = Strings::trimCopy(in);

		assertTrue(out == ref, 
			"Value mismatch!, Ref = " + ref + ", out = " + out
		);
	}

	virtual string name() const final override {
		return "TestStringTrim";
	}

	TestStringTrim(const string &in, const string &ref) : in(in), ref(ref) {}
};

class TestStringIsPrefixOf : public Test {
private:
	string prefix;
	string str;

public:
	virtual void run() final override {
		assertTrue(Strings::isPrefixOf(prefix, str), 
			"Not prefix of!"
		);
	}

	virtual string name() const final override {
		return "TestStringIsPrefixOf";
	}

	TestStringIsPrefixOf(const string &prefix, const string &str) : prefix(prefix), str(str) {}
};

class TestStringIsNotPrefixOf : public Test {
private:
	string prefix;
	string str;

public:
	virtual void run() final override {
		assertFalse(Strings::isPrefixOf(prefix, str), 
			"Is prefix of!"
		);
	}

	virtual string name() const final override {
		return "TestStringIsNotPrefixOf";
	}

	TestStringIsNotPrefixOf(const string &prefix, const string &str) : prefix(prefix), str(str) {}
};

int main() {
	Testrunner runner({
		new TestStringSplit(';', "", {}),
		new TestStringSplit(';', "lorem ipsum", {"lorem ipsum"}),
		new TestStringSplit(' ', "lorem ipsum dolor sit amet", {"lorem", "ipsum", "dolor", "sit", "amet"}),
		new TestStringReplaceAll("abc", "b", "", "ac"),
		new TestStringReplaceAll("abc", "", "x", "abc"),
		new TestStringReplaceAll("aaa", "a", "aa", "aaaaaa"),
		new TestStringReplaceAll("abc", "b", "x", "axc"),
		new TestStringTrim("abc", "abc"),
		new TestStringTrim(" abc ", "abc"),
		new TestStringTrim("\t\n \tabc", "abc"),
		new TestStringTrim("abc\t\n \t", "abc"),
		new TestStringIsPrefixOf("a", "aaa"),
		new TestStringIsPrefixOf("abc", "abcdef"),
		new TestStringIsNotPrefixOf("abc", "defabc")
	});

	return runner.evaluateTestcases(true);
}