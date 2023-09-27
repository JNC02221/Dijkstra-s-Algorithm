//These are the files that I included in this file 
#include "GraphBase.hpp"
#include <list>
#include <map>





class Edge //This is a class for edge objects that will hold all the info needed in one edge
{
    public:
        std::string verx1;
        std::string verx2;
        int weight;

};


class Vertex //This is a class for a vertex object that will hold all the information the graph may need from the vertex
{
    public:
        std::string lable;
        int dist_from_start;
        std::list<Edge> Routes;

};



class Graph : public GraphBase //This is the class for the graph that holds the functions definition and a map of vertexes
{
    public:
        Graph();
        bool Check(std::string str);
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
        std::map<std::string,Vertex> Vertexis;
};
