/*
Copyright 2020 Andrzej Borucki

This file is part of the mpcpp library wrapper.

The mpcpp is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The mpcpp is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MPFR Library; see the file COPYING.LESSER.  If not, see
https://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */
#pragma once
#include <string>
#include <gmp.h>

namespace gmp {
    enum Library {libMpf, libMpfr};

    class Format {
    public:
        static std::string addPrecZeros(std::string str, size_t precision);
        static std::string removePrecZeros(std::string str);
    public:
        static std::string output(char *buf, Library library, bool precWithZeros, const size_t precision, const mp_exp_t exp, const int sign);
    };
 }