/*
* Copyright 2017 Justas Masiulis
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef REMOTE_MEMORY_WRITE_MEMORY_HPP
#define REMOTE_MEMORY_WRITE_MEMORY_HPP

namespace remote {

    namespace detail {

        extern "C" __declspec(dllimport) int __stdcall
        WriteProcessMemory(void* process_handle, void* base_address, const void* buffer, SIZE_T_ size
                           , SIZE_T_* bytes_read);

    }

    template<typename T, class Address, class Size>
    inline void write(const void* handle, Address address, const T* buffer, Size size)
    {
        if (!detail::WriteProcessMemory(const_cast<void*>(handle)
                                        , reinterpret_cast<void*>(address)
                                        , buffer
                                        , size
                                        , nullptr))
            throw_last_error("WriteProcessMemory() failed");
    }

    template<class T, class Address, class Size>
    inline void write(const void* handle, Address address, const T* buffer, Size size, std::error_code& ec) noexcept
    {
        if (!detail::WriteProcessMemory(const_cast<void*>(handle)
                                        , reinterpret_cast<void*>(address)
                                        , buffer
                                        , size
                                        , nullptr))
            ec = get_last_error();
    }

}

#endif //REMOTE_MEMORY_WRITE_MEMORY_HPP