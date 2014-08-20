// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: enum.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "enum.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace entity {

namespace {

const ::google::protobuf::EnumDescriptor* PosiDirectionType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* PosiOffsetFlag_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* LegStatus_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* LimitPriceType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* CompareCondition_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_enum_2eproto() {
  protobuf_AddDesc_enum_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "enum.proto");
  GOOGLE_CHECK(file != NULL);
  PosiDirectionType_descriptor_ = file->enum_type(0);
  PosiOffsetFlag_descriptor_ = file->enum_type(1);
  LegStatus_descriptor_ = file->enum_type(2);
  LimitPriceType_descriptor_ = file->enum_type(3);
  CompareCondition_descriptor_ = file->enum_type(4);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_enum_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_enum_2eproto() {
}

void protobuf_AddDesc_enum_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nenum.proto\022\006entity*1\n\021PosiDirectionTyp"
    "e\022\007\n\003NET\0201\022\010\n\004LONG\0202\022\t\n\005SHORT\0203*%\n\016PosiO"
    "ffsetFlag\022\010\n\004OPEN\020\000\022\t\n\005CLOSE\020\001*Q\n\tLegSta"
    "tus\022\014\n\010UNOPENED\020\000\022\016\n\nIS_OPENING\020\001\022\n\n\006OPE"
    "NED\020\002\022\016\n\nIS_CLOSING\020\003\022\n\n\006CLOSED\020\004*(\n\016Lim"
    "itPriceType\022\010\n\004Last\020\000\022\014\n\010Opposite\020\001*`\n\020C"
    "ompareCondition\022\020\n\014GREATER_THAN\020\000\022\026\n\022GRE"
    "ATER_EQUAL_THAN\020\001\022\r\n\tLESS_THAN\020\002\022\023\n\017LESS"
    "_EQUAL_THAN\020\003", 333);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "enum.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_enum_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_enum_2eproto {
  StaticDescriptorInitializer_enum_2eproto() {
    protobuf_AddDesc_enum_2eproto();
  }
} static_descriptor_initializer_enum_2eproto_;
const ::google::protobuf::EnumDescriptor* PosiDirectionType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PosiDirectionType_descriptor_;
}
bool PosiDirectionType_IsValid(int value) {
  switch(value) {
    case 49:
    case 50:
    case 51:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* PosiOffsetFlag_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PosiOffsetFlag_descriptor_;
}
bool PosiOffsetFlag_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* LegStatus_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LegStatus_descriptor_;
}
bool LegStatus_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* LimitPriceType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LimitPriceType_descriptor_;
}
bool LimitPriceType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* CompareCondition_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CompareCondition_descriptor_;
}
bool CompareCondition_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace entity

// @@protoc_insertion_point(global_scope)
