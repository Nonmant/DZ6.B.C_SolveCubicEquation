//https://contest.yandex.ru/contest/29188/problems/

#include "funcs.h"
#include <bits/stdc++.h>

void parseVect(std::istream & input,
               std::vector<int> & v,
               int & len){
    input>>len;
    v.resize(len);
    std::copy_n(std::istream_iterator<int>(input),len,v.begin());
}

/*! @brief First argument, that returns true for given func
 *
 * @tparam Func function pointer, lambda, on given vector should have
 * that form: "___---"
 * @param func function pointer, lambda, that should accept int as input
 * @param left Left limit
 * @param right Right limit
 * @param tol Tolerance
 * @return value
 */
template<typename Func>
double indexOfFirst(Func func, double left, double right, double tol){
    while (left+tol<right){
        double middle = (left+right)/2;
        if(func(middle)){
            right = middle;
        } else {
            left = middle;
        }
    }
    return (left+right)/2;
}

/*! @brief Index of last element, that returns true for given func
 *
 * @tparam Func function pointer, lambda, on given vector should have
 * that form: "---____"
 * @tparam T type of values stored in vector
 * @param v vector to search in, sorted
 * @param func function pointer, lambda, that should accept int as input
 * @param left First index, default 0
 * @param right Last index, default -1 means length of given vector
 * @return index,that you should check again
 */
 /*
template<typename Func>
double indexOfLast(Func func, double left, double right, double tol){
    while (left<right+tol){
        double middle = (left+right+tol)/2;
        if(func(middle)){
            left = middle;
        } else {
            right = middle-tol;
        }
    }
    return (left+right)/2;
}*/

template<typename Func>
std::pair<double,double> findRange(Func func){
    std::pair<double,double> ans(-1000,1000);
    double vLeft, vRight;
    int steps = 10;
    while (
            (steps-->0)&&
            ((vLeft = func(ans.first))>=0)==(((vRight = func(ans.second))>0))
            ){
        double k = (vLeft-vRight)/(ans.first - ans.second);
        double b = vLeft - k*ans.first;
        double v = -b/k;
        if(v<ans.first)
            ans.first = v;
        else
            ans.second = v;
    }
    return ans;
}

void parseFile(std::istream & input, std::ostream & output){
    double tol = 0.000001;
    double a,b,c,d;
    input>>a>>b>>c>>d;
    auto func = [&a, &b, &c, &d](double x){return a*pow(x,3) + b*pow(x,2) + c*x +d;};
    std::pair<double,double> range = findRange(func);

    if(func(range.first)>=0 == func(range.second)>0){
        //Parabolic
        output<<"WF";
        return;
    }
    double ans;
    if(func(range.first)>0){
        ans = indexOfFirst([&a, &b, &c, &d](double x){return a*pow(x,3) + b*pow(x,2) + c*x +d <0;},range.first,range.second,tol);
    } else{
        ans = indexOfFirst([&a, &b, &c, &d](double x){return a*pow(x,3) + b*pow(x,2) + c*x +d >0;},range.first,range.second,tol);
    }

    output<<std::setprecision(17)<<ans<<'\n';
}
