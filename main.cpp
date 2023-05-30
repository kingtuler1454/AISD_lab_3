/*
Реализовать шаблонный класс, моделирющий ориентированный граф со следующим примерным интерфейсом (можно найти более эффективные решения):
В глубину
Беллмана-Форда
3
3. Пусть дан некоторый связный граф, в котором узлы – это травмпункты. Предположим,в преддверии зимы вы хотите улучшить покрытие города. Для этого вам необходимо понять
, какой травмпункт находится дальше всего от своих прямых соседей (т.е. средняя длина связанных с ним ребер максимальна). Напишите функцию, которая находит такой травмпункт.

*/

template<typename Vertex, typename Distance = double>
class Graph{
public:
    struct Edge{
        vertexType id1;
         vertexType id2;
        dist_type dist;
    Edge(vertexType id1_ = 0, vertexType id2_ = 0, dist_type distance_ = 0) : id1(id1_), id2(id2_), dist(distance_) {}

    }


    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    std::vector<Vertex> vertices() const;


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to,  
                                             const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge (const Edge& e); //c учетом расстояния в Edge
    
    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //порядок
    size_t degree() const; //степень


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from, 
                                        const Vertex& to) const; 
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const; 
};
