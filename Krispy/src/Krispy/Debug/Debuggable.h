//
// Created by dallin on 8/14/20.
//
// Used as a base class for all objects that should have debug capabilities (print to console, etc)

#pragma once
#include <spdlog/fmt/ostr.h>

namespace Krispy {
    class Debuggable {
    public:
        Debuggable() = default;
        ~Debuggable() = default;

        virtual std::string ToString() const = 0;

        template<typename OStream>
        friend OStream &operator<<(OStream &os, const Debuggable &item)
        {
            return os << item.ToString();
        }
    };
}



