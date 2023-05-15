#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip>      // std::setprecision
#include <algorithm>

using namespace std;
using ll = long long;
const ll inf = 1e18;

vector<vector<double>> matrizAdj;
vector<tuple<int,int>> verticeACoord;

int C,N,R,W,U,V;

double dist(tuple<int,int> p1, tuple<int,int> p2){
    double dist = sqrt(pow(get<0>(p1)-get<0>(p2),2)+pow(get<1>(p1)-get<1>(p2),2));
    return dist;
}

vector<tuple<int,int,double>> prim_n2(){
    vector<tuple<int,int,double>> res;
    vector<bool> es_rojo(N+1,false); es_rojo[1] = true;
    vector<int> rojo_mas_cercano(N+1,1);
    for(int it = 0; it < N-1; it++){
        //agregar a la arista violeta mas barata
        int agrego = 1;
        while(es_rojo[agrego]) agrego++;
        for(int v = agrego+1; v < N+1; v++)
            if(!es_rojo[v] and matrizAdj[v][rojo_mas_cercano[v]] < matrizAdj[agrego][rojo_mas_cercano[agrego]])
                agrego = v;

        //pintar de rojo su extremo azul
        es_rojo[agrego] = true;

        //actualizar info de rojo_mas_cercano
        for(int v = 1; v < N+1; v++)
            if(!es_rojo[v] and matrizAdj[v][agrego] < matrizAdj[v][rojo_mas_cercano[v]]) rojo_mas_cercano[v] = agrego;
        res.push_back(make_tuple(agrego,rojo_mas_cercano[agrego],matrizAdj[agrego][rojo_mas_cercano[agrego]]));
    }
    return res;
}
bool sortby3(const tuple<int, int, double>& a,
               const tuple<int, int, double>& b)
{
    return (get<2>(a) > get<2>(b));
}


int main(){
    cin >> C;
    for(int it=0;it<C;it++){
        cin >> N >> R >> W >> U >> V;
        verticeACoord = vector<tuple<int,int>>(N+1, make_tuple(-1,-1));
        matrizAdj = vector<vector<double>>(N+1,vector<double>(N+1,inf));
        for(int it2=0;it2<N;it2++){
            int x,y;
            cin >> x >> y;
            verticeACoord[it2+1]= make_tuple(x,y);
        }
        for(int v=1;v<N+1;v++){
            tuple<int,int> coord = verticeACoord[v];
            for(int u=v+1;u<N+1;u++){
                double distancia = dist(coord,verticeACoord[u]);
                if(distancia <= R){
                    double precio = U * distancia;
                    matrizAdj[v][u]=precio;
                    matrizAdj[u][v]=precio;
                }else{
                    double precio = V * distancia;
                    matrizAdj[v][u]=precio;
                    matrizAdj[u][v]=precio;
                }
            }
        }
        vector<tuple<int,int,double>> res1 = prim_n2();

        //Idea: sacar las W-1 aristas mas caras
        sort(res1.begin(), res1.end(), sortby3);
        for(int i=0;i<W-1;i++){
            get<2>(res1[i])=0;
        }

        double sumaUTP = 0;
        double sumaF   = 0;
        for(auto elem : res1){
            double distancia = dist(verticeACoord[get<0>(elem)],verticeACoord[get<1>(elem)]);
            if(distancia <= R){
                sumaUTP +=get<2>(elem);
            }else{
                sumaF += get<2>(elem);
            }
        }

        cout << fixed << setprecision(3) << "Caso #" << it+1 << ": " << sumaUTP << " " << sumaF << endl;
    }
    return 0;
}