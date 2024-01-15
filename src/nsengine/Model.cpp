#include "Model.h"

namespace nsengine
{
	void Model::OnLoad() 
	{
		model = std::make_shared<rend::Model>(GetPath().c_str());
	};

	std::shared_ptr<rend::Model> Model::GetModel()
	{
		return model;
	}
}