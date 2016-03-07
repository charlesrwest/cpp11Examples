#define CATCH_CONFIG_MAIN //Make main function automatically
#include "catch.hpp"
#include "SOMException.hpp"
#include<memory>
#include<string>
#include<cstdio>
#include<functional>
#include<unistd.h>
#include<random>
#include<cmath>
#include<typeinfo>
#include<algorithm>
#include<regex>
#include<chrono>
#include<thread>
#include<future> 



TEST_CASE("Move functionality", "Move functionality")
{
std::vector<int> bob{2,4,6,8};

std::vector<int> bill = std::move(bob);
REQUIRE(bill.size() == 4); //Memory stored in bob moved to bill
REQUIRE(bob.size() == 0);
}














constexpr double oneHundred = 100.0;
constexpr double nearTen = sqrt(oneHundred);

TEST_CASE("Const expression", "Const expression")
{
REQUIRE(fabs(nearTen-10.0) < .001 );
}




















class initializerListTestClass
{
public:
initializerListTestClass(std::initializer_list<int> inputIntegers)
{
values = std::vector<int>(inputIntegers.begin(), inputIntegers.end());
}

std::vector<int> values;
};

TEST_CASE("Initializer lists", "Initializer lists")
{
initializerListTestClass bob{10, 8, 6, 4, 2};

REQUIRE(bob.values.size() == 5);
}













TEST_CASE("Auto/decltype", "Auto/decltype")
{
auto bob = 5;
decltype(bob) bill = 30;

REQUIRE(typeid(bob) == typeid(int));
REQUIRE(typeid(bill) == typeid(int));
}


























TEST_CASE("Range based for loop", "Range based for loop")
{
std::vector<int> bob{2,4,5,6,7,8};

int i=0;
for(const int &instance : bob)
{
REQUIRE(instance == bob[i]);
i++;
}
}















TEST_CASE("Lambda functions", "Lambda functions")
{
auto exampleLambda1 = [](int input1, int input2) -> int
{
return input1+input2;
};

REQUIRE(exampleLambda1(6,8) == (6+8));

int five = 5;
int ten = 10;

auto exampleLambda2 = [&]() -> int 
{
return five+ten;
};

REQUIRE(exampleLambda2() == 15);
}


















class delegatingConstructorClass
{
public:
delegatingConstructorClass(double inputNumber)
{
number = inputNumber;
}

delegatingConstructorClass() : delegatingConstructorClass(10.0)
{
}

double number;
};

TEST_CASE("Delegating constructors", "Delegating constructors")
{
delegatingConstructorClass bob;

REQUIRE(fabs(bob.number-10.0) < .001);
}

































//Talk about override, nullptr






















enum bob
{
BOB_ENUM_VALUE1 = 1,
BOB_ENUM_VALUE2 = 2,
BOB_ENUM_VALUE3 = 3
};

enum jerry
{
JERRY_ENUM_VALUE1 = 1,
JERRY_ENUM_VALUE2 = 2,
JERRY_ENUM_VALUE3 = 3
};

enum class bill : char
{
ENUM_VALUE1 = 1,
ENUM_VALUE2 = 2,
ENUM_VALUE3 = 3
};



TEST_CASE("Enum class", "Enum class")
{
REQUIRE(JERRY_ENUM_VALUE1 == BOB_ENUM_VALUE1);

bill value = bill::ENUM_VALUE1;
REQUIRE(value == bill::ENUM_VALUE1);
}




























TEST_CASE("Right angle bracket", "Right angle bracket")
{
std::vector<std::vector<int>> testVector;

REQUIRE(testVector.size() == 0);
}












class defaultConstructorDemoClass
{
defaultConstructorDemoClass() = default;
defaultConstructorDemoClass(int) {};

void function(double inputDouble) {};
void function(int) = delete;
};











std::tuple<int,std::string, double> returnThings(long int inputNumber)
{
return std::tuple<int,std::string, double>{inputNumber, std::to_string(inputNumber), inputNumber};
}

TEST_CASE("Tuples/tie", "Tuples/tie")
{
std::tuple<int, std::string, double> tuple = returnThings(4);

REQUIRE(std::get<0>(tuple) == 4);
REQUIRE(std::get<1>(tuple) == "4");
REQUIRE(fabs(std::get<2>(tuple) - 4.0) < .01);

int integer = 0;
std::string testString;
double floatingPoint = 0.0;

std::tie(integer, testString, floatingPoint) = returnThings(5);
REQUIRE(integer == 5);
REQUIRE(testString == "5");
REQUIRE(fabs(floatingPoint - 5.0) < .01);
}









