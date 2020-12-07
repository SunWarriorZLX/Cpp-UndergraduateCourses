#include "elgamal.h"

/*素数判断*/
bool elgamal::IsPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return false;
    return true;
}

/*模重复平方根算法*/
int elgamal::QuickMod(unsigned long int b, int n, int m, unsigned long result) {
    if (n % 2)
        result = (b * result) % m;
    if (n / 2 == 0)
        return result;
    return QuickMod((b * b) % m, n / 2, m, result);
}

/*模重复平方根(Hash)*/
int elgamal::QuickMod(unsigned long int b, string H, int m) {
    unsigned long int result = 1;
    for (int i = H.length() - 1; i >= 0; i--) {
        for (int j = 1; j <= 8; j = j << 1) {
            if (j & GetHex(H[i]))
                result = (b * result) % m;
            b = (b * b) % m;
        }
    }
    return result;
}

/*分解质因数*/
vector<int> elgamal::Factorization(int n) {
    vector<int> reslut;
    int i = 2;
    while (!IsPrime(n)) {
        if (n % i == 0) {
            reslut.push_back(i);
            while (n % i == 0)
                n = n / i;
        }
        i++;
    }
    return reslut;
}

/*判断是否为原根*/
bool elgamal::IsPrimitive(int G, int m) {
    vector<int> factor = Factorization(m - 1);  //Factorization 分解质因数
    for (int i = 0; i < factor.size(); i++) {
        if (QuickMod(G, (m - 1) / factor[i], m) == 1)//QuickMod g^n(modm) 模重复平方根
            return false;
    }
    return true;
}

/*拓展欧几里得求逆向元*/
int elgamal::ExGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int ans = ExGCD(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ans;
}

/*大数取模，默认从左到右->高位到低位*/
int elgamal::mod(string s, int m) {
    int len = s.length();
    int start = 0;
    if (s[0] == '-') {
        start = 1;
    }
    int num = 0;
    for (int i = start; i < len; i++) {
        num = (num * 16 + GetHex(s[i])) % m;
    }
    return num;
}

/*符转16进制数字*/
int elgamal::GetHex(char s) {
    switch (s) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
        case 'a':
            return 10;
        case 'B':
        case 'b':
            return 11;
        case 'C':
        case 'c':
            return 12;
        case 'D':
        case 'd':
            return 13;
        case 'E':
        case 'e':
            return 14;
        case 'F':
        case 'f':
            return 15;
    }
}

/*签名*/
vector<unsigned long int> elgamal::Sign(string H) {
    srand(time(NULL));
    cout << "--------------- sign ---------------" << endl;
    cout << "MD5:" << H << endl;
    vector<unsigned long int> result;//保存(r,s)
    y = 0;
    while (y == 0) {
        do {
            p = rand() % 0xFFFF;
        } while (!IsPrime(p));  //随机选取一个素数，初始化p
        do {
            g = rand() % p;
        } while (!IsPrimitive(g, p) || g == 0); //选取p的原根
        do {
            x = rand() % p;
        } while (x == 1 || x == 0);//选取用户私钥
        y = QuickMod(g, x, p);//计算公钥
    }
    int x1, y1;
    do {
        k = rand() % (p - 1);
        ExGCD(k, (p - 1), x1, y1);
    } while ((k * x1 + (p - 1) * y1) != 1); //拓展欧几里得计算k的逆元
    Inck = x1;
    if (Inck < 0) Inck += (p - 1);
    cout << "-------------- public --------------" << endl;
    cout << "p=" << p << endl << "g=" << g << endl << "public  key=" << y << endl;
    cout << "------------- private --------------" << endl;
    cout << "private key=" << x << endl;
    result.push_back(QuickMod(g, k, p));  //r
    unsigned long int s;
    s = GetS(H, result[0], Inck);
    result.push_back(s);
    cout << "------------- result ---------------" << endl;
    cout << "r=" << result[0] << endl;
    cout << "s=" << result[1] << endl;
    cout << "------------ finished --------------" << endl;
    return result;
}

unsigned long elgamal::GetS(string H, unsigned long r, unsigned long InK) {
    long result;
    long temp1, temp2;
    temp1 = mod(H, (p - 1));
    temp2 = x * r % (p - 1);
    result = temp1 - temp2;
    if (result < 0)
        result += (p - 1);
    result = result * InK % (p - 1);
    return result;
}

/*验证签名*/
bool elgamal::test(vector<unsigned long int> key, string H) {
    cout << endl << "--------- Verify signature ---------" << endl;
    cout << "MD5:" << H << endl;
    cout << "p=" << p << endl << "g=" << g << endl << "public  key=" << y << endl;
    cout << "r=" << key[0] << endl;
    cout << "s=" << key[1] << endl;
    unsigned long int s1, s2;
    s1 = QuickMod(y, key[0], p) * QuickMod(key[0], key[1], p);
    s1 = s1 % p;
    s2 = QuickMod(g, H, p);
    cout << "------------- result ---------------" << endl;
    cout << "y^r * r^s(mod p)=" << s1 << endl;
    cout << "g^MD5(mod p)=" << s2 << endl;
    if (s1 == s2) {
        cout << "Verification passed!" << endl;
        cout << "------------ finished --------------" << endl;
        return true;
    } else {
        cout << "Wrong signature" << endl;
        cout << "------------ finished --------------" << endl;
        return false;
    }
}

elgamal::elgamal() {}

elgamal::~elgamal() {}
