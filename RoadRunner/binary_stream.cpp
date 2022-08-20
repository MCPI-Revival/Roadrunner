/*
   Copyright Alexander Argentakis
   Repo: https://github.com/MFDGaming/CBinaryStream
   This file is licensed under the MIT license
   This is a modified version of CBinaryStream for
   use in the roadrunner server software for MCPI
 */

#include "binary_stream.hpp"

#include <cstring>

BinaryStream::BinaryStream() {
    this->buffer = (uint8_t *)malloc(0);
    this->offset = 0;
    this->size = 0;
}

BinaryStream::~BinaryStream() {
    free(this->buffer);
    this->offset = 0;
    this->size = 0;
}

bool BinaryStream::read(size_t size, uint8_t **output) {
    if ((this->offset + size) <= this->size) {
        *output = this->buffer + this->offset;
        this->offset += size;
        return true;
    }
    return false;
}

void BinaryStream::write(uint8_t *buffer, size_t size) {
    size_t old_size = this->size;
    this->size += size;
    this->buffer = (uint8_t *)realloc(this->buffer, this->size);
    memcpy(this->buffer + old_size, buffer, size);
}

bool BinaryStream::read_u8(uint8_t *output) {
    uint8_t *out;
    bool has_error = this->read(1, &out);
    if (has_error)
        *output = out[0];
    return has_error;
}

void BinaryStream::write_u8(uint8_t input) {
    this->write(&input, 1);
}

bool BinaryStream::read_i8(int8_t *output) {
    return this->read_u8((uint8_t *)output);
}

void BinaryStream::write_i8(int8_t input) {
    this->write_u8(*((uint8_t *)&input));
}

bool BinaryStream::read_u16le(uint16_t *output) {
    uint8_t *out;
    bool has_error = this->read(2, &out);
    if (has_error)
        *output = ((uint16_t)out[0]) | (((uint16_t)out[1]) << 8);
    return has_error;
}

void BinaryStream::write_u16le(uint16_t input) {
    uint8_t byte_array[] = {
        (uint8_t)(input & 0xff),
        (uint8_t)((input >> 8) & 0xff)};
    this->write(byte_array, 2);
}

bool BinaryStream::read_i16le(int16_t *output) {
    return this->read_u16le((uint16_t *)output);
}

void BinaryStream::write_i16le(int16_t input) {
    this->write_u16le(*((uint16_t *)&input));
}

bool BinaryStream::read_u16be(uint16_t *output) {
    uint8_t *out;
    bool has_error = this->read(2, &out);
    if (has_error)
        *output = (((uint16_t)out[0]) << 8) | ((uint16_t)out[1]);
    return has_error;
}

void BinaryStream::write_u16be(uint16_t input) {
    uint8_t byte_array[] = {
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)(input & 0xff)};
    this->write(byte_array, 2);
}

bool BinaryStream::read_i16be(int16_t *output) {
    return this->read_u16be((uint16_t *)output);
}

void BinaryStream::write_i16be(int16_t input) {
    this->write_u16be(*((uint16_t *)&input));
}

bool BinaryStream::read_u24le(uint32_t *output) {
    uint8_t *out;
    bool has_error = this->read(3, &out);
    if (has_error)
        *output = ((uint32_t)out[0]) | (((uint32_t)out[1]) << 8) | (((uint32_t)out[2]) << 16);
    return has_error;
}

void BinaryStream::write_u24le(uint32_t input) {
    uint8_t byte_array[] = {
        (uint8_t)(input & 0xff),
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)((input >> 16) & 0xff)};
    this->write(byte_array, 3);
}

bool BinaryStream::read_u24be(uint32_t *output) {
    uint8_t *out;
    bool has_error = this->read(3, &out);
    if (has_error)
        *output = (((uint32_t)out[0]) << 16) | (((uint32_t)out[1]) << 8) | ((uint32_t)out[2]);
    return has_error;
}

void BinaryStream::write_u24be(uint32_t input) {
    uint8_t byte_array[] = {
        (uint8_t)((input >> 16) & 0xff),
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)(input & 0xff)};
    this->write(byte_array, 3);
}

