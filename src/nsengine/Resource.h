#pragma once
#include <string>
#include <memory>
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

	private:
		friend struct Resources;
		std::weak_ptr<Resources> resources;
		std::string path;
		void load();
	};


	//struct Sound : Resource
	//{
	//private:
	//	virtual void onLoad();
	//};
	//
	//struct Model : Resource
	//{
	//
	//private:
	//	virtual void onLoad();
	//};
}