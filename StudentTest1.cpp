#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;
// Test case for adding elements to the MagicalContainer
TEST_CASE("Adding elements to MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Adding a single element") {
        container.addElement(10);
        CHECK(container.size() == 1);
    }

    SUBCASE("Adding multiple elements") {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        CHECK(container.size() == 3);
    }
}

// Test case for removing elements from the MagicalContainer
TEST_CASE("Removing elements from MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Removing an existing element") {
        container.addElement(10);
        container.addElement(20);
        CHECK_NOTHROW(container.removeElement(10));
        CHECK(container.size() == 1);
    }

    SUBCASE("Removing a non-existing element") {
        container.addElement(10);
        container.addElement(20);
        CHECK_THROWS_AS(container.removeElement(30), runtime_error);
        CHECK(container.size() == 2);
    }
}

// Test case for the AscendingIterator
TEST_CASE("AscendingIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(15);
    container.addElement(25);


    SUBCASE("Iterating over elements") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 15);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::AscendingIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for the SideCrossIterator
TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(40);

    SUBCASE("Iterating over elements") {
        MagicalContainer::SideCrossIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::SideCrossIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for the PrimeIterator
TEST_CASE("PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.addElement(6);

    SUBCASE("Iterating over elements") {
        MagicalContainer::PrimeIterator it(container);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::PrimeIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}
//--------------------------------------------------------------
// Test case for comparing iterators from the same container
TEST_CASE("Comparing iterators from the same container") {
    MagicalContainer container;
    for (int i = 1; i <= 10; ++i) {
        container.addElement(i * 10);
    }

    SUBCASE("Comparing AscendingIterator with itself") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }

    SUBCASE("Comparing SideCrossIterator with itself") {
        MagicalContainer::SideCrossIterator it1(container);
        MagicalContainer::SideCrossIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }

    SUBCASE("Comparing PrimeIterator with itself") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }
}
//------------------------------------------------------
// Test case for traversing the AscendingIterator
TEST_CASE("Traversing AscendingIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Iterating in ascending order") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 4);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(*it == 14);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for traversing the PrimeIterator
TEST_CASE("Traversing PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Iterating over prime elements") {
        MagicalContainer::PrimeIterator it(container);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for the SideCrossIterator
TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Iterating in side-cross order from start to end") {
        MagicalContainer::SideCrossIterator it(container);

        CHECK(*it == 1);
        ++it;
        CHECK(*it == 14);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(*it == 4);
        ++it;
        CHECK(it == it.end());
    }
}
//-------------------------------------------------------
// Test case for comparing AscendingIterator
TEST_CASE("Comparing AscendingIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Comparing iterators after increments") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);

        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK_FALSE((it1 < it2));
        CHECK((it1 > it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK_FALSE((it1 < it2));
        CHECK((it1 > it2));

        ++it2;
        ++it2;
        ++it1;
        CHECK(it1 == it1.end());
        CHECK(it2 == it2.end());
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));
    }
}


// Test case for comparing PrimeIterator
TEST_CASE("Comparing PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Comparing iterators after increments") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);

        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK_FALSE((it1 < it2));
        CHECK((it1 > it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it1;
        CHECK_FALSE((it1 == it2));
        CHECK((it1 != it2));
        CHECK((it1 > it2));
        CHECK_FALSE((it1 < it2));

        ++it2;
        CHECK((it1 == it2));
        CHECK_FALSE((it1 != it2));
        CHECK_FALSE((it1 > it2));
        CHECK_FALSE((it1 < it2));

        CHECK(it1 == it1.end());
        CHECK(it2 == it2.end());

    }
}


