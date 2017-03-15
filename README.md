# 使う
対戦させたいAIのlibを持ってきてください。それぞれのファイル名を使って、

```
$ make
$ ./othello [black filename] [white filename]
```

とすると、ふたつのAIが戦いだします。

Windowsの場合、

```
$ make windows
```

とすると、たぶんできます。
（Windowsではコンパイル環境がないため未実証、Linuxでmingwでクロスコンパイルで動いたので多分大丈夫。）

# 作る
othello-ai.hをインクルードしてください。

othello-ai.h, othello-def.hを見ればなんとなく分かるはずです。
initとturnを実装してください。

# sample
humanという、ただ人間とのCUI I/Oを実装したAIがサンプルとしてあります。AIはあなたです。

```
$ cd sample
$ make
```

とすると、libhuman.soができます。

```
$ ./othello sample/libhuman.so sample/libhuman.so
```

として、二人で遊んでください。
