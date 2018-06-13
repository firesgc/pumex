//
// Copyright(c) 2017-2018 Paweł Księżopolski ( pumexx )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#pragma once
#include <vulkan/vulkan.h>
#include <pumex/Export.h>
#include <pumex/NodeVisitor.h>
#include <pumex/RenderContext.h>

namespace pumex
{
	
class CommandBuffer;

class PUMEX_EXPORT FindSecondaryCommandBuffersVisitor : public NodeVisitor
{
public:
  FindSecondaryCommandBuffersVisitor();

  void apply(Node& node) override;
  void apply(Group& node) override;

  std::set<Node*> nodes;
};

// visitor that validates all dirty nodes ( pipelines etc ).
class PUMEX_EXPORT ValidateNodeVisitor : public NodeVisitor
{
public:
  ValidateNodeVisitor(const RenderContext& renderContext);

  void apply(Node& node) override;

  RenderContext renderContext;
};

// visitor that validates all dirty descriptor sets and descriptors
class PUMEX_EXPORT ValidateDescriptorVisitor : public NodeVisitor
{
public:
  ValidateDescriptorVisitor(const RenderContext& renderContext);

  void apply(Node& node) override;

  RenderContext renderContext;
};

// visitor that collects missing data for render contexts while building secondary command buffers
const uint32_t CRCV_TARGETS = 2;

class PUMEX_EXPORT CompleteRenderContextVisitor : public NodeVisitor
{
public:
  CompleteRenderContextVisitor(RenderContext& renderContext);

  void apply(GraphicsPipeline& node) override;
  void apply(ComputePipeline& node) override;
  void apply(AssetBufferNode& node) override;
protected:
  RenderContext& renderContext;
  bool           targetCompleted[CRCV_TARGETS];
};


// visitor that builds command buffers
class PUMEX_EXPORT BuildCommandBufferVisitor : public NodeVisitor
{
public:
  BuildCommandBufferVisitor(const RenderContext& renderContext, CommandBuffer* commandBuffer);

  void apply(Node& node) override;
  void apply(GraphicsPipeline& node) override;
  void apply(ComputePipeline& node) override;
  void apply(AssetBufferNode& node) override;
  void apply(AssetBufferDrawObject& node) override;
  void apply(AssetBufferIndirectDrawObjects& node) override;
  void apply(AssetNode& node) override;
  void apply(DispatchNode& node) override;
  void apply(Text& node) override;

  void applyDescriptorSets(Node& node);

  // elements of the context that are constant through visitor work
  RenderContext renderContext;
  CommandBuffer* commandBuffer;
};

}