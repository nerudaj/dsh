#include <catch.hpp>
#include "../LevelD.hpp"
#include "Assertions.hpp"

TEST_CASE("Paths save/load", "[LevelD]")
{
	LevelD out;
	LevelD in;
	std::vector<LevelD::Path::Point> points = {
		{ 10, 10, 0 },
		{ 10, 20, 30 },
		{ 20, 20, 0 },
		{ 300, 10, 10 },
		{ 1000, 10, 0 },
		{ 50, 50, 5 },
		{ 50, 60, 0 },
		{ 50, 100, 7 },
		{ 100, 100, 0 },
		{ 1, 1, 9 },
		{ 42, 69, 1 }
	};

	SECTION("Empty")
	{
		REQUIRE(out.paths.empty());
	}

	SECTION("Defined path no points")
	{
		out.paths.push_back({ false, 10, 0, {} });
	}

	SECTION("Defined path with some points")
	{
		out.paths.push_back({ true, 2, 1, points });
	}

	SECTION("Thousand paths")
	{
		for (unsigned i = 0; i < 1000; i++)
		{
			out.paths.push_back({ static_cast<bool>(i % 2), i, i, points });
		}
	}

	out.saveToFile("temp.lvd");
	in.loadFromFile("temp.lvd");

	assertPaths(in, out);
}