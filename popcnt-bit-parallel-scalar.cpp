std::uint64_t popcnt_parallel_64bit_naive(const uint8_t* data, const size_t n) {

    uint64_t result = 0;

    size_t i = 0;

#define ITER { \
        const uint64_t t1 = *reinterpret_cast<const uint64_t*>(data + i); \
        const uint64_t t2 = (t1 & 0x5555555555555555llu) + ((t1 >>  1) & 0x5555555555555555llu); \
        const uint64_t t3 = (t2 & 0x3333333333333333llu) + ((t2 >>  2) & 0x3333333333333333llu); \
        const uint64_t t4 = (t3 & 0x0f0f0f0f0f0f0f0fllu) + ((t3 >>  4) & 0x0f0f0f0f0f0f0f0fllu); \
        const uint64_t t5 = (t4 & 0x00ff00ff00ff00ffllu) + ((t4 >>  8) & 0x00ff00ff00ff00ffllu); \
        const uint64_t t6 = (t5 & 0x0000ffff0000ffffllu) + ((t5 >> 16) & 0x0000ffff0000ffffllu); \
        const uint64_t t7 = (t6 & 0x00000000ffffffffllu) + ((t6 >> 32) & 0x00000000ffffffffllu); \
        result += t7; \
        i += 8; \
    }

    while (i + 4*8 <= n) {
        ITER ITER ITER ITER
    }

#undef ITER

    for (/**/; i < n; i++) {
        result += lookup8bit[data[i]];
    }

    return result;
}


std::uint64_t popcnt_parallel_64bit_optimized(const uint8_t* data, const size_t n) {

    uint64_t result = 0;

    size_t i = 0;

    while (i + 4*8 <= n) {

        uint64_t partial = 0; // packed_byte

#define ITER { \
            const uint64_t t1 = *reinterpret_cast<const uint64_t*>(data + i); \
            const uint64_t t2 = (t1 & 0x5555555555555555llu) + ((t1 >>  1) & 0x5555555555555555llu); \
            const uint64_t t3 = (t2 & 0x3333333333333333llu) + ((t2 >>  2) & 0x3333333333333333llu); \
            const uint64_t t4 = (t3 & 0x0f0f0f0f0f0f0f0fllu) + ((t3 >>  4) & 0x0f0f0f0f0f0f0f0fllu); \
            partial += t4; \
            i += 8; \
        }

        ITER ITER ITER ITER

#undef ITER

        const uint64_t t5 = (partial & 0x00ff00ff00ff00ffllu) + ((partial >>  8) & 0x00ff00ff00ff00ffllu);
        const uint64_t t6 = (t5 & 0x0000ffff0000ffffllu) + ((t5 >> 16) & 0x0000ffff0000ffffllu);
        const uint64_t t7 = (t6 & 0x00000000ffffffffllu) + ((t6 >> 32) & 0x00000000ffffffffllu);

        result += t7;
    }

    for (/**/; i < n; i++) {
        result += lookup8bit[data[i]];
    }

    return result;
}


// popcnt_mul from popcnt-harley-seal.cpp
std::uint64_t popcnt_parallel_64bit_mul(const uint8_t* data, const size_t n) {
    
    uint64_t result = 0;

    size_t i = 0;

    for (/**/; i < n; i += 8) {

        const uint64_t m1  = UINT64_C(0x5555555555555555);
        const uint64_t m2  = UINT64_C(0x3333333333333333);
        const uint64_t m4  = UINT64_C(0x0F0F0F0F0F0F0F0F);
        const uint64_t h01 = UINT64_C(0x0101010101010101);
        
        uint64_t x = *reinterpret_cast<const uint64_t*>(data + i);
        x -=            (x >> 1)  & m1;
        x = (x & m2) + ((x >> 2)  & m2);
        x = (x +        (x >> 4)) & m4;

        result += (x * h01) >> 56;
    }

    for (/**/; i < n; i++) {
        result += lookup8bit[data[i]];
    }

    return result;
}
