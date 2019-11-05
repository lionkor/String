#ifndef DYNAMICSTRING_H
#define DYNAMICSTRING_H

#include <cstring>
#include <limits>
#include <iostream>
#include <algorithm>

class DynamicString
{
public:
    inline std::size_t size() const
    {
        return m_chars.all.dynamic ? m_chars.heap.size : m_chars.stack.size;
    }
    
protected:
    static constexpr unsigned char MAX_ALLOC = 23;
    
    DynamicString() {}
    ~DynamicString() 
    {
        if (m_chars.all.dynamic)
            delete[] chars();
    }
    
    inline void set_size(std::size_t size)
    {
        if (m_chars.all.dynamic)
            m_chars.heap.size = size;
        else
            m_chars.stack.size = size;
    }

    inline const char* chars() const 
    {
        return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data;
    }
    
    inline char*& chars()
    {
        if (m_chars.all.dynamic)
        {
            return m_chars.heap.data;
        }
        else
        {
            return m_chars.stack.data;
        }
    }
    
    inline void store(const char* cstr, std::size_t csize)
    {
        if (csize > MAX_ALLOC)
        {
            m_chars.all.dynamic = true;
            set_size(csize);
            chars() = new char[size() + 1];
        }
        else
        {
            m_chars.all.dynamic = false;
            set_size(csize);
        }
        
        if (chars() != cstr)
            strcpy(chars(), cstr);
    }
    
    inline void store(const char* cstr) { store(cstr, strlen(cstr)); }
    
    inline void resize(int delta)
    {
        // FIXME: This is very inefficient. We should implement capacity in m_chars.heap
        if (m_chars.all.dynamic)
        {
            char* new_chars = new char[m_chars.heap.size + 1];
            std::memcpy(new_chars, m_chars.heap.data, m_chars.heap.size);
            delete[] m_chars.heap.data;
            m_chars.heap.data = new_chars;
            m_chars.heap.size += delta;
        }
        else
        {
            std::memset(m_chars.stack.data + m_chars.stack.size, 0, delta);
            m_chars.stack.size += delta;
        }
    }
    
    inline void set_dynamic(bool dynamic)
    {
        m_chars.all.dynamic = dynamic;
    }
    
    union MainDataUnion {
        MainDataUnion() {}
        struct
        {
            unsigned char dynamic : 1;
        } all;
        struct
        {
            unsigned char dynamic : 1 = 1;
            std::size_t size : std::numeric_limits<std::size_t>::digits - 1;
            // FIXME: Implement capacity
            char* data;
        } heap;
        struct
        {
            unsigned char dynamic : 1 = 0;
            unsigned char size : std::numeric_limits<unsigned char>::digits - 1;
            char data[MAX_ALLOC];
        } stack;
    } m_chars;
};

#endif // DYNAMICSTRING_H
