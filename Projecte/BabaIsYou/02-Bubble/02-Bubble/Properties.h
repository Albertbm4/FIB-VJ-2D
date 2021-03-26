#ifndef _PROPERTIES_INCLUDE
#define _PROPERTIES_INCLUDE

#include <map>
#include <vector>
#include <string>
using namespace std;

class Properties {
public:
	Properties();
	~Properties();

	bool can(const string& propertie, const string& type);
	void setPropertie(const string& propertie, const string& type);

	void setBasicProperties();
	void deleteProperties();

private:
	map<string, vector<string>> props;
};

#endif  // _PROPERTIES_INCLUDE