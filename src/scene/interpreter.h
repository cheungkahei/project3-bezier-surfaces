#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include <scene/scene.h>

namespace interpreter {

	/*defined classes*/
	class interpreter_t;

	class interpreter_t
	{
	 	public:
			interpreter_t(){};
			interpreter_t(const std::string& filename, 
					scene_t& scene);

			int read(const std::string& filename,
					scene_t& scene);

			void clear();
	};
}

#endif



