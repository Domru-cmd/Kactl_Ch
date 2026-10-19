LATEXCMD = xelatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "本 Makefile 用于构建 KACTL(KTH 算法竞赛模板库)"
	@echo ""
	@echo "可用命令:"
	@echo "	make fast		- 快速构建 KACTL(只运行一遍 LaTeX)"
	@echo "	make kactl		- 构建 KACTL"
	@echo "	make clean		- 清理构建过程"
	@echo "	make veryclean		- 清理并删除 kactl.pdf"
	@echo "	make test		- 运行 stress-tests/ 中的所有对拍测试"
	@echo "	make test-compiles	- 测试编译所有头文件"
	@echo "	make help		- 显示本帮助"
	@echo "	make showexcluded	- 显示未收录进文档的文件"
	@echo ""
	@echo "更多信息请见 'doc/README'"

fast: | build
	$(LATEXCMD) content/kactl.tex </dev/null
	cp build/kactl.pdf kactl.pdf

kactl: test-session.pdf | build
	$(LATEXCMD) content/kactl.tex && $(LATEXCMD) content/kactl.tex
	cp build/kactl.pdf kactl.pdf

clean:
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.pdf kactl.ptc

veryclean: clean
	rm -f kactl.pdf test-session.pdf

.PHONY: help fast kactl clean veryclean

build:
	mkdir -p build/

test:
	./doc/scripts/run-all.sh .

test-compiles:
	./doc/scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
