/*******************************
Copyright (c) 2016-2017 Grégoire Angerand

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
#ifndef YAVE_DEVICE_DEVICE_H
#define YAVE_DEVICE_DEVICE_H

#include <yave/yave.h>
#include "PhysicalDevice.h"

#include <yave/bindings/DescriptorSetLayoutPool.h>
#include <yave/images/Sampler.h>
#include <yave/commands/pool/CmdBufferPool.h>
#include <yave/queues/QueueFamily.h>

#include <yave/vk/destroy.h>

namespace yave {

class Device : NonCopyable {

	public:
		explicit Device(Instance& instance);
		~Device();

		const PhysicalDevice& physical_device() const;
		const Instance& instance() const;

		vk::Device vk_device() const;
		vk::Queue vk_queue(vk::QueueFlags) const;
		vk::Sampler vk_sampler() const;

		const QueueFamily& queue_family(vk::QueueFlags flags) const;

		template<typename T>
		void destroy(T t) const {
			if(t != T()) {
				detail::destroy(this, t);
			}
		}

		auto create_disposable_cmd_buffer() const {
			return _disposable_cmd_pool.create_buffer();
		}

		auto create_secondary_cmd_buffer() const {
			return _secondary_cmd_pool.create_buffer();
		}

		auto create_cmd_buffer() const {
			return _primary_cmd_pool.create_buffer();
		}

		template<typename T>
		auto create_descriptor_set_layout(T&& t) const {
			return _descriptor_layout_pool->create_descriptor_set_layout(std::forward<T>(t));
		}

	private:
		Instance& _instance;
		PhysicalDevice _physical;

		core::Vector<QueueFamily> _queue_families;

		core::Vector<vk::Queue> _queues;

		vk::Device _device;

		Sampler _sampler;

		mutable CmdBufferPool<CmdBufferUsage::Secondary> _secondary_cmd_pool;
		mutable CmdBufferPool<CmdBufferUsage::Disposable> _disposable_cmd_pool;
		mutable CmdBufferPool<CmdBufferUsage::Primary> _primary_cmd_pool;

		DescriptorSetLayoutPool* _descriptor_layout_pool;
};


template<typename T>
void DeviceLinked::destroy(T t) const {
	if(_device) {
		_device->destroy(t);
	}
}



}


#endif // YAVE_DEVICE_DEVICE_H
