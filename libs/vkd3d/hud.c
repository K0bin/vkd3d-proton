/*
 * Copyright (c) 2023 Robin Kertels
 * Copyright (c) 2017 Philip Rebohle
 *
 * SPDX-License-Identifier: MIT
 */

#define VKD3D_DBG_CHANNEL VKD3D_DBG_CHANNEL_API

#include "vkd3d_private.h"

#include "hud_text_vert.h"
#include "hud_text_frag.h"
#include "hud_graph_vert.h"
#include "hud_graph_frag.h"

struct vkd3d_hud
{
    struct d3d12_device *device;
    VkPipeline text_pipeline;
};

static vkd3d_hud_create_pipelines(struct d3d12_device *device, VkPipeline *pipeline, VkFormat format, VkImageLayout layout)
{
    const struct vkd3d_vk_device_procs *vk_procs = &device->vk_procs;
    VkPipelineShaderStageCreateInfo shader_stages[2];
    VkPipelineInputAssemblyStateCreateInfo ia_state;
    VkPipelineRasterizationStateCreateInfo rs_state;
    VkPipelineRenderingCreateInfoKHR rendering_info;
    VkPipelineVertexInputStateCreateInfo vi_state;
    VkPipelineMultisampleStateCreateInfo ms_state;
    VkPipelineViewportStateCreateInfo vp_state;
    VkPipelineDynamicStateCreateInfo dyn_state;
    VkGraphicsPipelineCreateInfo pipeline_info;
    VkShaderModuleCreateInfo shader_info;
    VkShaderModule shaders[2];
    const uint32_t sample_mask = 0xFFFFFFFF;
    VkResult vr;

    static const VkDynamicState dynamic_states[] =
    {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };

    vi_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vi_state.pNext = NULL;
    vi_state.flags = 0;
    vi_state.vertexBindingDescriptionCount = 0;
    vi_state.pVertexBindingDescriptions = NULL;
    vi_state.vertexAttributeDescriptionCount = 0;
    vi_state.pVertexAttributeDescriptions = NULL;

    ia_state.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia_state.pNext = NULL;
    ia_state.flags = 0;
    ia_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    ia_state.primitiveRestartEnable = false;

    vp_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp_state.pNext = NULL;
    vp_state.flags = 0;
    vp_state.viewportCount = 1;
    vp_state.pViewports = NULL;
    vp_state.scissorCount = 1;
    vp_state.pScissors = NULL;

    rs_state.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rs_state.pNext = NULL;
    rs_state.flags = 0;
    rs_state.depthClampEnable = VK_TRUE;
    rs_state.rasterizerDiscardEnable = VK_FALSE;
    rs_state.polygonMode = VK_POLYGON_MODE_FILL;
    rs_state.cullMode = VK_CULL_MODE_NONE;
    rs_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rs_state.depthBiasEnable = VK_FALSE;
    rs_state.depthBiasConstantFactor = 0.0f;
    rs_state.depthBiasClamp = 0.0f;
    rs_state.depthBiasSlopeFactor = 0.0f;
    rs_state.lineWidth = 1.0f;

    ms_state.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms_state.pNext = NULL;
    ms_state.flags = 0;
    ms_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    ms_state.sampleShadingEnable = false;
    ms_state.minSampleShading = 1.0f;
    ms_state.pSampleMask = &sample_mask;
    ms_state.alphaToCoverageEnable = VK_FALSE;
    ms_state.alphaToOneEnable = VK_FALSE;

    dyn_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn_state.pNext = NULL;
    dyn_state.flags = 0;
    dyn_state.dynamicStateCount = ARRAY_SIZE(dynamic_states);
    dyn_state.pDynamicStates = dynamic_states;

    rendering_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
    rendering_info.pNext = NULL;
    rendering_info.viewMask = 0;
    rendering_info.colorAttachmentCount = 1;
    rendering_info.pColorAttachmentFormats = &format;
    rendering_info.depthAttachmentFormat = VK_FORMAT_UNDEFINED;
    rendering_info.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;

    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.pNext = &rendering_info;
    pipeline_info.flags = 0;
    pipeline_info.stageCount = 0;
    pipeline_info.pStages = shader_stages;
    pipeline_info.pVertexInputState = &vi_state;
    pipeline_info.pInputAssemblyState = &ia_state;
    pipeline_info.pTessellationState = NULL;
    pipeline_info.pViewportState = &vp_state;
    pipeline_info.pRasterizationState = &rs_state;
    pipeline_info.pMultisampleState = &ms_state;
    pipeline_info.pDepthStencilState = ds_state;
    pipeline_info.pColorBlendState = cb_state;
    pipeline_info.pDynamicState = &dyn_state;
    pipeline_info.layout = layout;
    pipeline_info.renderPass = VK_NULL_HANDLE;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
    pipeline_info.basePipelineIndex = -1;

    if (d3d12_device_uses_descriptor_buffers(device))
        pipeline_info.flags |= VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT;

    shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shader_info.pNext = NULL;
    shader_info.codeSize = sizeof(hud_text_vert);
    shader_info.flags = 0;
    shader_info.pCode = hud_text_vert;
    VK_CALL(vkCreateShaderModule(device->vk_device, &shader_info, NULL, &shaders[0]));

    shader_info.codeSize = sizeof(hud_text_frag);
    shader_info.pCode = hud_text_frag;
    VK_CALL(vkCreateShaderModule(device->vk_device, &shader_info, NULL, &shaders[1]));

    shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shader_stages[0].flags = 0;
    shader_stages[0].pNext = NULL;
    shader_stages[0].pName = NULL; // TODO
    shader_stages[0].module = shaders[0];
    shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shader_stages[0].pSpecializationInfo = NULL;

    shader_stages[0] = shader_stages[1];
    shader_stages[0].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shader_stages[0].module = shaders[1];
}


