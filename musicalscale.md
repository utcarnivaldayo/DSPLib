# 音階クラス

~~~c++
class MusicalScale
~~~

A4が440[Hz]とした場合のA0～C8の音階に対応する周波数を提供する。

---

### MusicalScale

~~~c++
MusicalScale();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

A4が440[Hz]とした場合のA0～C8の音階に対応する周波数をセットする。

---

### ~MusicalScale

~~~c++
~MusicalScale();
~~~

#### 引数

void

#### 戻り値

void

#### 解説

デストラクタ。メンバ変数を初期化する。

---

### SetMusicalScale

~~~c++
bool SetMusicalScale(double concert_pitch);
~~~

#### 引数

*1.* concert_pitch : A4の基準周波数

#### 戻り値

true : 成功

false : 失敗

#### 解説

A4の基準周波数をconcert_pitchとした場合のA0～C8をセットする。



