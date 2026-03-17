#include <iostream>

class BumpAllocator {

    private:
        char* m_buffer; // start of memory pool
        std::size_t m_size; // total capacity
        std::size_t m_offset; // current position (bumper pointer)
    

    public:
    BumpAllocator(std::size_t capacity) : m_size(capacity), m_offset(0)
    {
        m_buffer = new char[capacity];
    }
        void* bump_alloc(std::size_t size, std::size_t alignment)
        {
            std::size_t aligned = (m_offset + alignment -1) & ~(alignment-1);
            if (aligned+size > m_size)
            {
                return nullptr;
            }
            void* ptr = m_buffer + aligned;

            m_offset = aligned+size;

            return ptr;
        }

        void reset()
        {
            m_offset = 0;
        }
};