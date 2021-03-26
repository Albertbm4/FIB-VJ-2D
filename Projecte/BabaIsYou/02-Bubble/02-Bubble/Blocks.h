#ifndef _BLOCKS_INCLUDE
#define _BLOCKS_INCLUDE

#include <map>
#include <string>
using namespace std;

class Blocks {
public:
	Blocks() {};
	~Blocks();

	static Blocks& instance() {
		static Blocks B;
		return B;
	}

	void init();
	pair<string, string> getRef(const int& id);
	int getId(const string& type);

private:
	map<int, pair<string, string>> blocksRef;
};

#endif  // _BLOCKS_INCLUDE