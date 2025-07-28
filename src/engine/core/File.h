#pragma once

// Includes
#include <string>
#include <filesystem>

namespace gltut
{
// Global functions
/**
	\brief Reads a file to a string
	\param path The path to the file
	\return The file contents as a string
	\throw std::ios_base::failure if the file could not be read
*/
std::string readFileToString(const std::filesystem::path& path);

// End of the namespace gltut
}
