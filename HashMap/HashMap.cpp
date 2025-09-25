#include <stdio.h>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <utility>

#define TOMBSTONE ((char*)0x1)

// Code derived from: https://labuladong.online/algo/en/data-structure-basic/hashmap-basic/#basic-principles-of-hash-tables
class HashMap {
	private:
		std::vector<std::pair<char*, char*>> map;
		int capacity;

		// uint32 for better compatibility
		uint32_t hash(char* key, size_t len) {
			// Offsets for 32 bit as per FNV guidelines
			const uint32_t offset = 0x811C9DC5;       // 2166136261
			const uint32_t prime = 0x01000193;        // 16777619

			uint32_t hash = offset;
			for (size_t i = 0; i < len; i++) {
				hash ^= static_cast<uint32_t>(key[i]);
				hash *= prime;
			}
			return hash;
		}



	public:
		HashMap(int cap) : map(cap, {nullptr, nullptr}), capacity(cap) {}	

		// Linear probing impl based on: https://www.geeksforgeeks.org/java/how-to-handle-collisions-when-using-a-custom-hash-function-in-a-hashmap/
		void put(char* key, char* value) {
			int index = hash(key, strlen(key)) % capacity;
			int og_index = index;
			int tombstone_index;
			bool tombstone_found = false;

			while (map[index].first != nullptr) {

				if (map[index].first != TOMBSTONE && strcmp(map[index].first, key) == 0) {
					map[index].second = value;
					return;
				}

				// Tombstone handling for removed indices
				if (map[index].first == TOMBSTONE && !tombstone_found) {
					tombstone_found = true;
					tombstone_index = index;
				}

				index = (index+1) % capacity;
				if (index == og_index) {
					return;
				}
			}

			if (tombstone_found) {
				map[tombstone_index] = {key, value};
			} else {
				map[index] = {key, value};
			}
		}

		char* get(char* key) {
			int index = hash(key, strlen(key)) % capacity;
			int og_index = index;

			while (map[index].first != nullptr) {

				if (map[index].first != TOMBSTONE && strcmp(map[index].first, key) == 0) {
					return map[index].second;
				}

				index = (index+1) % capacity;
				if (index == og_index) {
					break;
				}
			}
			return nullptr;
		}

		void remove(char* key) {
			int index = hash(key, strlen(key)) % capacity;
			int og_index = index;

			while (map[index].first != nullptr) {

				if (map[index].first != TOMBSTONE && strcmp(map[index].first, key) == 0) {
					map[index] = {TOMBSTONE, nullptr};
					break;
				}

				index = (index+1) % capacity;
				if (index == og_index) {
					break;
				}
			}

		}
};

int main() {
	char key1[] = "1";
	char key2[] = "2";
	char key3[] = "3";
	char key4[] = "4";


	char val1[] = "Link";
	char val2[] = "Zelda";
	char val3[] = "Ganon";
	char val4[] = "Epona";

	HashMap* custom = new HashMap(10);
	custom->put(key1, val1);
	custom->put(key2, val2);
	custom->put(key3, val3);
	custom->put(key4, val4);

	std::cout << custom->get(key1) << "\n";
	std::cout << custom->get(key2) << "\n";
	std::cout << custom->get(key3) << "\n";
	std::cout << custom->get(key4) << "\n";

	custom->remove(key3);
	std::cout << "\n";

	std::cout << custom->get(key1) << "\n";
	std::cout << custom->get(key2) << "\n";
	std::cout << (custom->get(key3) ? custom->get(key3) : "(null)") << "\n";	// For some reason, returning this will mess up the returning for key4 and the output wouldnt display. (should return a nullptr)
											// I needed to do something like this to get further outputs to display.
											// I checked within GDB and internally i do get the actual key value pairs, might be something to do with my impl or lack of understanding with cout
	std::cout << custom->get(key4) << "\n";


	delete custom;
	return 0;
}
