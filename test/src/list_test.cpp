/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 08:40:43 by charles           #+#    #+#             */
/*   Updated: 2020/12/01 00:20:47 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers_test.hpp"
#include <vector>

static void testConstructorDefault()
{
    testName = "List.List default";

    ft::list<int> l1;
    ft::list<char> l2;
    ft::list<char*> l3;
    ft::list<char**> l4;
    ft::list< ft::list<char**> > l5;

    ASSERT(l1.size() == 0);
    ASSERT(l2.size() == 0);
    ASSERT(l3.size() == 0);
    ASSERT(l4.size() == 0);
    ASSERT(l5.size() == 0);
    ASSERT(l1.empty());
    ASSERT(l2.empty());
    ASSERT(l3.empty());
    ASSERT(l4.empty());
    ASSERT(l5.empty());

    ASSERT(l1.max_size() > 0);
}

static void testConstructorFill()
{
    testName = "List.List fill";

    ft::list<int> l1(5);
    ASSERT(l1.size() == 5);
    ASSERT(l1.front() == int());
    ASSERT(l1.back() == int());
    for (ft::list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
        ASSERT(*it == int());

    ft::list<char> l2(3);
    ASSERT(l2.size() == 3);
    ASSERT(l2.front() == char());
    ASSERT(l2.back() == char());
    for (ft::list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
        ASSERT(*it == char());

    ft::list<float> l3(4, 42.42f);
    ASSERT(l3.size() == 4);
    ASSERT(l3.front() == 42.42f);
    ASSERT(l3.back() == 42.42f);
    for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
        ASSERT(*it == 42.42f);
}

static void testConstructorRange()
{
    testName = "List.List range";

    size_t i;
    int         arr1[5] = {1, 2, 3, 4, 5};
    std::string arr2[3] = {"bonjour", "je", "suis"};
    float       arr3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};

    ft::list<int> l1(arr1, arr1 + 5);
    ASSERT(l1.size() == 5);
    ASSERT(l1.front() == 1);
    ASSERT(l1.back() == 5);
    i = 0;
    for (ft::list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
        ASSERT(*it == arr1[i++]);

    ft::list<std::string> l2(arr2, arr2 + 3);
    ASSERT(l2.size() == 3);
    ASSERT(l2.front() == "bonjour");
    ASSERT(l2.back() == "suis");
    i = 0;
    for (ft::list<std::string>::iterator it = l2.begin(); it != l2.end(); ++it)
        ASSERT(*it == arr2[i++]);


    ft::list<float> l3(arr3, arr3 + 5);
    ASSERT(l3.size() == 5);
    ASSERT(l3.front() == 1.2f);
    ASSERT(l3.back() == 5.6f);
    i = 0;
    for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
        ASSERT(*it == arr3[i++]);

    ft::list<int> l4(arr1 + 1, arr1 + 4);
    ASSERT(l4.size() == 3);
    ASSERT(l4.front() == 2);
    ASSERT(l4.back() == 4);
    i = 0;
    for (ft::list<int>::iterator it = l4.begin(); it != l4.end(); ++it)
        ASSERT(*it == arr1[1 + i++]);
}

static void testConstructorCopy()
{
    testName = "List.List copy";

    size_t           i;
    int              arr1[5] = {1, 2, 3, 4, 5};
    float            arr3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
    ft::list<int> l1_copied;
    ft::list<char>   l2_copied(3);
    ft::list<float>  l3_copied(4, 42.42f);
    ft::list<float>  l4_copied(arr3, arr3 + 5);
    ft::list<int>    l5_copied(arr1 + 1, arr1 + 4);

    ft::list<int>    l1(l1_copied);
    ft::list<char>   l2(l2_copied);
    ft::list<float>  l3(l3_copied);
    ft::list<float>  l4(l4_copied);
    ft::list<int>    l5(l5_copied);

    ASSERT(l1.size() == 0);
    ASSERT(l1.empty());

    ASSERT(l2.size() == 3);
    ASSERT(l2.front() == char());
    ASSERT(l2.back() == char());
    for (ft::list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
        ASSERT(*it == char());

    ASSERT(l3.size() == 4);
    ASSERT(l3.front() == 42.42f);
    ASSERT(l3.back() == 42.42f);
    for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
        ASSERT(*it == 42.42f);

    ASSERT(l4.size() == 5);
    ASSERT(l4.front() == 1.2f);
    ASSERT(l4.back() == 5.6f);
    i = 0;
    for (ft::list<float>::iterator it = l4.begin(); it != l4.end(); ++it)
        ASSERT(*it == arr3[i++]);

    ASSERT(l5.size() == 3);
    ASSERT(l5.front() == 2);
    ASSERT(l5.back() == 4);
    i = 0;
    for (ft::list<int>::iterator it = l5.begin(); it != l5.end(); ++it)
        ASSERT(*it == arr1[1 + i++]);
}

static void testOperatorAssign()
{
    testName = "List.operator=";

    size_t           i;
    int              arr1[5] = {1, 2, 3, 4, 5};
    float            arr3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
    ft::list<int>    l1_copied;
    ft::list<char>   l2_copied(3);
    ft::list<float>  l3_copied(4, 42.42f);
    ft::list<float>  l4_copied(arr3, arr3 + 5);
    ft::list<int>    l5_copied(arr1 + 1, arr1 + 4);

    ft::list<int>    l1;
    ft::list<char>   l2;
    ft::list<float>  l3;
    ft::list<float>  l4;
    ft::list<int>    l5;

    l1 = l1_copied;
    l2 = l2_copied;
    l3 = l3_copied;
    l4 = l4_copied;
    l5 = l5_copied;

    ASSERT(l1.size() == 0);
    ASSERT(l1.empty());

    ASSERT(l2.size() == 3);
    ASSERT(l2.front() == char());
    ASSERT(l2.back() == char());
    for (ft::list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
        ASSERT(*it == char());

    ASSERT(l3.size() == 4);
    ASSERT(l3.front() == 42.42f);
    ASSERT(l3.back() == 42.42f);
    for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
        ASSERT(*it == 42.42f);

    ASSERT(l4.size() == 5);
    ASSERT(l4.front() == 1.2f);
    ASSERT(l4.back() == 5.6f);
    i = 0;
    for (ft::list<float>::iterator it = l4.begin(); it != l4.end(); ++it)
        ASSERT(*it == arr3[i++]);

    ASSERT(l5.size() == 3);
    ASSERT(l5.front() == 2);
    ASSERT(l5.back() == 4);
    i = 0;
    for (ft::list<int>::iterator it = l5.begin(); it != l5.end(); ++it)
        ASSERT(*it == arr1[1 + i++]);
}

void listTest()
{
    testContainer = "List";

    testConstructorDefault();
    testConstructorFill();
    testConstructorRange();
    testConstructorCopy();
    testOperatorAssign();

    // testBegin();
    // testEnd();
    // testRbegin();
    // testRend();
    //
    // testResize();
    // testReserve();
    //
    // testOperatorBracket();
    // testAt();
    // testFront();
    // testBack();
    //
    // testAssign();
    // testPushBack();
    // testPopBack();
    // testInsert();
    // testErase();
    // testSwap();
    // testClear();
    //
    // testOperatorEqual();
    // testOperatorCompar();
    // testSwapFunc();
}
