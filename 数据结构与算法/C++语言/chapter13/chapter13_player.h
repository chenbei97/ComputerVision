#pragma once
#ifndef  chapter12_palyer_
#define chapter12_palyer_
struct player
{
	int id, score; // 选手的id和score
	operator int() const { return score; }
};
#endif // ! chapter12_palyer_