bool BinaryStream::read_u32le(uint32_t *output) {
    uint8_t *out;
    bool has_error = this->read(4, &out);
    if (has_error)
        *output = ((uint32_t)out[0]) | (((uint32_t)out[1]) << 8) | (((uint32_t)out[2]) << 16) | (((uint32_t)out[3]) << 24);
    return has_error;
}

void BinaryStream::write_u32le(uint32_t input) {
    uint8_t byte_array[] = {
        (uint8_t)(input & 0xff),
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)((input >> 16) & 0xff),
        (uint8_t)((input >> 24) & 0xff)};
    this->write(byte_array, 4);
}

bool BinaryStream::read_i32le(int32_t *output) {
    return this->read_u32le((uint32_t *)output);
}

void BinaryStream::write_i32le(int32_t input) {
    this->write_u32le(*((uint32_t *)&input));
}

bool BinaryStream::read_u32be(uint32_t *output) {
    uint8_t *out;
    bool has_error = this->read(4, &out);
    if (has_error)
        *output = (((uint32_t)out[0]) << 24) | (((uint32_t)out[1]) << 16) | (((uint32_t)out[2]) << 8) | ((uint32_t)out[3]);
    return has_error;
}

void BinaryStream::write_u32be(uint32_t input) {
    uint8_t byte_array[] = {
        (uint8_t)((input >> 24) & 0xff),
        (uint8_t)((input >> 16) & 0xff),
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)(input & 0xff)};
    this->write(byte_array, 4);
}

bool BinaryStream::read_i32be(int32_t *output) {
    return this->read_u32be((uint32_t *)output);
}

void BinaryStream::write_i32be(int32_t input) {
    this->write_u32be(*((uint32_t *)&input));
}

bool BinaryStream::read_u64le(uint64_t *output) {
    uint8_t *out;
    bool has_error = this->read(8, &out);
    if (has_error)
        *output = ((uint64_t)out[0]) | (((uint64_t)out[1]) << 8) | (((uint64_t)out[2]) << 16) | (((uint64_t)out[3]) << 24) | (((uint64_t)out[4]) << 32) | (((uint64_t)out[5]) << 40) | (((uint64_t)out[6]) << 48) | (((uint64_t)out[7]) << 56);
    return has_error;
}

void BinaryStream::write_u64le(uint64_t input) {
    uint8_t byte_array[] = {
        (uint8_t)(input & 0xff),
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)((input >> 16) & 0xff),
        (uint8_t)((input >> 24) & 0xff),
        (uint8_t)((input >> 32) & 0xff),
        (uint8_t)((input >> 40) & 0xff),
        (uint8_t)((input >> 48) & 0xff),
        (uint8_t)((input >> 56) & 0xff)};
    this->write(byte_array, 8);
}

bool BinaryStream::read_i64le(int64_t *output) {
    return this->read_u64le((uint64_t *)output);
}

void BinaryStream::write_i64le(int64_t input) {
    this->write_u64le(*((uint64_t *)&input));
}

bool BinaryStream::read_u64be(uint64_t *output) {
    uint8_t *out;
    bool has_error = this->read(8, &out);
    if (has_error)
        *output = (((uint64_t)out[0]) << 56) | (((uint64_t)out[1]) << 48) | (((uint64_t)out[2]) << 40) | (((uint64_t)out[3]) << 32) | (((uint64_t)out[4]) << 24) | (((uint64_t)out[5]) << 16) | (((uint64_t)out[6]) << 8) | ((uint64_t)out[7]);
    return has_error;
}

void BinaryStream::write_u64be(uint64_t input) {
    uint8_t byte_array[] = {
        (uint8_t)((input >> 56) & 0xff),
        (uint8_t)((input >> 48) & 0xff),
        (uint8_t)((input >> 40) & 0xff),
        (uint8_t)((input >> 32) & 0xff),
        (uint8_t)((input >> 24) & 0xff),
        (uint8_t)((input >> 16) & 0xff),
        (uint8_t)((input >> 8) & 0xff),
        (uint8_t)(input & 0xff)};
    this->write(byte_array, 8);
}

bool BinaryStream::read_i64be(int64_t *output) {
    return this->read_u64be((uint64_t *)output);
}

