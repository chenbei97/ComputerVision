#pragma once
#ifndef chapter13_abstractWinnerTree_
#define chapter13_winnerTree_
template<class T>
class abstractWinnerTree {
	public: 
		virtual ~abstractWinnerTree() {}
		virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
		virtual int winner() const = 0; // ����Ӯ�������������
		virtual void replay(int thePlayer) = 0; // ������thePlayer�ķ����仯������,�������������
};
#endif // !chapter13_abstractWinnerTree_
