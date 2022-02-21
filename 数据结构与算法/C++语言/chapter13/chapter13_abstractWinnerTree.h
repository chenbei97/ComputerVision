#pragma once
#ifndef chapter13_abstractWinnerTree_
#define chapter13_winnerTree_
template<class T>
class abstractWinnerTree {
	public: 
		virtual ~abstractWinnerTree() {}
		virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
		virtual int winner() const = 0; // 返回赢者在数组的索引
		virtual void replay(int thePlayer) = 0; // 参赛者thePlayer的分数变化后重赛,这里给的是索引
};
#endif // !chapter13_abstractWinnerTree_
