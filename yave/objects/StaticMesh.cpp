/*******************************
Copyright (C) 2013-2016 gregoire ANGERAND

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************/

#include "StaticMesh.h"

#include <yave/commands/CmdBufferRecorder.h>
#include <yave/material/Material.h>
#include <yave/RenderPass.h>
#include <yave/Device.h>

namespace yave {


StaticMesh::StaticMesh(const AssetPtr<StaticMeshInstance>& instance, const AssetPtr<Material>& material) :
		_instance(instance),
		_material(material),
		_uniform_buffer(_material->device(), 1),
		_mapping(_uniform_buffer),
		_descriptor_set(_material->device(), {Binding(_uniform_buffer)}) {

	set_storage(_mapping.begin());
	transform() = math::identity();
}

StaticMesh::StaticMesh(StaticMesh&& other) :
		_instance(std::move(other._instance)),
		_material(std::move(other._material)),
		_uniform_buffer(std::move(other._uniform_buffer)),
		_mapping(std::move(other._mapping)),
		_descriptor_set(std::move(other._descriptor_set)) {
	set_storage(_mapping.begin());
}

void StaticMesh::draw(CmdBufferRecorder& recorder, const DescriptorSet& vp) const {
	recorder.bind_pipeline(_material->compile(recorder.current_pass(), recorder.viewport()), _descriptor_set, vp);
	recorder.draw(*_instance);
}

}
