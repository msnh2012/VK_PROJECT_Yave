/*******************************
Copyright (c) 2016-2022 Grégoire Angerand

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**********************************/

#include "VPLLightingPass.h"

#include <yave/framegraph/FrameGraph.h>
#include <yave/framegraph/FrameGraphPass.h>
#include <yave/framegraph/FrameGraphFrameResources.h>
#include <yave/graphics/device/DeviceResources.h>
#include <yave/graphics/commands/CmdBufferRecorder.h>

namespace yave {

VPLLightingPass VPLLightingPass::create(FrameGraph& framegraph, const GBufferPass& gbuffer, const VPLGenerationPass& generation_pass) {
    const math::Vec2ui size = framegraph.image_size(gbuffer.depth);

    FrameGraphPassBuilder builder = framegraph.add_pass("VPL lighting pass");

    const auto lit = builder.declare_image(VK_FORMAT_R16G16B16A16_SFLOAT, size);

    builder.add_uniform_input(gbuffer.depth);
    builder.add_uniform_input(gbuffer.color);
    builder.add_uniform_input(gbuffer.normal);
    builder.add_uniform_input(gbuffer.scene_pass.camera_buffer, 0, PipelineStage::ComputeBit);
    builder.add_storage_input(generation_pass.vpl_buffer);
    builder.add_storage_output(lit);
    builder.set_render_func([=](CmdBufferRecorder& recorder, const FrameGraphPass* self) {
        const auto& program = device_resources()[DeviceResources::VPLLightingProgram];
        recorder.dispatch_size(program, size, {self->descriptor_sets()[0]});
    });


    VPLLightingPass pass;
    pass.lit = lit;
    return pass;
}

}

