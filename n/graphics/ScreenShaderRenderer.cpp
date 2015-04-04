/*******************************
Copyright (C) 2013-2015 gregoire ANGERAND

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

#include "ScreenShaderRenderer.h"
#include "VertexArrayObject.h"
#include "Material.h"

namespace n {
namespace graphics {

ScreenShaderRenderer::ScreenShaderRenderer(Shader<FragmentShader> *sh, const core::String &name, BufferedRenderer *c, uint slt, const math::Vec2ui &s) : BufferedRenderer(s.isNull() ? c->getFrameBuffer().getSize() : s), child(c), shader(sh, ShaderCombinaison::NoProjectionShader), slot(slt), uName(name) {
	buffer.setAttachmentEnabled(0, true);
	buffer.setDepthEnabled(false);
}

void *ScreenShaderRenderer::prepare() {
	return child->prepare();
}

void ScreenShaderRenderer::render(void *ptr) {
	child->render(ptr);

	buffer.bind();
	gl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.bind();
	shader.setValue(uName, child->getFrameBuffer().getAttachement(slot));

	GLContext::getContext()->getScreen().draw(VertexAttribs());
}

}
}
