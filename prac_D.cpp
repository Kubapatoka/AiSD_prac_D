#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

//pracownia D
//AISD 2022
//autor: Jakub Kopystiañski

#define MODULO 1000000007;

int n;
int rodzaje = 1;
string Ans = "YES";
vector<int> T[500010]; //drzewo pierwsze
vector<int> D[500010];  //drzewo drugie
//int degT[500010];
//int degD[500010];

int cenD, cenT;

int roz_pod_T[500010];
int roz_pod_D[500010];

#define f first
#define s second

map< pair<pair<int,int>, int>, int> M;

void DFS1(int v, int p)
{
  int roz = 1;
  for(int i = 0; i < T[v].size(); i++)
  {
    int a = T[v][i];
    if(a != p)
    {
        DFS1(a,v);
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
        DFS2(a,v);
      roz+=roz_pod_D[a];
    }
  }
  roz_pod_D[v] = roz;
}


void find_centroid()
{
  DFS1(1,1);
  DFS2(1,1);

  /*for(int i = 1; i <= n; i++)
  {
      cout << "roz pod T[" << i << "] = " << roz_pod_T[i] << "\n";
  }

  cout << "\n";

  for(int i = 1; i<= n; i++)
  {
      cout << "roz pod D[" << i << "] = " << roz_pod_D[i] << "\n";
  }
*/

  vector<int> centr_T;
  for(int i = 1; i <= n; i++)
  {
    bool czy_centroid = true;
    if(n - roz_pod_T[i] > n/2)continue;
    for(int j = 0; j < T[i].size(); j++)
    {
      int a = T[i][j];
      if(roz_pod_T[a] < roz_pod_T[i] && roz_pod_T[a] > n/2)czy_centroid = false;
    }
    if(czy_centroid)centr_T.push_back(i);
  }

    /*for(int i = 0; i < centr_T.size(); i++)
  {
      cout << "centroidy w T: " << centr_T[i] << "\n";
  }*/



  vector<int> centr_D;
  for(int i = 1; i <= n; i++) //szukamy centroidów
  {
    bool czy_centroid = true;
    if(n - roz_pod_D[i] > n/2)continue;
    for(int j = 0; j < D[i].size(); j++)
    {
      int a = D[i][j];

      if(roz_pod_D[a] < roz_pod_D[i] && roz_pod_D[a] > n/2)czy_centroid = false;
    }
    if(czy_centroid)centr_D.push_back(i);
  }

  /*for(int i = 0; i < centr_D.size(); i++)
  {
      cout << "centroidy w D: " << centr_D[i] << "\n";
  }*/


  if(centr_D.size() != centr_T.size())
  {
    Ans = "NO";
  }

  //if(centr_T.size() > 2) cout << "znaleziono ponad dwa centroidy!!!";

  if(centr_T.size() == 2)
  {
    n++;
    T[n].push_back(centr_T[0]);
    T[n].push_back(centr_T[1]);
    //T[centr_T[0]].push_back(n);
    //T[centr_T[1]].push_back(n);
    for(int i = 0; i < T[centr_T[0]].size(); i++)
    {
        if (centr_T[1] == T[centr_T[0]][i]) T[centr_T[0]][i] = n;
    }
    for(int i = 0; i < T[centr_T[1]].size(); i++)
    {
        if (centr_T[0] == T[centr_T[1]][i]) T[centr_T[1]][i] = n;
    }

    cenT = n;
  }
  else cenT = centr_T[0];

  //if(centr_D.size() > 2) cout << "znaleziono ponad dwa centroidy!!!";

  if(centr_D.size() == 2)
  {
    D[n].push_back(centr_D[0]);
    D[n].push_back(centr_D[1]);
    //D[centr_D[0]].push_back(n);
    //D[centr_D[1]].push_back(n);
    for(int i = 0; i < D[centr_D[0]].size(); i++)
    {
        if (centr_D[1] == D[centr_D[0]][i]) D[centr_D[0]][i] = n ;
    }
    for(int i = 0; i < D[centr_D[1]].size(); i++)
    {
        if (centr_D[0] == D[centr_D[1]][i]) D[centr_D[1]][i] = n ;
    }
    cenD = n;
  }
  else cenD = centr_D[0];


}

int DFS3(int v, int p)
{
    pair< pair<int,int>, int> wynik = make_pair(make_pair(0,0),0);
    for(int i = 0; i < T[v].size(); i++)
    {
        int a = T[v][i];
        if(a!=p)
        {
            int wa = DFS3(a,v);
            wynik.f.f = wynik.f.f^wa;
            wynik.f.s += wa*wa;
            wynik.s += wa*wa*wa;
            wynik.f.f = wynik.f.f%MODULO;
            wynik.f.s = wynik.f.s%MODULO;
            wynik.s = wynik.s%MODULO;
        }
    }
    if(M.find(wynik) == M.end())
    {
        M[wynik] = rodzaje;
        rodzaje++;
    }
    return M[wynik];
}


int DFS4(int v, int p)
{
    pair< pair<int,int>, int> wynik = make_pair(make_pair(0,0),0);
    for(int i = 0; i < D[v].size(); i++)
    {
        int a = D[v][i];
        if(a!=p)
        {
            int wa = DFS4(a,v);
            wynik.f.f = wynik.f.f^wa;
            wynik.f.s += wa*wa;
            wynik.s += wa*wa*wa;
            wynik.f.f = wynik.f.f%MODULO;
            wynik.f.s = wynik.f.s%MODULO;
            wynik.s = wynik.s%MODULO;
        }
    }
    if(M.find(wynik) == M.end())
    {
        M[wynik] = rodzaje;
        rodzaje++;
    }
    return M[wynik];
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  int liczba_testow;
  cin >> liczba_testow;
  for(int id_testu = 0; id_testu < liczba_testow; id_testu++)
  {
    cin >> n;
    Ans = "YES";
    for(int i = 0; i < n-1; i++)
    {
      int a,b;
      cin >> a >> b;
      T[a].push_back(b);
      T[b].push_back(a);
    }

    for(int i = 0; i < n-1; i++)
    {
      int a,b;
      cin >> a >> b;
      D[a].push_back(b);
      D[b].push_back(a);
    }
    find_centroid();
    //cout << "Centroid w pierwszym drzewie: " << cenT << " Centroid w drugim:  " << cenD << "\n";
    if(Ans == "YES")
    {
        vector<int> drzewa_T, drzewa_D;
        for(int i = 0; i < T[cenT].size(); i++)
        {
            drzewa_T.push_back(DFS3(T[cenT][i], cenT));
        }

        for(int i = 0; i < D[cenD].size(); i++)
        {
            drzewa_D.push_back(DFS4(D[cenD][i], cenD));
        }

        sort(drzewa_T.begin(), drzewa_T.end());
        sort(drzewa_D.begin(), drzewa_D.end());
        if(drzewa_D.size() != drzewa_T.size())Ans = "NO";
        if(Ans == "YES")
        {
            for(int i = 0; i < drzewa_T.size(); i++)
            {
                if(drzewa_D[i] != drzewa_T[i])Ans = "NO";
            }
        }
        drzewa_D.clear();
        drzewa_T.clear();
    }
    cout << Ans << "\n";
    for(int i = 0; i <= n; i++)
    {
        T[i].clear();
        D[i].clear();
        roz_pod_D[i] = 0;
        roz_pod_T[i] = 0;
    }
    rodzaje = 1;
    M.clear();
  }
  return 0;
}
