// Includes
#include "File.h"
#include <fstream>

namespace gltut
{
// Global functions
std::string readFileToString(const std::filesystem::path& path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open(path);
	return {
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
}

// End of the namespace gltut
}
