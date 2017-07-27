#include <iostream>
#include <fstream>
#include <vector>
#include "json.h"

using namespace std;

//https://en.wikibooks.org/wiki/JsonCpp

class mesh
{
	public:
		string meshType;
};

void Indent(ostream& ofs, int indent) {
	for (int i = 0; i < indent; i++)
		//ofs << ' ';
		break;
}

void MyPrint(ostream& ofs, const Json::Value& val, vector<mesh>& v, int indent = 0) {
	switch (val.type()) {
	case Json::nullValue: "null"; break;
	case Json::booleanValue: (val.asBool() ? "true" : "false"); break;
	case Json::intValue: val.asLargestInt(); break;
	case Json::uintValue: val.asLargestUInt(); break;
	case Json::realValue: val.asDouble(); break;
	case Json::stringValue: {
		// analyze String value of attribute:
		string res = val.asString();
		if (res == "Expr") {
			//cout << ":::found an Expr";
			mesh expr;
			expr.meshType = "Expr";
			v.push_back(expr);
		}
		else if (res == "FunctionDef")
		{
			//cout << ":::found a FunctionDef";
			mesh fdef;
			fdef.meshType = "FunctionDef";
			v.push_back(fdef);
		}
		else if (res == "Assign")
		{
			//cout << ":::found an Assign";
			mesh asgn;
			asgn.meshType = "Assign";
			v.push_back(asgn);
		}
		//ofs << '"' << res << '"';

	} break;
	case Json::arrayValue: {
		Json::ArrayIndex size = val.size();
		if (size == 0)
			break;
		else {
			//ofs << "[\n";
			int newIndent = indent + 4;
			for (Json::ArrayIndex i = 0; i<size; i++) {
				//Indent(ofs, newIndent);
				MyPrint(ofs, val[i], v, newIndent);
				//ofs << (i + 1 == size ? "\n" : ",\n");
			}
			//Indent(ofs, indent);
			//ofs << ']';
		}
		break;
	}
	case Json::objectValue: {
		if (val.empty())
			//ofs << "{}";
			break;
		else {
			//ofs << "{\n";
			int newIndent = indent + 4;
			vector<string> keys = val.getMemberNames();
			for (size_t i = 0; i<keys.size(); i++) {
				//Indent(ofs, newIndent);
				const string& key = keys[i];
				//ofs << '"' << key << '"' << " : ";
				MyPrint(ofs, val[key], v, newIndent);
				//ofs << (i + 1 == keys.size() ? "\n" : ",\n");
			}
			Indent(ofs, indent);
			//ofs << '}';
		}
		break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}

int main() {
	vector<mesh> vec;
	ifstream ifs("./file1.json");
	Json::Value val;
	ifs >> val;
	MyPrint(cout, val, vec);
	cout << '\n';

	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec.at(i).meshType << endl;
	}


	system("PAUSE");
	return 0;
}