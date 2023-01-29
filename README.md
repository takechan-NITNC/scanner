# 概要
C言語の入力解析ライブラリです。
## 存在意義
stdio.hにも備わっているfscanfなどの関数では，長い入力に対応するのが面倒です。用意しておいた領域よりも長い入力によるバッファオーバーフローを厳密に回避するためには読み取り文字数の制限や読み飛ばしなど，変換指定に関する高度な知識と複雑なプログラミングが求められます。

また，ポインタを用いた代入はコードの冗長化に繋がることがあります。以下のプログラムでは，int型の値を受け取る関数functionに，標準入力から受け取った値を代入しています。C言語を少しでも触ったことがある人にとってはいつものことですが，標準入力から受け取った値を関数に渡すだけのために３文も必要なのです。その中でも特に，変数を１つ宣言しなければいけないことはプログラマーへの負担になりえます。
```c
#include <stdio.h>
void function(int);
int main(void)
{
    int input;
    scanf("%d", &input);
    function(input);
    return 0;
}
```

これほど単純なことのために３文を要する原因は，ポインタを用いた代入です。ポインタを介するのではなく戻り値として標準入力から読み取った整数を返す関数next_intを考えてみましょう。そのような関数が存在すれば，上のプログラムは次のようになります。
```c
int next_int();
void function(int);
int main(void)
{
    function(next_int());
    return 0;
}
```

３文を要していた処理が１文に収まり，変数inputの宣言も消滅しました。

引数に入力ストリームを指定するなどの違いはありますが，このライブラリは上記のnext_int関数のようなものを集めたものとなります。
## 依存先
このライブラリは[char-array-list](https://github.com/takechan-NITNC/char-array-list)に依存しています。

[char-array-list](https://github.com/takechan-NITNC/char-array-list)にはchar_array_list.hとchar_array_list.cが含まれます。scanner.cをコンパイルする際には，この２ファイルを同じディレクトリ（scanner.cと同じでなくても良い）に置き，そのディレクトリをインクルードパスに指定した上でchar_array_list.cを一緒にコンパイルするようにしてください。
## 使用例
[AtCoderのpractice contest](https://atcoder.jp/contests/practice)の「A - Welcome to AtCoder」を解いてみましょう。このプログラムではnext_int関数・next_line関数が本ライブラリに含まれる関数となります。
```c
#include <stdio.h>
#include <scanner.h>
int main(void)
{
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += next_int(stdin);
    }
    char *s = next_line(stdin);
    printf("%d %s\n", sum, s);
    free(s);
    return 0;
}
```

適切にscanner.h・scanner.c・char_array_list.h・char_array_list.cを配置してこのプログラムとscanner.c・char_array_list.cをコンパイルすると，問題の要件を満たす実行ファイルを生成できます。ただしAtCoderはmain.cのみの提出しか認めていないので，実際に提出してAC判定をもらうにはscanner.c・char_array_list.cの内容をmain.cに加えたり，include命令をヘッダファイルの内容に置き換えたりする必要があります。
# 仕様
## 用語
「区切り文字」とは，isspace関数が真になる入力とEOFの総称です。
## 関数
このライブラリには，以下の関数が含まれます。
### int has_next(FILE\*)
指定された入力ストリームから文字列を読み取れる可能性があるかを返します。可能性がある場合は０以外，無い場合（ファイル終端など）は０を返します。指定された入力ストリームを読み進めることはありません。
### char *next(FILE\*)
まず，区切り文字以外が現れるまで指定された入力ストリームを読み飛ばしますます。

区切り文字以外の文字が現れたら，その文字から次に現れる区切り文字まで読み取ります。読み取った内容の末尾（区切り文字）をヌル文字に変更した文字列を返します。

戻り値が表す文字列は動的割り当て記憶域を使用します。その文字列が必要でなくなったら，必ずfree関数を用いて記憶域を解放してください。
### int next_int(FILE\*)
next関数と同様の読み取りを行いますが，この関数は読み取った文字列をint型に変換して返します。変換できなかった場合，エラーメッセージを出力して強制終了します。
### int next_double(FILE\*)
next関数と同様の読み取りを行いますが，この関数は読み取った文字列をdouble型に変換して返します。変換できなかった場合，エラーメッセージを出力して強制終了します。
### char *next_line(FILE\*)
指定された入力ストリームを次の改行文字あるいはEOFまで読み進めます。読み取った内容の末尾（改行文字あるいはEOF）をヌル文字に変更した文字列を返します。

戻り値が表す文字列は動的割り当て記憶域を使用します。その文字列が必要でなくなったら，必ずfree関数を用いて記憶域を解放してください。