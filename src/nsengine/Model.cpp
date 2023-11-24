#include "Model.h"

namespace nsengine
{
	void Model::onLoad() 
	{
		model = std::make_shared<rend::Model>();
	};
}