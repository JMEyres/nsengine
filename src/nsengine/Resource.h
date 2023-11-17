#include<string>
#include<memory>
#include<rend/rend.h>

namespace nsengine
{
	struct Resources;
	struct Resource
	{
		virtual void onLoad() = 0;

		std::string getPath() const;

	private:
		std::weak_ptr<Resources> resources;
		std::string path;
		void load();

	};

	struct Texture : Resource
	{
		void onCreate(int width, int height);
	private:
		void onLoad() override;
		std::shared_ptr<rend::Texture> texture;

	};

	struct Sound : Resource
	{
	private:
		void onLoad() override;
	};
}