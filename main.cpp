#include <iostream>
#include <conio.h>
#include <vector>
#include <locale.h>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <windows.h>

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
    Graph(const vector<Vertex>& v) { for (auto& elem : v)add_vertex(elem); }
    bool has_vertex(const Vertex& v) const
    {
        for (auto& elem : dict) if (v == elem.first) return true;
        return false;
    }
    void add_vertex(const Vertex& v)
    {
        if (has_vertex(v)) cout << "\nТакая вершина уже существует\n";
        else {
            dict.insert({ v, {} });
            cout << "\nУспешно\n";
        }
    }
    bool remove_vertex(const Vertex& v)
    {
        if (!has_vertex(v))
        {
            cout << "\nТакой вершины не существует\n";
            return false;
        }
        for (auto& elem : dict) remove_edge(elem.first, v);
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
            if (it->v1 == v1 and it->v2 == v2)
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
    bool has_edge(const Edge& edge)
    {
        for (auto& elem : dict.find(edge.v1)->second) if (elem.v1 == edge.v1 && elem.v2 == edge.v2 && elem.distance == edge.distance)  return true;
        return false;
    }
    //получение всех ребер, выходящих из вершины
    vector<Edge> edges(const Vertex& v1) const
    {
        if (!has_vertex(v1)) {
            cout << "Нет такой вершины";

        }
       
        return(dict.find(v1)->second);
    }
    size_t order() const { return dict.size(); }//порядок
    size_t degree(const Vertex& v) const
    {
        if (!has_vertex(v)) cout << "Нет такой вершины!";
        return edges(v).size();
    }//степень

    //поиск кратчайшего пути
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
        cout << "Вершины" << "\n";
        for (auto& elem : dict)cout << elem.first << " ";
        cout << endl;
    }
    void print_graph()
    {
        cout << "Вершина --> (Куда, расстояние)" << "\n";
        for (auto& elem : dict)
        {
            cout << elem.first << " --> ";
            for (auto& tmp : elem.second)
            {
                if (tmp.distance != 0)
                {
                    cout << "(" << tmp.v2 << "," << tmp.distance << ")";
                }
                else
                {
                    cout << "(" << tmp.v2 << ",None)";
                }
            }
            cout << "\n";
        }
        cout << endl;
    }
    void task()
    {
        vector<Vertex> result;

        double maximum_of_average_distances = 0;
        for (const auto& pair : dict)
        {
            double tmp = 0;
            int size_vector = pair.second.size();
            for (const auto& edge : pair.second)
            {
                tmp += edge.distance;
            }
            tmp /= size_vector;
            if (tmp > maximum_of_average_distances)
            {
                if (tmp == maximum_of_average_distances) result.push_back(pair.first);
                else {
                    result.clear();
                    result.push_back(pair.first);
                }
                maximum_of_average_distances = tmp;
            }

        }
        cout << "Максимально среднее удаление наблюдается у  -->";
        for (auto& i : result) cout << i << ' ';

    }
    //обход
     
     vector<Vertex> help_walk(vector<Vortex> vizited,const Vertex& v)const
     {
        vizited.push_back(v);
         for (auto & elem :dict.find(v)->second) if()


        return vizited;
     }
     std::vector<Vertex>  walk(const Vertex& start_vertex)const; 
 // void DFS(const Vertex& start_vertex) 
 {  
            vector<Vertex> vizited;

            visited[start_vertex] = true;
            list<int> adjList = adjLists[start_vertex];

            cout << start_vertex << " ";

            list<int>::iterator i;
            for (i = adjList.begin(); i != adjList.end(); ++i)
                if (!visited[*i])
                DFS(*i);
}
};




int main()
{
    int tmp;
    vector <int> chose_vector;
    setlocale(LC_ALL, "Rus");
    cout << "Ведите первую вершину ";
    cin >> tmp;
    chose_vector.push_back(tmp);

    Graph<int, int> graph(chose_vector);
    bool flag = true;
    int v1, v2;
    do {
        system("CLS");
        cout << "\nНаш граф:\n";
        graph.print_graph();
        cout << "\nВыберите: \n1)Проверить существование вершины\n2)Добавить вершину\n3)Удалить вершину:\n4)Вернуть список вершин\n5)Добавить ребро\n6)Удалить ребро\n7)Проверка существования рерба\n7)Узнать степень вершины\n8)Доп задача\n9)Поиск кратчайшего пути\n10_Обход в глубину\n11)Выход";
        cin >> tmp;
        switch (tmp)
        {
        case 1:
            cout << "Ведите вершину ";
            cin >> tmp;
            if (graph.has_vertex(tmp)) cout << "Вершина есть";
            else cout << "Вершины нет";
            _getch();
            break;
        case 2:
            cout << "Ведите вершину ";
            cin >> tmp;
            graph.add_vertex(tmp);
            _getch();
            break;
        case 3:
            cout << "Ведите вершину ";
            cin >> tmp;
            if (graph.remove_vertex(tmp)) cout << "\nУспешно\n";
            _getch();
            break;
        case 4:
            chose_vector = graph.vertices();
            cout << "\n";
            for (auto& elem : chose_vector) cout << elem << ' ';
            _getch();
            cout << "\n";
            break;
        case 5:
            cout << "Введите откуда будет исходить ребро: ";
            cin >> v1;
            cout << "Введите куда будет идти ребро: ";
            cin >> v2;
            cout << "Введите вес ребра: ";
            cin >> tmp;
            graph.add_edge(v1,v2,tmp);
            break;
        case 6:
            cout << "Введите первую вершину: ";
            cin >> v1;
            cout << "Введите вторую вершину: ";
            cin >> v2;
            graph.remove_edge(v1, v2);
            break;
        case 7:
            cout << "Ведите вершину ";
            cin >> tmp;
            if (graph.degree(tmp)) cout << graph.degree(tmp);
            _getch();
            break;
        case 8:
            graph.task();
            _getch();
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            flag = false;
            cout << "\nДо свидания\n";
            break;
        default:
            cout << "\nНет такого варианта\n";
            _getch();
            system("CLS");
            break;

        }
    } while (flag);
    graph.add_vertex(1);
    graph.add_vertex(3);
    graph.add_vertex(7);
    graph.add_vertex(7);
    graph.print_graph();
    graph.add_edge(1, 4, 5);
    graph.add_edge(1, 3, 1);
    graph.add_edge(6, 4, 1);
    graph.add_edge(3, 6, 4);

    graph.remove_edge(3, 2);
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
