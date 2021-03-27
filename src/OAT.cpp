#include "OAT.h"
#include "Constants.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
using IncludesVector = vector<string>;

// Variables
string OAT::dec(string var_name, string var_value) { return "auto " + var_name + "{ " + var_value + " };\n"; }
string OAT::dec(string var_name, string var_value, string type) { return type + " " + var_name + "{ " + var_value + " };\n"; }
string OAT::mov(string l_var, string r_var) { return "auto " + r_var + "{ " + l_var + " };\n"; }

// Math
string OAT::math(string l_var, string r_var, string mode) { return l_var + " " + mode + "= " + r_var + ";\n"; }
string OAT::cat(string l_var, string r_var) { return l_var + " += " + "std::string(" + r_var + ");\n"; }

// Input/Output
string OAT::io(string mode, string var)
{
	if (mode == "out") { return "std::cout << " + var + ";\n"; }
	else if (mode == "nlout") { return "std::cout << " + var + " << '\\n';\n"; }
	else if (mode == "in") { return "std::string " + var + "{};\n" + constants::INDENTATION + "std::cin >> " + var + ";\n"; }
	else { return string(""); }
}

string OAT::process_c(string c)
{
	if (c == "NEWLINE") { return constants::NEWLINE_CHARACTER; }
	else if (c == "SPACE") { return constants::SPACE; }
	else if (c == "TRUE") { return constants::TRUE; }
	else if (c == "FALSE") { return constants::FALSE; }
	else { return c; };
}

string OAT::process_line(string a, string b, string c, IncludesVector *include_vector)
{
	if (a == "dec") { return OAT::dec(b, c); }
	else if (a == "strdec")
	{
		// Push #include <string> into vector
		include_vector->push_back("#include <string>\n");
		return OAT::dec(b, c, "std::string");
	}
	else if (a == "intdec") { return OAT::dec(b, c, "int"); }
	else if (a == "chardec") { return OAT::dec(b, c, "char"); }
	else if (a == "floatdec") { return OAT::dec(b, c, "float"); }
	else if (a == "doubledec") { return OAT::dec(b, c, "double"); }
	else if (a == "booldec") { return OAT::dec(b, c, "bool"); }
	else if (a == "cat")
	{
		include_vector->push_back("#include <string>\n");
		return OAT::cat(b, c);
	}
	else if (a == "mov") { return OAT::mov(b, c); }
	else if (a == "add") { return OAT::math(b, c, "+"); }
	else if (a == "sub") { return OAT::math(b, c, "-"); }
	else if (a == "mul") { return OAT::math(b, c, "*"); }
	else if (a == "div") { return OAT::math(b, c, "/"); }
	else if (a == "mod") { return OAT::math(b, c, "%"); }
	//else if (a == "pow") { return OAT::math(b, c, "**"); } // Include <math.h> and use the pow() function
	else if (a == "io") {
		include_vector->push_back("#include <iostream>\n");
		return OAT::io(b, c);
	}
	else { return string(""); }
}