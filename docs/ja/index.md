多変量正規分布
==========

このプログラムは多変量正規分布の計算をする。
Zdravko I. Botev 氏のRパッケージTruncatedNormal
のC++版である。

インストール
=========

    ./configure --prefix=YOUR_INSTALL_DIR
    make
    make install

準備
===
環境変数 DIGITAL_NET_PATH をインストールディレクトリ以下のshare/truncatednormalに
セットする。

    export DIGITAL_NET_PATH=YOUR_INSTALL_DIR/share/truncatednormal

LIBRARY_PATH と CPLUS_INCLUDE_PATH を適切にセットする。

注意
=======
データファイル 'nxlw.dat' と 'solw.dat' はLittel Endianシステムで作られた
バイナリファイルであり、 Big Endian システムでは正確に動作しないだろう。

使用法
=====
多変量正規分布の計算をするC++関数は[MCQMCIntegration::truncatedNormal()](../namespace_m_c_q_m_c_integration.html#af4e5dfd18fce6c772805a91bd7fa2c02)である。
この関数の引数として[MCQMCIntegration::DigitalNetID](../class_m_c_q_m_c_integration_1_1_digital_net.html)を使用する。
この関数の返却値は[MCQMCIntegreation::TruncatedNormalResult](../struct_m_c_q_m_c_integration_1_1_truncated_normal_result.html)である。

MCQMCIntegration::truncatedNormal()の引数
---------------------------------------

<dl>
  <dt>const std::vector< double > &  	lower</dt>
  <dd>積分領域の下限を表すベクトル。長さは積分領域の次元sである。</dd>

  <dt>const std::vector< double > &  	upper</dt>
  <dd>積分領域の上限を表すベクトル。長さは積分領域の次元sである。</dd>

  <dt>const std::vector< std::vector< double > > &  	sigma</dt>
  <dd>分散・共分散行列</dd>

  <dt>uint64_t  	number</dt>
  <dd>積分を行う回数。この回数だけ積分を繰り返し、平均と誤差を求める。</dd>

  <dt>DigitalNetID	dnid</dt>
  <dd>使用するデジタルネットを表す。
  <ul>
  <li>NXLW : WAFOM値の低い Niederreiter-Xing 点集合。</li>
  <li>SOLW : WAFOM値の低い　Sobol 点集合。</li>
  </ul>
  </dd>

  <dt>uint32_t  	m</dt>
  <dd>デジタルネットの上位mビットまでの精度, また１回の積分で2^m個の点を使用する。</dd>

  <dt>double  	probability</dt>
  <dd>積分結果が誤差内に入ると期待される確率</dd>
</dl>

MCQMCIntegration::truncatedNormal()の返却値
-----------------------------------------

<dl>
  <dt>probability</dt>
  <dd>指定された正規分布の値(累積確率)</dd>

  <dt>absoluteError</dt>
  <dd>絶対誤差</dd>

  <dt>relativeError</dt>
  <dd>相対誤差</dd>

  <dt>upperBound</dt>
  <dd>正規分布の値の理論上の上限</dd>

  <dt>success</dt>
  <dd>計算が成功したかどうかを示す。true:成功, false:失敗</dd>
</dl>

MCQMCIntegration::truncatedNormal()呼び出し例
------------------------------------------
この例では、
まず#includeとnamespaceの指定をしている。

````{#prepare1 .cpp}
#include <MCQMCIntegration/TruncatedNormal.h>
#include <iostream>
#include <string>
#include <random>
#include <cmath>

using namespace std;
using namespace MCQMCIntegration;
````

次に多変量正規分布の値を求める範囲と分散共分散行列の初期値を設定している。
truncatedNormalの引数はVector型であるが、初期値を設定するために配列にしている。

````{#prepare2 .cpp}
// parameter example
const uint32_t s = 5;
double LOWER[5] = {-INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY};
double UPPER[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
double SIGMA[5][5] = {
    {1.666667e+00, 8.333333e-01, 8.333333e-01, 8.333333e-01, 8.333333e-01},
    {8.333333e-01, 1.666667e+00, 8.333333e-01, 8.333333e-01, 8.333333e-01},
    {8.333333e-01, 8.333333e-01, 1.666667e+00, 8.333333e-01, 8.333333e-01},
    {8.333333e-01, 8.333333e-01, 8.333333e-01, 1.666667e+00, 8.333333e-01},
    {8.333333e-01, 8.333333e-01, 8.333333e-01, 8.333333e-01, 1.666667e+00}
};
````

以下はmain関数になる。配列をvectorに変更し、truncatedNormal関数を呼び出している。

````{#main .cpp}
int main()
{
    // prepare integration area.
    vector<double> lower(LOWER, LOWER+s);
    vector<double> upper(UPPER, UPPER+s);
    vector< vector<double> > sigma(s);
    for (uint32_t i = 0; i < s; i++) {
        for (uint32_t j = 0; j < s; j++) {
            sigma[i].push_back(SIGMA[i][j]);
        }
    }
    // QMC
    DigitalNetID id = NXLW;
    const TruncatedNormalResult result
        = truncatedNormal(lower,
                          upper,
                          sigma,
                          10000, // number of samples
                          id,    // Low WAFOM Niederreiter-Xing
                          10,    // 2^10 points in digital net point set.
                          0.99);
    if (!result.success) {
        cout << "calculation failed" << endl;
        return -1;
    }
    // show result
    cout << "probability:" << result.probability << endl;
    cout << "absoluteError:" << result.absoluteError << endl;
    cout << "relativeError:" << result.relativeError << endl;
    cout << "theoreticalUpperBound:" << result.upperBound << endl;
    return 0;
}
````


REFERENCE
=========
* [https://cran.r-project.org/package=TruncatedNormal](https://cran.r-project.org/package=TruncatedNormal)
* Z. I. Botev (2015), The Normal Law Under Linear Restrictions:
Simulation and Estimation via Minimax Tilting, submitted to JRSS(B)
* Z. I. Botev and P. L’Ecuyer (2015), Efficient Estimation and Simulation
of the Truncated Multivariate Student-t Distribution,
Proceedings of the 2015 Winter Simulation Conference,
Huntington Beach, CA, USA
* Gibson G. J., Glasbey C. A., Elston D. A. (1994),
Monte Carlo evaluation of multivariate normal integrals and
sensitivity to variate ordering,
In: Advances in Numerical Methods and Applications, pages 120–126

LICENSE
=======
````
Copyright (C) 2015 Zdravko I. Botev.

Copyright (C) 2017 Shinsuke Mori, Makoto Matsutmoto, Mutsuo Saito
and Hiroshima University.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
````