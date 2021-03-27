#include "OAT.h"
#include "Constants.h"
#include <cmath>
#include <string>
#include <vector>

using std::string;
using std::vector;
using IncludesVector = vector<string>;

namespace vars
{
	static string placeholder_var{ constants::DEFAULT };
	static bool ipow_dec{ false };
	static bool fpow_dec{ false };
	static bool dpow_dec{ false };
}

// Variables
string OAT::dec(string var_name, string var_value) { return "auto " + var_name + "{ " + var_value + " };\n"; }
string OAT::dec(string var_name, string var_value, string type) { return type + " " + var_name + "{ " + var_value + " };\n"; }
string OAT::mov(string l_var, string r_var) { return "auto " + r_var + "{ " + l_var + " };\n"; }
string OAT::def(string var_name)
{
	vars::placeholder_var = var_name;
	return string("");
}
string OAT::conv(string var_name, string type) { return type + " " + vars::placeholder_var + " = static_cast<" + type + ">(" + var_name + ");\n"; }
string OAT::fconv(string old_var, string new_var) { return "float " + new_var + " = strtof(" + old_var + ");\n"; }
string OAT::dconv(string old_var, string new_var) { return "double " + new_var + " = atof(" + old_var + ".c_str());\n"; }
string OAT::round(string l_var, string r_var) { return "auto " + r_var + " = round(" + l_var + ");\n"; }

// Math
string OAT::math(string l_var, string r_var, string mode)
{
	if (mode == "pow") { return "auto " + vars::placeholder_var + " = pow(" + l_var + ", " + r_var + ");\n"; }
	else { return l_var + " " + mode + "= " + r_var + ";\n"; }
}
string OAT::cat(string l_var, string r_var) { return l_var + " += " + "std::string(" + r_var + ");\n"; }

string OAT::ipow(string base, string exp) { return "int " + vars::placeholder_var + " = ipow(" + base + ", " + exp + ");\n"; } // Made by Byzantian
string OAT::fpow(string base, string exp) { return "int " + vars::placeholder_var + " = fpow(" + base + ", " + exp + ");\n"; } // Made by Byzantian
string OAT::dpow(string base, string exp) { return "double " + vars::placeholder_var + " = dpow(" + base + ", " + exp + ");\n"; } // Made by Byzantian

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
	else if (a == "def") { return OAT::def(b); }
	else if (a == "conv") { return OAT::conv(b, c); }
	else if (a == "fconv")
	{
		include_vector->push_back("#include <cstdlib>\n");
		return OAT::fconv(b, c);
	}
	else if (a == "dconv")
	{
		include_vector->push_back("#include <cstdlib>\n");
		return OAT::dconv(b, c);
	}
	else if (a == "add") { return OAT::math(b, c, "+"); }
	else if (a == "sub") { return OAT::math(b, c, "-"); }
	else if (a == "mul") { return OAT::math(b, c, "*"); }
	else if (a == "div") { return OAT::math(b, c, "/"); }
	else if (a == "mod") { return OAT::math(b, c, "%"); }
	else if (a == "pow")
	{
		include_vector->push_back("#include <cmath>\n");
		return OAT::math(b, c, "pow");
	}
	else if (a == "ipow") { return OAT::ipow(b, c); }
	else if (a == "fpow") { return OAT::fpow(b, c); }
	else if (a == "dpow") { return OAT::dpow(b, c); }
	else if (a == "round")
	{
		include_vector->push_back("#include <cmath>\n");
		return OAT::round(b, c);
	}
	else if (a == "io") {
		include_vector->push_back("#include <iostream>\n");
		return OAT::io(b, c);
	}
	else { return string(""); }
}

string OAT::declare_function(string function_name)
{
	if (function_name == "ipow" && !(vars::ipow_dec))
	{
		vars::ipow_dec = true;
		return "int ipow(int base, int exp) { return exp == 0 ? 1 : base * ipow(base, exp - 1); }\n";
	}
	else if (function_name == "fpow" && !(vars::fpow_dec))
	{
		vars::fpow_dec = true;
		return "float fpow(float base, float exp) { return exp == 0 ? 1 : base * fpow(base, exp - 1); }\n";
	}
	else if (function_name == "dpow" && !(vars::dpow_dec))
	{
		vars::dpow_dec = true;
		return "double dpow(double base, double exp) { return exp == 0 ? 1 : base * dpow(base, exp - 1); }\n";
	}
	else { return ""; }
}