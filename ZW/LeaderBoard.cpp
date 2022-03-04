#include "LeaderBoard.h"
void LeaderBoard::sortare(QList<int> s, QList<QString> n)
{//algoritm sortare
    score = s;
    nume = n;
    QString aux2;
    int i,j,aux1;
    for(i=0;i<score.size();++i)
        for(j=i+1;j<score.size();++j)
        {
            if(score[i]<score[j]){
                aux1=score[i];
                score[i] = score[j];
                score[j] = aux1;

                aux2=nume[i];
                nume[i] = nume[j];
                nume[j] = aux2;
            }
        }

}
