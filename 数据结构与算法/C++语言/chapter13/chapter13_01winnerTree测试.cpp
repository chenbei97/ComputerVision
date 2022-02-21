#include "chapter13_winnerTree.h"
#include "chapter13_player.h"
#include <iostream>
using namespace std;
void _chapter13_winnerTree_testCode() {
    int n = 10;
    player* thePlayer = new player[n + 1];
    int scores[11] = { 0,79,40,81,95,43,67,51,99,32,24 };
    for (int i = 1; i <= 10; i++) {
        thePlayer[i].id = i;
        thePlayer[i].score = scores[i];
    }
    winnerTree<player>* w =
        new winnerTree<player>(thePlayer, n);
    cout << "The winner tree is" << endl;
    w->output(cout);
    cout << *w << endl;

    thePlayer[2].score = 0;
    w->replay(2);
    cout << "Changed player 2 to zero, new tree is" << endl;
    w->output(cout);

    thePlayer[3].score = -1;
    w->replay(3);
    cout << "Changed player 3 to -1, new tree is" << endl;
    w->output(cout);

    thePlayer[7].score = 2;
    w->replay(7);
    cout << "Changed player 7 to 2, new tree is" << endl;
    w->output(cout);
}