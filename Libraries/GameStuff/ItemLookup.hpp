#pragma once

#include <vector>

#ifndef sf::Vector2f
namespace sf {
	struct Vector2f {
		float x, y;
	};
}
#endif

#ifndef NULL
	#define NULL 0x0
#endif

template<class Object>
struct ItemLookupCell {
	unsigned size;
	std::vector<Object*> items;

	std::vector<Object*>::iterator begin() { return items.begin(); }
	std::vector<Object*>::const_iterator begin() const { return items.begin(); }
	std::vector<Object*>::iterator end() { return items.begin() + size; }
	std::vector<Object*>::const_iterator end() const { return items.begin() + size; }
};

template<class Object, unsigned CellWidth, unsigned AllocSize = 10>
class ItemLookup {
protected:
	std::vector<ItemLookupCell<Object>> data;
	unsigned width;
	unsigned height;

public:
	inline unsigned toIndex(const sf::Vector2f &coord) {
		return (unsigned(coord.y) * width + unsigned(coord.x)) / CellWidth;
	}

	void addItem(const sf::Vector2f &coord, const Object *ptr) {
		auto &cell = data[toIndex(coord)];

		if (cell.size == cell.items.size()) {
			data.resize(cell.size + AllocSize, NULL);
		}

		cell.items[cell.size++] = ptr;
	}

	void delItem(const sf::Vector2f &coord, const Object *ptr) {
		auto &cell = data[toIndex(coord)];

		for (unsigned i = 0; i < cell.size; i++) {
			if (cell.objects[i] == ptr) {
				// Swap pointer with last element in objects array
				// decrement size (effectively removing last item)
				cell.objects[i] = cell.objects[--cell.size];
			}
		}
	}

	const ItemLookupCell &getItems(const sf::Vector2f &coord) const {
		return data[toIndex(coord)];
	}

	void init(unsigned width, unsigned height, const std::vector<bool> &bitmask = {}) {
		data.resize(width * height);

		for (unsigned i = 0; i < bitmask.size(); i++) {
			if (bitmask[i]) {
				data[i].size = 0;
				data[i].items.resize(AllocSize, NULL);
			};
		}
	}

	void clear() {
		data.clear();
	}

	ItemLookup(unsigned width, unsigned height, const std::vector<bool> &bitmask = {}) {
		init(width, height, bitmask);
	}
};