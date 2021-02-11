# Soundクラス

~~~c++
class Sound
~~~

量子化8bit、16bitの音楽ファイルを扱うクラスです。モノラルからマルチチャンネルの信号まで扱うことができます。ファイルのフォーマットとしてはバイナリファイル(.bat)、テキストファイル(.csv)、音楽ファイル(.wav)に対応しています。

---

### Sound

~~~c++
Sound();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

デフォルトコンストラクタ、Soundクラスのメンバ変数を初期化する。

---

### Sound

~~~c++
Sound(unsigned int seed);
~~~

#### 引数

seed : 疑似乱数生成器(メルセンヌツイスター)のseed値

#### 戻り値

void

#### 解説

コンストラクタ、疑似乱数生成器(メルセンヌツイスター)のseed値を与える。

---

### operator=

~~~c++
void operator=(const Sound& copy);
~~~

#### 引数

copy : Soundクラスのインスタンス

#### 戻り値

void

#### 解説

引数のインスタンスからコピーを行う。

----

### ~Sound

~~~c++
~Sound();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

デストラクタ。メンバ変数等は初期化される。

---

### ReadWAV

~~~c++
bool ReadWAV(const char* filename);
~~~

#### 引数

filename : .wavファイルへのパス(/ファイル名.wavまで含める)。

#### 戻り値

true : 成功

false : 失敗

#### 解説

モノラルのwavファイルの読み込みを行う。

---

### ReadCSV

~~~c++
bool ReadCSV(const char* filename, unsigned int sampling_frequency);
~~~

#### 引数

*1.* filename : .csvファイルへのパス(/ファイル名.wavまで含める)。

*2.* sampling_frequency : サンプリング周波数

#### 戻り値

ture : 成功

false : 失敗

#### 解説

モノラルのcsvファイルの読み込みを行う。

---

### ReadDAT

~~~c++
bool ReadDAT(const char* filename, short int quantization_bit, unsigned int sampling_frequency);
~~~

#### 引数

*1.* filename : ファイル名

*2.* quantization_bit : 量子化ビット

*3.* sampling_frequency : サンプリング周波数

####  戻り値

true : 成功

false : 失敗

#### 解説

モノラルのバイナリファイルの読み込みを行う。

---

### WriteWAV

~~~c++
bool WriteWAV(const char* filename, short int quantization_bit);
~~~

#### 引数

*1*. filename : 書き出すwavファイル名(拡張子.wavまでつける)

*2.* quantization_bit : 量子化ビット

#### 戻り値

true : 成功

false : 失敗

#### 解説

モノラルのwavファイルを書き出す。

----

### WriteCSV

~~~c++
bool WriteCSV(const char* filename, short int quantization_bit);
~~~

#### 引数

*1*. filename : 書き出すwavファイル名(拡張子.csvまでつける)

*2.* quantization_bit : 量子化ビット

#### 戻り値

true : 成功

false : 失敗

#### 解説

モノラルのcsvファイルを書き出す。

---

### GetLength

~~~c++
  inline unsigned int GetLength();
~~~

#### 引数

void

#### 戻り値

length : データ長

#### 解説

データ長を返す。

---

### GetQuantizationBit

~~~c++
inline short int GetQuantizationBit();
~~~

#### 引数

void

#### 戻り値

quantization_bit : 量子化

#### 解説

量子化ビット数を返す。

---

### GetSamplingFrequency

~~~c++
inline unsigned int GetSamplingFrequency();
~~~

#### 引数

void

#### 戻り値

sampling_frequency : サンプリング周波数

#### 解説

サンプリング周波数を返す。

---

### GetTime

~~~c++
inline double GetTime();
~~~

#### 引数

void

#### 戻り値

time : データ長[s]

#### 解説

データ長[s]を返す。

---

### operator[]

~~~c++
double& operator[](unsigned int sample);
~~~

#### 引数

*1.* sample : データのインデックス

#### 戻り値

data : sample番目のデータ。

#### 解説

 sample番目のデータを参照する。インデックスが範囲外の場合には0を返す。



---

### GenerateUniform

