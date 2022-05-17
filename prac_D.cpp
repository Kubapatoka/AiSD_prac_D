#include<iostream>
#include<vector>
using namespace std;

//pracownia D
//AISD 2022
//autor: Jakub Kopystiański

int n;
vector<int> T[500010]; //drzewo pierwsze
vector<int> D[500010];  //drzewo drugie
//int degT[500010];
//int degD[500010];

int cenD, cenT;

int roz_pod_T[500010];
int roz_pod_D[500010];

void DFS1(int v, int p)
{
  int roz = 1;
  for(int i = 0; i < T[v].size(); i++)
  {
    int a = T[v][i];
    if(a != p){
      roz+=roz_pod_T[a];
    }
  }
  roz_pod_T[v] = roz;
}

void DFS2(int v, int p)
{
  int roz = 1;
  for(int i = 0; i < D[v].size(); i++)
  {
    int a = D[v][i];
    if(a != p){
      roz+=roz_pod_D[a];
    }
  }
  roz_pod_D[v] = roz;
}


void find_centroid()
{
  DFS1(1,1);
  DFS2(1,1);
  vector<int> centr_T;
  for(int i = 1; i <= n; i++)
  {
    bool czy_centroid = true;
    for(int j = 0; j < T[i].size(); j++)
    {
      int a = T[i][j];
      if(n - roz_pod_T[i] > n/2)break;
      if(roz_pod_T[a] < roz_pod_T[i] && roz_pod_T[a] > n/2)czy_centroid = false;
    }
    if(czy_centroid)centr_T.push_back(i);
  }

  vector<int> centr_D;
  for(int i = 1; i <= n; i++) //szukamy centroidów
  {
    bool czy_centroid = true;
    for(int j = 0; j < D[i].size(); j++)
    {
      int a = D[i][j];
      if(n - roz_pod_D[i] > n/2)break;
      if(roz_pod_D[a] < roz_pod_D[i] && roz_pod_D[a] > n/2)czy_centroid = false;
    }
    if(czy_centroid)centr_T.push_back(i);
  }

  if(centr_D.size() != centr_T.size())
  {
    //wypisz że nie
  }

  if(centr_T.size() > 2) cout << "znaleziono ponad dwa centroidy!!!";

  if(centr_T.size() == 2)
  {
    n++;
    T[n].push_back(centr_T[0]);
    T[n].push_back(centr_T[1]);
    T[centr_T[0]].push_back(n);
    T[centr_T[1]].push_back(n);
    cenT = n;
  }
  else cenT = centr_T[0];

  if(centr_D.size() > 2) cout << "znaleziono ponad dwa centroidy!!!";

  if(centr_D.size() == 2)
  {
    D[n].push_back(centr_D[0]);
    D[n].push_back(centr_D[1]);
    D[centr_D[0]].push_back(n);
    D[centr_D[1]].push_back(n);
    cenD = n;
  }
  else cenD = centr_D[0];








}

int main()
{
  int liczba_testow;
  cin >> liczba_testow;
  for(int id_testu = 0; id_testu < liczba_testow; id_testu++)
  {
    cin >> n;
    for(int i = 0; i < n-1; i++)
    {
      int a,b;
      cin >> a >> b;
      T[a].push_back(b);
      T[b].push_back(a);
      //degT[a]++;
      //degT[b]++;
    }

    for(int i = 0; i < n-1; i++)
    {
      int a,b;
      cin >> a >> b;
      D[a].push_back(b);
      D[b].push_back(a);
      //degD[a]++;
      //degD[b]++;
    }


    find_centroid();
    cout << "Centroid w pierwszym drzewie: " << cenT << " Centroid w drugim:  " << cenD << "\n";



  }
}
