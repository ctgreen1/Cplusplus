#include "Range.h"
#include <cassert>
#include <iostream>
#include <sstream>
 
using namespace std;
 
int main() {
    Range<int> a(4,20), b(500,900), c(504,920), d(80,90), e(1,6), f(74,89);
    const Range<unsigned short> g(80,90), h(2,5), i(16,45);
    Range<long long> j(5,7), k(-3,2), l(-21,14);
    const Range<long double> m(2.5,8.25);
    const long double n = -0.5;
    Range<long double> o(-4.125, -1.25);
    const Range<int> range_containing_zero(-2,5447204), zero(0);
 
    auto i_result = a; i_result += b;
    cout << a << " += " << b << " yields " << i_result << '\n';
    assert(i_result == c);
 
    i_result = d - e;
    cout << d << " - " << e << " = " << i_result << '\n';
    assert(i_result == f);
 
    auto us_result = g / h;
    cout << g << " / " << h << " = " << us_result << '\n';
    assert(us_result == i);
 
    auto ll_result = j; ll_result *= k;
    cout << j << " *= " << k << " yields " << ll_result << '\n';
    assert(ll_result == l);
 
    auto ld_result = m; ld_result *= n;
    cout << m << " *= " << n << " yields " << ld_result << '\n';
    assert(ld_result == o);
    assert(ld_result.min() == -4.125 && ld_result.max() == -1.25);
 
    stringstream ss("  [ 12 \t   ,34   \n  ]  foobar");
    string s;
    assert(ss >> a >> s);
    assert(Range(12,34)==a && s == "foobar");
 
    bool caught = false;
    try {
        o.assign(5.001L, 4.999L);  // out of order
    }
    catch (const runtime_error &re) {
        cout << "Tried to assign out of order: " << re.what() << '\n';
        caught = true;
    }
    assert(caught);
 
    caught = false;
    try {
        f /= range_containing_zero;
    }
    catch (const runtime_error &re) {
        cout << "Tried to divide by zero: " << re.what() << '\n';
        caught = true;
    }
    assert(caught);

    assert(zero / a == 0);
    cout << "Done.\n";
}
 
static_assert(sizeof(Range<short>) == 2*sizeof(short));
static_assert(sizeof(Range<unsigned int>) == 2*sizeof(unsigned int));
static_assert(sizeof(Range<long double>) == 2*sizeof(long double));
