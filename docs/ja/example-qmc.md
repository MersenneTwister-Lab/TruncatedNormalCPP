MCQMCIntegration::truncatedNormal()呼び出し例
==========================================
この例では、
まず#includeとnamespaceの指定をしている。

````{#prepare1 .cpp}
#include <MCQMCIntegration/TruncatedNormal.h>
#include <MCQMCIntegration/DigitalNet.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
using namespace MCQMCIntegration;
````

次に多変量正規分布の値を求める範囲と分散共分散行列の初期値を設定している。
truncatedNormalの引数はVector型であるが、初期値を設定するために配列にしている。

````{#prepare2 .cpp}
// パラメータの例
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
    // 積分領域の準備
    vector<double> lower(LOWER, LOWER+s);
    vector<double> upper(UPPER, UPPER+s);
    // 分散共分散行列の準備
    vector< vector<double> > sigma(s);
    for (uint32_t i = 0; i < s; i++) {
        for (uint32_t j = 0; j < s; j++) {
            sigma[i].push_back(SIGMA[i][j]);
        }
    }
    // QMCによる多変量正規分布の計算
    DigitalNetID id = NXLW;
    const TruncatedNormalResult result
        = truncatedNormal(lower,
                          upper,
                          sigma,
                          10000, // number of samples
                          id,    // Low WAFOM Niederreiter-Xing
                          10,    // 2^10 points in digital net point set.
                          0.99);
    // 結果のチェック
    if (!result.success) {
        cout << "calculation failed" << endl;
        return -1;
    }
    // 結果の表示
    cout << "probability:" << result.probability << endl;
    cout << "absoluteError:" << result.absoluteError << endl;
    cout << "relativeError:" << result.relativeError << endl;
    cout << "theoreticalUpperBound:" << result.upperBound << endl;
    return 0;
}
````

この実行結果は以下のようになる。

````
probability:0.166662
absoluteError:4.55524e-06
relativeError:2.73321e-05
theoreticalUpperBound:0.191145
````