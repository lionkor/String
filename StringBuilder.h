#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <cstring>
#include <cstdarg>
#include <memory>

#include "Core.h"
#include "String.h"

class StringBuilder
{
public:
    /// Ctor.
    StringBuilder();
    /// Copy ctor. // FIXME: Delete?
    StringBuilder(const StringBuilder&);
    /// Dtor.
    virtual ~StringBuilder();
    
    /// Appends a c-string (Inserts at the end).
    void append(const char*);
    /// Appends a String (Inserts at the end).
    void append(const String&);
    
    /// Prepends a c-string (Inserts in the beginning).
    void prepend(const char*);
    /// Prepends a String (Inserts in the beginning).
    void prepend(const String&);
    
    /// Appends formatted string (Inserts at the end).
    void appendf(const char* fmt, ...);
    /// Prepends formatted string (Inserts at the beginning).
    void prependf(const char* fmt, ...);
    
    /// Appends a char (Inserts at the end).
    void append(char);
    /// Prepends a char (Inserts in the beginning).
    void prepend(char);
    
    
    /// Builds the String and returns it.
    [[nodiscard]] String build();
    
    StringBuilder& operator=(const StringBuilder&);
    
    /// Returns the current contents of the char* data.
    const char* c_str() const { return m_chars; }
private:
    inline void store(const char* cstr)
    {
        if (cstr == m_chars) return;
        if (std::strcmp(cstr, m_chars) == 0) return;
        
        std::size_t new_size = std::strlen(cstr);
        if (new_size > m_capacity)
        {
            // resize
        }
    }
    
    /*
     * [Hello\0______________________]
     *  size | | capacity - size - 1
     */
    
    std::size_t m_size;
    std::size_t m_capacity;
    char* m_chars;
    bool m_built { false };
};

#endif // STRINGBUILDER_H
