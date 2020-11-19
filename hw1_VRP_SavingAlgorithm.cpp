#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int main() {
    const int pt = 21;
    const int maxWeight = 100;
    double array[21][3] = {
            {45,40,0},
            {22, 22, 21},
            {12, 50, 31},
            {34, 28, 18},
            {90, 12, 33},
            {80, 58, 22},
            {12, 80, 15},
            {5,  65, 32},
            {91, 37, 13},
            {56, 33, 19},
            {12, 9,  28},
            {79, 69, 40},
            {31, 5,  21},
            {14, 99, 37},
            {99, 56, 43},
            {99, 79, 18},
            {50, 50, 29},
            {30, 39, 17},
            {5,  64, 42},
            {19, 27, 39},
            {44, 82, 22}
    };
//计算距离矩阵
    double dis[pt][pt];

    for (int i = 0; i < pt; i++) {
        for (int j = 0; j < pt; j++) {
            dis[i][j] = sqrt((array[i][0] - array[j][0]) * (array[i][0] - array[j][0]) +
                             (array[i][1] - array[j][1]) * (array[i][1] - array[j][1]));
            //cout<<dis[i][j]<<' ';
            dis[i][j] = round(dis[i][j] * 100.0) / 100;//取两位小数
        }
    }
    double distance=0;
    for(int i=0;i<pt;i++)
         distance+=dis[i][0]*2;
    //cout<<distance<<endl;//初始距离



    vector<vector<int>>route;
    double saving[4];
    double maxSaving=0;
    int ipoint,jpoint,kpoint;
    double sumDemand=0;
for(int i = 0; i < 20; i++) //构造路径
{
    vector<int> singleRoute;
    singleRoute.push_back(i+1);
    route.push_back(singleRoute);
}

while(true) {
    maxSaving=0;
    for (int i = 0; i < route.size() - 1; i++) {
        for (int j = i + 1; j < route.size(); j++) {
            sumDemand = 0;
            for (int s = 0; s < route[i].size(); s++) {
                sumDemand += array[route[i][s]][2];
            }
            for (int r = 0; r < route[j].size(); r++) {
                sumDemand += array[route[j][r]][2];
            }
            if (sumDemand <= maxWeight && route[i][0]!=0 && route[j][0]!=0) {
                saving[0] = dis[route[i][0]][0] + dis[route[j][0]][0] - dis[route[i][0]][route[j][0]];
                saving[1] = dis[route[i].back()][0] + dis[route[j][0]][0] - dis[route[i].back()][route[j][0]];
                saving[2] = dis[route[i][0]][0] + dis[route[j].back()][0] - dis[route[i][0]][route[j].back()];
                saving[3] = dis[route[i].back()][0] + dis[route[j].back()][0] - dis[route[i].back()][route[j].back()];
                for (int k = 0; k < 4; k++) {
                    if (maxSaving < saving[k]) {
                        maxSaving = saving[k];
                        ipoint = i;
                        jpoint = j;
                        kpoint = k;
                    }
                }
            }
        }
    }
    sumDemand = 0;
    if(maxSaving==0)
        break;
    else{

    distance-=maxSaving;
    maxSaving=0;
    for(int i=0;i<4;i++)
                saving[i]=0;
//找到之后开始合并
    vector<int> addRoute;
    if (kpoint == 0) {
        while (!route[ipoint].empty()) {
            addRoute.push_back(route[ipoint].back());
            route[ipoint].pop_back();
        }
        for (int i = 0; i < route[jpoint].size(); i++) {
            addRoute.push_back(route[jpoint][i]);
        }
        route[ipoint][0]=0;
        route[jpoint][0]=0;
        route.push_back(addRoute);
        addRoute.clear();
    }
    if (kpoint == 1) {
        for (int i = 0; i < route[ipoint].size(); i++) {
            addRoute.push_back(route[ipoint][i]);
        }
        for (int j = 0; j < route[jpoint].size(); j++) {
            addRoute.push_back(route[jpoint][j]);
        }
        route.push_back(addRoute);
        route[ipoint][0]=0;
        route[jpoint][0]=0;
        addRoute.clear();
    }
    if (kpoint == 2) {
        while (!route[ipoint].empty()) {
            addRoute.push_back(route[ipoint].back());
            route[ipoint].pop_back();
        }
        while (!route[jpoint].empty()) {
            addRoute.push_back(route[jpoint].back());
            route[jpoint].pop_back();
        }
        route[ipoint][0]=0;
        route[jpoint][0]=0;
        route.push_back(addRoute);
        addRoute.clear();
    }
    if (kpoint == 3) {
        for (int i = 0; i < route[ipoint].size(); i++) {
            addRoute.push_back(route[ipoint][i]);
        }
        while (!route[jpoint].empty()) {
            addRoute.push_back(route[jpoint].back());
            route[jpoint].pop_back();
        }
        route.push_back(addRoute);
        route[ipoint][0]=0;
        route[jpoint][0]=0;
        addRoute.clear();
    }

}
    //输出

}
cout<<"The First Problem"<<endl;
    for(int i = 0; i < route.size(); i++) {
        if(route[i][0]!=0)
            cout<<"route: "<<"0-";
        for (int j = 0; j < route[i].size(); j++) {
            if(route[i][0]!=0)
            cout <<route[i][j] << "-";
        }
        if(route[i][0]!=0)
            cout<<'0'<<endl;
    }
    cout<<"distance: "<<distance;



