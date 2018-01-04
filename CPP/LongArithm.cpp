#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef long long _l;

class BigInteger{
private:
    vector<_l> num;
    const short BASE = 8;

    void push_back(_l n){this->num.push_back(n);}
    void resize(size_t s){this->num.resize(s);}
    size_t size(){return this->num.size();}
public:
    static _l stoi(string s){
        _l sum = 0;
        for (int i = 0; i < s.size(); i++){
            if (s[i] >= '0' && s[i] <= '9')
                sum = sum*10 + s[i] - '0';
        }
        return sum;
    }
    BigInteger(){}
    BigInteger(string s){
        reverse(s.begin(), s.end());
        for(int i = 0; i < s.size(); i+=BASE){
            string str = s.substr(i, BASE);
            reverse(str.begin(), str.end());
            this->push_back(BigInteger::stoi(str));
        }
    }
    _l at(size_t _pos){
        return (num[_pos]);
    }
    BigInteger add(BigInteger b){
        BigInteger res;
        _l extra = 0, tmp = 0;
        if (b.size() > this->size()) this->resize(b.size());
        else b.resize(this->size());
        for (_l i = 0; i < this->size(); i++){
            tmp = this->at(i) + b.at(i) + extra;
            extra = tmp / BigInteger::stoi("1" + string("0", BASE));
            res.push_back(tmp % BigInteger::stoi("1" + string("0", BASE)));
        }
        res.push_back(extra);
    }

    BigInteger operator+ (BigInteger b){
        return this->add(b);
    }

    void print(){
        for(_l i = num.size()-1; i >= 0; i--){
            cout << num[i];
        }
    }
};

int main()
{
    BigInteger a("12345678901234567890123456789");
    BigInteger b("12345678901234567890123456789");
    BigInteger c("12345678901234567890123456789");
    a.print();
    (a+b+c).print();
    return 0;
}
