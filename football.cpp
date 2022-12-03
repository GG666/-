#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <map>
#include <iomanip>

#define ak1 attackScore1
#define ak2 attackScore2
#define de1 defenseScore1
#define de2 defenseScore2

#define tt1 totalScore1
#define tt2 totalScore2

#define matchTimes 2000

using namespace std;
int main()
{
    double ak1, ak2, de1, de2;
    int tt1, tt2;
    cout << "Please input the score of attack, defense and total score that you rate the team 1\n";
    cin >> ak1 >> de1 >> tt1;

    cout << "Please input the score of attack, defense and total score that you rate the team 2\n";
    cin >> ak2 >> de2 >> tt2;
    int temp1, temp2;
    temp1 = (tt1 << 1) + ak1 + de1;
    temp1 = temp1 << 16;

    temp2 = (tt2 << 1) + ak2 + de2;
    temp2 = temp2 << 16;
    double adv = (temp1 - temp2) / (80);

    bool ball;
    vector<pair<int, int>> PS; // predicted scores
    PS.reserve(matchTimes);

    map<int, int> score1;
    map<int, int> score2;
    map<pair<int, int>, int> count_pair;
    map<int, pair<int, int>> sorted_pair;

    srand(time(NULL));
    int countWin = 0, countEq = 0, countLose = 0;

    int countBall1 = 0, cb2 = 0;
    for (int j = 0; j < matchTimes; ++j)
    {
        int count1 = 0, count2 = 0;
        for (int i = 0; i < 90; ++i)
        {

            // true => ball is in team 1
            ball = adv + rand() + rand() + rand() + rand() > RAND_MAX * 2;

            double noise = (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1);
            double noise2 = (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1) + (rand() % 3 - 1);
            if (ball)
            {
                ++countBall1;
                count1 += ((noise) * ((tt1 - tt2 + (ak1 - de2) * 2) / 7 + noise2) > 7.63);
            }
            else
            {
                ++cb2;
                count2 += ((noise) * ((tt2 - tt1 + (ak2 - de1) * 2) / 7 + noise2) > 7.63);
            }
        }

        PS.push_back({count1, count2});
        ++count_pair[{count1, count2}];
        
        if (count1 > count2)
        {
            ++countWin;
        }
        else if (count1 == count2)
        {
            ++countEq;
        }
        else
        {
            ++countLose;
        }
        ++score1[count1];
        ++score2[count2];
    }

    int count = 0;
    for (auto &i : PS)
    {
        cout << "Match " << ++count << " => " << i.first << " : " << i.second << endl;
    }

    cout << "====================================================\n";
    for (auto &i : score1)
    {
        cout << "The score " << i.first << " occurs " << setw(3) << i.second << " times in team 1\n";
    }

    cout << "====================================================\n";
    for (auto &i : score2)
    {
        cout << "The score " << i.first << " occurs " << setw(3) << i.second << " times in team 2\n";
    }

    cout << "The win ratio of team 1 is " << (double)countWin / matchTimes << endl;
    cout << "The lose ratio of team 1 is " << (double)countLose / matchTimes << endl;
    cout << "The equal ratio of  is " << (double)countEq / matchTimes << endl;

    cout << "====================================================\n";

    cout << countBall1 << ' ' << cb2 << endl;

    for(auto &i : count_pair){
        sorted_pair[i.second] = i.first;
    }
    count = 0;
    for(auto it = sorted_pair.rbegin(); it!= sorted_pair.rend(); ++it){
        cout<<"The "<<setw(2)<<++count<< " possible scores is ["<<it->second.first<<", "<<it->second.second<<"] it occurs "<<setw(3)<<it->first<<" times.\n";
    }
}
// 7 5 7
// 6 5 6

// 3 7 5
// 6 3 5

// 7 3 6
// 4 4 4