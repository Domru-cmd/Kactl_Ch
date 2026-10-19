# KACTL(中文版)

本仓库收录 KACTL——[KTH(瑞典皇家理工学院)](https://en.wikipedia.org/wiki/KTH_Royal_Institute_of_Technology) 的 ICPC 队伍参考文档,并已本地化:
全部描述性注释与文档译为简体中文,代码统一为 `fivour.cpp` 风格(见 [风格规范.md](./风格规范.md))。
它由 25 页可复制粘贴的 C++ 代码组成,用于 ICPC 赛制的程序设计竞赛。

最终的可浏览版本见 [kactl.pdf](./kactl.pdf),原始源码见 [content/](./content/)。

## 目标

KACTL 算法应当:实用、简短、足够快、经过充分测试,并在相关时易读、易改。
它们不追求过度泛化——代码是手工输入的,过度泛化只会增加负担。
受篇幅限制,我们也排除过于常见/简单的算法(如 Dijkstra)和过于冷门的算法(如一般图带权匹配)。

如果你觉得有内容缺失、值得清理,或发现了 bug,请提 issue 或[发 pull request](https://help.github.com/articles/fork-a-repo/)!

## 定制本模板

本模板开箱即用,也易于定制——例如修改封面、自选收录的算法
(受篇幅限制,仓库中的算法并未全部收录进 pdf),或启用彩色语法高亮。

`content/kactl.tex` 是主文件,可修改队伍名称、logo、语法高亮等。
它会引入各 `content/` 子目录中的 `chapter.tex`,这些文件定义每一章的内容,
包含以 LaTeX 形式给出的源码、文字与数学公式。
要从某一章增删代码,在对应 `chapter.tex` 中增删相应的 `\kactlimport` 行即可。
为获得更美观的排版,可以插入 `\hardcolumnbreak`、`\columnbreak` 或 `\newpage` 命令,
不过这一般只在重要比赛前做,不在主分支上进行。
未收录进 pdf 的算法在 `chapter.tex` 中保持注释状态。

构建:在 \*nix 机器上运行 `make kactl`(或 `make fast`),会更新 `kactl.pdf`。
本中文化版本使用 XeLaTeX + xeCJK 排版中文,需要 TeX Live(含 `xetex`、`xecjk`、`ctex`)与 Noto CJK 字体。
(Windows 可能也可以,但未测试。)更多说明见 `doc/README`。

提示:
1. 运行 `make showexcluded` 可以查看默认被排除的文件。默认配置为新手与资深队伍做了合理折中。
2. 善用哈希核对誊抄:每个算法右上角有 6 位 MD5 哈希,可用 `hash.sh` 或 `.vimrc` 中的 `:Hash` 命令生成,计算时忽略空白与注释。

## 代码风格

本副本已统一为 `fivour.cpp` 风格:4 空格缩进、K&R 大括号、`using` 别名、不使用 `rep`/`all`/`sz` 宏;
描述性注释一律使用简体中文。具体规则见 [风格规范.md](./风格规范.md)。

每个算法文件都有一段注释头:作者、日期、许可、来源、描述、时间与测试状态。

## 测试

KACTL 追求对算法正确性的高置信度:测试既在在线评测系统上进行,也对新算法使用对拍测试——
对大量随机用例,将结果与朴素算法比较。
对拍测试位于 `stress-tests` 目录,每次提交都会由 CI 运行;
CI 还会验证所有头文件可编译(排除列表见 `doc/scripts/skip_headers`),并验证 LaTeX 可编译。

`old-unit-tests` 里有一些早已损坏的单元测试,最后维护大约在十年前。

## 许可

与竞赛编程的惯例一样,许可情况不太明确:许多源文件标注了许可
(我们尽量采用 [CC0](https://creativecommons.org/share-your-work/public-domain/cc0/)),但也有不少没有标注。
可以假定其他作者持善意态度;而且多数情况下代码并不分发,应当无需许可。
为便于溯源,来源与作者都注在源文件中。

`stress-tests` 中的一切内容默认为 CC0,但从互联网各处取来的参考实现除外。
