#include <catch.hpp>
#include "../Config.hpp"

TEST_CASE("Item init", "[Item]") {
	SECTION("const char*") {
		cfg::Item item(std::string("hello world").c_str());

		REQUIRE(item.asString() == "hello world");
	}

	SECTION("std::string") {
		cfg::Item item("hello world");

		REQUIRE(item.asString() == "hello world");
	}

	SECTION("bool") {
		REQUIRE(cfg::Item(true).asString() == "1");
		REQUIRE(cfg::Item(false).asString() == "0");
	}

	SECTION("int, long") {
		REQUIRE(cfg::Item(268374).asString() == "268374");
		REQUIRE(cfg::Item(2061728394L).asString() ==  "2061728394");
	}

	SECTION("float") {
		REQUIRE(cfg::Item(42.69f).asString() == "42.689999");
	}
}

TEST_CASE("Item assign", "[Item]") {
	cfg::Item item;

	SECTION("const char*") {
		item = std::string("hello world").c_str();
		REQUIRE(item.asString() == "hello world");
	}

	SECTION("std::string") {
		item = "hello world";
		REQUIRE(item.asString() == "hello world");
	}

	SECTION("bool") {
		item = true;
		REQUIRE(item.asString() == "1");

		item = false;
		REQUIRE(item.asString() == "0");
	}

	SECTION("int, long") {
		item = 268374;
		REQUIRE(item.asString() == "268374");

		item = 2061728394L;
		REQUIRE(item.asString() ==  "2061728394");
	}

	SECTION("float") {
		item = 42.69f;
		REQUIRE(item.asString() == "42.689999");
	}
}

TEST_CASE("Item equal", "[Item]") {
	cfg::Item item;

	SECTION("const char*") {
		item = std::string("hello world").c_str();
		REQUIRE(item == std::string("hello world").c_str());
		REQUIRE(item == "hello world");

		item = std::string("").c_str();
		REQUIRE(item == false);
		item = std::string("0").c_str();
		REQUIRE(item == false);
		item = std::string("false").c_str();
		REQUIRE(item == false);
		item = std::string("False").c_str();
		REQUIRE(item == false);
		item = std::string("FALSE").c_str();
		REQUIRE(item == false);
		item = std::string("anything").c_str();
		REQUIRE(item == true);

		item = std::string("123456").c_str();
		REQUIRE(item == 123456);

		item = std::string("2061728394").c_str();
		REQUIRE(item == 2061728394L);

		item = std::string("42.689999").c_str();
		REQUIRE(item == 42.69f);
	}

	SECTION("std::string") {
		item = "hello world";
		REQUIRE(item == std::string("hello world").c_str());
		REQUIRE(item == "hello world");

		item = "";
		REQUIRE(item == false);
		item = "0";
		REQUIRE(item == false);
		item = "false";
		REQUIRE(item == false);
		item = "False";
		REQUIRE(item == false);
		item = "FALSE";
		REQUIRE(item == false);
		item = "anything";
		REQUIRE(item == true);

		item = "123456";
		REQUIRE(item == 123456);

		item = "2061728394";
		REQUIRE(item == 2061728394L);

		item = "42.689999";
		REQUIRE(item == 42.69f);
	}

	SECTION("bool") {
		item = true;
		REQUIRE(item == std::string("1").c_str());
		REQUIRE(item == "1");
		REQUIRE(item == true);
		REQUIRE(item == 1);
		REQUIRE(item == 1L);
		REQUIRE(item == 1.f);

		item = false;
		REQUIRE(item == std::string("0").c_str());
		REQUIRE(item == "0");
		REQUIRE(item == false);
		REQUIRE(item == 0);
		REQUIRE(item == 0L);
		REQUIRE(item == 0.f);
	}

	SECTION("int") {
		item = 123456;
		REQUIRE(item == std::string("123456").c_str());
		REQUIRE(item == "123456");
		REQUIRE(item == true);
		REQUIRE(item == 123456);
		REQUIRE(item == 123456L);
		REQUIRE(item == 123456.f);

		item = 0;
		REQUIRE(item == false);
	}

	SECTION("long") {
		item = 123456L;
		REQUIRE(item == std::string("123456").c_str());
		REQUIRE(item == "123456");
		REQUIRE(item == true);
		REQUIRE(item == 123456);
		REQUIRE(item == 123456L);
		REQUIRE(item == 123456.f);

		item = 0L;
		REQUIRE(item == false);
	}

	SECTION("float") {
		item = 42.69f;
		REQUIRE(item == std::string("42.689999").c_str());
		REQUIRE(item == "42.689999");
		REQUIRE(item == true);
		REQUIRE(item == 42);
		REQUIRE(item == 42.69f);

		item = 2061728394.2f;
		REQUIRE(item == 2061728384L);
		REQUIRE(item == 2061728394.2f);

		item = 0.f;
		REQUIRE(item == false);
	}
}