/*//输出检查

    for(int i = 0; i < route.size(); i++)
    {
        for(int j=0;j<route[i].size();j++)
        {
            cout<<route[i][j]<<' ';
        }
        cout<<endl;
    }
*/







//输出距离矩阵
/*
for (int i = 0; i < pt; i++) {
    cout<<'[';
    for (int j = 0; j < pt; j++)
    {
        cout << dis[i][j] << ',';
    }
    cout << "],"<<endl;
}
 */

//第二问

vector<vector<int>>newroute;
for(int i=0;i<route.size();i++)
{
    if((!route[i].empty() )&& route[i][0]!=0)
    {
        newroute.push_back(route[i]);
    }
}

/* newroute
cout<<endl<<"newroute";
for(int i=0;i<newroute.size();i++)
{
    for(int j=0;j<newroute[i].size();j++)
        cout<<newroute[i][j]<<' ';
    cout<<endl;
}
 */
double totalDemandi=0;
double totalDemandj=0;
double save=0;
double maxsave=0;
double temp;
int newipoint,newjpoint,newinpoint,newjnpoint;
while(true) {
    for (int i = 0; i < newroute.size() - 1; i++) {
        for (int j = i + 1; j < newroute.size(); j++) {
            for (int in = 0; in < newroute[i].size(); in++) {
                for (int jn = 0; jn < newroute[j].size(); jn++) {
                    totalDemandi = 0;
                    totalDemandj = 0;
                    for (int s = 0; s < newroute[i].size(); s++) {
                        totalDemandi += array[newroute[i][s]][2];
                    }
                    for (int s = 0; s < newroute[j].size(); s++) {
                        totalDemandj += array[newroute[j][s]][2];
                    }
                    if ((totalDemandi - array[newroute[i][in]][2] + array[newroute[j][jn]][2] <= maxWeight) &&
                        (totalDemandj - array[newroute[j][jn]][2] + array[newroute[i][in]][2] <= maxWeight))
                        //满足demand
                    {
                        save = 0;
                        if (in == 0) {
                            save += dis[0][newroute[i][in]];
                            save -= dis[0][newroute[j][jn]];
                        } else {
                            save += dis[newroute[i][in - 1]][newroute[i][in]];
                            save -= dis[newroute[i][in - 1]][newroute[j][jn]];
                        }
                        if (in == (newroute[i].size() - 1)) {
                            save += dis[0][newroute[i][in]];
                            save -= dis[0][newroute[j][jn]];
                        } else {
                            save += dis[newroute[i][in]][newroute[i][in + 1]];
                            save -= dis[newroute[j][jn]][newroute[i][in + 1]];
                        }
                        if (jn == 0) {
                            save += dis[0][newroute[j][0]];
                            save -= dis[0][newroute[i][in]];
                        } else {
                            save += dis[newroute[j][jn - 1]][newroute[j][jn]];
                            save -= dis[newroute[j][jn - 1]][newroute[i][in]];
                        }
                        if (jn == (newroute[j].size() - 1)) {
                            save += dis[0][newroute[j][jn]];
                            save -= dis[0][newroute[i][in]];
                        } else {
                            save += dis[newroute[j][jn]][newroute[j][jn + 1]];
                            save -= dis[newroute[i][in]][newroute[j][jn + 1]];
                        }
                        if (save > maxsave) {
                            maxsave = save;
                            newinpoint = in;
                            newjnpoint = jn;
                            newipoint = i;
                            newjpoint = j;
                        }

                    }
                }
            }
        }
    }
    if(maxsave==0)
        break;
    distance-=maxsave;
    temp = newroute[newipoint][newinpoint];
    newroute[newipoint][newinpoint] = newroute[newjpoint][newjnpoint];
    newroute[newjpoint][newjnpoint] = temp;
    maxsave=0;
}
    cout<<endl<<endl<<"The Second Problem"<<endl;
    for(int i=0;i<newroute.size();i++)
    {
        cout<<"route: 0-";
        for(int j=0;j<newroute[i].size();j++)
            cout<<newroute[i][j]<<'-';
        cout<<"0"<<endl;
    }
    cout<<"distance: ";
    cout<<distance;
