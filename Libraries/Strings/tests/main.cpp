#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../Strings.hpp"

TEST_CASE("Strings::split", "[Strings]") {
	SECTION("Empty vector") {
		auto vec = Strings::split(';', "");
		REQUIRE(vec.size() == 0);
	}

	SECTION("No cut") {
		auto vec = Strings::split(';', "lorem ipsum");
		REQUIRE(vec.size() == 1);
		REQUIRE(vec[0] == "lorem ipsum");
	}

	SECTION("Standard cut") {
		auto vec = Strings::split(' ', "lorem ipsum dolor sit amet");
		REQUIRE(vec.size() == 5);
		REQUIRE(vec[0] == "lorem");
		REQUIRE(vec[1] == "ipsum");
		REQUIRE(vec[2] == "dolor");
		REQUIRE(vec[3] == "sit");
		REQUIRE(vec[4] == "amet");
	}
}

TEST_CASE("Strings::replaceAll", "[Strings]") {
	REQUIRE(Strings::replaceAllCopy("abc", "b", "") == "ac");
	REQUIRE(Strings::replaceAllCopy("abc", "x", "") == "abc");
	REQUIRE(Strings::replaceAllCopy("aaa", "a", "aa") == "aaaaaa");
	REQUIRE(Strings::replaceAllCopy("abc", "b", "x") == "axc");
}

TEST_CASE("Strings::trim", "[Strings]") {
	REQUIRE(Strings::trimCopy("abc") == "abc");
	REQUIRE(Strings::trimCopy(" abc ") == "abc");
	REQUIRE(Strings::trimCopy("\t\n \tabc") == "abc");
	REQUIRE(Strings::trimCopy("abc\t\n \t") == "abc");
}

TEST_CASE("Strings::isPrefixOf", "[Strings]") {
	REQUIRE(Strings::isPrefixOf("a", "aaa"));
	REQUIRE(Strings::isPrefixOf("abc", "abcdef"));
	REQUIRE(!Strings::isPrefixOf("abc", "fedcba"));
}

TEST_CASE("Strings::encodeToBase64", "[Strings]") {
	REQUIRE(
		Strings::encodeToBase64("abc") == "YWJj"
	);

	REQUIRE(
		Strings::encodeToBase64("Man is distinguished, not only by his reason, but ")
		== "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCA="
	);
}

TEST_CASE("Strings::decodeFromBase64", "[Strings]") {
	SECTION("Valid inputs") {
		REQUIRE(
			Strings::decodeFromBase64("TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCA=")
			== "Man is distinguished, not only by his reason, but "
		);

		// No padding
		REQUIRE(
			Strings::decodeFromBase64("TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCA")
			== "Man is distinguished, not only by his reason, but "
		);
	}

	SECTION("Invalid inputs") {
		try {
			Strings::decodeFromBase64("InvalidChars!");
			REQUIRE(false);
		} catch (...) { REQUIRE(true); }
	}
}