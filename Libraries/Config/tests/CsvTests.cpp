#include <catch.hpp>
#include <iostream>
#include "../Config.hpp"
#include "Helper.hpp"

const std::string TEST_FILE_PATH = "test.csv";

TEST_CASE("cfg::Csv::loadFromFile OK", "[Csv]") {
	std::string blob = GENERATE(as<std::string>{}, 
		"aaa,bbb,ccc\nddd,eee,fff",
		"aaa,bbb,ccc\nddd,eee,fff\n",
		"\"aaa\",\"bbb\",\"ccc\"\n\"ddd\",\"eee\",\"fff\"",
		"\"aaa\",\"bbb\",\"cc\nc\"\n\"ddd\",\"eee\",\"fff\"",
		"\"aaa\",\"bbb\",\"cc,c\"\n\"ddd\",\"eee\",\"fff\"",
		"\"aaa\",\"bbb\",\"cc\"\"c\"\n\"ddd\",\"eee\",\"fff\""
	);

	SECTION("OK") {
		bool pedantic = GENERATE(true, false);

		try {
			Helper::writeFile(TEST_FILE_PATH, blob);
			cfg::Csv::loadFromFile(TEST_FILE_PATH, pedantic);
			REQUIRE(true);
		} catch (...) {
			REQUIRE(false);
		}
	}
}

TEST_CASE("cfg::Csv::loadFromFile FAIL", "[Csv]") {
	std::string blob = GENERATE(as<std::string>{}, 
		"aaa,bb\"b",
		"aaa,\"bbb\"e"
	);

	SECTION("FAIL") {
		try {
			Helper::writeFile(TEST_FILE_PATH, blob);
			cfg::Csv::loadFromFile(TEST_FILE_PATH);
			REQUIRE(false);
		} catch (...) { REQUIRE(true); }
	}
}

TEST_CASE("cfg::Csv::loadFromFile pedantic FAIL") {
	std::string blob = GENERATE(as<std::string>{}, 
		"aaa,bbb,ccc\nddd,eee,fff,ggg\n",
		"aaa,bbb,ccc\nddd,eee\n"
	);

	SECTION("FAIL") {
		const bool PEDANTIC = true;

		try {
			Helper::writeFile(TEST_FILE_PATH, blob);
			cfg::Csv::loadFromFile(TEST_FILE_PATH, PEDANTIC);
			REQUIRE(false);
		} catch (...) { REQUIRE(true); }
	}
}

TEST_CASE("cfg::Csv::loadFromFile items match + saveToFile", "[Csv]") {
	std::string blob;
	std::string thirdItem;

	SECTION("Create TEST_FILE_PATH") {
		int mode = GENERATE(0, 1);

		SECTION("Only data") {
			blob = "aaa,bbb,ccc\nddd,eee,fff";
			thirdItem = "ccc";
		}

		SECTION("Data with endl symbol") {
			blob = "\"aaa\",\"bbb\",\"cc\nc\"\n\"ddd\",\"eee\",\"fff\"";
			thirdItem = "cc\nc";
		}

		SECTION("Data with escape symbol") {
			blob = "\"aaa\",\"bbb\",\"cc\"\"c\"\n\"ddd\",\"eee\",\"fff\"";
			thirdItem = "cc\"c";
		}

		SECTION("Data with delimiter symbol") {
			blob = "\"aaa\",\"bbb\",\"cc,c\"\n\"ddd\",\"eee\",\"fff\"";
			thirdItem = "cc,c";
		}

		// Create file at TEST_FILE_PATH based on mode
		if (mode == 0) {
			Helper::writeFile(TEST_FILE_PATH, blob);
		}
		else {
			std::vector<std::vector<cfg::Item>> csvData = {
				{"aaa", "bbb", thirdItem},
				{"ddd", "eee", "fff"}
			};

			cfg::Csv::saveToFile(csvData, TEST_FILE_PATH);
		}
	}

	auto csv = cfg::Csv::loadFromFile(TEST_FILE_PATH);

	REQUIRE(csv.size() == 2);
	REQUIRE(csv[0].size() == 3);
	REQUIRE(csv[1].size() == 3);
	REQUIRE(csv[0][0] == "aaa");
	REQUIRE(csv[0][1] == "bbb");
	REQUIRE(csv[0][2] == thirdItem);
	REQUIRE(csv[1][0] == "ddd");
	REQUIRE(csv[1][1] == "eee");
	REQUIRE(csv[1][2] == "fff");
}
