#pragma once

#include <random>
#include <cstdint>
#include <limits>
#include <chrono>

namespace misc
{
    template<typename T, typename std::enable_if<std::is_scalar<T>::value>::type* = nullptr>
    struct default_key_generator
    {
        T operator()() const
        {
            static std::default_random_engine generator((int)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
            static std::uniform_int_distribution<int> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

            return static_cast<uint8_t>(distribution(generator));
        }
    };

    template<typename generator = default_key_generator<uint8_t>>
    struct xor_encryption_impl
    {
        xor_encryption_impl()
        {
            m_key = generator()();
        }

        void encrypt(uint8_t* dest, uint8_t* src, size_t size) const
        {
            for (size_t i = 0; i < size; i++)
            {
                dest[i] = src[i] ^ m_key;
            }
        }

        void decrypt(uint8_t* dest, uint8_t* src, size_t size) const
        {
            for (size_t i = 0; i < size; i++)
            {
                dest[i] = src[i] ^ m_key;
            }
        }

        uint8_t m_key;
    };

    typedef xor_encryption_impl<> default_encryption_impl;

    template<typename T, typename encryption = default_encryption_impl, typename std::enable_if<std::is_scalar<T>::value>::type* = nullptr>
    struct encrypted_variable
    {
        encrypted_variable()
        {
            set(T());
        }

        encrypted_variable(const T& _value)
        {
            set(_value);
        }

        encrypted_variable(const encrypted_variable<T>& _copy)
        {
            set(_copy.get());
        }

        encrypted_variable(encrypted_variable<T>&& _move)
        {
            set(_move.get());
        }

        encrypted_variable<T>& operator= (const encrypted_variable<T>& other)
        {
            encrypted_variable<T> temporary(other);

            set(temporary.get());

            return *this;
        }

        encrypted_variable<T>& operator=(const T& _value)
        {
            this->set(_value);
            return *this;
        }

        encrypted_variable<T>& operator= (encrypted_variable<T>&& other)
        {
            set(other.get());

            return *this;
        }

        operator T() const
        {
            return get();
        }

        void set(const T& _value)
        {
            T copy(_value);

            uint8_t* ptr = (uint8_t*)&copy;
            uint8_t* local = (uint8_t*)&value;

            m_encryption_impl.encrypt(local, ptr, sizeof(T));
        }

        T get() const
        {
            T copy;

            uint8_t* ptr = (uint8_t*)&copy;
            uint8_t* local = (uint8_t*)&value;

            m_encryption_impl.decrypt(ptr, local, sizeof(T));

            return copy;
        }

        T value;
        encryption m_encryption_impl;
    };
}