/*
Copyright (c) 2021, NVIDIA CORPORATION. All rights reserved.

NVIDIA CORPORATION and its licensors retain all intellectual property
and proprietary rights in and to this software, related documentation
and any modifications thereto. Any use, reproduction, disclosure or
distribution of this software and related documentation without an express
license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#ifndef NVIDIA_GXF_BT_SELECTOR_BEHAVIOR_HPP_
#define NVIDIA_GXF_BT_SELECTOR_BEHAVIOR_HPP_

#include <vector>

#include "gxf/std/codelet.hpp"
#include "gxf/std/controller.hpp"
#include "gxf/std/scheduling_terms.hpp"

namespace nvidia {
namespace gxf {

// Selector Behavior
// Runs all child entites in sequence until one succeeds, then reports success.
// If all child entities fail (or no child entities are present), this codelet
// fails.
class SelectorBehavior : public Codelet {
 public:
  virtual ~SelectorBehavior() = default;

  gxf_result_t registerInterface(Registrar* registrar) override;
  gxf_result_t initialize() override;
  gxf_result_t start() override { return GXF_SUCCESS; }
  gxf_result_t tick() override;
  gxf_result_t stop() override { return GXF_SUCCESS; }

 private:
  // parent codelet points to children's scheduling terms to schedule child
  // entities
  Parameter<std::vector<Handle<nvidia::gxf::BTSchedulingTerm> > > children_;
  std::vector<Handle<nvidia::gxf::BTSchedulingTerm> > children;
  std::vector<gxf_uid_t> children_eid;
  // its own scheduling term to start/stop itself
  Parameter<Handle<nvidia::gxf::BTSchedulingTerm> > s_term_;
  Handle<nvidia::gxf::BTSchedulingTerm> s_term;
  size_t getNumChildren() const;
  entity_state_t GetChildStatus(size_t child_id);
  gxf_result_t startChild(size_t child_id);
  size_t current_child_id;
  SchedulingConditionType ready_conditions;
  SchedulingConditionType never_conditions;
};

}  // namespace gxf
}  // namespace nvidia

#endif  // NVIDIA_GXF_BT_SELECTOR_BEHAVIOR_HPP_
