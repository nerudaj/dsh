#include <catch.hpp>
#include "../Config.hpp"
#include <fstream>

const std::string TEST_FILE_PATH = "test.ini";

void writeFile(const std::string &path, const std::string &blob) {
	std::ofstream save(path);
	save.write(blob.c_str(), blob.size());
	save.close();
	save.clear();
}

TEST_CASE("cfg::Ini::loadFromFile", "[Ini]") {
	cfg::Ini ini;

	SECTION("OK 1") {
		std::string blob = "key1=";

		writeFile(TEST_FILE_PATH, blob);
		ini.loadFromFile(TEST_FILE_PATH);

		// Following does not work
		// REQUIRE_NOTHROW([&]() { writeFile(TEST_FILE_PATH, blob); });
		// REQUIRE_NOTHROW([&] () { ini.loadFromFile(TEST_FILE_PATH); });

		REQUIRE(ini["root"].hasKey("key1"));
		REQUIRE(ini["root"]["key1"] == "");
	}

	SECTION("OK 2") {
		std::string blob = "key1=value1\n\n[section]\nkey2=value2\nkey3=10\nkey4=false";

		writeFile(TEST_FILE_PATH, blob);
		ini.loadFromFile(TEST_FILE_PATH);

		// Following does not work
		// REQUIRE_NOTHROW([&]() { writeFile(TEST_FILE_PATH, blob); });
		// REQUIRE_NOTHROW([&] () { ini.loadFromFile(TEST_FILE_PATH); });

		REQUIRE(ini["root"].hasKey("key1"));
		REQUIRE(ini["root"]["key1"] == "value1");

		REQUIRE(ini.hasSection("section"));
		REQUIRE(ini["section"].hasKey("key2"));
		REQUIRE(ini["section"].hasKey("key3"));
		REQUIRE(ini["section"].hasKey("key4"));

		REQUIRE(ini["section"]["key2"] == "value2");
		REQUIRE(ini["section"]["key3"] == 10);
		REQUIRE(ini["section"]["key4"] == false);
	}

	SECTION("Fails") {
		std::string blob = GENERATE(as<std::string>{}, 
			"key1=value1\n\n[section\nkey2=value2\nkey3=10\nkey4=false",
			"key1=value1\n\n[section]\nkey2=value2\nkey3;10\nkey4=false",
			"value1"
		);

		writeFile(TEST_FILE_PATH, blob);
		try {
			ini.loadFromFile(TEST_FILE_PATH);
			REQUIRE(false);
		}
		catch (...) {}

		// Following does not work:
		//REQUIRE_NOTHROW([&]() { writeFile(TEST_FILE_PATH, blob); });
		//REQUIRE_THROWS([&]() { ini.loadFromFile(TEST_FILE_PATH); });
	}
}

TEST_CASE("cfg::Ini::saveToFile", "[Ini]") {
	cfg::Ini ini;
	ini["root"]["key1"] = "value1";
	ini["section"]["key2"] = "value2";

	ini.saveToFile(TEST_FILE_PATH);

	cfg::Ini ini2;
	ini2.loadFromFile(TEST_FILE_PATH);

	REQUIRE(ini2["root"].hasKey("key1"));
	REQUIRE(ini2["section"].hasKey("key2"));
	REQUIRE(ini2["root"]["key1"] == "value1");
	REQUIRE(ini2["section"]["key2"] == "value2");
}