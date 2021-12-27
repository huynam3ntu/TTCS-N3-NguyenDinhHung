#include <bits/stdc++.h>
using namespace std;
const int base = 1000000000; const int base_digits = 9;

struct bigint {
	//Danh sach thuoc tinh
    vector<int> a; int sign;
    typedef vector<long long> vll;
    
    //Ham tao
    bigint() :
        sign(1) {
    }
    bigint(const string &s) {	//Nhan doi so dau vao la chuoi
        read(s);
    }
    void operator=(const bigint &v) {
        sign = v.sign;
        a = v.a;
    }
    bigint operator-() const {
        bigint res = *this;
        res.sign = -sign;
        return res;
    }
    
    bigint(long long v) {
        *this = v;
    }
    void operator=(long long v) {
        sign = 1;
        if (v < 0)
            sign = -1, v = -v;
        for (; v > 0; v = v / base)
            a.push_back(v % base); //them __ vao sau vecto a
    }
    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--)
            res = res * base + a[i];
        return res * sign;
    }
    
    //Nhap - Xuat
    friend istream& operator >> (istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
    friend ostream& operator << (ostream &stream, const bigint &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back()); //kiem tra vecto cua v co rong hay khong? TRUE: 0 FALSE truy cap den phan tu cuoi cung cua vector
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i]; //setw: dieu chinh lai size, setfill la xac dinh ki tu them vao
        return stream;
    }
    
    //Xu ly voi so nguyen
    bigint operator * (int v) const {	//nhan so lon voi so nguyen
        bigint res = *this;
        res *= v;
        return res;
    }
    bigint operator / (int v) const {	//Chia 1 so nguyen lon voi 1 so nguyen
        bigint res = *this;
        res /= v;
        return res;
    }
	int operator%(int v) const {	//Chia du 2 so nguyen
        if (v < 0)
            v = -v;
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i)
            m = (a[i] + m * (long long) base) % v;
        return m * sign;
    }
    //Dinh nghia lai toan tu *=, /= cua so nguyen
    void operator *= (int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.push_back(0);	//Them 0 vao sau cung cua vector a
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / base);
            a[i] = (int) (cur % base);
        }
        trim();
    }
    void operator /= (int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long) base;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }
    
    //Ghi de, dinh nghia lai cac toan tu dung de so sanh <, >, <=, >=, ==, != giua 2 so nguyen lon
    bool operator < (const bigint &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }
    bool operator > (const bigint &v) const {
        return v < *this;
    }
    bool operator <= (const bigint &v) const {
        return !(v < *this);
    }
    bool operator >= (const bigint &v) const {
        return !(*this < v);
    }
    bool operator == (const bigint &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator != (const bigint &v) const {
        return *this < v || v < *this;
    }
    
    //Ghi de, dinh nghia lai cac toan tu dung de tinh toan + - * / % giua 2 so nguyen lon
    bigint operator + (const bigint &v) const {	//Cong 2 so nguyen lon
        if (sign == v.sign) {
            bigint res = v;
            
            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int) res.a.size())
                    res.a.push_back(0);	//them 0 vao sau vector cua res
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry)
                    res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }
    bigint operator - (const bigint &v) const {	//Tru 2 so nguyen lon
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                bigint res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                        res.a[i] += base;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
    bigint operator / (const bigint &v) const { //Div 2 so nguyen lon
        return divmod(*this, v).first;
    }
    bigint operator % (const bigint &v) const { //Mod 2 so nguyen lon
        return divmod(*this, v).second;
    }
    bigint operator * (const bigint &v) const {	//Nhan 2 so nguyen lon
        vector<int> a6 = convert_base(this->a, base_digits, 6);
        vector<int> b6 = convert_base(v.a, base_digits, 6);
        vll a(a6.begin(), a6.end());
        vll b(b6.begin(), b6.end());
        while (a.size() < b.size())
            a.push_back(0);	//Them 0 vao sau vector a
        while (b.size() < a.size())
            b.push_back(0);	//Them 0 vao sau vector b
        while (a.size() & (a.size() - 1))
            a.push_back(0), b.push_back(0);	//Them 0 vao sau 2 vector a, b
        vll c = karatsubaMultiply(a, b);
        bigint res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int) c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int) (cur % 1000000));	//Them __ vao sau vector cua res
            carry = (int) (cur / 1000000);
        }
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
    
    void operator += (const bigint &v) {
        *this = *this + v;
    }
    void operator -= (const bigint &v) {
        *this = *this - v;
    }
    void operator *= (const bigint &v) {
        *this = *this * v;
    }
    void operator /= (const bigint &v) {
        *this = *this / v;
    }
    
    //Ham ho tro
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();	//Loai bo phan tu cuoi cung trong vector
        if (a.empty())
            sign = 1;
    }
    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);	//Them x vao sau vector a
        }
        trim();
    }
    bigint abs() const {	//Tra ve gia tri tuyet doi
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    }
    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {	//Ho tro div - mod 2 so nguyen lon
        int norm = base / (b1.a.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.a.resize(a.a.size());	//Thay doi kich thuoc vector cua q
 
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.a[i] = d;
        }
 
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
	static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) { //chuyen doi co so vector
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++)
            p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));	//Them __ vao sau vector cua res
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int) cur);	//Them __ vao sau vector cua res
        while (!res.empty() && !res.back())
            res.pop_back();	//Xoa phan tu cuoi cung cua vector res
        return res;
    }
    static vll karatsubaMultiply(const vll &a, const vll &b) {	//Thuat toan nhan nhanh: giam so lan nhan giua 2 so nguyen lon
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }
 
        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());
 
        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);
 
        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];
 
        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            r[i] -= a2b2[i];
 
        for (int i = 0; i < (int) r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    } 
};

int main(){
	bigint n1, n2;
    cout << "\n\nSo thu nhat: ";
    cin >> n1;
    cout << "\nSo thu hai: ";
    cin >> n2;
    
    //Test toan tu so sanh
    if (n1>n2)
		cout << "\nso thu nhat > so thu hai\n";
	else
		if(n1<n2)
			cout << "\nso thu nhat < so thu hai\n";
		else
			cout << "\nso thu nhat = so thu hai\n";
			
    //Test cong 2 so
    cout << n1 << " + " << n2 << " = " << (n1+n2) << '\n';
    //Test tru 2 so
    cout << n1 << " - " << n2 << " = " << (n1-n2) << '\n';

	//Nhan 2 so - su dung ham tao bigint tu bien string
    string s1 = "12345678987654321", s2 = "-1357111264246893";
    bigint n3(s1), n4(s2);	//big int nhan doi so dau vao la string
    cout << s1 << " * " << s2 << " = " << (n3*n4) << '\n';
    cout << s1 << " / " << s2 << " = " << (n3/n4) << '\n';
    // su dung bang toan tu *= da dinh nghia o tren de so sanh ket qua
    n3 *= n4;
    cout << s1 << " * " << s2 << " = " << n3 << '\n';
    
    //demo tinh giai thua 1 so n
    bigint answer = 1;
    int N;
    cout << "Nhap so N = ";
    cin >> N;
    // Tinh giai thua
    for(int i = 2; i <= N; ++i){
        answer *= i; //su dung toan tu *= da dinh nghia
    }
    cout << N <<"! = " << answer << '\n';
    
	return 0;
}