HRESULT vkd3d_hud_create(struct d3d12_device *device, struct vkd3d_hud **hud)
{
    const struct vkd3d_vk_device_procs *vk_procs = &device->vk_procs;
    VkCommandPoolCreateInfo pool_create_info;
    struct vkd3d_hud *object;
    uint32_t i;

    if (!(object = vkd3d_malloc(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->device = device;

    vkd3d_hud_create_pipelines(device, &object->text_pipeline);

    return S_OK;
}

static void vkd3d_hud_begin_text_rendering(struct vkd3d_hud *hud)
{

}

void vkd3d_hud_render(struct vkd3d_hud *hud,
        VkCommandBuffer vk_cmd,
        VkImageView image_view,
        VkSurfaceFormatKHR surface_format,
        VkExtent2D surface_size)
{
    const struct vkd3d_vk_device_procs *vk_procs = &hud->device->vk_procs;
    VkRenderingAttachmentInfo attachment_info;
    VkRenderingInfo rendering_info;
    VkViewport viewport;

    memset(&attachment_info, 0, sizeof(attachment_info));
    attachment_info.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
    attachment_info.imageView = image_view;
    attachment_info.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachment_info.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    attachment_info.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    memset(&rendering_info, 0, sizeof(rendering_info));
    rendering_info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
    rendering_info.renderArea.extent = surface_size;
    rendering_info.layerCount = 1;
    rendering_info.colorAttachmentCount = 1;
    rendering_info.pColorAttachments = &attachment_info;

    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = surface_size.width;
    viewport.height = surface_size.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VK_CALL(vkCmdPipelineBarrier(vk_cmd,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                0, 0, NULL, 0, NULL, 0, NULL));

    VK_CALL(vkCmdBeginRendering(vk_cmd, &rendering_info));
    
    VK_CALL(vkCmdSetViewport(vk_cmd, 0, 1, &viewport));
    VK_CALL(vkCmdSetScissor(vk_cmd, 0, 1, &rendering_info.renderArea));

}