~~~c++
bool GenerateUniform(double min, double max, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* min : 一様乱数の最小値

*2.* max : 一様乱数の最大値

*3.* time : 生成する信号長[s]

*4.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

[min, max)の一様乱数の信号を生成する。

---

### GenerateNormal

~~~c++
bool GenerateNormal(double mean, double standard_deviation, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* mean : ガウス分布の平均値

*2.* standard_deviation : ガウス分布の標準偏差

*3.* time : 信号長[s]

*4.* sampling_frequnency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

ガウス分布$N(mean, standard\_deviation)$に基づく、ガウスノイズ(ホワイトノイズ)を生成する。

---

### GenerateSine

~~~c++
bool GenerateSine(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* amplitude : 正弦波の振幅値

*2.* phase : 正弦波の初期位相

*3.* frequency : 正弦波の周波数

*4.* time : 信号長[s]

*5.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

正弦波を生成する。

---

### GenerateCosine

~~~c++
bool GenerateCosine(double amplitude, double phase, double frequency, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1*. amplitude : 余弦波の振幅値

*2.* phase : 正弦波の初期位相

*3.* frequency : 正弦波の周波数

*4.* time : 信号長[s]

*5.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

余弦波を生成する。

---

### GenerateImpulse

~~~c++
bool GenerateImpulse(double amplitude, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* amplitude : インパルスの大きさ

*2.* time : 信号長[s]

*3.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

インパルス信号を生成する。

---

### GenerateStep

~~~c++
bool GenerateStep(double amplitude, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* amplitude : インパルスの大きさ

*2.* time : 信号長[s]

*3.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

ステップ信号を生成する。

---

### GenerateChirp

~~~c++
bool GenerateChirp(double amplitude, double phase, double start_frequency, double final_frequency, double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* amplitude : チャープ信号振幅値

*2.* phase : 初期位相

*3.* start_frequency : 開始周波数

*4.* final_frequency : 最終周波数

*5.* time : 信号長[s]

*6.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

チャープ信号を生成する。

----

### GenerateSilence

~~~c++
bool GenerateSilence(double time, unsigned int sampling_frequency);
~~~

#### 引数

*1.* time : 時間

*2.* sampling_frequency : サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

無音の信号を生成する。

---

### HardClipping

~~~c++
static bool HardClipping(Sound& sound, double threshold_min, double threshold_max);
~~~

#### 引数

*1.* sound : サウンドクラスのインスタンス

*2.* threshold_min : 閾値の最小値

*3.* threshold_max : 閾値の最大値

#### 戻り値

true : 成功

false : 失敗

#### 解説

信号が閾値の最小値・最大値をそれぞれ超える場合は閾値で置き換える。

---

### Rounding

~~~c++
static bool Rounding(Sound& sound);
~~~

#### 引数

*1.* sound : サウンドクラスのインスタンス

#### 戻り値

true : 成功

false : 失敗

#### 解説

信号値の小数点第1位を四捨五入する。

---

### Gain

~~~c++
static bool Gain(Sound& sound, double gain);
~~~

#### 引数

*1.* sound : サウンドクラスのインスタンス

*2.* gain : ゲイン調整のための係数

#### 戻り値

true : 成功

false : 失敗

#### 解説

信号のゲインを調整する。

---

### Bias

~~~c++
static bool Bias(Sound& sound, double bias);
~~~

#### 引数

*1.* sound : サウンドクラスのインスタンス

*2.* bias : 信号へのバイアス

#### 戻り値

true : 成功

false : 失敗

#### 解説

信号のバイアスを調整する。

---

### AntiPhase

~~~c++
static bool AntiPhase(Sound& sound);
~~~

#### 引数

*1.* sound : サウンドクラスのインスタンス

#### 戻り値

true : 成功

false : 失敗

#### 解説

信号の位相を反転する。

----

### Reverse

~~~c++
static bool Reverse(Sound& sound)
~~~

#### 引数

*1.* サウンドクラスのインスタンス

#### 戻り値

true : 成功

false : 失敗

#### 解説

信号を逆にする。

---

### ReadWAV(マルチチャンネル用)

~~~c++
static bool ReadWAV(const char* filename, Sound* sound, short int channel);
~~~

#### 引数

*1.* filename : wavファイル

*2.* sound : サウンドクラスのチャンネル数分の配列

*3.* channel : チャンネル数

#### 戻り値

true : 成功

false : 失敗

#### 解説

マルチチャンネルのwavファイルを読み込む。

---

### ReadDAT(マルチチャンネル用)

~~~c++
static bool ReadDAT(const char* filename, Sound* sound, short int channel, short int quantization_bit, unsigned int sampling_frequency);
~~~

#### 引数

*1.* filename : バイナリファイル

*2.* sound : サウンドクラスのチャンネル数分の配列

*3.* channel : チャンネル数

*4.* quantization_bit : 量子化ビット

*5.* サンプリング周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

マルチチャンネルのバイナルファイルを読み込む。

---

### WriteWAV(マルチチャンネル用)

~~~c++
static bool WriteWAV(const char* filename, Sound* sound, short int channel, short int quantization_bit);
~~~

#### 引数

*1.* filename : 書き出すwavファイル名

*2.* sound : サウンドクラスのチャンネル数分の配列

*3.* channel : チャンネル数

*4.* quantization_bit : 量子化ビット

#### 戻り値

true : 成功

false : 失敗

#### 解説

マルチチャンネルのwavファイルを書き出す。

---

### WriteDAT(マルチチャンネル用)

~~~c++
static bool WriteDAT(const char* filename, Sound* sound, short int channel, short int quantization_bit);
~~~

#### 引数

*1.* filename : 書き出すバイナリファイル名

*2.* sound : サウンドクラスのチャンネル数分の配列

*3.* channel : チャンネル数

*4.* quantization_bit : 量子化ビット

#### 戻り値

true : 成功

false : 失敗

#### 解説

マルチチャンネルのバイナリファイルを書き出す。

### IsEmpty

~~~c++
 bool IsEmpty();
~~~

#### 引数

void

#### 戻り値

true : 信号データがnullptr。

false : データがある。

#### 解説

信号データがnullptrかどうかを判定する。

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

クラスのメンバを初期化する。ヒープは解放される。

---

### CalculateSpeedOfSound

~~~c++
static double CalculateSpeedOfSound(double degree_celsius);
~~~

#### 引数

*1.* degree_celsius : セルシウス温度[$^\circ C$]

#### 戻り値

speed_of_sound : 音速[m/s]

#### 解説

空気中における現在の気温[$^\circ C$]の音速を計算する。