#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using std::string;

namespace constants
{
	// Config
	static constexpr bool DELETE_CPP_FILE{ false }; // false for debug, true for release

	// Transpiler
	static const string FIRST_MAIN{ "int main()\n{\n" };
	static const string INDENTATION{ "	" };
	static const string NEWLINE{ "\n" }; // Was char, had to change
	static const string LAST_MAIN{ INDENTATION + "return 0;\n}\n" };
	static const string DEFAULT{ "DEF" }; // Placeholder variable

	// C Replacement
	static const string SPACE{ "\" \"" }; // Was char, had to change
	static const string NEWLINE_CHARACTER{ "\"\\n\"" };
	static const string TRUE{ "true" };
	static const string FALSE{ "false" };

	// Messages
	static const string HELP_MESSAGE{
		"Incorrect arguments.\n"
		"OAT Usage:\n"
		"[OAT Executable] [anyfile.oa] [c/nc - compile/nocompile]\n"
		"Warning: You need g++ to compile.\n"
	};
}

#endif // CONSTANTS_H