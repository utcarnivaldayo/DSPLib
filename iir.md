# IIRフィルタクラス

~~~c++
class FIR
~~~

FIRフィルタによりフィルタリングや周波数特性を計算します。

---

### IIR 

~~~c++
IIR();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

IIRフィルタクラスのデフォルトコンストラクタ。メンバ変数を初期化する。

---

### ~IIR

~~~c++
~IIR();
~~~

#### 引数

void

##### 戻り値

void

#### 解説

IIRフィルタクラスのデストラクタ。メンバ変数の初期化やヒープの解放を行う。

---

### SetCoefficients

~~~c++
 bool SetCoefficients(double *scaling_coefficient, double *numerator_coefficients, double *denominator_coefficients, unsigned int n, unsigned int m);
~~~

#### 引数

*1.* scaling_coefficient : セットする縦続形IIRフィルタのスケーリング係数

*2.* numerator_coefficients : セットする縦続形IIRフィルタの分子係数

*3.* denominator_coefficients : セットする縦続形IIRフィルタの分母係数

*4.* n : 分子次数

*5.* m : 分母次数

#### 戻り値

true : 成功

false : 失敗

#### 解説

縦続形IIRフィルタのフィルタ係数をセットする。このとき、内部的に遅延器のヒープも確保される。

---

### SetCoefficients

~~~c++
 void SetCoefficients(double *scaling_coefficient, double *numerator_coefficients, double *denominator_coefficients);
~~~

#### 引数

1.* scaling_coefficient : セットする縦続形IIRフィルタのスケーリング係数

*2.* numerator_coefficients : セットする縦続形IIRフィルタの分子係数

*3.* denominator_coefficients : セットする縦続形IIRフィルタの分母係数

#### 戻り値

void

#### 解説

**以前に設定したフィルタ次数と同次数**で、フィルタ係数のみを変更したい場合にこちらのメソッドを用いる。

---

### SetFrequencySample

~~~c++
bool SetFrequencySample(double* normalized_angular_frequency, unsigned int s);
~~~

#### 引数

*1.* normalized_angular_frequency : 離散化した正規化角周波数

*2.* s  : 周波数分割数

#### 戻り値

true : 成功

false : 失敗

#### 解説

周波数特性を計算するために離散化した正規化角周波数をセットする。

---

### GetN

~~~c++
inline unsigned int GetN();
~~~

#### 引数

void

#### 戻り値

n : 分子次数

#### 解説

分子次数を取得する。

---

###  GetM

~~~c++
 inline unsigned int GetM();
~~~

#### 引数

void

#### 戻り値

m : 分母次数

#### 解説

分母次数を取得する。

---

### GetDelaysLength

~~~c++
inline unsigned int GetDelaysLength();
~~~

#### 引数

void

#### 戻り値

delays_length : 遅延器の長さ

#### 解説

 遅延器の長さ

---

### GetS 

~~~c++
inline unsigned int GetS();
~~~

#### 引数

void

#### 戻り値

s : 周波数分割数

#### 解説

周波数分割数を取得する。

---

### CalculateFrequencyResponse

~~~c++
 bool CalculateFrequencyResponse();
~~~

#### 引数

void

#### 戻り値

true : 成功

false : 失敗

#### 解説

周波数特性を計算する。フィルタ係数や正規化角周波数がセットされていない場合、失敗する。

---

### CalculateGroupDelay

~~~c++
bool CalculateGroupDelay();
~~~

#### 引数

void

#### 戻り値

true : 成功

false : 失敗

#### 解説

群遅延特性を計算する。フィルタ係数や正規化角周波数がセットされていない場合、失敗する。

---

### operator()

~~~c++
 double operator() (const double& input);
~~~

#### 引数

input : フィルタへの入力

#### 戻り値

output : フィルタの出力

#### 解説

フィルタリングを行う。

---

### operator[]

~~~c++
 std::complex<double>& operator[](unsigned int index);
~~~

~~~c++
const std::complex<double>& operator[](unsigned int index) const;
~~~

#### 引数

*1.* index : 周波数特性のインデックス

#### 戻り値

frequency_response[index] : 周波数特性

#### 解説

index番目の周波数特性にアクセスする。

---

### IsStability

~~~c++
 bool IsStability();
~~~

#### 引数

void

#### 戻り値

true : 安定

false : 不安定

#### 解説

IIRフィルタの安定性を判別する。分母係数がnulltprであるときもfalseになる点に注意。

