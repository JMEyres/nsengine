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
	struct Resource
	{
		virtual void onLoad() = 0;

		std::string getPath();

	protected:
		friend struct Resources;
		std::weak_ptr<Resources> resources;
		std::string cwd = std::filesystem::current_path().string();
		std::string path;
		void load();
	};
}