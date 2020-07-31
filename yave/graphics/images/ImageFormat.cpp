/*******************************
Copyright (c) 2016-2020 Grégoire Angerand

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

#include "ImageFormat.h"

#include <y/core/String.h>

namespace yave {


bool ImageFormat::operator==(const ImageFormat& other) const {
    return _format == other._format;
}

bool ImageFormat::operator!=(const ImageFormat& other) const {
    return _format != other._format;
}

bool ImageFormat::is_valid() const {
    return _format != VK_FORMAT_UNDEFINED && _format < VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT;
}

VkFormat ImageFormat::vk_format() const {
    return _format;
}

bool ImageFormat::is_block_format() const {
    switch(_format) {
        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
        case VK_FORMAT_BC2_UNORM_BLOCK:
        case VK_FORMAT_BC2_SRGB_BLOCK:
        case VK_FORMAT_BC3_UNORM_BLOCK:
        case VK_FORMAT_BC3_SRGB_BLOCK:
        case VK_FORMAT_BC4_UNORM_BLOCK:
        case VK_FORMAT_BC4_SNORM_BLOCK:
        case VK_FORMAT_BC5_UNORM_BLOCK:
        case VK_FORMAT_BC5_SNORM_BLOCK:
        case VK_FORMAT_BC6H_UFLOAT_BLOCK:
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:
        case VK_FORMAT_BC7_UNORM_BLOCK:
        case VK_FORMAT_BC7_SRGB_BLOCK:
            return true;

        default:
            return false;
    }
}

bool ImageFormat::is_depth_format() const {
    switch(_format) {
        case VK_FORMAT_D16_UNORM:
        case VK_FORMAT_D32_SFLOAT:
        case VK_FORMAT_D16_UNORM_S8_UINT:
        case VK_FORMAT_D24_UNORM_S8_UINT:
        case VK_FORMAT_D32_SFLOAT_S8_UINT:
            return true;

        default:
            return false;
    }
}

bool ImageFormat::is_float() const {
    switch(_format) {
        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
        case VK_FORMAT_R4G4_UNORM_PACK8:
        case VK_FORMAT_R8_UNORM:
        case VK_FORMAT_R8_SNORM:
        case VK_FORMAT_R8_USCALED:
        case VK_FORMAT_R8_SSCALED:
        case VK_FORMAT_R8_UINT:
        case VK_FORMAT_R8_SINT:
        case VK_FORMAT_R8_SRGB:
        case VK_FORMAT_S8_UINT:
        case VK_FORMAT_BC2_UNORM_BLOCK:
        case VK_FORMAT_BC2_SRGB_BLOCK:
        case VK_FORMAT_BC3_UNORM_BLOCK:
        case VK_FORMAT_BC3_SRGB_BLOCK:
        case VK_FORMAT_BC4_UNORM_BLOCK:
        case VK_FORMAT_BC4_SNORM_BLOCK:
        case VK_FORMAT_BC5_UNORM_BLOCK:
        case VK_FORMAT_BC5_SNORM_BLOCK:
        case VK_FORMAT_BC7_UNORM_BLOCK:
        case VK_FORMAT_BC7_SRGB_BLOCK:
        case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
        case VK_FORMAT_R5G6B5_UNORM_PACK16:
        case VK_FORMAT_B5G6R5_UNORM_PACK16:
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
        case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16:
        case VK_FORMAT_R8G8_UNORM:
        case VK_FORMAT_R8G8_SNORM:
        case VK_FORMAT_R8G8_USCALED:
        case VK_FORMAT_R8G8_SSCALED:
        case VK_FORMAT_R8G8_UINT:
        case VK_FORMAT_R8G8_SINT:
        case VK_FORMAT_R8G8_SRGB:
        case VK_FORMAT_R16_UNORM:
        case VK_FORMAT_R16_SNORM:
        case VK_FORMAT_R16_USCALED:
        case VK_FORMAT_R16_SSCALED:
        case VK_FORMAT_R16_UINT:
        case VK_FORMAT_R16_SINT:
        case VK_FORMAT_D16_UNORM:
        case VK_FORMAT_R8G8B8_UNORM:
        case VK_FORMAT_R8G8B8_SNORM:
        case VK_FORMAT_R8G8B8_USCALED:
        case VK_FORMAT_R8G8B8_SSCALED:
        case VK_FORMAT_R8G8B8_UINT:
        case VK_FORMAT_R8G8B8_SINT:
        case VK_FORMAT_R8G8B8_SRGB:
        case VK_FORMAT_B8G8R8_UNORM:
        case VK_FORMAT_B8G8R8_SNORM:
        case VK_FORMAT_B8G8R8_USCALED:
        case VK_FORMAT_B8G8R8_SSCALED:
        case VK_FORMAT_B8G8R8_UINT:
        case VK_FORMAT_B8G8R8_SINT:
        case VK_FORMAT_B8G8R8_SRGB:
        case VK_FORMAT_D16_UNORM_S8_UINT:
        case VK_FORMAT_R8G8B8A8_UNORM:
        case VK_FORMAT_R8G8B8A8_SNORM:
        case VK_FORMAT_R8G8B8A8_USCALED:
        case VK_FORMAT_R8G8B8A8_SSCALED:
        case VK_FORMAT_R8G8B8A8_UINT:
        case VK_FORMAT_R8G8B8A8_SINT:
        case VK_FORMAT_R8G8B8A8_SRGB:
        case VK_FORMAT_B8G8R8A8_UNORM:
        case VK_FORMAT_B8G8R8A8_SNORM:
        case VK_FORMAT_B8G8R8A8_USCALED:
        case VK_FORMAT_B8G8R8A8_SSCALED:
        case VK_FORMAT_B8G8R8A8_UINT:
        case VK_FORMAT_B8G8R8A8_SINT:
        case VK_FORMAT_B8G8R8A8_SRGB:
        case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
        case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
        case VK_FORMAT_A8B8G8R8_USCALED_PACK32:
        case VK_FORMAT_A8B8G8R8_SSCALED_PACK32:
        case VK_FORMAT_A8B8G8R8_UINT_PACK32:
        case VK_FORMAT_A8B8G8R8_SINT_PACK32:
        case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
        case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_USCALED_PACK32:
        case VK_FORMAT_A2R10G10B10_SSCALED_PACK32:
        case VK_FORMAT_A2R10G10B10_UINT_PACK32:
        case VK_FORMAT_A2R10G10B10_SINT_PACK32:
        case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
        case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
        case VK_FORMAT_A2B10G10R10_USCALED_PACK32:
        case VK_FORMAT_A2B10G10R10_SSCALED_PACK32:
        case VK_FORMAT_A2B10G10R10_UINT_PACK32:
        case VK_FORMAT_A2B10G10R10_SINT_PACK32:
        case VK_FORMAT_R16G16_UNORM:
        case VK_FORMAT_R16G16_SNORM:
        case VK_FORMAT_R16G16_USCALED:
        case VK_FORMAT_R16G16_SSCALED:
        case VK_FORMAT_R16G16_UINT:
        case VK_FORMAT_R16G16_SINT:
        case VK_FORMAT_R32_UINT:
        case VK_FORMAT_R32_SINT:
        case VK_FORMAT_X8_D24_UNORM_PACK32:
        case VK_FORMAT_D24_UNORM_S8_UINT:
        case VK_FORMAT_R16G16B16_UNORM:
        case VK_FORMAT_R16G16B16_SNORM:
        case VK_FORMAT_R16G16B16_USCALED:
        case VK_FORMAT_R16G16B16_SSCALED:
        case VK_FORMAT_R16G16B16_UINT:
        case VK_FORMAT_R16G16B16_SINT:
        case VK_FORMAT_R16G16B16A16_UNORM:
        case VK_FORMAT_R16G16B16A16_SNORM:
        case VK_FORMAT_R16G16B16A16_USCALED:
        case VK_FORMAT_R16G16B16A16_SSCALED:
        case VK_FORMAT_R16G16B16A16_UINT:
        case VK_FORMAT_R16G16B16A16_SINT:
        case VK_FORMAT_R32G32_UINT:
        case VK_FORMAT_R32G32_SINT:
        case VK_FORMAT_R64_UINT:
        case VK_FORMAT_R64_SINT:
        case VK_FORMAT_R32G32B32_UINT:
        case VK_FORMAT_R32G32B32_SINT:
        case VK_FORMAT_R32G32B32A32_UINT:
        case VK_FORMAT_R32G32B32A32_SINT:
        case VK_FORMAT_R64G64_UINT:
        case VK_FORMAT_R64G64_SINT:
        case VK_FORMAT_R64G64B64_UINT:
        case VK_FORMAT_R64G64B64_SINT:
        case VK_FORMAT_R64G64B64A64_UINT:
        case VK_FORMAT_R64G64B64A64_SINT:
            return false;

        case VK_FORMAT_BC6H_UFLOAT_BLOCK:
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:
        case VK_FORMAT_R32_SFLOAT:
        case VK_FORMAT_D32_SFLOAT:
        case VK_FORMAT_R16_SFLOAT:
        case VK_FORMAT_R16G16_SFLOAT:
        case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
        case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32:
        case VK_FORMAT_R16G16B16A16_SFLOAT:
        case VK_FORMAT_R16G16B16_SFLOAT:
        case VK_FORMAT_R32G32_SFLOAT:
        case VK_FORMAT_R64_SFLOAT:
        case VK_FORMAT_R32G32B32_SFLOAT:
        case VK_FORMAT_R32G32B32A32_SFLOAT:
        case VK_FORMAT_R64G64_SFLOAT:
        case VK_FORMAT_R64G64B64_SFLOAT:
        case VK_FORMAT_R64G64B64A64_SFLOAT:
            return true;

        default:
            y_fatal("Unsupported image format.");
    }
}

usize ImageFormat::bit_per_pixel() const {
    switch(_format) {
        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
            return 4;

        case VK_FORMAT_R4G4_UNORM_PACK8:
        case VK_FORMAT_R8_UNORM:
        case VK_FORMAT_R8_SNORM:
        case VK_FORMAT_R8_USCALED:
        case VK_FORMAT_R8_SSCALED:
        case VK_FORMAT_R8_UINT:
        case VK_FORMAT_R8_SINT:
        case VK_FORMAT_R8_SRGB:
        case VK_FORMAT_S8_UINT:
        case VK_FORMAT_BC2_UNORM_BLOCK:
        case VK_FORMAT_BC2_SRGB_BLOCK:
        case VK_FORMAT_BC3_UNORM_BLOCK:
        case VK_FORMAT_BC3_SRGB_BLOCK:
        case VK_FORMAT_BC4_UNORM_BLOCK:
        case VK_FORMAT_BC4_SNORM_BLOCK:
        case VK_FORMAT_BC5_UNORM_BLOCK:
        case VK_FORMAT_BC5_SNORM_BLOCK:
        case VK_FORMAT_BC6H_UFLOAT_BLOCK:
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:
        case VK_FORMAT_BC7_UNORM_BLOCK:
        case VK_FORMAT_BC7_SRGB_BLOCK:
            return 8;

        case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
        case VK_FORMAT_R5G6B5_UNORM_PACK16:
        case VK_FORMAT_B5G6R5_UNORM_PACK16:
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
        case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16:
        case VK_FORMAT_R8G8_UNORM:
        case VK_FORMAT_R8G8_SNORM:
        case VK_FORMAT_R8G8_USCALED:
        case VK_FORMAT_R8G8_SSCALED:
        case VK_FORMAT_R8G8_UINT:
        case VK_FORMAT_R8G8_SINT:
        case VK_FORMAT_R8G8_SRGB:
        case VK_FORMAT_R16_UNORM:
        case VK_FORMAT_R16_SNORM:
        case VK_FORMAT_R16_USCALED:
        case VK_FORMAT_R16_SSCALED:
        case VK_FORMAT_R16_UINT:
        case VK_FORMAT_R16_SINT:
        case VK_FORMAT_R16_SFLOAT:
        case VK_FORMAT_D16_UNORM:
            return 16;

        case VK_FORMAT_R8G8B8_UNORM:
        case VK_FORMAT_R8G8B8_SNORM:
        case VK_FORMAT_R8G8B8_USCALED:
        case VK_FORMAT_R8G8B8_SSCALED:
        case VK_FORMAT_R8G8B8_UINT:
        case VK_FORMAT_R8G8B8_SINT:
        case VK_FORMAT_R8G8B8_SRGB:
        case VK_FORMAT_B8G8R8_UNORM:
        case VK_FORMAT_B8G8R8_SNORM:
        case VK_FORMAT_B8G8R8_USCALED:
        case VK_FORMAT_B8G8R8_SSCALED:
        case VK_FORMAT_B8G8R8_UINT:
        case VK_FORMAT_B8G8R8_SINT:
        case VK_FORMAT_B8G8R8_SRGB:
        case VK_FORMAT_D16_UNORM_S8_UINT:
            return 24;

        case VK_FORMAT_R8G8B8A8_UNORM:
        case VK_FORMAT_R8G8B8A8_SNORM:
        case VK_FORMAT_R8G8B8A8_USCALED:
        case VK_FORMAT_R8G8B8A8_SSCALED:
        case VK_FORMAT_R8G8B8A8_UINT:
        case VK_FORMAT_R8G8B8A8_SINT:
        case VK_FORMAT_R8G8B8A8_SRGB:
        case VK_FORMAT_B8G8R8A8_UNORM:
        case VK_FORMAT_B8G8R8A8_SNORM:
        case VK_FORMAT_B8G8R8A8_USCALED:
        case VK_FORMAT_B8G8R8A8_SSCALED:
        case VK_FORMAT_B8G8R8A8_UINT:
        case VK_FORMAT_B8G8R8A8_SINT:
        case VK_FORMAT_B8G8R8A8_SRGB:
        case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
        case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
        case VK_FORMAT_A8B8G8R8_USCALED_PACK32:
        case VK_FORMAT_A8B8G8R8_SSCALED_PACK32:
        case VK_FORMAT_A8B8G8R8_UINT_PACK32:
        case VK_FORMAT_A8B8G8R8_SINT_PACK32:
        case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
        case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_USCALED_PACK32:
        case VK_FORMAT_A2R10G10B10_SSCALED_PACK32:
        case VK_FORMAT_A2R10G10B10_UINT_PACK32:
        case VK_FORMAT_A2R10G10B10_SINT_PACK32:
        case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
        case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
        case VK_FORMAT_A2B10G10R10_USCALED_PACK32:
        case VK_FORMAT_A2B10G10R10_SSCALED_PACK32:
        case VK_FORMAT_A2B10G10R10_UINT_PACK32:
        case VK_FORMAT_A2B10G10R10_SINT_PACK32:
        case VK_FORMAT_R16G16_UNORM:
        case VK_FORMAT_R16G16_SNORM:
        case VK_FORMAT_R16G16_USCALED:
        case VK_FORMAT_R16G16_SSCALED:
        case VK_FORMAT_R16G16_UINT:
        case VK_FORMAT_R16G16_SINT:
        case VK_FORMAT_R16G16_SFLOAT:
        case VK_FORMAT_R32_UINT:
        case VK_FORMAT_R32_SINT:
        case VK_FORMAT_R32_SFLOAT:
        case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
        case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32:
        case VK_FORMAT_X8_D24_UNORM_PACK32:
        case VK_FORMAT_D32_SFLOAT:
        case VK_FORMAT_D24_UNORM_S8_UINT:
            return 32;

        case VK_FORMAT_R16G16B16_UNORM:
        case VK_FORMAT_R16G16B16_SNORM:
        case VK_FORMAT_R16G16B16_USCALED:
        case VK_FORMAT_R16G16B16_SSCALED:
        case VK_FORMAT_R16G16B16_UINT:
        case VK_FORMAT_R16G16B16_SINT:
        case VK_FORMAT_R16G16B16_SFLOAT:
            return 48;

        case VK_FORMAT_R16G16B16A16_UNORM:
        case VK_FORMAT_R16G16B16A16_SNORM:
        case VK_FORMAT_R16G16B16A16_USCALED:
        case VK_FORMAT_R16G16B16A16_SSCALED:
        case VK_FORMAT_R16G16B16A16_UINT:
        case VK_FORMAT_R16G16B16A16_SINT:
        case VK_FORMAT_R16G16B16A16_SFLOAT:
        case VK_FORMAT_R32G32_UINT:
        case VK_FORMAT_R32G32_SINT:
        case VK_FORMAT_R32G32_SFLOAT:
        case VK_FORMAT_R64_UINT:
        case VK_FORMAT_R64_SINT:
        case VK_FORMAT_R64_SFLOAT:
            return 64;

        case VK_FORMAT_R32G32B32_UINT:
        case VK_FORMAT_R32G32B32_SINT:
        case VK_FORMAT_R32G32B32_SFLOAT:
            return 96;

        case VK_FORMAT_R32G32B32A32_UINT:
        case VK_FORMAT_R32G32B32A32_SINT:
        case VK_FORMAT_R32G32B32A32_SFLOAT:
        case VK_FORMAT_R64G64_UINT:
        case VK_FORMAT_R64G64_SINT:
        case VK_FORMAT_R64G64_SFLOAT:
            return 128;

        case VK_FORMAT_R64G64B64_UINT:
        case VK_FORMAT_R64G64B64_SINT:
        case VK_FORMAT_R64G64B64_SFLOAT:
            return 192;

        case VK_FORMAT_R64G64B64A64_UINT:
        case VK_FORMAT_R64G64B64A64_SINT:
        case VK_FORMAT_R64G64B64A64_SFLOAT:
            return 256;

        default:
            y_fatal("Unsupported image format.");
    }
}

usize ImageFormat::components() const {
    switch(_format) {
        case VK_FORMAT_R8_UNORM:
        case VK_FORMAT_R8_SNORM:
        case VK_FORMAT_R8_USCALED:
        case VK_FORMAT_R8_SSCALED:
        case VK_FORMAT_R8_UINT:
        case VK_FORMAT_R8_SINT:
        case VK_FORMAT_R8_SRGB:
        case VK_FORMAT_S8_UINT:
        case VK_FORMAT_R16_UNORM:
        case VK_FORMAT_R16_SNORM:
        case VK_FORMAT_R16_USCALED:
        case VK_FORMAT_R16_SSCALED:
        case VK_FORMAT_R16_UINT:
        case VK_FORMAT_R16_SINT:
        case VK_FORMAT_R16_SFLOAT:
        case VK_FORMAT_D16_UNORM:
        case VK_FORMAT_R32_UINT:
        case VK_FORMAT_R32_SINT:
        case VK_FORMAT_R32_SFLOAT:
        case VK_FORMAT_D32_SFLOAT:
        case VK_FORMAT_R64_UINT:
        case VK_FORMAT_R64_SINT:
        case VK_FORMAT_R64_SFLOAT:
            return 1;

        case VK_FORMAT_R8G8_UNORM:
        case VK_FORMAT_R8G8_SNORM:
        case VK_FORMAT_R8G8_USCALED:
        case VK_FORMAT_R8G8_SSCALED:
        case VK_FORMAT_R8G8_UINT:
        case VK_FORMAT_R8G8_SINT:
        case VK_FORMAT_R8G8_SRGB:
        case VK_FORMAT_R16G16_UNORM:
        case VK_FORMAT_R16G16_SNORM:
        case VK_FORMAT_R16G16_USCALED:
        case VK_FORMAT_R16G16_SSCALED:
        case VK_FORMAT_R16G16_UINT:
        case VK_FORMAT_R16G16_SINT:
        case VK_FORMAT_R16G16_SFLOAT:
        case VK_FORMAT_R32G32_UINT:
        case VK_FORMAT_R32G32_SINT:
        case VK_FORMAT_R32G32_SFLOAT:
        case VK_FORMAT_R64G64_UINT:
        case VK_FORMAT_R64G64_SINT:
        case VK_FORMAT_R64G64_SFLOAT:
            return 2;

        case VK_FORMAT_R8G8B8_UNORM:
        case VK_FORMAT_R8G8B8_SNORM:
        case VK_FORMAT_R8G8B8_USCALED:
        case VK_FORMAT_R8G8B8_SSCALED:
        case VK_FORMAT_R8G8B8_UINT:
        case VK_FORMAT_R8G8B8_SINT:
        case VK_FORMAT_R8G8B8_SRGB:
        case VK_FORMAT_B8G8R8_UNORM:
        case VK_FORMAT_B8G8R8_SNORM:
        case VK_FORMAT_B8G8R8_USCALED:
        case VK_FORMAT_B8G8R8_SSCALED:
        case VK_FORMAT_B8G8R8_UINT:
        case VK_FORMAT_B8G8R8_SINT:
        case VK_FORMAT_B8G8R8_SRGB:
        case VK_FORMAT_R16G16B16_UNORM:
        case VK_FORMAT_R16G16B16_SNORM:
        case VK_FORMAT_R16G16B16_USCALED:
        case VK_FORMAT_R16G16B16_SSCALED:
        case VK_FORMAT_R16G16B16_UINT:
        case VK_FORMAT_R16G16B16_SINT:
        case VK_FORMAT_R16G16B16_SFLOAT:
        case VK_FORMAT_R32G32B32_UINT:
        case VK_FORMAT_R32G32B32_SINT:
        case VK_FORMAT_R32G32B32_SFLOAT:
        case VK_FORMAT_R64G64B64_UINT:
        case VK_FORMAT_R64G64B64_SINT:
        case VK_FORMAT_R64G64B64_SFLOAT:
            return 3;

        case VK_FORMAT_R8G8B8A8_UNORM:
        case VK_FORMAT_R8G8B8A8_SNORM:
        case VK_FORMAT_R8G8B8A8_USCALED:
        case VK_FORMAT_R8G8B8A8_SSCALED:
        case VK_FORMAT_R8G8B8A8_UINT:
        case VK_FORMAT_R8G8B8A8_SINT:
        case VK_FORMAT_R8G8B8A8_SRGB:
        case VK_FORMAT_B8G8R8A8_UNORM:
        case VK_FORMAT_B8G8R8A8_SNORM:
        case VK_FORMAT_B8G8R8A8_USCALED:
        case VK_FORMAT_B8G8R8A8_SSCALED:
        case VK_FORMAT_B8G8R8A8_UINT:
        case VK_FORMAT_B8G8R8A8_SINT:
        case VK_FORMAT_B8G8R8A8_SRGB:
        case VK_FORMAT_R16G16B16A16_UNORM:
        case VK_FORMAT_R16G16B16A16_SNORM:
        case VK_FORMAT_R16G16B16A16_USCALED:
        case VK_FORMAT_R16G16B16A16_SSCALED:
        case VK_FORMAT_R16G16B16A16_UINT:
        case VK_FORMAT_R16G16B16A16_SINT:
        case VK_FORMAT_R16G16B16A16_SFLOAT:
        case VK_FORMAT_R32G32B32A32_UINT:
        case VK_FORMAT_R32G32B32A32_SINT:
        case VK_FORMAT_R32G32B32A32_SFLOAT:
        case VK_FORMAT_R64G64B64A64_UINT:
        case VK_FORMAT_R64G64B64A64_SINT:
        case VK_FORMAT_R64G64B64A64_SFLOAT:
            return 4;

        case VK_FORMAT_BC1_RGB_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK:
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
        case VK_FORMAT_R4G4_UNORM_PACK8:
        case VK_FORMAT_BC2_UNORM_BLOCK:
        case VK_FORMAT_BC2_SRGB_BLOCK:
        case VK_FORMAT_BC3_UNORM_BLOCK:
        case VK_FORMAT_BC3_SRGB_BLOCK:
        case VK_FORMAT_BC4_UNORM_BLOCK:
        case VK_FORMAT_BC4_SNORM_BLOCK:
        case VK_FORMAT_BC5_UNORM_BLOCK:
        case VK_FORMAT_BC5_SNORM_BLOCK:
        case VK_FORMAT_BC6H_UFLOAT_BLOCK:
        case VK_FORMAT_BC6H_SFLOAT_BLOCK:
        case VK_FORMAT_BC7_UNORM_BLOCK:
        case VK_FORMAT_BC7_SRGB_BLOCK:
        case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
        case VK_FORMAT_R5G6B5_UNORM_PACK16:
        case VK_FORMAT_B5G6R5_UNORM_PACK16:
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
        case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16:
        case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
        case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
        case VK_FORMAT_A8B8G8R8_USCALED_PACK32:
        case VK_FORMAT_A8B8G8R8_SSCALED_PACK32:
        case VK_FORMAT_A8B8G8R8_UINT_PACK32:
        case VK_FORMAT_A8B8G8R8_SINT_PACK32:
        case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
        case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_USCALED_PACK32:
        case VK_FORMAT_A2R10G10B10_SSCALED_PACK32:
        case VK_FORMAT_A2R10G10B10_UINT_PACK32:
        case VK_FORMAT_A2R10G10B10_SINT_PACK32:
        case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
        case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
        case VK_FORMAT_A2B10G10R10_USCALED_PACK32:
        case VK_FORMAT_A2B10G10R10_SSCALED_PACK32:
        case VK_FORMAT_A2B10G10R10_UINT_PACK32:
        case VK_FORMAT_A2B10G10R10_SINT_PACK32:
        case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
        case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32:
        case VK_FORMAT_X8_D24_UNORM_PACK32:
        case VK_FORMAT_D24_UNORM_S8_UINT:
        case VK_FORMAT_D16_UNORM_S8_UINT:
            return 0;

        default:
            y_fatal("Unsupported image format.");
    }
}

VkImageAspectFlags ImageFormat::vk_aspect() const {
    switch(_format) {
        case VK_FORMAT_D16_UNORM:
        case VK_FORMAT_D32_SFLOAT:
            return VK_IMAGE_ASPECT_DEPTH_BIT;

        case VK_FORMAT_D16_UNORM_S8_UINT:
        case VK_FORMAT_D24_UNORM_S8_UINT:
        case VK_FORMAT_D32_SFLOAT_S8_UINT:
            return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

        default:
            return VK_IMAGE_ASPECT_COLOR_BIT;
    }
}



std::string_view ImageFormat::name() const {
    auto clean_name = [](std::string_view orig) { return orig.substr(10); };
#define VK_FORMAT_CASE(fmt) case fmt: return clean_name(#fmt);
    switch(_format) {
        VK_FORMAT_CASE(VK_FORMAT_UNDEFINED)
        VK_FORMAT_CASE(VK_FORMAT_R4G4_UNORM_PACK8)
        VK_FORMAT_CASE(VK_FORMAT_R4G4B4A4_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_B4G4R4A4_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_R5G6B5_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_B5G6R5_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_R5G5B5A1_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_B5G5R5A1_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_A1R5G5B5_UNORM_PACK16)
        VK_FORMAT_CASE(VK_FORMAT_R8_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R8_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R8_SRGB)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R8G8_SRGB)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8_SRGB)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_SINT)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8_SRGB)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R8G8B8A8_SRGB)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_SINT)
        VK_FORMAT_CASE(VK_FORMAT_B8G8R8A8_SRGB)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_UNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_SNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_USCALED_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_SSCALED_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_UINT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_SINT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A8B8G8R8_SRGB_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2R10G10B10_UNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2R10G10B10_SNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2R10G10B10_USCALED_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2R10G10B10_SSCALED_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2R10G10B10_UINT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2R10G10B10_SINT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2B10G10R10_UNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2B10G10R10_SNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2B10G10R10_USCALED_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2B10G10R10_SSCALED_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2B10G10R10_UINT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_A2B10G10R10_SINT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_R16_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R16_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R16_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_SNORM)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_USCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_SSCALED)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R16G16B16A16_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R32_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R32_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R32_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32B32_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32B32_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32B32_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32B32A32_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32B32A32_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R32G32B32A32_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R64_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R64_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R64_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64B64_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64B64_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64B64_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64B64A64_UINT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64B64A64_SINT)
        VK_FORMAT_CASE(VK_FORMAT_R64G64B64A64_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_B10G11R11_UFLOAT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_E5B9G9R9_UFLOAT_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_D16_UNORM)
        VK_FORMAT_CASE(VK_FORMAT_X8_D24_UNORM_PACK32)
        VK_FORMAT_CASE(VK_FORMAT_D32_SFLOAT)
        VK_FORMAT_CASE(VK_FORMAT_S8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_D16_UNORM_S8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_D24_UNORM_S8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_D32_SFLOAT_S8_UINT)
        VK_FORMAT_CASE(VK_FORMAT_BC1_RGB_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC1_RGB_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC1_RGBA_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC1_RGBA_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC2_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC2_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC3_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC3_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC4_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC4_SNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC5_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC5_SNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC6H_UFLOAT_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC6H_SFLOAT_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC7_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_BC7_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_EAC_R11_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_EAC_R11_SNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_EAC_R11G11_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_EAC_R11G11_SNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_4x4_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_4x4_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_5x4_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_5x4_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_5x5_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_5x5_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_6x5_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_6x5_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_6x6_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_6x6_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_8x5_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_8x5_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_8x6_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_8x6_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_8x8_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_8x8_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x5_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x5_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x6_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x6_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x8_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x8_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x10_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_10x10_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_12x10_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_12x10_SRGB_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_12x12_UNORM_BLOCK)
        VK_FORMAT_CASE(VK_FORMAT_ASTC_12x12_SRGB_BLOCK)

        default:
            break;
    }
    return "";
#undef VK_FORMAT_CASE
}


}

