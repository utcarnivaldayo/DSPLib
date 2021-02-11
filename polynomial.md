# Polynomialクラス

~~~c++
class Polynomial
~~~

多項式の根を求めたり、根から多項式へ展開するなどの多項式に関係する関数を提供する。本クラスは静的なクラスです。

---

### QuadraticFormula

~~~c++
static bool QuadraticFormula(std::complex<double> *roots, double c_1, double c_2, double c_0 = 1.0);
~~~

#### 引数

*1.* roots : 2つの根を格納する配列

*2.* c_1 : 2次多項式の係数

*3.* c_2 : 2次多項式の係数

*4.* c_0 : 2次多項式の係数

#### 戻り値

true : 成功

false : 失敗

#### 解説

2次多項式$c_0 x^2 + c_1 x + c_2 = 0$の2つの根を求める。

---

### VietaFormula

~~~c++
static bool VietaFormula(double *coefficients, std::complex<double> *root, unsigned int n, double scaling_coefficient = 1.0);
~~~

#### 引数

*1.* coefficients : 求めたい多項式の係数の格納する配列

*2.* roots : n個の根

*3.* n : 多項式の次数

*4.* scaling_coefficient : スケーリング係数

#### 戻り値

true : 成功

false : 失敗

#### 解説

n次多項式$s (x - root_1)(x-root_2) \cdots (x - root_n) = 0$ (sはスケーリング係数)の根から$x^n + c_1 x^{n-1} + c_2 x^{n -2} + \cdots + c_{n - 1}x + c_n = 0$の多項式係数$c_1$から$c_n$を求める。

----

### Horner

~~~c++
static std::complex<double> Horner(double *coefficients, unsigned int n, std::complex<double> &z, double non_monic = 1.0);
~~~

~~~c++
 static std::complex<double> Horner(std::complex<double> *coefficients, unsigned int n, std::complex<double> &z, std::complex<double> non_monic = 1.0);
~~~

~~~c++
static double Horner(double *coefficients, unsigned int n, double &z, double non_monic = 1.0);
~~~

#### 引数

*1.* coefficients : 多項式の係数

*2.* n : 多項式の次数

*3.* z : z多項式の具体値

*4.* non_monic : 多項式の最高次数が1でない場合(モニック多項式でない)ときの係数

#### 戻り値

polynomial : 多項式の計算結果

#### 解説

n次多項式$z^n + c_1 z^{n-1} + c_2 z^{n -2} + \cdots + c_{n - 1}z + c_n$においてzに具体値を与えたときの多項式の計算結果を求める。

---

### ReverseHorner

~~~c++
static std::complex<double> ReverseHorner(double *coefficients, unsigned int length, std::complex<double> &z);
~~~

#### 引数

1.* coefficients : 多項式の係数

*2.* length : 多項式の次数 + 1

*3.* z : z多項式の具体値

#### 戻り値

true : 成功

false : 失敗

#### 解説

FIRフィルタの周波数計算$H(\omega) = \sum_{n =0}^{N} c_{n} z^{-n}|_{z = e^{j\omega}}$のようにインデックスが増えると高次になるタイプの多項式計算用Horner法。

---

### DKAMethod

~~~c++
static bool DKAMethod(std::complex<double> *zeros, std::complex<double> *coefficients, unsigned int n);
~~~

#### 引数

*1.* zeros : 求めたい根

*2.* coefficients : 多項式の係数

*3.* n : 多項式の次数

#### 戻り値

true : 成功

false : 失敗

#### 解説

n次多項式$z^n + c_1 z^{n-1} + c_2 z^{n -2} + \cdots + c_{n - 1}z + c_n$のn個の根を数値計算的に求める。次数や係数値によっては上手く収束しない場合がある。