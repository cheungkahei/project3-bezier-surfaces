#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>

namespace interpreter {

	/*defined classes*/
	class interpreter_t;

	class interpreter_t
	{
	 	public:
			interpreter_t(){};
			interpreter_t();

			int read(const std::string& commandLine);
	};
}

#endif
