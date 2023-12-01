#include "Model.h"

namespace nsengine
{
	void Model::onLoad() 
	{
		model = std::make_shared<rend::Model>(getPath().c_str());
		//model->load();
	};
}