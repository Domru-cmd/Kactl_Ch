/**
 * 作者:Simon Lindholm
 * 日期:2015-03-19
 * 许可:CC0
 * 来源:自己整理
 * 描述:
 */
#pragma once

#define F {...; ++i;}
int i = from;
while (i & 3 && i < to) F // 需要时用于对齐
while (i + 4 <= to) { F F F F }
while (i < to) F
