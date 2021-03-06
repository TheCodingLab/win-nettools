/*
* nettols is a library for comonly used network stuff for windows and linux
* Copyright (C) 2017  TheCodingLab
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "buffer.h"

#ifndef _WIN32
#include <memory.h>
#endif

namespace nettools
{
    byte_buffer::byte_buffer(const size_t capacity) : m_buf(static_cast<u8 *>(malloc(capacity))), m_cap(capacity), m_lim(capacity), m_off(0)
    {}

    byte_buffer::~byte_buffer()
    {
        free(m_buf); }

    u8 *byte_buffer::get_buffer_at_offset() const
    { return m_buf + m_off; }

    size_t byte_buffer::get_capacity() const
    { return m_cap; }

    size_t byte_buffer::get_limit() const
    { return m_lim; }

    size_t byte_buffer::get_offset() const
    { return m_off; }

    void byte_buffer::set_limit(const size_t lim)
    { m_lim = lim; }

    void byte_buffer::set_offset(const size_t off)
    { m_off = off; }

    void byte_buffer::flip()
    {
        m_lim = m_off;
        m_off = 0;
    }

    void byte_buffer::reset()
    {
        m_lim = m_cap;
        m_off = 0;
    }

    void byte_buffer::get(const size_t off, void *buf, const size_t len) const
    { memcpy(buf, m_buf + off, len); }

    i8 byte_buffer::get_i8(const size_t off) const
    { return m_buf[off]; }

    i16 byte_buffer::get_i16(const size_t off) const
    { return static_cast<i16>(((m_buf[off] & 0xff) << 8) | (m_buf[off + 1] & 0xff)); }

    i32 byte_buffer::get_i32(const size_t off) const
    {
        return (m_buf[off] & 0xff) << 24 |
               (m_buf[off + 1] & 0xff) << 16 |
               (m_buf[off + 2] & 0xff) << 8 |
               m_buf[off + 3] & 0xff;
    }

    i64 byte_buffer::get_i64(const size_t off) const
    {
        return (static_cast<i64>(m_buf[off] & 0xff) << 56) |
               (static_cast<i64>(m_buf[off + 1] & 0xff) << 48) |
               (static_cast<i64>(m_buf[off + 2] & 0xff) << 40) |
               (static_cast<i64>(m_buf[off + 3] & 0xff) << 32) |
               (static_cast<i64>(m_buf[off + 4] & 0xff) << 24) |
               (static_cast<i64>(m_buf[off + 5] & 0xff) << 16) |
               (static_cast<i64>(m_buf[off + 6] & 0xff) << 8) |
               static_cast<i64>(m_buf[off + 7] & 0xff);
    }

    u8 byte_buffer::get_u8(const size_t off) const
    { return static_cast<u8>(get_i8(off)); }

    u16 byte_buffer::get_u16(const size_t off) const
    { return static_cast<u16>(get_i16(off)); }

    u32 byte_buffer::get_u32(const size_t off) const
    { return static_cast<u32>(get_i32(off)); }

    u64 byte_buffer::get_u64(const size_t off) const
    { return static_cast<u64>(get_i64(off)); }

    void byte_buffer::put(const size_t off, const void *buf, const size_t len) const
    { memcpy(m_buf + off, buf, len); }

    void byte_buffer::put_i8(const size_t off, const i8 val) const
    { m_buf[off] = static_cast<u8>(val); }

    void byte_buffer::put_i16(const size_t off, const i16 val) const
    {
        m_buf[off] = static_cast<u8>((val >> 8) & 0xff);
        m_buf[off + 1] = static_cast<u8>(val & 0xff);
    }

    void byte_buffer::put_i32(const size_t off, const i32 val) const
    {
        m_buf[off] = static_cast<u8>((val >> 24) & 0xff);
        m_buf[off + 1] = static_cast<u8>((val >> 16) & 0xff);
        m_buf[off + 2] = static_cast<u8>((val >> 8) & 0xff);
        m_buf[off + 3] = static_cast<u8>(val & 0xff);
    }

    void byte_buffer::put_i64(const size_t off, const i64 val) const
    {
        m_buf[off] = static_cast<u8>((val >> 56) & 0xff);
        m_buf[off + 1] = static_cast<u8>((val >> 48) & 0xff);
        m_buf[off + 2] = static_cast<u8>((val >> 40) & 0xff);
        m_buf[off + 3] = static_cast<u8>((val >> 32) & 0xff);
        m_buf[off + 4] = static_cast<u8>((val >> 24) & 0xff);
        m_buf[off + 5] = static_cast<u8>((val >> 16) & 0xff);
        m_buf[off + 6] = static_cast<u8>((val >> 8) & 0xff);
        m_buf[off + 7] = static_cast<u8>(val & 0xff);
    }

    void byte_buffer::put_u8(const size_t off, const u8 val) const
    { put_i8(off, static_cast<i8>(val)); }

    void byte_buffer::put_u16(const size_t off, const u16 val) const
    { put_i16(off, static_cast<i16>(val)); }

    void byte_buffer::put_u32(const size_t off, const u32 val) const
    { put_i32(off, static_cast<i32>(val)); }

    void byte_buffer::put_u64(const size_t off, const u64 val) const
    { put_i64(off, static_cast<i64>(val)); }

    void byte_buffer::get(void *buf, const size_t len)
    {
        memcpy(buf, m_buf + m_off, len);
        m_off += len;
    }


    i8 byte_buffer::get_i8()
    {
        const size_t tmp = m_off;
        m_off += 1;
        return get_i8(tmp);
    }

    i16 byte_buffer::get_i16()
    {
        const size_t tmp = m_off;
        m_off += 2;
        return get_i16(tmp);
    }

    i32 byte_buffer::get_i32()
    {
        const size_t tmp = m_off;
        m_off += 4;
        return get_i32(tmp);
    }

    i64 byte_buffer::get_i64()
    {
        const size_t tmp = m_off;
        m_off += 8;
        return get_i64(tmp);
    }

    u8 byte_buffer::get_u8()
    {
        const size_t tmp = m_off;
        m_off += 1;
        return static_cast<u8>(get_i8(tmp));
    }

    u16 byte_buffer::get_u16()
    {
        const size_t tmp = m_off;
        m_off += 2;
        return static_cast<u16>(get_i16(tmp));
    }

    u32 byte_buffer::get_u32()
    {
        const size_t tmp = m_off;
        m_off += 4;
        return static_cast<u32>(get_i32(tmp));
    }

    u64 byte_buffer::get_u64()
    {
        const size_t tmp = m_off;
        m_off += 8;
        return static_cast<u64>(get_i64(tmp));
    }

    void byte_buffer::put(const void *buf, const size_t len)
    {
        memcpy(m_buf + m_off, buf, len);
        m_off += len;
    }

    void byte_buffer::put_i8(const i8 val)
    {
        const size_t tmp = m_off;
        m_off += 1;
        put_i8(tmp, val);
    }

    void byte_buffer::put_i16(const i16 val)
    {
        const size_t tmp = m_off;
        m_off += 2;
        put_i16(tmp, val);
    }

    void byte_buffer::put_i32(const i32 val)
    {
        const size_t tmp = m_off;
        m_off += 4;
        put_i32(tmp, val);
    }

    void byte_buffer::put_i64(const i64 val)
    {
        const size_t tmp = m_off;
        m_off += 8;
        put_i64(tmp, val);
    }

    void byte_buffer::put_u8(const u8 val)
    {
        const size_t tmp = m_off;
        m_off += 1;
        put_i8(tmp, static_cast<i8>(val));
    }

    void byte_buffer::put_u16(const u16 val)
    {
        const size_t tmp = m_off;
        m_off += 2;
        put_i16(tmp, static_cast<i16>(val));
    }

    void byte_buffer::put_u32(const u32 val)
    {
        const size_t tmp = m_off;
        m_off += 4;
        put_i32(tmp, static_cast<i32>(val));
    }

    void byte_buffer::put_u64(const u64 val)
    {
        const size_t tmp = m_off;
        m_off += 8;
        put_i64(tmp, static_cast<i64>(val));
    }
}
