
= Bun + Next.js + Vitestで着順掲示板を作ってみた

こんにちは。三冠ウマ娘のカズ之助くんです。

今回は自宅に着順掲示板が欲しかった話を書いていきます。

== 着順掲示板ってなに？

さて、皆さんは競馬場と呼ばれる施設に行ったことはあるでしょうか？

日本には競馬場という馬専門の動物園が国内のあちこちに点在しています。行ったことない方はぜひ足を運んでみてください。楽しいですよ。

競馬場に行くと、コースの向こう側(馬場内と呼ばれるエリア)にクソでかモニターがあります。
このモニターにはレースの映像が映し出されていて、レースが終わると着順が表示されます。

//image[article1/turfVision1][去年の有馬記念前日、推し馬のラストランを見に中山競馬場に行ったときのもの][scale=0.7]

クソでかいですね。近くで見ると余計クソデカに見えます。

//image[article1/turfVision2][画像は東京競馬場のもの。中山競馬場のものよりさらにクソデカ][scale=0.7]

このモニターのことをターフビジョンといいます。

ターフビジョン、いいですよね……。欲しくなっちゃいます。

//image[article1/turfVision3][ターフビジョンの端にある着順掲示板][scale=0.7]

ターフビジョンの隅っこにあるのが着順掲示板です。私これほしい！！

私こういう情報をただずっと同じ画面で表示し続けてるディスプレイ大好き侍です。

== なにつくったのさ

というわけで早速作ってみました。@<fn>{raceBoardUrl}

//footnote[raceBoardUrl][https://raceboard.kazuki19992.com (スマホでのみ対応)]

馬券風のフォームに表示したい情報を入力していって、緑のボタンを押下すると着順掲示板風の画面に遷移します。

「着順掲示板を共有する」ボタンを押すと、X(旧: Twitter)でハッシュタグ付きで共有できます。便利ですね。うれしいね。

//image[article1/generator-image][着順掲示板ジェネレーター]
//image[article1/ipad-preview][グリーンチャンネルと着順掲示板を横並びにするとそれっぽい！@<fn>{ipad-memo}][scale=0.7]
//footnote[ipad-memo][グリーンチャンネルの画像をそのまま載せるわけにはいかないので、Photockのフリー画像をそれっぽく加工したものを上に貼り付けています。なお、着順は先週のアルゼンチン共和国杯(GII)のものです。同着ってすごいよね！]

== Figmaで素材をそれっぽくつくろう

さて、順番が前後しましたが、何をつくったのかを見ていただいたところで、どうやって作ったのかの話をしていこうと思います。

みなさんはFigmaってご存知ですか？figmaではないです。Figmaです@<fn>{Figma-memo}。フィギュアの方ではないです。@<fn>{figma-memo}デザインツールの方です。
//footnote[Figma-memo][https://www.figma.com/ 仕事や個人開発とかでよくお世話になっています……。]
//footnote[figma-memo][https://www.figma.jp/ja/figma/ リコリス・リコイルのキャラクターの錦木千束のフィギュアがあってとても可愛くて「よすぎる……」となっていました。ねんどろいどとかもfigmaさんの商品なんだね……。]

そのFigmaを使って、着順掲示板で必要になりそうな素材をそれっぽく作ってみました。

//image[article1/figma-cap][Figmaでそれっぽく作った素材たち]

今回は、これらの素材を作ってみました。

 * 馬番, レース番号用の0〜9の数字
 * レース番号用の10〜12の数字
 * タイム表示用の0〜9の数字
 * 着差表示
 * 審議/確定/未表示
 * レコード/テスト中/未表示

== 作った数字をフォントにしよう

それっぽく数字を作ったので、フォントにしましょう。

調べてみたところによると、SVGからフォントを作れるWebアプリがあるようです@<fn>{svg-to-font}。助かる〜〜〜〜〜！！！

//footnote[svg-to-font][https://glyphter.com/]

SVGファイルを、対応する文字のマスにドラッグ&ドロップしていけば良いようです。楽すぎる。

//image[article1/gen-font-1][囲った部分が塗りつぶされている！？][scale=0.5]

なんてこった！囲い部分が塗りつぶされているじゃないか！？！？！？！？

仕方ないので、文字部分を抜いたフォントを作りましょう。

//image[article1/gen-font-2][文字部分を抜いたフォントを作る][scale=0.5]

このようなフォントを作って、文字色を黒、背景色をオレンジにすれば着順掲示板と同じように表示されるはずです。天才って呼んでいいよ。

== プロジェクトをつくろう

さて、今回はWebアプリとして作ろうと思います。

