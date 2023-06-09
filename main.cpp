#include <iostream>
#include <conio.h>
#include <vector>
#include <locale.h>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <windows.h>
#include <limits>

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
            return {};
        }
        else  return(dict.find(v1)->second);
    }
    size_t order() const { return dict.size(); }//порядок
    size_t degree(const Vertex& v) const
    {
        if (!has_vertex(v)) cout << "Нет такой вершины!";
        return edges(v).size();
    }//степень

    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& v1, const Vertex& v2, Distance* dist = nullptr) const {
        if (!has_vertex(v1) || !has_vertex(v2))
        {
            cout << "Вершина не найдена!";
            _getch();
            return {};
           
        }
        else {
            #undef max
           
            std::vector<Edge> result;
            std::unordered_map<Vertex, Distance> distance;
            std::unordered_map<Vertex, Edge> ancestors;
            for (auto& item : dict) distance[item.first] = std::numeric_limits<Distance>::max();
            distance[v1] = 0;
            for (size_t i = 0; i < order() - 1; ++i) {
                for (const auto& pair : dict) {
                    for (const auto& edge : pair.second) {
                        if (distance[edge.v1] + edge.distance < distance[edge.v2]) {
                            distance[edge.v2] = distance[edge.v1] + edge.distance;
                            ancestors[edge.v2] = edge;
                        }
                    }
                }
            }

            for (const auto& pair : dict) {
                for (const auto& edge : pair.second) {
                    if (distance[edge.v1] + edge.distance < distance[edge.v2])
                    {
                        cout << "Граф имеет отрицательный цикл";
                        _getch();
                        return {};
                    }
                }
            
            }

            if (distance[v2] == std::numeric_limits<Distance>::max()) {
                cout << "\nНевозожно связать вершины\n";
                _getch();
                return {};
            }
            
            Vertex current = v2; // текущая вершина - конечная
            while (current !=v1) {
                result.push_back(ancestors[current]);
                current = ancestors[current].v1;
            }

            std::reverse(result.begin(), result.end());
            cout << "Результат:\n";
            for (const auto& elem : result) cout << elem.v1 << " ";
            _getch();
            return result;

        }
    }
    void print_vertex()
    {
        cout << "Вершины" << "\n";
        for (auto& elem : dict)cout << elem.first << " ";
        cout << endl;
    }
    void print_graph()
    {
        cout << "\nV1   -->   V2" << "\n";
        cout << "   вес   \n";
        bool entered = false;
        for (auto& elem : dict)
        {
            for (auto& tmp : elem.second)
            {
                entered = true;
                cout << "\n" << elem.first << " --> ";
                cout << tmp.v2<<"\n";
                cout << "   " << tmp.distance << "\n";

            }
            if (!entered)  cout << "\n" << elem.first << " -->None ";
        }
    }
    void task()
    {
        vector<Vertex> result;

        double maximum_of_average_distances = 0;
        for (const auto& elem : dict)
        {
            double tmp = 0;
            int size_vector = elem.second.size();
            for (const auto& edge : elem.second)
            {
                tmp += edge.distance;
            }
            tmp /= size_vector;
            if (tmp > maximum_of_average_distances)
            {
                if (tmp == maximum_of_average_distances) result.push_back(elem.first);
                else {
                    result.clear();
                    result.push_back(elem.first);
                }
                maximum_of_average_distances = tmp;
            }

        }
        cout << "Максимально среднее удаление наблюдается у вершины ";
        for (auto& i : result) cout << i << ' ';

    }
    //обход
    bool in_vector(vector<Vertex> vizited, const Vertex tmp )const
    {
        for (auto& elem : vizited) if (elem == tmp) return true;
        return false;
     }

     vector<Vertex> help_walk(vector<Vertex> vizited,const Vertex& v)const
     {

        vizited.push_back(v);
        for (auto& elem : dict.find(v)->second)  if (!in_vector(vizited,elem.v2)) vizited = help_walk(vizited, elem.v2);
        return vizited;
     }

     vector<Vertex> walk(const Vertex& start_vertex)
     {
         if (has_vertex(start_vertex))
         {
             vector<Vertex> vizited;
             return help_walk(vizited, start_vertex);
         }
         else cout << "Нет такой вершины";
         return {};
     }


};



template<typename Vertex, typename Distance >
int main2()
{
    Vertex tmp1;
    int tmp;
    vector <Vertex> chose_vector;
    setlocale(LC_ALL, "Rus");
    cout << "Ведите первую вершину ";
    cin >> tmp;
    chose_vector.push_back(tmp);

    Graph<Vertex, Distance> graph(chose_vector);
    bool flag = true;
    Vertex v1, v2;
    do {
        system("CLS");
        cout << "\nНаш граф:\n";
        graph.print_graph();
        cout << "\nВыберите: \n1)Проверить существование вершины\n2)Добавить вершину\n3)Удалить вершину\n4)Вернуть список вершин\n5)Добавить ребро\n6)Удалить ребро\n7)Узнать степень вершины\n8)Доп задача\n9)Поиск кратчайшего пути\n10)Обход в глубину\n11)Автозаполнение\n12)Выход";
        cin >> tmp;
        switch (tmp)
        {
        case 1:
            cout << "Ведите вершину ";
            cin >> tmp1;
            if (graph.has_vertex(tmp1)) cout << "Вершина есть";
            else cout << "Вершины нет";
            _getch();
            break;
        case 2:
            cout << "Ведите вершину ";
            cin >> tmp1;
            graph.add_vertex(tmp1);
            _getch();
            break;
        case 3:
            cout << "Ведите вершину ";
            cin >> tmp1;
            if (graph.remove_vertex(tmp1)) cout << "\nУспешно\n";
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
            cin >> tmp1;
            if (graph.degree(tmp1)) cout << graph.degree(tmp1);
            _getch();
            break;
        case 8:
            graph.task();
            _getch();
            break;
        case 9:
            cout << "Введите первую вершину: ";
            cin >> v1;
            cout << "Введите вторую вершину: ";
            cin >> v2;
            graph.shortest_path(v1, v2);
            _getch();
            break;
        case 10:
            cout << "Ведите вершину ";
            cin >> tmp1;
            chose_vector=graph.walk(tmp1);
            cout << "\n";
            for (auto& elem : chose_vector) cout << elem << ' ';
            _getch();
            cout << "\n";
            break;
        case 11:
            graph.add_edge(1, 2, 1);
            graph.add_edge(2, 3, 1);
            graph.add_edge(1, 3, 16);
            graph.add_edge(1, 4, 12);
            graph.add_edge(1, 5, 5);
            graph.add_edge(5, 6, 7);
            graph.add_edge(5, 7, 8);
            break;
        case 12:
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
   

   
    return 0;
};

int main()
{
    int tmp;
    cout << "Выберите режим работы:\n1)<int int>\n2)<double double>\n3)<float float>\n";
    cin >> tmp;
    switch (tmp)
    {
    case 1:
        main2<int,int>();
        break;
    case 2:
        main2<double ,double>();
        break;
    case 3:
        main2<float,float>();
        break;
    default:
        cout << "\nНет такого варианта\n";
        _getch();
        system("CLS");
        break;
    }
}