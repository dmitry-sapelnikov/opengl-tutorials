// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

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
		std::istreambuf_iterator<char>()};
}

// End of the namespace gltut
}
