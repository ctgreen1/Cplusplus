//Header File
#include <iostream>
#include <string>
#include <stdexcept>

template<typename T>
class Range {

  public:

    T first, second;

    //CTOR single-arg
    Range(T val) {Range(val, val);}

    //CTOR two-arg
    Range(T low, T high) {
	if(low <= high) {
	    first = low;
	    second = high;
	}
	else {
        std::cout << "[" << low << "," << high << "] ";
	    try { throw  std::runtime_error(" Out of order."); }
	    catch (const std::runtime_error &e) { throw; }
	}
    }

    //COPY CTOR
    Range(const Range &rhs) {
        first = rhs.first;
        second = rhs.second;
    }

    //Assignment operator
    Range& operator=(const Range &rhs) {
        first = rhs.first;
        second = rhs.second;
        return *this;
    }

    //.assign method
    void assign(T low, T high) {
        try {
            std::cout << "[" << low << "," << high << "] ";
	        if(low > high) {throw std::runtime_error("Out of order"); }
	        else {
	         Range(low, high);
	        }
	    }
	    catch (const std::runtime_error &e) { throw; }
    }

    //.min method
    T min() { return first;}

    //.max method
    T max() { return second;}

    //+= operator
    Range &operator+=(const Range<T> &r) {
	first += r.first;
	second += r.second;
	return *this;
    }
    Range &operator+=(const T r) {
        first += r;
        second += r;
        return *this;
    }

    //-= operator
    Range &operator-=(const Range<T> &r) {
	first -= r.second;
	second -= r.first;
	return *this;
    }
    Range &operator-=(const T r) {
        first -= r;
        second -= r;
        return *this;
    }

    // *= operator
    Range &operator*=(const Range<T> &r) {
        auto temp = second;
        first = temp * r.first;
        second = temp * r.second;
        return *this;
    }
    Range& operator*=(const T r) {
        auto temp = second;
        second =  first * r;
        first = temp * r;
        return *this;
    }

    // /= operator
    Range &operator/=(const Range<T> &r) {
	if(r.first <= 0 && r.second >= 0) {
        std::cout << "[" << first << "," << second << "] / [" << r.first << "," << r.second << "] ";
	    try {throw std::runtime_error("Tried to divide by 0"); }
        catch(const std::runtime_error &e) { throw; }
	}
        //T temp = second;
        first /= r.second;
        second /= r.first;
        return *this;
    }
    Range &operator/=(const T r) {
        if(r == 0) {
            std::cout << "[" << first << "," << second << "] / [" << r << "," << r << "] ";
            try {throw std::runtime_error("Tried to divide by 0");}
            catch (const std::runtime_error &e) { throw; }
        }
        T temp = second;
        first /= r.second;
        second /= r.first;
        return *this;
    }

};

//+ operator
template<class T>
Range<T> operator+(const Range<T> &lhs, const Range<T> &rhs) {
    T val1 = lhs.first;
    val1 += rhs.first;
    T val2 = lhs.second;
    val2 += rhs.second;
    Range<T> q(val1, val2);
    return q;
}
template<class T>
Range<T> operator+(const Range<T> &lhs, const T r) {
    T val1 = lhs.first;
    val1 += r;
    T val2 = lhs.second;
    val2 += r;
    Range<T> s(val1, val2);
    return s;
}

//- operator
template<class T>
Range<T> operator-(const Range<T> &lhs, const Range<T> &rhs) {
    T val1 = lhs.first;
    val1 -= rhs.second;
    T val2 = lhs.second;
    val2 -= rhs.first;
    Range<T> t(val1, val2);
    return t;
}
template<class T>
Range<T> operator-(const Range<T> &lhs, const T r) {
    T val1 = lhs.first;
    val1 -= r;
    T val2 = lhs.second;
    val2 -= r;
    Range<T> u(val1, val2);
    return u;
}

// / operator
template<class T>
Range<T> operator/(const Range<T> &lhs, const Range<T> &rhs) {
    if(rhs.first <= 0 && rhs.second >= 0) {
        std::cout << "[" << lhs.first << "," << lhs.second << "] / [" << rhs.first << "," << rhs.second << "] ";
	    try{throw std::runtime_error("Tried to divide by 0"); }
        catch(const std::runtime_error &e) { throw; }
	}
    T val1 = lhs.first;
    val1 /= rhs.second;
    T val2 = lhs.second;
    val2 /= rhs.first;
    Range<T> t(val1, val2);
    return t;
}
template<class T>
Range<T> operator/(const Range<T> &lhs, const T r) {
    T val1 = lhs.first;
    val1 /= r;
    T val2 = lhs.second;
    val2 /= r;
    Range<T> u(val1, val2);
    if(r == 0) {
        std::cout <<  "[" << lhs.first << "," << lhs.second << "] / [" << r << "," << r << "] ";
        try{ throw std::runtime_error("Tried to divide by 0");}
        catch (const std::runtime_error &e) { throw; }
        }

    return u;
}

// * operator
template<class T>
Range<T> operator*(const Range<T> &lhs, const Range<T> &rhs) {
    T val1 = lhs.second;
    val1 *= rhs.first;
    T val2 = lhs.second;
    val2 *= rhs.second;
    Range<T> t(val1, val2);
    return t;
}
template<class T>
Range<T> operator*(const Range<T> &lhs, const T r) {
    T val1 = lhs.second;
    val1 *= r;
    T val2 = lhs.second;
    val2 *= r;
    Range<T> t(val1, val2);
    return t;
}

//== operator
template<class T>
bool operator==(const Range<T> &lhs, const Range<T> &rhs) {
    return lhs.first==rhs.first && lhs.second==rhs.second;
}
template<class T>
bool operator==(const Range<T> &lhs, const T rhs) {
    return lhs.first==rhs && lhs.second==rhs;
}

//free function for istream
template<class T>
std::istream& operator>>(std::istream &is, Range<T> &val) {
    T first, second;
    char bracket;
    char comma;
    std::string s;
    //char 2bracket;
    if (is >> std::skipws >> bracket >> first >> comma >> second >> s)
	    val = Range(first, second);
    else
	    is.setstate(std::ios::failbit);
    return is;
}

// free function for ostream
template<class T>
std::ostream& operator<<(std::ostream &os, const Range<T> &u) {
    return os << "[" << u.first << "," << u.second << "]";
}



//std::cerr << "runtime_error: " << e.what() << " [" << rhs.first << "," << rhs.second << "]" <<  '\n'
