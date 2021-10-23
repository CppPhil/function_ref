#include <cstdint>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <tl/function_ref.hpp>

namespace {
void f(tl::function_ref<int(int)> func)
{
  std::cout << func(5) << '\n';
}

int twoTimes(int i)
{
  return i * 2;
}

struct TwoTimes {
  int operator()(int i) const noexcept
  {
    return i * 2;
  }
};

struct City {
  std::string   name;
  std::uint64_t population;
  std::string   country;
};

std::vector<City> findAllMatching(
  const std::vector<City>&            cities,
  tl::function_ref<bool(const City&)> predicate)
{
  std::vector<City> result{};
  result.reserve(cities.size());
  std::copy_if(
    cities.begin(), cities.end(), std::back_inserter(result), predicate);
  result.shrink_to_fit();
  return result;
}

double timesTwo(double a)
{
  return a * 2;
}

struct Struct {
  void memFun(int i) const
  {
    std::cout << i << '\n';
  }
};
} // anonymous namespace

int main()
{
  f(&twoTimes);
  f([](int i) { return i * 2; });
  f(TwoTimes{});

  const std::vector<City> cities{
    {"Tokyo", 37'339'804, "Japan"},
    {"Milan", 3'144'473, "Italy"},
    {"Caracas", 2'945'858, "Venezuela"},
    {"Hanoi", 4'874'982, "Vietnam"},
    {"Santiago", 6'811'595, "Chile"},
    {"Xi'An", 8'274'651, "China"},
    {"Los Angeles", 3'983'540, "United States"},
    {"Kinshasa", 14'970'460, "Democratic Republic of the Congo"},
    {"Mexico City", 21'918'936, "Mexico"},
    {"Shenzhen", 12'591'696, "China"},
    {"Dubai", 2'921'376, "United Arab Emirates"},
    {"Paris", 11'078'546, "France"},
    {"Algiers", 2'809'158, "Algeria"},
    {"Moscow", 12'593'252, "Russia"},
    {"Shanghai", 27'795'702, "China"},
    {"Lisbon", 2'971'587, "Portugal"},
    {"Delhi", 31'181'376, "India"},
    {"Bangalore", 12'764'935, "India"},
    {"Dhaka", 21'741'090, "Bangladesh"},
    {"Sao Paulo", 22'237'472, "Brazil"},
    {"London", 9'425'622, "United Kingdom"},
    {"Cairo", 21'322'750, "Egypt"},
    {"Istanbul", 15'415'197, "Turkey"},
    {"Berlin", 3'566'791, "Germany"},
    {"Kolkata", 14'974'073, "India"},
    {"Beijing", 20'896'820, "China"},
    {"Madrid", 6'668'865, "Spain"},
    {"Chengdu", 9'305'116, "China"},
    {"Chongqing", 16'382'376, "China"},
    {"New York City", 8'230'290, "United States"},
    {"Mumbai", 20'667'656, "India"},
    {"Manila", 14'158'573, "Philippines"},
    {"Bangkok", 10'722'815, "Thailand"}};

  const std::vector<City> moreThan10Mil{findAllMatching(
    cities, [](const City& city) { return city.population > 10'000'000; })};
  std::cout << "More than " << 10'000'000 << ":\n";
  for (const City& city : moreThan10Mil) {
    std::cout << city.name << '\n';
  }

  const std::vector<City> chineseCities{findAllMatching(
    cities, [](const City& city) { return city.country == "China"; })};
  std::cout << "Chinese cities:\n";
  for (const City& city : chineseCities) {
    std::cout << city.name << ' ' << city.population << '\n';
  }

  // tl::function_ref<double(double)> dangling{&timesTwo};
  // std::cout << dangling(2.5) << '\n';
  const auto                       functionPointer{&timesTwo};
  tl::function_ref<double(double)> fix{functionPointer};
  std::cout << fix(2.5) << '\n';

  // tl::function_ref<void(const Struct&, int)> dangling{&Struct::memFun};
  // dangling(Struct{}, 5);
  const auto                                 mfp{&Struct::memFun};
  tl::function_ref<void(const Struct&, int)> fix2{mfp};
  fix2(Struct{}, 5);

  // tl::function_ref<void()> dangling{
  //  [] { std::cout << "Hello from lambda.\n"; }};
  // dangling();
  auto                     lambda{[] { std::cout << "Hello from lambda.\n"; }};
  tl::function_ref<void()> fix3{lambda};
  fix3();
}