今回は以下の構成でプロジェクトを作成しました。

 * 環境: bun
 * フレームワーク: next.js + typescript
 * CSSフレームワーク: Tailwindcss
 * テスト: Vitest + react-testing-library + happy-dom
 * lint: eslint

せっかくなので、最近話題の @<tt>{bun} を使ってみたいと思います。

//list[create][bunでnext.jsのプロジェクトをつくる][bash]{
$ bun create next-app
//}

@<list>{create}を実行すると、Next.jsのプロジェクトを作成できます。

あとはお好みでeslintの設定やVitestの設定などを済ませてしまいましょう。

== テスト環境をつくる

今回は @<tt>{bun test} を使うかvitestを使用するかで迷って結局今回はvitestを使用することにしました。

next.jsでvitestを使用する方法は調べればたくさんの方々が私よりもわかりやすく簡潔に教えてくれるので、ここではちょっとしたTipsをご紹介します。

私はこのサイト@<fn>{site-vitest}を参考にさせていただきました。ありがとうございます。

//footnote[site-vitest][https://nado1999.me/articles/vitest-testing-library-20220512]

//embed[latex]{
\clearpage
//}

=== Vitestでテストを実行すると node_modulesが生成されてウザい問題

vitest.config.jsに @<code>{cache:false} を追加しましょう。

これはキャッシュを無効化するものです。無効化したところでjestより速いので別に問題ないでしょう。

=== テストファイルでパスエイリアスが使えない

@<tt>{tsconfig.json} に @<tt>{baseUrl}, @<tt>{paths} を設定したのにテストファイルでパスエイリアスが使えなくてキレそうになっていました。

これは、 @<tt>{vite-tsconfig-paths} を導入して、 @<tt>{plugins} に @<tt>{tsConfigPaths} を追加するといい感じに解決します。

=== vitest.config.jsをどんな感じに書いた？

私はこのようなvitest.config.jsを使っています。

今回はjsdomより軽量なhappy-domを使用しています。

//listnum[vitest.config.js][vitest.config.jsの中身]{
/// <reference types="vitest" />

import react from '@vitejs/plugin-react'
import { defineConfig } from 'vitest/config'
import tsConfigPaths from 'vite-tsconfig-paths'

export default defineConfig({
  plugins: [react(), tsConfigPaths()],
  test: {
    globals: true,
    environment: 'happy-dom',
    cache: false,
    setupFiles: './src/__test__/setup.ts',
  }
})
//}

//listnum[setup.ts][setup.tsの中身]{
import "@testing-library/jest-dom";
//}
@<list>{vitest.config.js}を見ていただくとわかると思いますが、 @<tt>{setupFiles} に  @<tt>{./src/__test__/setup.ts} を指定しています。@<tt>{setup.ts} は、@<list>{setup.ts}のように書いています。

ここに記述したものをテスト実行前に読み込んでくれるものです。

今回は、 @<tt>{@testing-library/jest-dom} を読み込ませています。

== コーディングしていこう

さて、早速コーディングしていきましょう。

コードはココに置いてあります。@<fn>{github-url}

//footnote[github-url][https://github.com/kazuki19992/raceCourseBoard]

=== AppRouterとディレクトリ構成

今回、Next.jsのAppRouterを使用しました。AppRouterはディレクトリ構造/ディレクトリ名によってページのパスが決定されます。

今回は以下のようなパス設計にしました。

 * raceboard.kazuki19992.com
 ** 着順掲示板ジェネレーターのフォーム画面
 * raceboard.kazuki19992.com/[id]
 ** 着順掲示板の画面

作った着順掲示板をURLで共有することができると個人的に楽しいし嬉しいのでこのような設計にしています。

したがって、src/app以下は次のようなディレクトリ構造にしています。

//embed[latex]{
\clearpage
//}

 * app/
 ** [id]/
 *** components/
 *** hooks/
 *** page.tsx
 ** components/
 ** hooks/
 ** globals.css
 ** layout.tsx
 ** page.tsx

=== AppRouter時のAPI Routeについて

今回は結局使わないことにしましたが、PageRouterとAppRouterでAPI Routeの使い方が異なります。

PageRouter時は、 @<tt>{pages/api} 以下のファイルがAPIとして扱われます。

対して、AppRouter時は @<tt>{app/api/route.js|ts} を作ります。軽く調べた限りでは @<tt>{api} ディレクトリではなくても問題はないようです。

@<tt>{route.js | ts} のファイルがAPIとして扱われるようです。

//image[article1/next-api][Next.jsの公式ドキュメントより]

動的なAPIルーティングは @<tt>{app/[slug]/route.js | ts}とするようです。

=== カスタムフックでViewとロジックを分離しよう

Viewとロジックなど、責務が異なるものを分離するとコードの見通しがよくなり、変更に強くなります。あとテストも書きやすくなります。

