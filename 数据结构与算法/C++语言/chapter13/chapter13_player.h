#pragma once
#ifndef  chapter12_palyer_
#define chapter12_palyer_
struct player
{
	int id, score; // ѡ�ֵ�id��score
	operator int() const { return score; }
};
#endif // ! chapter12_palyer_
