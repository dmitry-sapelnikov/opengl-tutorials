// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <filesystem>
#include <string>

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
