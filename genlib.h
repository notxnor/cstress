#ifndef _IGen
#define _IGen

#include <random>
#include <chrono>
#include <cassert>

namespace genlib {
    std::mt19937 mt;

    void init(long long seed = 0) {
        if (seed)
            mt = std::mt19937(seed);
        else
            mt = std::mt19937(std::chrono::steady_clock::now().
                              time_since_epoch().
                              count());
    }

    int ni(int r) {
        return std::uniform_int_distribution<int>(1, r)(mt);
    }
    long long nll(long long r) {
        return std::uniform_int_distribution<long long>(1, r)(mt);
    }
    unsigned long long null(unsigned long long r) {
        return std::uniform_int_distribution<unsigned long long>(1, r)(mt);
    }

    int ni(int l, int r) {
        return std::uniform_int_distribution<int>(l, r)(mt);
    }
    long long nll(long long l, long long r) {
        return std::uniform_int_distribution<long long>(l, r)(mt);
    }
    unsigned long long null(unsigned long long l, unsigned long long r) {
        return std::uniform_int_distribution<unsigned long long>(l, r)(mt);
    }

    double nd(double l, double r) {
        return std::uniform_real_distribution<double>(l, r)(mt);
    }

    /*
        0b001 - only a-z
        0b010 - only A-Z
        0b100 - only 0-9
    */
    std::string nw(std::size_t len, int mask = 0b001) {
        assert(mask);
        std::vector<char> charset;
        if (mask & 1)
            for (int i = 'a'; i <= 'z'; ++i)
                charset.push_back(i);
        if (mask & 2)
            for (int i = 'A'; i <= 'Z'; ++i)
                charset.push_back(i);
        if (mask & 4)
            for (int i = '0'; i <= '9'; ++i)
                charset.push_back(i);
        std::string res;
        for (std::size_t i = 0; i < len; ++i)
            res.push_back(charset[ni(0, (int)charset.size() - 1)]);
        return res;
    }

    std::pair<long long, long long> nop(long long l, long long r) {
        long long x = nll(l, r), y = nll(l, r);
        if (x > y)
            std::swap(x, y);
        return std::make_pair(x, y);
    }

    std::vector<long long> nvec(std::size_t len, long long l, long long r) {
        std::vector<long long> res;
        for (std::size_t i = 0; i < len; ++i)
            res.push_back(nll(l, r));
        return res;
    }
    std::vector<long long> nperm(std::size_t len) {
        std::vector<long long> res(len);
        std::iota(res.begin(), res.end(), 1);
        std::shuffle(res.begin(), res.end(), mt);
        return res;
    }
};

#endif
