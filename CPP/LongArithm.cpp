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
    static string mulstr(const char* str, _l num){ string a = ""; for (_l i = 0; i < num; i++) a += str; return a; }
    void clear_zeros(){ for (_l i = num.size()-1; i>=0; --i){if(num[i] != 0) return; else num.pop_back(); } }
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
    BigInteger(_l v){num.push_back(v);}
    BigInteger(const BigInteger& bint){
        this->num = bint.num;
    }
    BigInteger& operator=(const char s){
        BigInteger b(s);
        return *this = b;
    }
    BigInteger& operator=(const BigInteger& bint){
        if(this != &bint){
            this->num = bint.num;
        }
        return *this;
    }
    BigInteger& operator=(const _l& v){
        num.push_back(v);
    }
    _l at(size_t _pos){
        return (num[_pos]);
    }


    BigInteger add(BigInteger& b){
        BigInteger res;
        _l extra = 0, tmp = 0;
        if (b.size() > this->size()) this->resize(b.size());
        else b.resize(this->size());
        for (_l i = 0; i < this->size(); i++){
            tmp = this->at(i) + b.at(i) + extra;
            extra = tmp / BigInteger::stoi("1" + BigInteger::mulstr("0", BASE));
            res.push_back(tmp % BigInteger::stoi("1" + BigInteger::mulstr("0", BASE)));
        }
        res.push_back(extra);
        return res;
    }

    BigInteger operator+ (BigInteger& b){
        return this->add(b);
    }
    BigInteger operator+ (_l b){
        BigInteger B(b);
        return this->add(B);
    }

    void print(const char* end="\n", const char* sep=""){
        if(this->size() == 0)
            return;
        clear_zeros();
        for(_l i = num.size()-1; i >= 0; i--){
            if(num[i] == 0){
                cout << BigInteger::mulstr("0", BASE) << sep;
            }
            else{
                cout << num[i] << sep;
            }
        }
        cout << end;
    }
};

int main()
{
    BigInteger a("9999999999999999999999999999999999999999");
    BigInteger b = a + 1;
    b.print("\n", "|");
    return 0;
}