void BinaryStream::write_i64be(int64_t input) {
    this->write_u64be(*((uint64_t *)&input));
}

bool BinaryStream::read_f32le(float *output) {
    return this->read_u32le((uint32_t *)output);
}

void BinaryStream::write_f32le(float input) {
    this->write_u32le(*((uint32_t *)&input));
}

bool BinaryStream::read_f32be(float *output) {
    return this->read_u32be((uint32_t *)output);
}

void BinaryStream::write_f32be(float input) {
    this->write_u32be(*((uint32_t *)&input));
}

bool BinaryStream::read_f64le(double *output) {
    return this->read_u64le((uint64_t *)output);
}

void BinaryStream::write_f64le(double input) {
    this->write_u64le(*((uint64_t *)&input));
}

bool BinaryStream::read_f64be(double *output) {
    return this->read_u64be((uint64_t *)output);
}

void BinaryStream::write_f64be(double input) {
    this->write_u64be(*((uint64_t *)&input));
}

bool BinaryStream::read_bool(bool *output) {
    return this->read_u8((uint8_t *)output);
}

void BinaryStream::write_bool(bool input) {
    this->write_u8(*((uint8_t *)&input));
}

bool BinaryStream::read_varint32(uint32_t *output) {
    uint32_t value = 0;
    uint8_t i;
    uint8_t to_read;
    for (i = 0; i < 35; i += 7) {
        if (!this->read_u8(&to_read)) {
            return false;
        }
        value |= ((uint32_t)(to_read & 0x7f)) << i;
        if ((to_read & 0x80) == 0) {
            *output = value;
            return true;
        }
    }
    return false;
}

void BinaryStream::write_varint32(uint32_t input) {
    uint32_t value = input;
    uint8_t i;
    for (i = 0; i < 5; ++i) {
        uint8_t to_write = (uint8_t)(value & 0x7f);
        value >>= 7;
        if (value != 0) {
            this->write_u8(to_write | 0x80);
        } else {
            this->write_u8(to_write);
            break;
        }
    }
}

bool BinaryStream::read_zigzag32(int32_t *output) {
    uint32_t raw;
    if (!this->read_varint32(&raw)) {
        return false;
    }
    uint32_t temp = ((raw & 1) == 1) ? (~(raw >> 1)) : (raw >> 1);
    *output = *((int32_t *)&temp);
    return true;
}

void BinaryStream::write_zigzag32(int32_t input) {
    uint32_t raw = (input >= 0) ? ((*((uint32_t *)&input)) << 1) : (((~(*((uint32_t *)&input))) << 1) | 1);
    this->write_varint32(raw);
}

bool BinaryStream::read_varint64(uint64_t *output) {
    uint64_t value = 0;
    uint8_t i;
    uint8_t to_read;
    for (i = 0; i < 70; i += 7) {
        if (!this->read_u8(&to_read)) {
            return false;
        }
        value |= ((uint64_t)(to_read & 0x7f)) << i;
        if ((to_read & 0x80) == 0) {
            *output = value;
            return true;
        }
    }
    return false;
}

void BinaryStream::write_varint64(uint64_t input) {
    uint64_t value = input;
    uint8_t i;
    for (i = 0; i < 10; ++i) {
        uint8_t to_write = (uint8_t)(value & 0x7f);
        value >>= 7;
        if (value != 0) {
            this->write_u8(to_write | 0x80);
        } else {
            this->write_u8(to_write);
            break;
        }
    }
}

bool BinaryStream::read_zigzag64(int64_t *output) {
    uint64_t raw;
    if (!this->read_varint64(&raw)) {
        return false;
    }
    uint64_t temp = ((raw & 1) == 1) ? (~(raw >> 1)) : (raw >> 1);
    *output = *((int64_t *)&temp);
    return true;
}

void BinaryStream::write_zigzag64(int64_t input) {
    uint64_t raw = (input >= 0) ? ((*((uint64_t *)&input)) << 1) : (((~(*((uint64_t *)&input))) << 1) | 1);
    this->write_varint64(raw);
}

bool BinaryStream::is_end_of_stream() {
    return (this->offset < this->size);
}
