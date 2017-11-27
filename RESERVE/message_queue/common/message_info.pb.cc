// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_info.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message_info.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace msg_info {
class msgDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<msg>
     _instance;
} _msg_default_instance_;

namespace protobuf_message_5finfo_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg, from_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg, name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg, type_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(msg, data_),
  0,
  1,
  3,
  2,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, sizeof(msg)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_msg_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "message_info.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _msg_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_msg_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\022message_info.proto\022\010msg_info\"\216\001\n\003msg\022\017"
      "\n\007from_id\030\001 \002(\t\022\014\n\004name\030\002 \002(\t\022\'\n\004type\030\003 "
      "\001(\0162\023.msg_info.msg._TYPE:\004INFO\022\014\n\004data\030\004"
      " \001(\t\"1\n\005_TYPE\022\t\n\005DEBUG\020\001\022\010\n\004INFO\020\002\022\010\n\004WA"
      "RN\020\003\022\t\n\005ERROR\020\004"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 175);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message_info.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_message_5finfo_2eproto

const ::google::protobuf::EnumDescriptor* msg__TYPE_descriptor() {
  protobuf_message_5finfo_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_message_5finfo_2eproto::file_level_enum_descriptors[0];
}
bool msg__TYPE_IsValid(int value) {
  switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const msg__TYPE msg::DEBUG;
const msg__TYPE msg::INFO;
const msg__TYPE msg::WARN;
const msg__TYPE msg::ERROR;
const msg__TYPE msg::_TYPE_MIN;
const msg__TYPE msg::_TYPE_MAX;
const int msg::_TYPE_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int msg::kFromIdFieldNumber;
const int msg::kNameFieldNumber;
const int msg::kTypeFieldNumber;
const int msg::kDataFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

msg::msg()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_message_5finfo_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:msg_info.msg)
}
msg::msg(const msg& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  from_id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_from_id()) {
    from_id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.from_id_);
  }
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_name()) {
    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_data()) {
    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:msg_info.msg)
}

void msg::SharedCtor() {
  _cached_size_ = 0;
  from_id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  type_ = 2;
}

msg::~msg() {
  // @@protoc_insertion_point(destructor:msg_info.msg)
  SharedDtor();
}

void msg::SharedDtor() {
  from_id_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void msg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* msg::descriptor() {
  protobuf_message_5finfo_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_message_5finfo_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const msg& msg::default_instance() {
  protobuf_message_5finfo_2eproto::InitDefaults();
  return *internal_default_instance();
}

msg* msg::New(::google::protobuf::Arena* arena) const {
  msg* n = new msg;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void msg::Clear() {
// @@protoc_insertion_point(message_clear_start:msg_info.msg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 15u) {
    if (cached_has_bits & 0x00000001u) {
      GOOGLE_DCHECK(!from_id_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*from_id_.UnsafeRawStringPointer())->clear();
    }
    if (cached_has_bits & 0x00000002u) {
      GOOGLE_DCHECK(!name_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*name_.UnsafeRawStringPointer())->clear();
    }
    if (cached_has_bits & 0x00000004u) {
      GOOGLE_DCHECK(!data_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*data_.UnsafeRawStringPointer())->clear();
    }
    type_ = 2;
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool msg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:msg_info.msg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string from_id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_from_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->from_id().data(), static_cast<int>(this->from_id().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "msg_info.msg.from_id");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required string name = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), static_cast<int>(this->name().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "msg_info.msg.name");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional .msg_info.msg._TYPE type = 3 [default = INFO];
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::msg_info::msg__TYPE_IsValid(value)) {
            set_type(static_cast< ::msg_info::msg__TYPE >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                3, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string data = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_data()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->data().data(), static_cast<int>(this->data().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "msg_info.msg.data");
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:msg_info.msg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:msg_info.msg)
  return false;
#undef DO_
}

void msg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:msg_info.msg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string from_id = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->from_id().data(), static_cast<int>(this->from_id().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "msg_info.msg.from_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->from_id(), output);
  }

  // required string name = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), static_cast<int>(this->name().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "msg_info.msg.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->name(), output);
  }

  // optional .msg_info.msg._TYPE type = 3 [default = INFO];
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->type(), output);
  }

  // optional string data = 4;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "msg_info.msg.data");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->data(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:msg_info.msg)
}

::google::protobuf::uint8* msg::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:msg_info.msg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string from_id = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->from_id().data(), static_cast<int>(this->from_id().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "msg_info.msg.from_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->from_id(), target);
  }

  // required string name = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), static_cast<int>(this->name().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "msg_info.msg.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }

  // optional .msg_info.msg._TYPE type = 3 [default = INFO];
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->type(), target);
  }

  // optional string data = 4;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "msg_info.msg.data");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->data(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:msg_info.msg)
  return target;
}

