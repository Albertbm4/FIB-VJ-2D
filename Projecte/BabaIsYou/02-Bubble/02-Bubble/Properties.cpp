#include "Properties.h"

Properties::Properties() {
    setBasicProperties();
}

Properties::~Properties() {
    props.clear();
}

bool Properties::can(const string& propertie, const string& type) {
    map<string, vector<string>>::iterator it = props.find(propertie);
    if (it == props.end()) return false;
    else {
        vector<string>& v = it->second;
        int i = 0;
        bool found = false;
        while (!found && i < int(v.size())) {
            if (v[i] == type) found = true;
            else ++i;
        }
        return found;
    }
}

void Properties::setPropertie(const string& propertie, const string& type) {
    map<string, vector<string>>::iterator it = props.find(propertie);
    if (it != props.end()) {
        vector<string>& v = it->second;
        int i = 0;
        bool found = false;
        while (!found && i < int(v.size())) {
            if (v[i] == type) found = true;
            else ++i;
        }
        if (!found) it->second.push_back(type);
    }
}

void Properties::setBasicProperties() {
    props["WIN"];
    props["SINK"];
    props["HOT"];
    props["YOU"];
    props["SHUT"];
    props["OPEN"];
    props["PUSH"];
    props["MOVE"];
    props["DEFEAT"];
    props["STOP"].push_back("PILAR");
    props["STOP"].push_back("GREY");
    props["MELT"];
    props["GHOST"];

    props["PUSH"].push_back("AND");
    props["PUSH"].push_back("WIN");
    props["PUSH"].push_back("GHOST");
    props["PUSH"].push_back("SINK");
    props["PUSH"].push_back("HOT");
    props["PUSH"].push_back("YOU");
    props["PUSH"].push_back("SHUT");
    props["PUSH"].push_back("OPEN");
    props["PUSH"].push_back("PUSH");
    props["PUSH"].push_back("MOVE");
    props["PUSH"].push_back("DEFEAT");
    props["PUSH"].push_back("STOP");
    props["PUSH"].push_back("MELT");
    props["PUSH"].push_back("ROCKW");
    props["PUSH"].push_back("SKULLW");
    props["PUSH"].push_back("SUNW");
    props["PUSH"].push_back("WALLW");
    props["PUSH"].push_back("RUBBLEW");
    props["PUSH"].push_back("STARW");
    props["PUSH"].push_back("WATERW");
    props["PUSH"].push_back("PILARW");
    props["PUSH"].push_back("ROCKETW");
    props["PUSH"].push_back("ALGAW");
    props["PUSH"].push_back("BAW");
    props["PUSH"].push_back("BABAW");
    props["PUSH"].push_back("BOLTW");
    props["PUSH"].push_back("BRICKW");
    props["PUSH"].push_back("COGW");
    props["PUSH"].push_back("CRABW");
    props["PUSH"].push_back("DOORW");
    props["PUSH"].push_back("FLAGW");
    props["PUSH"].push_back("GRASSW");
    props["PUSH"].push_back("KEKEW");
    props["PUSH"].push_back("LAVAW");
    props["PUSH"].push_back("ROCKW");
    props["PUSH"].push_back("ICEW");
    props["PUSH"].push_back("JELLYW");
    props["PUSH"].push_back("KEYW");
    props["PUSH"].push_back("AND");
    props["PUSH"].push_back("IS");
}

void Properties::deleteProperties() {
    props.clear();
    setBasicProperties();
}