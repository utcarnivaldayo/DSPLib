# インクリメンタルな統計量のクラス

~~~c++
class IncrementalStatistics
~~~

インクリメンタル(データを積み上げていくよう)な方式でデータの平均値、分散、標準偏差を計算します。インクリメンタルな方式では分散の計算の際にデータをすべて保持しておく必要がなく、メモリ使用量が少なく計算できます。

---

### IncrementalStatistics

~~~c++
IncrementalStatistics();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

デフォルトコンストラクタ。クラスのメンバ関数を初期化します。

---

### ~IncrementalStatistics

~~~c++
~IncrementalStatistics();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

デストラクタ。クラスのメンバ変数を初期化する。

---

### Variance

~~~c++
double Variance();
~~~

#### 引数

void

#### 戻り値

variance : 分散

#### 解説

分散を計算する。

---

### UnbiasVariance

~~~c++
double UnbiasVariance();
~~~

#### 引数

void

#### 戻り値

unbias_variance : 不偏分散

#### 解説

不偏分散を計算する。

---

### StandardDeviation

~~~c++
double StandardDeviation();
~~~

#### 引数

void

#### 戻り値

standard_deviation : 標準偏差

#### 解説

標準偏差を計算する。

---

### UnbiasStandardDeviation

~~~c++
double UnbiasStandardDeviation();
~~~

#### 引数

void

#### 戻り値

unbias_standard_deviation : 不偏分散より求めた標準偏差

#### 解説

不偏分散より求めた標準偏差を計算する。

---

### Mean

~~~c++
double Mean();
~~~

#### 引数

void

#### 戻り値

mean : 平均値

#### 解説

平均値を計算する。

---

### Size

~~~c++
unsigned int Size();
~~~

#### 引数

void

#### 戻り値

size : データサイズ数

#### 解説

データサイズ数を取得する。

---

### AddSample

~~~c++
void AddSample(double sample);
~~~

#### 引数

*1.* sample : データサンプル

#### 戻り値

void

#### 解説

sampleにデータを渡すことでインクリメントする。

----

### Clear

~~~c++
void Clear();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

メンバ変数を初期化する。





