/*
 * SPDX-FileCopyrightText: Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef NVIDIA_GXF_EXTENSIONS_TENSOR_RT_TEST_TENSOR_CHECKER_HPP_
#define NVIDIA_GXF_EXTENSIONS_TENSOR_RT_TEST_TENSOR_CHECKER_HPP_

#include <string>
#include <vector>

#include "gxf/std/allocator.hpp"
#include "gxf/std/codelet.hpp"
#include "gxf/std/receiver.hpp"
#include "gxf/std/tensor.hpp"

namespace nvidia {
namespace gxf {

// Verifies the content of result tensor for TensorRTInference codelet.
// Checks expected dimensions, tensor name, and where the max value presents.
class TensorChecker : public gxf::Codelet {
 public:
  gxf_result_t start() override;

  gxf_result_t tick() override;

  gxf_result_t stop() override;

  gxf_result_t registerInterface(gxf::Registrar* registrar) override;

 private:
  gxf::Parameter<gxf::Handle<gxf::Receiver>> rx_;
  gxf::Parameter<std::string> tensor_name_;
  gxf::Parameter<std::vector<int32_t>> dimensions_;
  gxf::Parameter<uint64_t> max_element_offset_;
};

}  // namespace gxf
}  // namespace nvidia

#endif  // NVIDIA_GXF_EXTENSIONS_TENSOR_RT_TEST_TENSOR_CHECKER_HPP_
