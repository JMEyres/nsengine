#include<string>
#include<memory>
#include<rend/rend.h>

struct Resource
{
	virtual void onLoad() = 0;

	std::string getPath() const;

private:
	std::string path;

	void load();

};

struct Texture : Resource
{
	void onLoad();

private:
	std::shared_ptr<rend::Texture> texture;

};