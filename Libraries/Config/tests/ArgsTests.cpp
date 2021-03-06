#include <catch.hpp>
#include "../Config.hpp"

TEST_CASE("Args::setupArguments", "[Args]") {
	cfg::Args args;

	SECTION("Passing") {
		auto setup = GENERATE(as<std::string>{}, "h", "h:", "hg", "h:g:");

		REQUIRE_NOTHROW([&](){
			args.setupArguments(setup);
		});
	}

	SECTION("Failing") {
		auto setup = GENERATE(as<std::string>{}, "h?", "h!", "");

		try {
			args.setupArguments(setup);
			REQUIRE(false);
		} catch (...) {}
		/* Following does not work:
		REQUIRE_THROWS([&](){
			args.setupArguments(setup);
		});*/
	}
}

TEST_CASE("Args::parse passing", "[Args]") {
	cfg::Args args;
	std::vector<std::string> setups = {"h", "hc:", "hc:", "hc:"};
	std::vector<std::vector<const char *>> argSetups = {
		{"progname"},
		{"progname"},
		{"progname", "-h"},
		{"progname", "-c", "value"}
	};

	REQUIRE(setups.size() == argSetups.size());

	SECTION("Passing") {
		auto i = GENERATE_COPY(range(unsigned(0), unsigned(setups.size())));

		REQUIRE_NOTHROW([&](){
			args.setupArguments(setups[i]);
			args.parse(argSetups[i].size(), argSetups[i].data());
		});
	}
}

TEST_CASE("Args::parse failing", "[Args]") {
	cfg::Args args;
	std::vector<std::string> setups = {"c:", "h"};
	std::vector<std::vector<const char *>> argSetups = {
		{"progname", "-c"},
		{"progname", "-c"}
	};

	REQUIRE(setups.size() == argSetups.size());

	SECTION("Failing") {
		auto i = GENERATE_COPY(range(unsigned(0), unsigned(setups.size())));

		try {
			args.setupArguments(setups[i]);
			args.parse(argSetups[i].size(), argSetups[i].data());
			REQUIRE(false);
		} catch(...) {}
		/* Following does not work:
		REQUIRE_THROWS([&](){
			args.setupArguments(setups[i]);
			args.parse(argSetups[i].size(), argSetups[i].data());
		});*/
	}
}

TEST_CASE("Args::isSet passing", "[Args]") {
	cfg::Args args;
	std::vector<std::string> setups = {"h", "hc:", "hc:"};
	std::vector<std::vector<const char *>> argSetups = {
		{"progname", "-h"},
		{"progname", "-h"},
		{"progname", "-c", "value", "-h"}
	};
	std::vector<std::vector<char>> queries = {
		{'h'},
		{'h'},
		{'h', 'c'}
	};

	REQUIRE(setups.size() == argSetups.size());
	REQUIRE(setups.size() == queries.size());

	SECTION("Passing") {
		auto i = GENERATE_COPY(range(unsigned(0), unsigned(setups.size())));

		//REQUIRE_NOTHROW([&](){
			args.setupArguments(setups[i]);
			args.parse(argSetups[i].size(), argSetups[i].data());
		//});

		for (auto query : queries[i]) {
			REQUIRE(args.isSet(query));
		}
	}
}

TEST_CASE("Args::isSet failing", "[Args]") {
	cfg::Args args;
	std::vector<std::string> setups = {"hc:"};
	std::vector<std::vector<const char *>> argSetups = {
		{"progname", "-c", "value", "-h"}
	};
	std::vector<std::vector<char>> queries = {
		{'H', 'C'}
	};

	REQUIRE(setups.size() == argSetups.size());
	REQUIRE(setups.size() == queries.size());

	SECTION("Failing") {
		auto i = GENERATE_COPY(range(unsigned(0), unsigned(setups.size())));

		REQUIRE_NOTHROW([&](){
			args.setupArguments(setups[i]);
			args.parse(argSetups[i].size(), argSetups[i].data());
		});

		for (auto query : queries[i]) {
			REQUIRE_FALSE(args.isSet(query));
		}
	}
}

TEST_CASE("Args::getPositionalArguments", "[Args]") {
	cfg::Args args("ho:");

	SECTION("Only switch set") {
		std::vector<const char*> params = {"progname", "-h"};
		args.parse(params.size(), params.data());
		auto pos = args.getPositionalArguments();
		REQUIRE(pos.size() == 0);
	}

	SECTION("Only param value set") {
		std::vector<const char*> params = {"progname", "-o", "ehlo"};
		args.parse(params.size(), params.data());
		auto pos = args.getPositionalArguments();
		REQUIRE(pos.size() == 0);
	}

	SECTION("Switch and positional argument") {
		std::vector<const char*> params = {"progname", "-h", "ehlo"};
		args.parse(params.size(), params.data());
		auto pos = args.getPositionalArguments();

		REQUIRE(pos.size() == 1);
		REQUIRE(pos[0] == "ehlo");
	}

	SECTION("Param and positional argument") {
		std::vector<const char*> params = {"progname", "-o", "ehlo", "ehlo"};
		args.parse(params.size(), params.data());
		auto pos = args.getPositionalArguments();

		REQUIRE(pos.size() == 1);
		REQUIRE(pos[0] == "ehlo");
	}

	SECTION("Positional, then param") {
		std::vector<const char*> params = {"progname", "ehlo", "-o", "ehlo"};
		args.parse(params.size(), params.data());
		auto pos = args.getPositionalArguments();

		REQUIRE(pos.size() == 1);
		REQUIRE(pos[0] == "ehlo");
	}
}

TEST_CASE("Args::getArgumentValue", "[Args]") {
	cfg::Args args("v:");

	SECTION("Int value") {
		std::vector<const char*> params = {"progname", "-v", "10"};
		args.parse(params.size(), params.data());

		REQUIRE(args.getArgumentValue('v').asInt() == 10);
	}

	SECTION("String value") {
		std::vector<const char*> params = {"progname", "-v", "ehlo"};
		args.parse(params.size(), params.data());

		REQUIRE(args.getArgumentValue('v').asString() == "ehlo");
	}

	SECTION("No value") {
		std::vector<const char*> params = {"progname" };
		args.parse(params.size(), params.data());

		try {
			args.getArgumentValue('v');
			REQUIRE(false);
		} catch (...) {}

		/* Following does not work:
		REQUIRE_THROWS([&]() {
			args.getArgumentValue('v');
		});*/
	}
}