// Test case for comparing SideCrossIterator
TEST_CASE("Comparing SideCrossIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Comparing iterators after increments") {
        MagicalContainer::SideCrossIterator itStart1(container);
        MagicalContainer::SideCrossIterator itStart2(container);

        CHECK((itStart1 == itStart2));
        CHECK_FALSE((itStart1 != itStart2));
        CHECK_FALSE((itStart1 > itStart2));
        CHECK_FALSE((itStart1 < itStart2));

        ++itStart1;
        CHECK_FALSE((itStart1 == itStart2));
        CHECK((itStart1 != itStart2));
        CHECK_FALSE((itStart1 < itStart2));
        CHECK((itStart1 > itStart2));

        ++itStart2;
        CHECK((itStart1 == itStart2));
        CHECK_FALSE((itStart1 != itStart2));
        CHECK_FALSE((itStart1 > itStart2));
        CHECK_FALSE((itStart1 < itStart2));

        ++itStart1;
        CHECK((itStart1 == itStart1));
        CHECK_FALSE((itStart1 != itStart1));
        CHECK_FALSE((itStart1 > itStart1));
        CHECK_FALSE((itStart1 < itStart1));
    }
}
//---------------------------------------------------
TEST_CASE("Iterator Increment Beyond End") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    SUBCASE("Ascending Iterator") {
        MagicalContainer::AscendingIterator it(container);

        // Increment until the end
        while (it != it.end()) {
            ++it;
        }
    
        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++it, runtime_error);
    }

    SUBCASE("Prime Iterator") {
        MagicalContainer::PrimeIterator it(container);

        // Increment until the end
        while (it != it.end()) {
            ++it;
        }

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++it, runtime_error);
    }

    SUBCASE("SideCross Iterator") {
        MagicalContainer::SideCrossIterator it(container);

        // Increment until the end
        while (it != it.end()) {
            ++it;
        }

        // Attempt to increment beyond the end
        CHECK_THROWS_AS(++it, runtime_error);
    }
}
//checking that the iterators dont impact each other
TEST_CASE("Multiple Iterators Test") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.addElement(6);
    container.addElement(7);
    container.addElement(8);
    container.addElement(9);

    SUBCASE("Ascending Iterators") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);

        ++(++it1);
        CHECK(*it1 == 3);
        ++it2;
        CHECK(*it2 == 2);
        ++(++(++it1));
        CHECK(*it2 == 2);
        CHECK(*it1 == 6);
    }

    SUBCASE("SideCross Iterators") {
        MagicalContainer::SideCrossIterator it1(container);
        MagicalContainer::SideCrossIterator it2(container);

        ++it1;
        CHECK(*it1 == 9);
        ++it2;
        CHECK(*it2 == 9);
        ++it1;
        CHECK(*it2 == 9);
        CHECK(*it1 == 2);
        ++(++(++it2));
        CHECK(*it2 == 3);
    }

    SUBCASE("Prime Iterators") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);

        ++it1;
        CHECK(*it1 == 3);
        CHECK(*it2 == 2);
        ++it2;
        ++it1;
        CHECK(*it2 == 3);
        CHECK(*it1 == 5);
        ++(++it2);
        CHECK(*it2 == 7);
    }
}
// Test case for the AscendingIterator with negative and positive numbers
TEST_CASE("AscendingIterator with Negative and Positive Numbers") {
    MagicalContainer container;
    container.addElement(-3);
    container.addElement(5);
    container.addElement(-2);
    container.addElement(0);
    container.addElement(4);
    container.addElement(-1);
    container.addElement(3);
    container.addElement(-4);
    container.addElement(2);
    container.addElement(1);

    SUBCASE("Iterating over elements") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == -4);
        ++it;
        CHECK(*it == -3);
        ++it;
        CHECK(*it == -2);
        ++it;
        CHECK(*it == -1);
        ++it;
        CHECK(*it == 0);
        ++it;
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 4);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }
}

// Test case for the PrimeIterator with no prime numbers in the container
TEST_CASE("PrimeIterator with No Prime Numbers") {
    MagicalContainer container;
    container.addElement(4);
    container.addElement(6);
    container.addElement(8);
    container.addElement(9);
    container.addElement(10);
    container.addElement(12);

    SUBCASE("Iterating over elements") {
        MagicalContainer::PrimeIterator it(container);

        CHECK(it == it.end());
        CHECK_THROWS_AS(++it, runtime_error);
    }
}

// Test case for the SideCrossIterator with a single element in the container
TEST_CASE("SideCrossIterator with Single Element") {
    MagicalContainer container;
    container.addElement(100);

    SUBCASE("Iterating over elements") {
        MagicalContainer::SideCrossIterator it(container);
        CHECK(*it == 100);
        ++it;
        CHECK(it == it.end());
    }
}

TEST_CASE("operator= throws when iterators are pointing at different containers") {
    MagicalContainer container1;
    MagicalContainer container2;

    container1.addElement(1);
    container1.addElement(2);
    container1.addElement(3);

    container2.addElement(4);
    container2.addElement(5);
    container2.addElement(6);    

   SUBCASE("AscendingIterator")
   {
        MagicalContainer::AscendingIterator it1(container1);
        MagicalContainer::AscendingIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
   }
   SUBCASE("SideCrossIterator")
   {
        MagicalContainer::SideCrossIterator it1(container1);
        MagicalContainer::SideCrossIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
   }
   SUBCASE("AscendingIterator")
   {
        MagicalContainer::PrimeIterator it1(container1);
        MagicalContainer::PrimeIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
   }
}


vector<int> numVec={-999,9999,0,4,13,-14,-3,3,77,7,123,-456,957,12345678,-23456781,1234,456,6,2,1,-1,871,888,15,20,-32,-144,700,123456789,333,-333,81};
//sortedNumVec={-23456781,-999,-456,-333,-144,-32,-14,-3,-1,0,1,2,3,4,6,7,13,15,20,77,81,123,333,456,700,871,888,957,1234,9999,12345678,123456789};
void fillVector(vector<int>* vector){
    ::srand((unsigned) time(NULL));
    vector->reserve(100);
    for (int i = 0; i < 100; ++i) {
        int num=::rand();
        int sign=::rand()%2;
        while(std::count(vector->begin(), vector->end(),num)){
            //no duplication for tests
            num=::rand();
        }
        switch (sign) {
            case 0:
                vector->push_back(num);
                break;
            case 1:
                vector->push_back(num*-1);
                break;
            default:
                break;
        }
    }
}
void buildContainer(MagicalContainer *container ,vector<int>* vector) {
    std::sort(vector->begin(), vector->end());
    for (int num: *vector) {
        container->addElement(num);
    }
}

