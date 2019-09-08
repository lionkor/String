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
    /// Copy ctor.
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
    String build();
    
    StringBuilder& operator=(const StringBuilder&);
    
    /// Returns the current contents of the char* data.
    const char* c_str() const { return m_chars.get(); }
private:
    std::size_t m_size;
    std::unique_ptr<char[]> m_chars;
    bool m_built { false };
};

#endif // STRINGBUILDER_H