恥ずかしながら社会人になってからカスタムフックでロジックとViewを分離する方法を教えていただきました……

ものすごく簡単な例ですが、カスタムフックは以下のように書くことができます。

//listnum[useRaceInfo.ts][useRaceInfo.tsの例]{
// src/app/[id]/components/RaceInfo/hooks/useRaceInfo.ts

export const useRaceInfo = () => {
  /**
   * レース番号を表示用に変換する
   * @param raceNumber レース番号(数字)
   * @returns 表示用のレース番号
   */
  const convertRaceNumber = (raceNumber: number): string => {
    if (raceNumber < 10) {
      return String(raceNumber);
    }
    switch (raceNumber) {
      case 10: {
        return "x";
      }
      case 11: {
        return "y";
      }
      case 12: {
        return "z";
      }
      default: {
        return "0";
      }
    }
  };
  return {
    convertRaceNumber,
  };
};
//}

@<list>{useRaceInfo.ts}のように書くことで、 @<tt>{useRaceInfo} というカスタムフックを作成できます。

このカスタムフックはレース番号を表示用の文字に置き換えて返す関数が入っているものです。

レース番号は0〜9までの数字と、10〜12で数字幅が異なります(0〜9が全角、10〜12が半角)。

そこで、0〜9のほかに、10を @<tt>{x}, 11を @<tt>{y}, 12を @<tt>{z} に割り当てています。

//listnum[useRaceInfoUser][useRaceInfo.tsを使う側のコード]{
const { convertRaceNumber } = useRaceInfo();

convertRaceNumber(12); // "z"
//}

このカスタムフックを使用する側では、@<list>{useRaceInfoUser}ようにコードを書くことで呼び出すことができます。

これだけで関数を使用することができ、UIとロジックを分離できます。

コードも見やすくなると思うので、私は積極的に取り入れています。

//embed[latex]{
\clearpage
//}

=== テストコードを書こう

せっかくテストを書きやすくしたのでテストコードも書いていきましょう。

カスタムフックは、基本的に関数コンポーネントの中で動くものです。 @<tt>{react-testing-library} で提供されている @<tt>{RenderHook} を使用することで、擬似的に関数コンポーネントの中で動かしているように見せかけることができます。
@<tt>{useState} や @<tt>{useEffect} などをカスタムフック内で使用する場合は @<tt>{RenderHook} を使う必要があります。

簡単なテストですが、次のように書くことができます。

//listnum[useRaceInfo.test.ts][useRaceInfo.tsのテストコード]{
// src/app/[id]/components/RaceInfo/hooks/__test__/useRaceInfo.test.ts

import { RenderHookResult, renderHook } from "@testing-library/react";
import { useRaceInfo } from "..";

type UseRaceInfo = ReturnType<typeof useRaceInfo>;

describe("useRaceInfo", () => {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  let r: RenderHookResult<any, UseRaceInfo>;

  const hook = () => renderHook(() => useRaceInfo());

  beforeEach(() => {
    r = hook();
  });

  describe("convertRaceNumber", () => {
    test("10未満の場合はそのまま文字列に変換して返す", () => {
      const raceNumber = 1;
      expect(r.result.current.convertRaceNumber(raceNumber)).toBe("1");
    });
    test("10の場合はxを返す", () => {
      const raceNumber = 10;
      expect(r.result.current.convertRaceNumber(raceNumber)).toBe("x");
    });
    test("11の場合はyを返す", () => {
      const raceNumber = 11;
      expect(r.result.current.convertRaceNumber(raceNumber)).toBe("y");
    });
    test("12の場合はzを返す", () => {
      const raceNumber = 12;
      expect(r.result.current.convertRaceNumber(raceNumber)).toBe("z");
    });
    test("13以上の場合は0を返す", () => {
      const raceNumber = 13;
      expect(r.result.current.convertRaceNumber(raceNumber)).toBe("0");
    });
  });
});
//}

また、このテスト元のコードである @<list>{useRaceInfo.ts} では、@<tt>{useState} や @<tt>{useEffect} などを使用していないため、次のように、もっと簡単に書くこともできます。

//listnum[useRaceInfo2.test.ts][useRaceInfo.tsのテストコードをもっと簡単に書いてみた例]{
// src/app/[id]/components/RaceInfo/hooks/__test__/useRaceInfo.test.ts (例)
import { useRaceInfo } from "..";

