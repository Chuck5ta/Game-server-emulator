/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2015  MaNGOS project <http://getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef MPQ_H
#define MPQ_H

#include <string.h>
#include <ctype.h>
#include <vector>
#include <iostream>
#include <deque>
#include "StormLib.h"

#ifdef _WIN32
#include <Windows.h>    // mainly only HANDLE definition is required
typedef __int64            int64;
typedef __int32            int32;
typedef __int16            int16;
typedef __int8             int8;
typedef unsigned __int64   uint64;
typedef unsigned __int32   uint32;
typedef unsigned __int16   uint16;
typedef unsigned __int8    uint8;
#else
#include <stdint.h>
#ifndef uint64_t
#ifdef __linux__
#include <linux/types.h>
#endif
#endif
typedef int64_t            int64;
typedef int32_t            int32;
typedef int16_t            int16;
typedef int8_t             int8;
typedef uint64_t           uint64;
typedef uint32_t           uint32;
typedef uint16_t           uint16;
typedef uint8_t            uint8;
typedef void*              HANDLE;
#endif

using namespace std;

class MPQFile
{
        //MPQHANDLE handle;
        bool eof; /**< TODO */
        char* buffer; /**< TODO */
        size_t pointer, size;

        /**
         * @brief disable copying
         *
         * @param f
         */
        MPQFile(const MPQFile& f) {}
        /**
         * @brief
         *
         * @param f
         */
        void operator=(const MPQFile& f) {}

    public:
        /**
         * @brief
         *
         * @param filename filenames are not case sensitive
         */
        MPQFile(HANDLE mpq, const char* filename);    // filenames are not case sensitive
        /**
         * @brief
         *
         */
        ~MPQFile() { close(); }
        /**
         * @brief
         *
         * @param dest
         * @param bytes
         * @return size_t
         */
        size_t read(void* dest, size_t bytes);
        /**
         * @brief
         *
         * @return size_t
         */
        size_t getSize() { return (size_t)size; }
        /**
         * @brief
         *
         * @return size_t
         */
		size_t getPos() { return (size_t)pointer; }
        /**
         * @brief
         *
         * @return char
         */
        char* getBuffer() { return buffer; }
        /**
         * @brief
         *
         * @return char
         */
        char* getPointer() { return buffer + pointer; }
        /**
         * @brief
         *
         * @return bool
         */
        bool isEof() { return eof; }
        /**
         * @brief
         *
         * @param offset
         */
        void seek(int offset);
        /**
         * @brief
         *
         * @param offset
         */
        void seekRelative(int offset);
        /**
         * @brief
         *
         */
        void close();
};

/**
 * @brief
 *
 * @param fcc
 */
inline void flipcc(char* fcc)
{
    char t;
    t = fcc[0];
    fcc[0] = fcc[3];
    fcc[3] = t;
    t = fcc[1];
    fcc[1] = fcc[2];
    fcc[2] = t;
}

#endif
