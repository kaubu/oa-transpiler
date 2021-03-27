#ifndef OAT_H
#define OAT_H

#include <string>
#include <vector>

using std::string;
using std::vector;
using IncludesVector = vector<string>;

class OAT
{
public:
	static string process_line(string a, string b, string c, IncludesVector *include_vector);
	static string process_c(string c);
	static string declare_function(string function_name);
private:
	// Variables
	static string dec(string var_name, string var_value); // dec foo 5 - Uses auto unless specificed
	static string dec(string var_name, string var_value, string type); // dec foo 5 - Uses auto unless specificed
	static string mov(string l_var, string r_var); // mov foo bar
	static string def(string var_name); // def name - Change default placeholder
	static string conv(string var_name, string type);
	static string fconv(string old_var, string new_var);
	static string dconv(string old_var, string new_var);

	// Math
	static string math(string l_var, string r_var, string mode); // Mode is +, -, *, /, etc
	static string cat(string l_var, string r_var); // Concatenate r_var to l_var. cat foo NEWLINE
	static string ipow(string base, string exp);
	static string fpow(string base, string exp);
	static string dpow(string base, string exp);
	static string round(string l_var, string r_var);

	// Input/Output
	static string io(string mode, string var = string("DEF")); // Mode could be out or in. Var is the message displayed.
};

#endif // OAT_H