---

### WriteCoefficients

~~~c++
bool WriteCoefficients(const char* filename);
~~~

#### 引数

*1.* filename : 出力ファイル名

#### 戻り値

ture : 成功

false : 失敗

#### 解説

テキストファイルにフィルタ係数を書き出す。

---

### WriteFrequencyResponse

~~~c++
bool WriteFrequencyResponse(const char* filename);
~~~

#### 引数

*1.* filename : 出力ファイル名

#### 戻り値

true : 成功

false : 失敗

#### 解説

テキストファイルに周波数特性を書き出す。

---

### WriteMagnitudeResponse

~~~c++
 bool WriteMagnitudeResponse(const char* filename, bool decibel = true);
~~~

#### 引数

*1.* filename : 出力ファイル名

*2.* decibel : デシベル単位で出力するかのフラグ

#### 戻り値

true : 成功

false : 失敗

#### 解説

テキストファイルに振幅特性を書き出す。

---

### WritePhaseResponse

~~~c++
bool WritePhaseResponse(const char* filename);
~~~

#### 引数

*1.* filaname : 出力ファイル名

#### 戻り値

true : 成功

false : 失敗

#### 解説

テキストファイルに位相特性を書き出す。

---

### WriteGroupDelay

~~~c++
bool WriteGroupDelay(const char* filename);
~~~

#### 引数

*1.* filename : 出力ファイル名

#### 戻り値

true : 成功

false :  失敗

#### 解説

テキストファイルに群遅延特性を書き出す。

---

### WriteZeros

~~~c++
bool WriteZeros(const char *filename);
~~~

#### 引数

*1.* filename : 出力ファイル名

#### 戻り値

true : 成功

false : 失敗

#### 解説

テキストファイルに零を書き出す。

---

### WritePoles

~~~c++
bool WritePoles(const char *filename);
~~~

#### 引数

*1.* filename : 出力ファイル名

#### 戻り値

true : 成功

false : 失敗

#### 解説

テキストファイルに極を書き出す。

----

### ClearDelays

~~~c++
 bool ClearDelays();
~~~

#### 引数

void

#### 戻り値

true : 成功

false : 失敗

#### 解説

すべて遅延器を0に初期化する。

---

### Clear

~~~c++
void Clear();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

メンバ変数の初期化やヒープの解放を行う。

---

### CreateFrequencySample

~~~c++
static bool CreateFrequencySample(double *normalized_angular_frequency, unsigned int s);
~~~

#### 引数

*1.* normalized_angular_frequency : 正規化角周波数を格納する配列

*2.* s : 周波数分割数

#### 戻り値

true : 成功

false : 失敗

#### 解説

区間$[0, \pi]$を等分にs分割した正規化角周波数を生成する。

---

### ToSymmetry

~~~c++
static bool ToSymmetry(double *numerator_coefficients, double *denominator_coefficients, unsigned int n, unsigned int m);
~~~

#### 引数

*1.* numerator_coefficients : 縦続形IIRフィルタの分子係数

*2.* denominator_coefficients : 縦続形IIRフィルタの分母係数

*3.* n : 分子次数

*4.* m : 分母次数

#### 戻り値

true : 成功

false : 失敗

#### 解説

正規化角周波数$\pi/2$に関して対称な特性となるフィルタ係数へ変換する。

---

### StabilityTriangle

~~~c++
static bool StabilityTriangle(const double &b_1, const double &b_2);
~~~

#### 引数

*1.* b_1 : 2次区間のフィルタ係数

*2.* b_2 : 2次区間のフィルタ係数

#### 戻り値

true : 安定

false : 不安定

#### 解説

2次区間の分母多項式$1 + b_1 z^{-1} + b_2 z^{-2}$に対して、安定三角による安定性の判別を行う。

---

### StabilityOfRealRoot

~~~c++
 static bool StabilityOfRealRoot(const double &b_1);
~~~

#### 引数

*1.* b_1 : 1次区間のフィルタ係数

#### 戻り値

true : 安定

false : 不安定

#### 解説

1次区間の安定性を判別する。

### CoefficientsToZeros

~~~c++
 static bool CoefficientsToZeros(std::complex<double> *zeros, double *coefficients, unsigned int n);
~~~

### 引数

*1.* zeros : 零を格納する配列

*2.* coefficients : 分子 or 分母フィルタ係数

*3.* n : 分子 or 分母次数

#### 解説

フィルタ係数から零を求める。

