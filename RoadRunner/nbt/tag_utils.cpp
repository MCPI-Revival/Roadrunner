#include <nbt/tag_utils.hpp>
#include <nbt/tag/byte.hpp>
#include <nbt/tag/short.hpp>
#include <nbt/tag/int.hpp>
#include <nbt/tag/long.hpp>
#include <nbt/tag/float.hpp>
#include <nbt/tag/double.hpp>
#include <nbt/tag/byte_array.hpp>
#include <nbt/tag/string.hpp>
#include <nbt/tag/list.hpp>
#include <nbt/tag/compound.hpp>
#include <nbt/tag/int_array.hpp>
#include <nbt/tag/long_array.hpp>

using RoadRunner::nbt::tag::Byte;
using RoadRunner::nbt::tag::Short;
using RoadRunner::nbt::tag::Int;
using RoadRunner::nbt::tag::Long;
using RoadRunner::nbt::tag::Float;
using RoadRunner::nbt::tag::Double;
using RoadRunner::nbt::tag::ByteArray;
using RoadRunner::nbt::tag::String;
using RoadRunner::nbt::tag::List;
using RoadRunner::nbt::tag::Compound;
using RoadRunner::nbt::tag::IntArray;
using RoadRunner::nbt::tag::LongArray;

Tag *create_tag(TagIdentifiers id) {
    switch (id) {
    case TagIdentifiers::BYTE:
        return new Byte();
    case TagIdentifiers::SHORT:
        return new Short();
    case TagIdentifiers::INT:
        return new Int();
    case TagIdentifiers::LONG:
        return new Long();
    case TagIdentifiers::FLOAT:
        return new Float();
    case TagIdentifiers::DOUBLE:
        return new Double();
    case TagIdentifiers::BYTE_ARRAY:
        return new ByteArray();
    case TagIdentifiers::STRING:
        return new String();
    case TagIdentifiers::LIST:
        return new List();
    case TagIdentifiers::COMPOUND:
        return new Compound();
    case TagIdentifiers::INT_ARRAY:
        return new IntArray();
    case TagIdentifiers::LONG_ARRAY:
        return new LongArray();
    default:
        return nullptr;
    }
}