TEST_SUITE("Container"){
    TEST_CASE("Basic operations on container"){
        MagicalContainer container;
        CHECK_EQ(container.size(),0);
        CHECK_NOTHROW(container.removeElement(100));

        CHECK_NOTHROW(container.addElement(100));
        CHECK_EQ(container.size(),1);

        CHECK_NOTHROW((container.removeElement(100)));
        puts("hereeeeeeeeeeeee\n");
        CHECK_EQ(container.size(),0);
        for (int i = 1; i <= 50; ++i) {
            container.addElement(i);
            CHECK_EQ(container.size(),i);
        }
        int size=container.size();
        container.addElement(10);
        container.addElement(11);
        CHECK_EQ(container.size(),size);
        for (int i = 50; i >0 ; --i) {
            CHECK_EQ(container.size(),i);
            container.removeElement(i);
        }
        CHECK_EQ(container.size(),0);
        container.removeElement(10);
        CHECK_EQ(container.size(),0);
    }
}

TEST_CASE("Is Prime"){
    CHECK_FALSE(isPrime(4));
    CHECK(isPrime(2));
    CHECK_FALSE(isPrime(1000));
    CHECK(isPrime(3));
    CHECK_FALSE(isPrime(81));
    CHECK(isPrime(5));
    CHECK(isPrime(31));
    CHECK(isPrime(1993));
    CHECK(isPrime(5659));
    CHECK_FALSE(isPrime(2023));
}

TEST_SUITE("Operators and Iterating over the list"){
    TEST_CASE("AscendingIterator"){
        MagicalContainer container;
        buildContainer(&container,&numVec);
        MagicalContainer::AscendingIterator ascIter(container);
        auto it=ascIter.begin();
        size_t i=0;
        CHECK((ascIter.begin()==ascIter.begin()));
        CHECK((ascIter.begin()!=ascIter.end()));
        for (; it != ascIter.end(); ++it,++i)  {
            CHECK_EQ(*it,numVec[i]);
            CHECK_EQ(*it.operator->(),numVec[i]);
        }
        CHECK(it==ascIter.end());
    }
    TEST_CASE("PrimeIterator"){
        MagicalContainer container;
        buildContainer(&container,&numVec);
        MagicalContainer::PrimeIterator primeIter(container);
        auto it=primeIter.begin();
        size_t i=0;
        CHECK((primeIter.begin()==primeIter.begin()));
        CHECK((primeIter.begin()!=primeIter.end()));
        for (; it != primeIter.end();++i)  {
            if(isPrime(numVec[i])) {
                CHECK(*it== numVec[i]);
                ++it;
            }
        }
        CHECK(it==primeIter.end());
    }
}


TEST_SUITE("Iterators validation after Insertion/Erasure , Relational Operators"){

    TEST_CASE("AscendingIterator"){
        MagicalContainer container;
        buildContainer(&container,&numVec);   //-23456781,-999,-456,-333,-144,-32,-14,-3,-1,
        // 0,1,2,3,4,6,7,13,15,20,77,81,123,333,456,700
        //,871,888,957,1234,9999,12345678,123456789
        MagicalContainer::AscendingIterator ascIterator(container);
        auto it=ascIterator.begin();

        CHECK(*it==-23456781);
        ++it;
        container.addElement(-111111);
        CHECK(*it==-999);
        container.addElement(-555);
        ++it;
        CHECK(*it==-555);
        container.removeElement(-456);
        ++it;
        CHECK(*it==-333);
        container.removeElement(-999);
        CHECK(*it==-333);
    }
    //to avoid non-simple logic in test we will use a pre-made vector
    TEST_CASE("SideCrossIterator"){
        MagicalContainer container;
        container.addElement(1);
        container.addElement(100);
        container.addElement(5);
        container.addElement(90);
        container.addElement(10);
        container.addElement(80);
        container.addElement(30);
        container.addElement(60);
        MagicalContainer::SideCrossIterator crossIterator(container);
        auto it=crossIterator.begin();

        CHECK(*it==1);
        ++it;
        container.addElement(110);
        CHECK(*it==100);
        ++it;
        CHECK(*it==10);
        container.removeElement(90);
        ++it;
        CHECK(*it==80);
    }

    TEST_CASE("PrimeIterator"){
        MagicalContainer container;
        buildContainer(&container,&numVec);   //-23456781,-999,-456,-333,-144,-32,-14,-3,-1,
        // 0,1,2,3,4,6,7,13,15,20,77,81,123,333,456,700
        //,871,888,957,1234,9999,12345678,123456789
        MagicalContainer::PrimeIterator primeIterator(container);
        auto it=primeIterator.begin();
        CHECK(*it==2);
        container.removeElement(3);
        container.addElement(5);
        ++it;
        CHECK(*it==5);
        container.removeElement(7);
        ++it;
        CHECK(*it==13);
        container.removeElement(2);
        CHECK(*it==13);

    }

}
