#include <iostream>
#include <fstream>
#include "json.h"

using namespace std;

string getType(Json::Value val) {
	switch (val.type()) {
	case Json::nullValue:	 return "nullValue"; break;
	case Json::intValue:	 return "intValue"; break;
	case Json::uintValue:	 return "uintValue"; break;
	case Json::realValue:	 return "realValue"; break;
	case Json::stringValue:  return "stringValue"; break;
	case Json::booleanValue: return "booleanValue"; break;
	case Json::arrayValue:	 return "arrayValue"; break;
	case Json::objectValue:	 return "objectValue"; break;
	default: return "wrong type"; break;
	}
}

int main() {
	ifstream ifs("file2.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj); //reader can also read strings

	string type = getType(obj);
	cout << "parsed type: " << type << endl;

	cout << "ast_type: " << obj["ast_type"].asString() << endl;

	//const Json::Value& body = obj["body"]; //array of body
	Json::Value body = obj["body"];
	string sType = getType(body);
	if (sType == "arrayValue")
	{
		cout << "found an array" << endl;
	}

	for (int i = 0; i < body.size(); i++) {
	}

	system("PAUSE");
	return 0;
}