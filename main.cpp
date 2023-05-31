#include <iostream>
#include <stdio.h>
#include <vector>
#include <locale.h>
#include <unordered_map>
#include <queue>

using namespace std;
template<typename Vertex, typename Distance >

class Graph
{
public:
    struct Edge
    {
        Vertex v1, v2;
        Distance distance;
    };
private:
   
    unordered_map<Vertex, vector<Edge>> dict;

public:
    Graph(const vector<Vertex>& v) {  for(auto& elem : v)add_vertex(elem);}
    bool has_vertex(const Vertex& v) const
    {
        for (auto& elem : dict) if (v == elem.first) return true;
        return false;
    }
    void add_vertex(const Vertex& v)
    {
        if (has_vertex(v)) cout << "\nТакая вершина уже существует\n";
        else
            dict.insert({ v, {} });
    }
    bool remove_vertex(const Vertex& v)
    {
        if (!has_vertex(v))
        {
            cout << "\nТакой вершины не существует\n";
            return false;
        }
        dict.erase(v);
        return true;
        
    }
    vector<Vertex> vertices() const//возвращаем список вершин
    {
        vector<Vertex> tmp;
        for (auto& elem : dict) tmp.push_back(elem.first);
        return tmp;
    }
    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& v1, const Vertex& v2, const Distance& distance)
    {
        if (!has_vertex(v1)) add_vertex(v1); 
        if (!has_vertex(v2)) add_vertex(v2); 
        dict.find(v1)->second.push_back({ v1, v2,distance });
    }
    bool remove_edge(const Vertex& v1, const Vertex& v2)
    {
        if (!has_vertex(v1) || !has_vertex(v2)) return false;
        auto& edges = dict.find(v1)->second;
        auto it = edges.begin();
        while (it != edges.end()) {
            if (it->v1 == v1 and it->v2== v2)
            {
                it = edges.erase(it);
            }
            else ++it;
        }
        return true;
    }
    bool remove_edge(const Edge& edge)
    {
        if (!has_edge(edge)) return false;
        auto& edges = dict.find(edge.v1)->second;
        auto it = edges.begin();
        while (it != edges.end()) {
            if (it->v1 == edge.v1 and it->v2 == edge.v2 and it->distance == edge.distance)
            {
                it = edges.erase(it);
            }
            else ++it;
        }
        return true;
    }
    //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& edge)
    {
        for (auto& elem : dict.find(edge.v1)->second) if (elem.v1 == edge.v1 && elem.v2 == edge.v2 && elem.distance ==edge.distance)  return true;
        return false;
    }
     //получение всех ребер, выходящих из вершины
    vector<Edge> edges(const Vertex& v1) const
    {
        if (!has_vertex(v1)) {
            cout<<"Нет такой вершины";
                        
        }
        // auto i = dict.find(v1)->second;
        return(dict.find(v1)->second);
    }
    size_t order() const {return dict.size();}//порядок
    size_t degree(const Vertex& v) const
    {
        if (!has_vertex(v)) cout<<"Нет такой вершины!";
        return edges(v).size();
    }//степень
    
    //поиск кратчайшего пути
    //std::vector<Edge> 
    void shortest_path(const Vertex& v1, const Vertex& v2) const
    {
        if (!has_vertex(v1) || !has_vertex(v2)) throw std::invalid_argument("Вершина не найдена!");
        vector<Edge> resullt;
        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Edge> ancestors;
        vector<Edge> parent;
        parent.push_back({ v1,v1,0 });
        //cout << parent[0].out << parent[0].in << parent[0].distance;
        for (auto& item : dict)
        {
            distance[item.first] = 100;
            distance[v1] = 0;
        }

        for (size_t i = 0; i < order() - 1; i++)
        {
            for (const auto& pair : dict)
            {
                for (const auto& edge : pair.second)
                {
                    if (distance[edge.v1] + edge.distance < distance[edge.v1])
                    {
                        distance[edge.v2] = distance[edge.v1] + edge.distance;
                        ancestors[edge.v2] = edge;
                    }
                }
            }
        }
        cout << distance[v2];
        
    }
    void print_vertex()
    {
        cout << "Вершины" <<"\n";
        for (auto& elem : dict )cout <<elem.first <<" ";
        cout << endl;
    }
    void print_graph()
    {
        cout << "Вершина --> (Куда, расстояние)" << "\n";
        for (auto& elem : dict)
        {
            cout << elem.first << " --> ";// << i.second[0].in;
            for (auto& j : elem.second)
            {
                if (j.distance!=0)
                {
                    cout << "(" << j.v2 << "," << j.distance << ")";
                }
                else
                {
                    cout << "(" << j.v2 << ",None)";
                }
            }
            cout << "\n";
        }
        cout << endl;
    }
   
    //обход
  //-----------------  std::vector<Vertex>  walk(const Vertex& start_vertex)const; 
};




int main()
{
    setlocale(LC_ALL, "Rus");
    Graph<int,int> graph({ 1,4,6,3,2,7 });

    graph.add_vertex(1);
    graph.add_vertex(3);
    graph.add_vertex(7);
    graph.add_vertex(7);
    graph.print_graph();
    graph.add_edge(1, 4, 5);
    graph.add_edge(1, 3, 1);
    graph.add_edge(6, 4, 1);
    graph.add_edge(3, 6, 4);

    //graph.remove_edge(3, 2);
    //graph.remove_edge(1,4,5);
    graph.add_edge(1, 7, 5);
    graph.add_edge(1, 3, 6);
    graph.add_edge(4, 2, 4);
    graph.add_edge(6, 6, 6);

    graph.print_vertex();
    graph.print_graph();
    // if (!graph.has_edge(2, 3)) cout << "p,,";
    // if (!graph.has_edge(1, 4)) cout << "p,,";
    // if (graph.has_edge(2, 7)) cout << "p,,";
    // if (graph.has_edge(3, 2)) cout << "p,,";
    auto i = graph.edges(1);
   // graph.walk(1);
    cout << "(" << 1 << "--->  ";
    // for (auto& j : i)
    // {
    //     cout << j.v2;
    // }
    cout << ")";
    graph.shortest_path(1, 4);
        // построить Graph

        //graph.print_adjacency_matrix();
    return 0;
};
//void print_adjacency_matrix()
 //{
 //    for (int i = 0; i < adjlist.size(); i++)
 //    {
 //        cout << i << " ---> ";// вершину и список смежных с ней
 //        for (int v : adjlist[i]) {
 //            cout << v << " ";
 //        }
 //        cout << endl;
 //    }
 //}
    //bool contain_vertex(int number_of_vertex)
    //{
    //    for (auto& i : vertex)
    //    {
    //        if (i == number_of_vertex) return true;
    //    }
    //    return false;
    //}
    //void add_vertex(const Vertex& v)
    //{
    //    if (!contain_vertex(v))vertex.push_back(v);
    //}