size_t msg::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:msg_info.msg)
  size_t total_size = 0;

  if (has_from_id()) {
    // required string from_id = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->from_id());
  }

  if (has_name()) {
    // required string name = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  return total_size;
}
size_t msg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:msg_info.msg)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required string from_id = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->from_id());

    // required string name = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_has_bits_[0 / 32] & 12u) {
    // optional string data = 4;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->data());
    }

    // optional .msg_info.msg._TYPE type = 3 [default = INFO];
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void msg::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:msg_info.msg)
  GOOGLE_DCHECK_NE(&from, this);
  const msg* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const msg>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:msg_info.msg)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:msg_info.msg)
    MergeFrom(*source);
  }
}

void msg::MergeFrom(const msg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:msg_info.msg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 15u) {
    if (cached_has_bits & 0x00000001u) {
      set_has_from_id();
      from_id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.from_id_);
    }
    if (cached_has_bits & 0x00000002u) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (cached_has_bits & 0x00000004u) {
      set_has_data();
      data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
    }
    if (cached_has_bits & 0x00000008u) {
      type_ = from.type_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void msg::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:msg_info.msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void msg::CopyFrom(const msg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:msg_info.msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void msg::Swap(msg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void msg::InternalSwap(msg* other) {
  using std::swap;
  from_id_.Swap(&other->from_id_);
  name_.Swap(&other->name_);
  data_.Swap(&other->data_);
  swap(type_, other->type_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata msg::GetMetadata() const {
  protobuf_message_5finfo_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_message_5finfo_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// msg

// required string from_id = 1;
bool msg::has_from_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void msg::set_has_from_id() {
  _has_bits_[0] |= 0x00000001u;
}
void msg::clear_has_from_id() {
  _has_bits_[0] &= ~0x00000001u;
}
void msg::clear_from_id() {
  from_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_from_id();
}
const ::std::string& msg::from_id() const {
  // @@protoc_insertion_point(field_get:msg_info.msg.from_id)
  return from_id_.GetNoArena();
}
void msg::set_from_id(const ::std::string& value) {
  set_has_from_id();
  from_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:msg_info.msg.from_id)
}
#if LANG_CXX11
void msg::set_from_id(::std::string&& value) {
  set_has_from_id();
  from_id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:msg_info.msg.from_id)
}
#endif
void msg::set_from_id(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_from_id();
  from_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:msg_info.msg.from_id)
}
void msg::set_from_id(const char* value, size_t size) {
  set_has_from_id();
  from_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:msg_info.msg.from_id)
}
::std::string* msg::mutable_from_id() {
  set_has_from_id();
  // @@protoc_insertion_point(field_mutable:msg_info.msg.from_id)
  return from_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* msg::release_from_id() {
  // @@protoc_insertion_point(field_release:msg_info.msg.from_id)
  clear_has_from_id();
  return from_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void msg::set_allocated_from_id(::std::string* from_id) {
  if (from_id != NULL) {
    set_has_from_id();
  } else {
    clear_has_from_id();
  }
  from_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from_id);
  // @@protoc_insertion_point(field_set_allocated:msg_info.msg.from_id)
}

// required string name = 2;
bool msg::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void msg::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
void msg::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
void msg::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
const ::std::string& msg::name() const {
  // @@protoc_insertion_point(field_get:msg_info.msg.name)
  return name_.GetNoArena();
}
void msg::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:msg_info.msg.name)
}
#if LANG_CXX11
void msg::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:msg_info.msg.name)
}
#endif
void msg::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:msg_info.msg.name)
}
void msg::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:msg_info.msg.name)
}
::std::string* msg::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:msg_info.msg.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* msg::release_name() {
  // @@protoc_insertion_point(field_release:msg_info.msg.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void msg::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:msg_info.msg.name)
}

// optional .msg_info.msg._TYPE type = 3 [default = INFO];
bool msg::has_type() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void msg::set_has_type() {
  _has_bits_[0] |= 0x00000008u;
}
void msg::clear_has_type() {
  _has_bits_[0] &= ~0x00000008u;
}
void msg::clear_type() {
  type_ = 2;
  clear_has_type();
}
::msg_info::msg__TYPE msg::type() const {
  // @@protoc_insertion_point(field_get:msg_info.msg.type)
  return static_cast< ::msg_info::msg__TYPE >(type_);
}
void msg::set_type(::msg_info::msg__TYPE value) {
  assert(::msg_info::msg__TYPE_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:msg_info.msg.type)
}

// optional string data = 4;
bool msg::has_data() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void msg::set_has_data() {
  _has_bits_[0] |= 0x00000004u;
}
void msg::clear_has_data() {
  _has_bits_[0] &= ~0x00000004u;
}
void msg::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
const ::std::string& msg::data() const {
  // @@protoc_insertion_point(field_get:msg_info.msg.data)
  return data_.GetNoArena();
}
void msg::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:msg_info.msg.data)
}
#if LANG_CXX11
void msg::set_data(::std::string&& value) {
  set_has_data();
  data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:msg_info.msg.data)
}
#endif
void msg::set_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:msg_info.msg.data)
}
void msg::set_data(const char* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:msg_info.msg.data)
}
::std::string* msg::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:msg_info.msg.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* msg::release_data() {
  // @@protoc_insertion_point(field_release:msg_info.msg.data)
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void msg::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:msg_info.msg.data)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace msg_info

// @@protoc_insertion_point(global_scope)