void setString(std::string &inputString)
{
inputString = "Bob";
}

TEST_CASE("Thread", "Thread")
{
std::string bobString;
std::thread thread0(setString, std::ref(bobString)); //Set function to execute in seperate thread

thread0.join(); //Wait for thread to finish
REQUIRE(bobString == "Bob");
}




































TEST_CASE("std::array", "std::array")
{
int basicArray[10] = {0,1,2,3,4,5,6,7,8,9};
std::array<int, 10> standardArray{0,1,2,3,4,5,6,7,8,9};

for(int i=0; i<10; i++)
{
REQUIRE(basicArray[i] == i);
}

for(int i=0; i<standardArray.size(); i++)
{
REQUIRE(standardArray[i] == i);
}

int i=0;
for(int instance : standardArray)
{
REQUIRE(instance == i);
i++;
}

REQUIRE(*standardArray.begin() == 0);
REQUIRE(*standardArray.rbegin() == 9);

std::reverse(standardArray.begin(), standardArray.end());
REQUIRE(*standardArray.begin() == 9);
REQUIRE(*standardArray.rbegin() == 0);

for(int i=0; i<standardArray.size(); i++)
{
REQUIRE(standardArray[i] == (9-i));
}
}

























TEST_CASE("unique/shared pointers", "unique/shared pointers")
{
{
//Allocate integer
std::unique_ptr<int> uniquePointer(new int(5));
REQUIRE(*uniquePointer == 5);
}
//uniquePointer goes out of scope, delete called on the memory it points to

{//Allocate "bob"
std::shared_ptr<std::string> sharedPointer0(new std::string("bob"));
REQUIRE(*sharedPointer0 == "bob");
REQUIRE(sharedPointer0.use_count() == 1);

{
std::shared_ptr<std::string> sharedPointer1 = sharedPointer0;
std::shared_ptr<std::string> sharedPointer2 = sharedPointer0;
std::shared_ptr<std::string> sharedPointer3 = sharedPointer0;

REQUIRE(*sharedPointer1 == "bob");
REQUIRE(sharedPointer1.use_count() == 4);
REQUIRE(*sharedPointer2 == "bob");
REQUIRE(sharedPointer2.use_count() == 4);
REQUIRE(*sharedPointer3 == "bob");
REQUIRE(sharedPointer3.use_count() == 4);
}

REQUIRE(*sharedPointer0 == "bob");
REQUIRE(sharedPointer0.use_count() == 1);
}
//Last shared pointer goes out of scope, "bob" deleted
}
























TEST_CASE("Regular Expressions", "Regular Expressions")
{

//Make regular expression
std::regex regularExpression("[ab].[ab]"); //Search for strings which start with a or b, followed by any character and end with a or b

std::string testString = "bob  aag  nvm  aaa  try  naa  aba";


std::sregex_iterator regexIterator(testString.begin(), testString.end(), regularExpression);

std::sregex_iterator endIterator;

std::vector<std::string> expectedValues{"bob", "aaa", "aba"}; 

int i=0;
while(regexIterator != endIterator) 
{
REQUIRE(regexIterator->str() == expectedValues[i]);
++regexIterator;
++i;
}
}





















TEST_CASE("random", "random")
{
std::default_random_engine generator;
std::uniform_real_distribution<double> uniformDistribution(0.0,10.0);
std::bernoulli_distribution bernoulliDistribution(.2);
std::binomial_distribution<int> binomialDistribution(10, .2);
std::normal_distribution<double> normalDistribution(0.0, 1.0);


for(int i=0; i<10; i++)
{
double randomNumber = uniformDistribution(generator);
REQUIRE(randomNumber >= 0.0); 
REQUIRE(randomNumber <= 10.0);
}

}





TEST_CASE("time", "time")
{

//Wall clock time, can be changed by the system clock changing -> can go backwards in time
std::chrono::system_clock::time_point systemNow = std::chrono::system_clock::now();

//Steady time, guaranteed to never go backwards
std::chrono::steady_clock::time_point steadyNow = std::chrono::steady_clock::now();

std::chrono::steady_clock::time_point steadyYesterday = steadyNow - std::chrono::hours(24);

auto timeSinceYesterday = steadyNow - steadyYesterday;
}


