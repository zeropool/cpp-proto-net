// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace entity {

namespace {

const ::google::protobuf::Descriptor* LegItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LegItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* PortfolioItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PortfolioItem_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_message_2eproto() {
  protobuf_AddDesc_message_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "message.proto");
  GOOGLE_CHECK(file != NULL);
  LegItem_descriptor_ = file->message_type(0);
  static const int LegItem_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LegItem, symbol_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LegItem, ratio_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LegItem, side_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LegItem, status_),
  };
  LegItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LegItem_descriptor_,
      LegItem::default_instance_,
      LegItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LegItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LegItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LegItem));
  PortfolioItem_descriptor_ = file->message_type(1);
  static const int PortfolioItem_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, quantity_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, diff_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, autoopen_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, autoclose_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, legs_),
  };
  PortfolioItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      PortfolioItem_descriptor_,
      PortfolioItem::default_instance_,
      PortfolioItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PortfolioItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(PortfolioItem));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_message_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LegItem_descriptor_, &LegItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    PortfolioItem_descriptor_, &PortfolioItem::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_message_2eproto() {
  delete LegItem::default_instance_;
  delete LegItem_reflection_;
  delete PortfolioItem::default_instance_;
  delete PortfolioItem_reflection_;
}

void protobuf_AddDesc_message_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::entity::protobuf_AddDesc_enum_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rmessage.proto\022\006entity\032\nenum.proto\"t\n\007L"
    "egItem\022\016\n\006Symbol\030\001 \002(\t\022\r\n\005Ratio\030\002 \002(\005\022\'\n"
    "\004Side\030\003 \002(\0162\031.entity.PosiDirectionType\022!"
    "\n\006Status\030\004 \002(\0162\021.entity.LegStatus\"\177\n\rPor"
    "tfolioItem\022\n\n\002ID\030\001 \002(\t\022\020\n\010Quantity\030\002 \002(\005"
    "\022\014\n\004Diff\030\003 \002(\001\022\020\n\010AutoOpen\030\004 \002(\010\022\021\n\tAuto"
    "Close\030\005 \002(\010\022\035\n\004Legs\030\006 \003(\0132\017.entity.LegIt"
    "em", 282);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message.proto", &protobuf_RegisterTypes);
  LegItem::default_instance_ = new LegItem();
  PortfolioItem::default_instance_ = new PortfolioItem();
  LegItem::default_instance_->InitAsDefaultInstance();
  PortfolioItem::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_message_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_message_2eproto {
  StaticDescriptorInitializer_message_2eproto() {
    protobuf_AddDesc_message_2eproto();
  }
} static_descriptor_initializer_message_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int LegItem::kSymbolFieldNumber;
const int LegItem::kRatioFieldNumber;
const int LegItem::kSideFieldNumber;
const int LegItem::kStatusFieldNumber;
#endif  // !_MSC_VER

LegItem::LegItem()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LegItem::InitAsDefaultInstance() {
}

LegItem::LegItem(const LegItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LegItem::SharedCtor() {
  _cached_size_ = 0;
  symbol_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ratio_ = 0;
  side_ = 49;
  status_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LegItem::~LegItem() {
  SharedDtor();
}

void LegItem::SharedDtor() {
  if (symbol_ != &::google::protobuf::internal::kEmptyString) {
    delete symbol_;
  }
  if (this != default_instance_) {
  }
}

void LegItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LegItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LegItem_descriptor_;
}

const LegItem& LegItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_message_2eproto();  return *default_instance_;
}

LegItem* LegItem::default_instance_ = NULL;

LegItem* LegItem::New() const {
  return new LegItem;
}

