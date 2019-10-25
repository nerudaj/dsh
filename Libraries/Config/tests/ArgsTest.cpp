#include <catch.hpp>
#include "../Config.hpp"

TEST_CASE("Args::setupArguments", "[Args]") {
	cfg::Args args;

	SECTION("Passing") {
		auto setup = GENERATE("h", "h:", "h!", "hg", "h:g:", "h!g!", "hg:i!");
		REQUIRE_NOTHROW(args.setupArguments(setup);
	}

	SECTION("Failing") {
		auto setup = GENERATE("h?", "");
		REQUIRE_THROWS(args.setupArguments(setup);
	}
}

/*
// ArgsParseFailTest
new ArgsParseFailTest("c:", {"progname", "-c"}),
new ArgsParseFailTest("m!", {"progname"}),
new ArgsParseFailTest("h", {"progname", "-c"}),
*/

TEST_CASE("Args::parse", "[Args]") {
	std::vector<std::string> setups = {"h", "hc:", "hc:", "hc:", "m!", "m!vc:", "m!vc:"};
	std::vector<std::vector<std::string>> argSetups = {
		{"progname"},
		{"progname"},
		{"progname", "-h"},
		{"progname", "-c", "value"},
		{"progname", "-m", "value"},
		{"progname", "-m", "value"},
		{"progname", "-m", "value", "-c", "value2"}
	};

	SECTION("Passing") {
		auto i = GENERATE(0, 1, 2, 3, 4, 5, 6);
		cfg::Args args(setups[i]);
		REQUIRE_NOTHROW(args.parse(argSetups[i]));
	}

	SECTION("Failing") {
		
	}
}