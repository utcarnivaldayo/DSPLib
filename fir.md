# FIRフィルタクラス

~~~c++
class FIR
~~~

FIRフィルタによりフィルタリングや周波数特性を計算します。

---

### FIR 

~~~c++
FIR();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

FIRフィルタクラスのデフォルトコンストラクタ。メンバ変数を初期化する。

---

### ~FIR

~~~c++
~FIR();
~~~

#### 引数

void

##### 戻り値

void

#### 解説

FIRフィルタクラスのデストラクタ。メンバ変数の初期化やヒープの解放を行う。

---

### SetCoefficients

~~~c++
 bool SetCoefficients(double* coefficients, unsigned int n);
~~~

#### 引数

*1.* coefficients : セットする直接形FIRフィルタのフィルタ係数。

*2.* n : FIRフィルタの次数 ※coefficientsの配列長ではないことに注意。

#### 戻り値

true : 成功

false : 失敗

#### 解説

直接形FIRフィルタのフィルタ係数をセットする。このとき、内部的に遅延器のヒープも確保される。

---

### SetCoefficients

~~~c++
void SetCoefficients(double* coefficients);
~~~

#### 引数

*1.* coefficients : セットする直接形FIRフィルタのフィルタ係数。

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

n : フィルタ次数

#### 解説

フィルタ次数を取得する。

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

FIRフィルタクラスのデストラクタ。メンバ変数の初期化やヒープの解放を行う。

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