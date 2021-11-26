/*
 * Copyright 2016 Józef Kucia for CodeWeavers
 * Copyright 2016 Henri Verbeet for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define VKD3D_DBG_CHANNEL VKD3D_DBG_CHANNEL_API

#include "vkd3d_private.h"
#include "vkd3d_swapchain_factory.h"
#include "vkd3d_descriptor_debug.h"
#ifdef VKD3D_ENABLE_RENDERDOC
#include "vkd3d_renderdoc.h"
#endif

static inline struct d3d12_device *d3d12_device_from_ID3D12VideoDevice(ID3D12VideoDevice *iface)
{
    return CONTAINING_RECORD(iface, struct d3d12_device, ID3D12VideoDevice_iface);
}

ULONG STDMETHODCALLTYPE d3d12_video_device_AddRef(ID3D12VideoDevice *iface)
{
    struct d3d12_device *device = d3d12_device_from_ID3D12VideoDevice(iface);
    return d3d12_device_add_ref(device);
}

static ULONG STDMETHODCALLTYPE d3d12_video_device_Release(ID3D12VideoDevice *iface)
{
    struct d3d12_device *device = d3d12_device_from_ID3D12VideoDevice(iface);
    return d3d12_device_release(device);
}


static HRESULT STDMETHODCALLTYPE d3d12_video_device_QueryInterface(d3d12_video_device_iface *iface,
        REFIID riid, void **object)
{
    struct d3d12_device *device = d3d12_device_from_ID3D12VideoDevice(iface);
    return d3d12_device_query_interface(device, riid, object);
}

static HRESULT d3d12_video_device_CheckFeatureSupport(d3d12_video_device_iface *iface,
        D3D12_FEATURE_VIDEO feature_video,
        void *feature_support,
        UINT feature_support_data_size)
{
  TRACE("iface %p, feature_video: %u, feature_support %p, feature_support_data_size %u.\n", iface, feature_video, feature_support, feature_support_data_size);

  if (feature_video == D3D12_FEATURE_VIDEO_PROCESS_REFERENCE_INFO) {
    D3D12_FEATURE_DATA_VIDEO_PROCESS_REFERENCE_INFO *feature_info = (D3D12_FEATURE_DATA_VIDEO_PROCESS_REFERENCE_INFO*) feature_support;
    feature_info->NodeIndex = 0;
    feature_info->DeinterlaceMode = D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_BOB;
    feature_info->Filters = D3D12_VIDEO_PROCESS_FILTER_FLAG_BRIGHTNESS | D3D12_VIDEO_PROCESS_FILTER_FLAG_CONTRAST | D3D12_VIDEO_PROCESS_FILTER_FLAG_HUE
    | D3D12_VIDEO_PROCESS_FILTER_FLAG_SATURATION | D3D12_VIDEO_PROCESS_FILTER_FLAG_NOISE_REDUCTION | D3D12_VIDEO_PROCESS_FILTER_FLAG_EDGE_ENHANCEMENT
    |D3D12_VIDEO_PROCESS_FILTER_FLAG_ANAMORPHIC_SCALING | D3D12_VIDEO_PROCESS_FILTER_FLAG_STEREO_ADJUSTMENT;
    feature_info->FeatureSupport = D3D12_VIDEO_PROCESS_FEATURE_FLAG_ALPHA_FILL | D3D12_VIDEO_PROCESS_FEATURE_FLAG_LUMA_KEY |D3D12_VIDEO_PROCESS_FEATURE_FLAG_ROTATION | D3D12_VIDEO_PROCESS_FEATURE_FLAG_STEREO | D3D12_VIDEO_PROCESS_FEATURE_FLAG_FLIP
    | D3D12_VIDEO_PROCESS_FEATURE_FLAG_ALPHA_BLENDING | D3D12_VIDEO_PROCESS_FEATURE_FLAG_PIXEL_ASPECT_RATIO;
    feature_info->InputFrameRate = (DXGI_RATIONAL) {
      .Numerator = 1,
      .Denominator = 60,
    };
    feature_info->OutputFrameRate = (DXGI_RATIONAL) {
      .Numerator = 1,
      .Denominator = 60,
    };
    feature_info->EnableAutoProcessing = TRUE;
    feature_info->PastFrames = 0;
    feature_info->FutureFrames = 999;

    return S_OK;
  }

  if (feature_video == D3D12_FEATURE_VIDEO_PROCESS_MAX_INPUT_STREAMS) {
    D3D12_FEATURE_DATA_VIDEO_PROCESS_MAX_INPUT_STREAMS  *feature_info = (D3D12_FEATURE_DATA_VIDEO_PROCESS_MAX_INPUT_STREAMS *) feature_support;
    feature_info->NodeIndex = 0;
    feature_info->MaxInputStreams = 16;
    TRACE("Returning 16 streams\n");
    return S_OK;
  }

  return E_NOTIMPL;
}

static HRESULT d3d12_video_device_CreateVideoDecoder(d3d12_video_device_iface *iface,
        const D3D12_VIDEO_DECODER_DESC *desc,
        REFIID riid,
        void **video_decoder)
{
  TRACE("iface %p, desc %p, riid %p, video_decoder: %p.\n", iface, desc, riid, video_decoder);

  return E_NOTIMPL;

}

static HRESULT d3d12_video_device_CreateVideoDecoderHeap(d3d12_video_device_iface *iface,
        const D3D12_VIDEO_DECODER_HEAP_DESC *desc,
        REFIID riid,
        void **video_decoder_heap)
{
  TRACE("iface %p, desc %p, riid %u, video_decoder: %p.\n", iface, desc, riid, video_decoder_heap);

  return E_NOTIMPL;
}

static HRESULT d3d12_video_device_CreateVideoProcessor(d3d12_video_device_iface *iface,
        UINT node_mask,
        const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC *output_stream_desc,
        UINT num_input_stream_descs,
        const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *input_stream_descs,
        REFIID riid,
        void **video_processor)
{
  TRACE("iface %p, node_mask: %u, output_stream_desc %p, num_input_stream_descs %u, input_stream_descs %p, riid %u, video_decoder: %p.\n", iface, node_mask, output_stream_desc, num_input_stream_descs, input_stream_descs, riid, video_processor);

  return E_NOTIMPL;
}

CONST_VTBL struct ID3D12VideoDeviceVtbl d3d12_video_device_vtbl =
{
    /* IUnknown methods */
    d3d12_video_device_QueryInterface,
    d3d12_video_device_AddRef,
    d3d12_video_device_Release,
    d3d12_video_device_CheckFeatureSupport,
    d3d12_video_device_CreateVideoDecoder,
    d3d12_video_device_CreateVideoDecoderHeap,
    d3d12_video_device_CreateVideoProcessor
};
