#include "Model.h"

namespace nsengine
{
	void Model::onLoad() 
	{
		model = std::make_shared<rend::Model>();
		model->load(getPath().c_str());
	};
}