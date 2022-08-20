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

    BinaryStream();

    ~BinaryStream();

    bool read(size_t size, uint8_t **output);

    void write(uint8_t *buffer, size_t size);

    bool read_u8(uint8_t *output);

    void write_u8(uint8_t input);

    bool read_i8(int8_t *output);

    void write_i8(int8_t input);

    bool read_u16le(uint16_t *output);

    void write_u16le(uint16_t input);

    bool read_i16le(int16_t *output);

    void write_i16le(int16_t input);

    bool read_u16be(uint16_t *output);

    void write_u16be(uint16_t input);

    bool read_i16be(int16_t *output);

    void write_i16be(int16_t input);

    bool read_u24le(uint32_t *output);

    void write_u24le(uint32_t input);

    bool read_u24be(uint32_t *output);

    void write_u24be(uint32_t input);

    bool read_u32le(uint32_t *output);

    void write_u32le(uint32_t input);

    bool read_i32le(int32_t *output);

    void write_i32le(int32_t input);

    bool read_u32be(uint32_t *output);

    void write_u32be(uint32_t input);

    bool read_i32be(int32_t *output);

    void write_i32be(int32_t input);

    bool read_u64le(uint64_t *output);

    void write_u64le(uint64_t input);

    bool read_i64le(int64_t *output);

    void write_i64le(int64_t input);

    bool read_u64be(uint64_t *output);

    void write_u64be(uint64_t input);

    bool read_i64be(int64_t *output);

    void write_i64be(int64_t input);

    bool read_f32le(float *output);

    void write_f32le(float input);

    bool read_f32be(float *output);

    void write_f32be(float input);

    bool read_f64le(double *output);

    void write_f64le(double input);

    bool read_f64be(double *output);

    void write_f64be(double input);

    bool read_bool(bool *output);

    void write_bool(bool input);

    bool read_varint32(uint32_t *output);

    void write_varint32(uint32_t input);

    bool read_zigzag32(int32_t *output);

    void write_zigzag32(int32_t input);

    bool read_varint64(uint64_t *output);

    void write_varint64(uint64_t input);

    bool read_zigzag64(int64_t *output);

    void write_zigzag64(int64_t input);

    bool is_end_of_stream();
};
