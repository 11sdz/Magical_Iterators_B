//
// Created by mintsdz on 6/12/23.
//

#ifndef CMAKEITER_MYALGOS_HPP
#define CMAKEITER_MYALGOS_HPP
#include <cmath>
#include <type_traits>
namespace ariel {
    template<typename T>
    typename std::enable_if<!std::is_pointer<T>::value, int>::type
    compareValues(const T& rval, const T& lval) {
        int res=0;
        if (rval > lval) {
            res =1;
        } else if (rval < lval) {
            res =-1;
        } else {
            res =0;
        }
        return res;
    }

    template<typename T>
    typename std::enable_if<std::is_pointer<T>::value, int>::type
    compareValues(const T& rval, const T& lval) {
        return compareValues(*rval, *lval);
    }
/*
 * ===============================================
 * ===============Prime Algo======================
 */
    static bool isPrime(int number) {
        if (number == 2) {
            return true;
        }
        if (number <= 0 || number == 1 || number % 2 == 0) {
            return false;
        }
        int sqrtNumber =(int)sqrt(number) + 1;
        for (int i = 3; i < sqrtNumber; i = i + 2) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }
}// ariel
#endif //CMAKEITER_MYALGOS_HPP
