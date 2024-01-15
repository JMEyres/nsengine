#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace nsengine
{
	struct Resources;
	/// @brief Base class for all resources to inherit from
	struct Resource
	{
		virtual void OnLoad() = 0;

		/// @brief Get the path of resource from current working directory
		/// @return String path with current working directory at the start
		std::string GetPath();

	protected:
		void Load();

		friend struct Resources;
		std::weak_ptr<Resources> resources;
		std::string cwd = std::filesystem::current_path().string();
		std::string path;
	};
}