describe("useRaceInfo", () => {
  const { convertRaceNumber } = useRaceInfo();

  describe("convertRaceNumber", () => {
    test("10未満の場合はそのまま文字列に変換して返す", () => {
      const raceNumber = 1;
      expect(convertRaceNumber(raceNumber)).toBe("1");
    });
    test("10の場合はxを返す", () => {
      const raceNumber = 10;
      expect(convertRaceNumber(raceNumber)).toBe("x");
    });
    test("11の場合はyを返す", () => {
      const raceNumber = 11;
      expect(convertRaceNumber(raceNumber)).toBe("y");
    });
    test("12の場合はzを返す", () => {
      const raceNumber = 12;
      expect(convertRaceNumber(raceNumber)).toBe("z");
    });
    test("13以上の場合は0を返す", () => {
      const raceNumber = 13;
      expect(convertRaceNumber(raceNumber)).toBe("0");
    });
  });
});
//}

関係ないですが、私はテストケース名は日本語で書く派です。見ててわかりやすいですし、テストコードなので環境に影響ないですし。

//embed[latex]{
\clearpage
//}

=== Viewのテストコードも書いていこう

次にViewのテストコードも書いていきましょう。

Viewのテストコードは @<tt>{react-testing-library} を使用して書くことができます。

//listnum[RaceInfo.test.tsx][RaceInfo.tsxのテストコード][typescript]{
import { RenderResult, render } from "@testing-library/react";
import { RaceInfo } from "..";
import { RaceCourse, RaceInfoProps } from "@/models";
import { raceInfoPropsTokyo } from "@/__fixtures__";

describe("RaceInfo", () => {
  const output = (props: RaceInfoProps) => render(<RaceInfo {...props} />);
  let r: RenderResult;
  beforeEach(() => {
    r = output(raceInfoPropsTokyo);
  });

  test("競馬場名が表示されている", () => {
    expect(
      r.getByText(RaceCourse[raceInfoPropsTokyo.raceCourseId])
    ).toBeInTheDocument();
  });

  test("レース番号が表示されている", () => {
    expect(r.getByText(raceInfoPropsTokyo.raceNumber)).toBeInTheDocument();
  });

  test("確定パネルが表示されている", () => {
    expect(
      r.getByTestId(raceInfoPropsTokyo.confirmedStatus)
    ).toBeInTheDocument();
  });
});
//}

かなり雑なテストを書いてみました。

@<list>{RaceInfo.test.tsx}のように書くことで、 @<tt>{RaceInfo} というコンポーネントをテストできます。

Viewのテストを書くときにはoutputという関数を用意し、外からプロパティを渡せるようにするといろんなテストケースに対応できると思います。

== デプロイしよう

デプロイは安定のVercelにしました。Next.jsを使うならVercel @<fn>{vercel} にデプロイするのが一番楽でいいと思います。

//footnote[vercel][https://vercel.com/]

リポジトリをインポートすればすぐにデプロイされます。楽〜〜〜〜〜！！！！！

これでリポジトリに変更が加わったらすぐに自動でデプロイされます。

個人開発にはとても良すぎます。

== これからやりたいこと(やるかわからんけど)
=== netkeibaのURLを使用して過去レースの再現をしたい
せっかく着順掲示板を作ったので、netkeibaのURLから過去のレースの着順掲示板を再現するようにしたいです。

netkeibaをスクレイピングするようになるので、Next.jsのAPI Routeを使用することはできません(デプロイ先のVercelの利用規約でスクレイピングは禁止されているので、API Route上でなんとかするならVercelではないところに移動する必要がある)。

別でスクレイピングをするためのバックエンドを用意する必要があるため、ちょっと面倒です。

でも、気が向いたときにやりたいなぁ……とは思っています。

=== 着順掲示板を画像で保存したい
現状は、作った着順掲示板を保存するためにはOSの機能を利用する必要があります。スクリーンショットです。とても偉大な機能ですね。

でも、電源ボタン+音量ボタン(ホームボタン)の組み合わせをするよりも、画面タップで画像を保存できたほうが明らかに楽ですし、OSのUIなども入ってこないため色々使いやすいと思います。

これも気が向いたときにやるかもしれません。

=== PWA化
今回ちょっと試そうとしたんですがAppRouterに対応したPWA化のライブラリとかがありませんでした。

PWAにすると楽にスマホアプリっぽくできるので個人的には好きなんですが、対応していなければ仕方ないです。コードとかも見たんですが難しそうだったので、ちょっとしっかり読んでみたいと思いました。

== さいごに
競馬はいいぞ！！！！！

今月(2023年11月26日)、東京都府中市にある東京競馬場で、現役世界ランク1位のイクイノックスという馬と、去年のダービー馬のドウデュース、今年の牝馬(女の子の馬)3冠のリバティアイランド、菊花賞や天皇賞(春)、宝塚記念の覇者タイトルホルダーの
激突が見られるので、ぜひ東京競馬場にいきましょう！！！！！！！！！！！！！