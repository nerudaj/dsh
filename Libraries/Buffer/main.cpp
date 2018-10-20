#include <iostream>
#include "Buffer.hpp"

struct MyObject {
	int health;
	int damage;
};

void printBufferStats(const Buffer<MyObject> &buffer) {
	std::cout << "Size: " << buffer.size() << "\n";
	std::cout << "Capacity: " << buffer.capacity() << "\n";
	std::cout << "Empty: " << buffer.empty() << "\n";
	std::cout << "Full: " << buffer.full() << "\n";
	std::cout << "\n";
}

int main() {
	Buffer<MyObject> buffer(10);
	
	printBufferStats(buffer);
	
	int cnt = 1;
	while (buffer.expand()) {
		buffer.last().health = cnt * 2;
		buffer.last().damage = cnt;
		cnt++;
	}
	
	printBufferStats(buffer);
	
	for (auto &item : buffer) {
		item.health = 20;
	}
	
	for (auto item : buffer) {
		std::cout << item.health << " ";
	}
	
	while(buffer.remove(0));
	
	printBufferStats(buffer);
	
	return 0;
}