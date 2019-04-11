#include "ItemLookup.hpp"

const unsigned W = 10;
const unsigned H = 10;
const unsigned G = 32;
const unsigned A = 10;

struct Circle {
	sf::Vector2f pos;
	float r;
};

class Object {
protected:
	Circle body;

public:
	const Circle &getBody() const { return body }
};

typedef ItemLookup<Object, G, A> Lookup;

class Player : public Object {
public:
	void update(Lookup &lookup) {
		lookup.delItem(body.pos, this);

		body.pos.x += 1.f;
		body.pos.y += 3.f;

		lookup.addItem(body.pos, this);
	}

	void spawn(float x, float y, Lookup &lookup) {
		body.x = x;
		body.y = y;
		body.r = 0.f;
		lookup.addItem(body.pos, this);
	}
};

int main() {
	Lookup lookup;
	Player p;
	p.spawn(100.f, 20.f, lookup);

	for (unsigned i = 0; i < 10; i++) {
		p.update(lookup);
	}
	
	return 0;
}