#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <charconv>
#include <functional>
#include "node.h"
#include "genericlookuptable.h"
#include "string"

void runTests() {
    using storage0 = LinkedListEmptyNode;
    using storage1 = LinkedListNode<"a", 3>;
    using storageN = LinkedListNode<"a", 3, LinkedListNode<"b", 4, LinkedListNode<"c", 9>>>;

    // get tests

    //0 cases
    static_assert(LinkedListGetValue<storage0, "a">::value  == -1); //invalid case

    //1 cases
    static_assert(LinkedListGetValue<storage1, "a">::value  == 3);
    static_assert(LinkedListGetValue<storage1, "b">::value  == -1); //invalid case

    // n cases
    static_assert(LinkedListGetValue<storageN, "a">::value  == 3);
    static_assert(LinkedListGetValue<storageN, "b">::value  == 4);
    static_assert(LinkedListGetValue<storageN, "c">::value  == 9);
    static_assert(LinkedListGetValue<storageN, "d">::value  == -1); //invalid case
    
    // set tests

    //0 cases
    static_assert(std::is_same<storage0, LinkedListSetValue<storage0, "a", 40>::newList>::value); //invalid case

    //1 cases
    static_assert(std::is_same<LinkedListNode<"a", 40>, LinkedListSetValue<storage1, "a", 40>::newList>::value); 
    static_assert(std::is_same<storage1, LinkedListSetValue<storage1, "b", 40>::newList>::value); //invalid case

    //n cases
    static_assert(std::is_same<LinkedListNode<"a", 40, LinkedListNode<"b", 4, LinkedListNode<"c", 9>>>, LinkedListSetValue<storageN, "a", 40>::newList>::value); 
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 40, LinkedListNode<"c", 9>>>, LinkedListSetValue<storageN, "b", 40>::newList>::value); 
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 4, LinkedListNode<"c", 40>>>, LinkedListSetValue<storageN, "c", 40>::newList>::value); 
    static_assert(std::is_same<storageN, LinkedListSetValue<storageN, "d", 40>::newList>::value);  //invalid case


    // add tests

    //0 cases
    static_assert(std::is_same<LinkedListNode<"a", 40>, LinkedListAddValue<storage0, "a", 40>::newList>::value);

    //1 cases
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 4>>, LinkedListAddValue<storage1, "b", 4>::newList>::value); 

    //n cases
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 4, LinkedListNode<"c", 9, LinkedListNode<"d", 12>>>>, LinkedListAddValue<storageN, "d", 12>::newList>::value); 


    // set or add tests

    //0 cases
    static_assert(std::is_same<LinkedListNode<"a", 40>, LinkedListSetOrAddValue<storage0, "a", 40>::newList>::value); 

    //1 cases
    static_assert(std::is_same<LinkedListNode<"a", 40>, LinkedListSetOrAddValue<storage1, "a", 40>::newList>::value); 
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 40>>, LinkedListSetOrAddValue<storage1, "b", 40>::newList>::value); //add case

    //n cases
    static_assert(std::is_same<LinkedListNode<"a", 40, LinkedListNode<"b", 4, LinkedListNode<"c", 9>>>, LinkedListSetOrAddValue<storageN, "a", 40>::newList>::value); 
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 40, LinkedListNode<"c", 9>>>, LinkedListSetOrAddValue<storageN, "b", 40>::newList>::value); 
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 4, LinkedListNode<"c", 40>>>, LinkedListSetOrAddValue<storageN, "c", 40>::newList>::value); 
    static_assert(std::is_same<LinkedListNode<"a", 3, LinkedListNode<"b", 4, LinkedListNode<"c", 9, LinkedListNode<"d", 40>>>>, LinkedListSetOrAddValue<storageN, "d", 40>::newList>::value);  //invalid case

}



int main(int argc, char* argv[])
{

    runTests();
    /*
    TODO.
    Make it so that you don't have to explicitly pass in a linkedlist item to Execute
    */

    using storage = LinkedListNode<"a", 3, LinkedListNode<"b", 4, LinkedListNode<"hey!", 9>>>;


    std::cout << LinkedListGetValue<storage, "a">::value << std::endl;
    std::cout << LinkedListGetValue<LinkedListSetValue<storage, "a", 40>::newList, "a">::value << std::endl;
    std::cout << LinkedListGetValue<LinkedListAddValue<storage, "new", 90>::newList, "new">::value << std::endl;


    using code = Execute<storage,
                         Assign<"x", Num<6>>,
                         Assign<"y", BinOpPlus<Num<2>, Num<7>>>,
                         Assign<"z", BinOpPlus<BinOpPlus<Num<2>, Num<10>>, Num<7>>>>;


    std::cout << LinkedListGetValue<code::values, "x">::value << std::endl;
    std::cout << LinkedListGetValue<code::values, "y">::value << std::endl;
    std::cout << LinkedListGetValue<code::values, "z">::value << std::endl;



    return 0;

    // using expression = BinOpPlus<Num<2>, BinOpPlus<Num<2>, Num<5>>>;
    using expression = BinOpPlus<Num<2>, Num<7>>;

    constexpr int result = expression::value;
    static_assert(result == 9);

    // static_assert(expression::value == 7);

    return 0;
  
}

