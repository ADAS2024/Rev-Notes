#include <stdio.h>
#include <vector>
#include <cstdint>
#include <cstring>


// Code derived from: https://labuladong.online/algo/en/data-structure-basic/hashmap-basic/#basic-principles-of-hash-tables
class HashMap {
	private:
		std::vector<char*> map;

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
		HashMap() : map(256, nullptr) {}

		void put(char* key, char* value) {
			int index = hash(key, strlen(key)) % map.size();
			map[index] = value;
		}

		char* get(char* key) {
			int index = hash(key, strlen(key)) % map.size();
			return map[index];
		}

		void remove(char* key) {
			int index = hash(key, strlen(key)) % map.size();
			map[index] = nullptr;
		}
};

int main() {
    HashMap* custom = new HashMap();

    delete custom;
    return 0;
}