void LegItem::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_symbol()) {
      if (symbol_ != &::google::protobuf::internal::kEmptyString) {
        symbol_->clear();
      }
    }
    ratio_ = 0;
    side_ = 49;
    status_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LegItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string Symbol = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_symbol()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->symbol().data(), this->symbol().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_Ratio;
        break;
      }
      
      // required int32 Ratio = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Ratio:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ratio_)));
          set_has_ratio();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_Side;
        break;
      }
      
      // required .entity.PosiDirectionType Side = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Side:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (entity::PosiDirectionType_IsValid(value)) {
            set_side(static_cast< entity::PosiDirectionType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(3, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_Status;
        break;
      }
      
      // required .entity.LegStatus Status = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Status:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (entity::LegStatus_IsValid(value)) {
            set_status(static_cast< entity::LegStatus >(value));
          } else {
            mutable_unknown_fields()->AddVarint(4, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LegItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string Symbol = 1;
  if (has_symbol()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->symbol().data(), this->symbol().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->symbol(), output);
  }
  
  // required int32 Ratio = 2;
  if (has_ratio()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->ratio(), output);
  }
  
  // required .entity.PosiDirectionType Side = 3;
  if (has_side()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->side(), output);
  }
  
  // required .entity.LegStatus Status = 4;
  if (has_status()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->status(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LegItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string Symbol = 1;
  if (has_symbol()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->symbol().data(), this->symbol().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->symbol(), target);
  }
  
  // required int32 Ratio = 2;
  if (has_ratio()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->ratio(), target);
  }
  
  // required .entity.PosiDirectionType Side = 3;
  if (has_side()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->side(), target);
  }
  
  // required .entity.LegStatus Status = 4;
  if (has_status()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      4, this->status(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LegItem::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string Symbol = 1;
    if (has_symbol()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->symbol());
    }
    
    // required int32 Ratio = 2;
    if (has_ratio()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->ratio());
    }
    
    // required .entity.PosiDirectionType Side = 3;
    if (has_side()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->side());
    }
    
    // required .entity.LegStatus Status = 4;
    if (has_status()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->status());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LegItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LegItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LegItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LegItem::MergeFrom(const LegItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_symbol()) {
      set_symbol(from.symbol());
    }
    if (from.has_ratio()) {
      set_ratio(from.ratio());
    }
    if (from.has_side()) {
      set_side(from.side());
    }
    if (from.has_status()) {
      set_status(from.status());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LegItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LegItem::CopyFrom(const LegItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LegItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;
  
  return true;
}

void LegItem::Swap(LegItem* other) {
  if (other != this) {
    std::swap(symbol_, other->symbol_);
    std::swap(ratio_, other->ratio_);
    std::swap(side_, other->side_);
    std::swap(status_, other->status_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LegItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LegItem_descriptor_;
  metadata.reflection = LegItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int PortfolioItem::kIDFieldNumber;
const int PortfolioItem::kQuantityFieldNumber;
const int PortfolioItem::kDiffFieldNumber;
const int PortfolioItem::kAutoOpenFieldNumber;
const int PortfolioItem::kAutoCloseFieldNumber;
const int PortfolioItem::kLegsFieldNumber;
#endif  // !_MSC_VER

PortfolioItem::PortfolioItem()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void PortfolioItem::InitAsDefaultInstance() {
}

PortfolioItem::PortfolioItem(const PortfolioItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void PortfolioItem::SharedCtor() {
  _cached_size_ = 0;
  id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  quantity_ = 0;
  diff_ = 0;
  autoopen_ = false;
  autoclose_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PortfolioItem::~PortfolioItem() {
  SharedDtor();
}

void PortfolioItem::SharedDtor() {
  if (id_ != &::google::protobuf::internal::kEmptyString) {
    delete id_;
  }
  if (this != default_instance_) {
  }
}

void PortfolioItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PortfolioItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PortfolioItem_descriptor_;
}

const PortfolioItem& PortfolioItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_message_2eproto();  return *default_instance_;
}

PortfolioItem* PortfolioItem::default_instance_ = NULL;

PortfolioItem* PortfolioItem::New() const {
  return new PortfolioItem;
}

void PortfolioItem::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_id()) {
      if (id_ != &::google::protobuf::internal::kEmptyString) {
        id_->clear();
      }
    }
    quantity_ = 0;
    diff_ = 0;
    autoopen_ = false;
    autoclose_ = false;
  }
  legs_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool PortfolioItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string ID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->id().data(), this->id().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_Quantity;
        break;
      }
      
      // required int32 Quantity = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Quantity:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &quantity_)));
          set_has_quantity();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(25)) goto parse_Diff;
        break;
      }
      
      // required double Diff = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_Diff:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &diff_)));
          set_has_diff();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_AutoOpen;
        break;
      }
      
      // required bool AutoOpen = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_AutoOpen:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &autoopen_)));
          set_has_autoopen();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_AutoClose;
        break;
      }
      
      // required bool AutoClose = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_AutoClose:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &autoclose_)));
          set_has_autoclose();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_Legs;
        break;
      }
      
      // repeated .entity.LegItem Legs = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_Legs:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_legs()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_Legs;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void PortfolioItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string ID = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->id(), output);
  }
  
  // required int32 Quantity = 2;
  if (has_quantity()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->quantity(), output);
  }
  
  // required double Diff = 3;
  if (has_diff()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->diff(), output);
  }
  
  // required bool AutoOpen = 4;
  if (has_autoopen()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->autoopen(), output);
  }
  
  // required bool AutoClose = 5;
  if (has_autoclose()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->autoclose(), output);
  }
  
  // repeated .entity.LegItem Legs = 6;
  for (int i = 0; i < this->legs_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->legs(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* PortfolioItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string ID = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->id(), target);
  }
  
  // required int32 Quantity = 2;
  if (has_quantity()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->quantity(), target);
  }
  
  // required double Diff = 3;
  if (has_diff()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->diff(), target);
  }
  
  // required bool AutoOpen = 4;
  if (has_autoopen()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->autoopen(), target);
  }
  
  // required bool AutoClose = 5;
  if (has_autoclose()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->autoclose(), target);
  }
  
  // repeated .entity.LegItem Legs = 6;
  for (int i = 0; i < this->legs_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->legs(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int PortfolioItem::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string ID = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->id());
    }
    
    // required int32 Quantity = 2;
    if (has_quantity()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->quantity());
    }
    
    // required double Diff = 3;
    if (has_diff()) {
      total_size += 1 + 8;
    }
    
    // required bool AutoOpen = 4;
    if (has_autoopen()) {
      total_size += 1 + 1;
    }
    
    // required bool AutoClose = 5;
    if (has_autoclose()) {
      total_size += 1 + 1;
    }
    
  }
  // repeated .entity.LegItem Legs = 6;
  total_size += 1 * this->legs_size();
  for (int i = 0; i < this->legs_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->legs(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void PortfolioItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const PortfolioItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PortfolioItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PortfolioItem::MergeFrom(const PortfolioItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  legs_.MergeFrom(from.legs_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_quantity()) {
      set_quantity(from.quantity());
    }
    if (from.has_diff()) {
      set_diff(from.diff());
    }
    if (from.has_autoopen()) {
      set_autoopen(from.autoopen());
    }
    if (from.has_autoclose()) {
      set_autoclose(from.autoclose());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void PortfolioItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PortfolioItem::CopyFrom(const PortfolioItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PortfolioItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  
  for (int i = 0; i < legs_size(); i++) {
    if (!this->legs(i).IsInitialized()) return false;
  }
  return true;
}

void PortfolioItem::Swap(PortfolioItem* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(quantity_, other->quantity_);
    std::swap(diff_, other->diff_);
    std::swap(autoopen_, other->autoopen_);
    std::swap(autoclose_, other->autoclose_);
    legs_.Swap(&other->legs_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata PortfolioItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PortfolioItem_descriptor_;
  metadata.reflection = PortfolioItem_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace entity

// @@protoc_insertion_point(global_scope)