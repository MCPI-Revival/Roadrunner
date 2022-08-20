/*
   Copyright Alexander Argentakis
   Repo: https://github.com/MFDGaming/CBinaryStream
   This file is licensed under the MIT license
   This is a modified version of CBinaryStream for
   use in the roadrunner server software for MCPI
 */

#pragma once

#include <cstdint>
#include <cstdlib>

class BinaryStream {
    public:
        uint8_t *buffer;
        size_t size;
        size_t offset;

        BinaryStream::BinaryStream();

        BinaryStream::~BinaryStream();

        bool BinaryStream::read(size_t size, uint8_t **output);

        void BinaryStream::write(uint8_t *buffer, size_t size);

        bool BinaryStream::read_u8(uint8_t *output);

        void BinaryStream::write_u8(uint8_t input);

        bool BinaryStream::read_i8(int8_t *output);

        void BinaryStream::write_i8(int8_t input);

        bool BinaryStream::read_u16le(uint16_t *output);

        void BinaryStream::write_u16le(uint16_t input);

        bool BinaryStream::read_i16le(int16_t *output);

        void BinaryStream::write_i16le(int16_t input);

        bool BinaryStream::read_u16be(uint16_t *output);

        void BinaryStream::write_u16be(uint16_t input);

        bool BinaryStream::read_i16be(int16_t *output);

        void BinaryStream::write_i16be(int16_t input);

        bool BinaryStream::read_u24le(uint32_t *output);

        void BinaryStream::write_u24le(uint32_t input);

        bool BinaryStream::read_u24be(uint32_t *output);

        void BinaryStream::write_u24be(uint32_t input);

        bool BinaryStream::read_u32le(uint32_t *output);

        void BinaryStream::write_u32le(uint32_t input);

        bool BinaryStream::read_i32le(int32_t *output);

        void BinaryStream::write_i32le(int32_t input);

        bool BinaryStream::read_u32be(uint32_t *output);

        void BinaryStream::write_u32be(uint32_t input);

        bool BinaryStream::read_i32be(int32_t *output);

        void BinaryStream::write_i32be(int32_t input);

        bool BinaryStream::read_u64le(uint64_t *output);

        void BinaryStream::write_u64le(uint64_t input);

        bool BinaryStream::read_i64le(int64_t *output);

        void BinaryStream::write_i64le(int64_t input);

        bool BinaryStream::read_u64be(uint64_t *output);

        void BinaryStream::write_u64be(uint64_t input);

        bool BinaryStream::read_i64be(int64_t *output);

        void BinaryStream::write_i64be(int64_t input);

        bool BinaryStream::read_f32le(float *output);

        void BinaryStream::write_f32le(float input);

        bool BinaryStream::read_f32be(float *output);

        void BinaryStream::write_f32be(float input);

        bool BinaryStream::read_f64le(double *output);

        void BinaryStream::write_f64le(double input);

        bool BinaryStream::read_f64be(double *output);

        void BinaryStream::write_f64be(double input);

        bool BinaryStream::read_bool(bool *output);

        void BinaryStream::write_bool(bool input);

        bool BinaryStream::read_varint32(uint32_t *output);
    
        void BinaryStream::write_varint32(uint32_t input);

        bool BinaryStream::read_zigzag32(int32_t *output);

        void BinaryStream::write_zigzag32(int32_t input);

        bool BinaryStream::read_varint64(uint64_t *output);
    
        void BinaryStream::write_varint64(uint64_t input);

        bool BinaryStream::read_zigzag64(int64_t *output);

        void BinaryStream::write_zigzag64(int64_t input);

        bool BinaryStream::is_end_of_stream();
};
