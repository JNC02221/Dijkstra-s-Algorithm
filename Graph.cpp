//These are the files that we included in this code
#include "Graph.hpp"
#include <limits>

bool check(std::list<std::string> x, std::string str) //This is the code that will check to make sure that the vertex has not yet been checked by the loop for finding the shortest path
{
    bool flag = true;
    for(int i=0;i<x.size();i++)
    {
        std::string temp = x.front();
        x.pop_front();
        if(temp == str)
        {
            flag = false;
        }
        x.push_back(temp);
    }
    return flag;
}



Graph::Graph() //This is the constructor for a graph
{
    std::map<std::string,Vertex> Vertexis;
}



void Graph::removeEdge(std::string label1, std::string label2) //This is the function that will remove an edge
{
    //These are all of the checks needed to be done before the edge can be removed
    bool flag, flag2 = false;
    for( auto x : Vertexis)
    {
        if(x.first == label1)
        {
            flag = true;
        }
        if(x.first == label2)
        {
            flag2 = true;
        }
    }
    for(int i=0;i<Vertexis[label1].Routes.size();i++)
    {
        Edge temp = Vertexis[label1].Routes.front();
        Vertexis[label1].Routes.pop_front();
        if(temp.verx2 == label2)
        {
            flag = true;
            flag2 = true;
        }
        Vertexis[label1].Routes.push_back(temp);
    }
/////////////////////////////////////////////////////////
//This is the actual code that will remove an edge
/////////////////////////////////////////////////////////
    Edge temp;
    if(flag && flag2)
    {
        for(__SIZE_TYPE__ i=0;i<Vertexis[label1].Routes.size();i++)
        {
            temp = Vertexis[label1].Routes.front();
            Vertexis[label1].Routes.pop_front();
            if((temp.verx1 == label1 || temp.verx2 == label1)&&(temp.verx1 == label2 || temp.verx2 ==label2))
            {
                break;
            }
            else
            {
            Vertexis[label1].Routes.push_back(temp);
            }
        }
        for(__SIZE_TYPE__ i=0;i<Vertexis[label2].Routes.size();i++)
        {
            temp = Vertexis[label2].Routes.front();
            Vertexis[label2].Routes.pop_front();
            if((temp.verx1 == label1 || temp.verx2 == label1)&&(temp.verx1 == label2 || temp.verx2 ==label2))
            {
                break;
            }
            else
            {
            Vertexis[label2].Routes.push_back(temp);
            }
        }
    
    }
}






void Graph::addVertex(std::string label) //This is the function that will add a vertex
{
    //This is the required checks needed to be done before the vertex can be added
    bool flag = true;
    for(auto x : Vertexis)
    {
        if(x.first == label)
        {
            flag = false;
        }
    }

    ////////////////////////
    //This is the actual code to add a vertex
    ////////////////////////
    if(flag)
    {
        Vertex temp;
        temp.lable = label;
        Vertexis[label] = temp; 
    }
}



void Graph::removeVertex(std::string label) //This is the function that will remove a vertex
{
    std::string temp;
    __SIZE_TYPE__ size = Vertexis[label].Routes.size();
    Edge temp2;
    for (__SIZE_TYPE__ i=0;i<size;i++)
    {
        temp = Vertexis[label].Routes.front().verx2;
        removeEdge(label,temp);
    }

    Vertexis.erase(label);

}



void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) //This is the function that will add an edge
{
    //These are all of the checks that must be done inorder to add the edge
    bool flag, flag2 = false;
    for(auto x : Vertexis)
    {
        if(x.first == label1)
        {
            flag = true;
        }
        if(x.first == label2)
        {
            flag2 = true;
        }
    }
    if(label1 != label2)
    {
        flag = true;
        flag2 = true;
    }
    for(int i=0;i<Vertexis[label1].Routes.size();i++)
    {
        Edge temp = Vertexis[label1].Routes.front();
        Vertexis[label1].Routes.pop_front();
        if(!(temp.verx2 == label2))
        {
            flag = true;
            flag2 = true;
        }
        Vertexis[label1].Routes.push_back(temp);
    }

////////////////////////////////
//This is the actual code that will add an edge
////////////////////////////////
    if(flag && flag2)
    {
        Edge temp;
        temp.weight = weight;
        temp.verx1 = label1;
        temp.verx2 = label2;
        Vertexis[label1].Routes.push_back(temp);
        temp.verx1 = label2;
        temp.verx2 = label1;
        Vertexis[label2].Routes.push_back(temp);
    }
}



unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) //This is the function that will find and return the shortest path to a node from a given starting node
{
    //These are all of the variables and maps/list that we needed for this code
    unsigned long dist = 0;
    std::string tempLabel;
    unsigned long min = std::numeric_limits<unsigned long>::max();
    bool flag;
    std::map<std::string, unsigned long> distMap;
    std::map<std::string, std::string> route;
    std::string it = startLabel;
    std::list<std::string> done;
    
    for (int i=0; i<Vertexis.size(); i++) //This is the first for loop that will make sure that every vertex is hit and made sure that it is at the lowest posible path
    {
        
        flag = true;
        for(int j=0; j<Vertexis[it].Routes.size();j++) //This is the next for loop that will go through the edges list to check all of the edges connected to the vertex being checked 
        {
            Edge temp = Vertexis[it].Routes.front();
            Vertexis[it].Routes.pop_front();
            
            if(distMap[temp.verx2] > (temp.weight+ dist) || (distMap[temp.verx2] == 0)) //Here we check to see if the current value saved in the map is reallly the lowest one and if not we set it to the real one
            {
                distMap[temp.verx2] = temp.weight + dist;
                route[temp.verx2] = temp.verx1;
            }
            if(((temp.weight + dist) < min))
            {
                min = temp.weight + dist;
                tempLabel = temp.verx2;
                flag = false;
            }
            Vertexis[it].Routes.push_back(temp);
        }
        if(flag)
        {
            for(auto k : distMap)
            {
                if(it == tempLabel)
                {
                    done.push_back(tempLabel);
                    tempLabel = k.first;
                    min = std::numeric_limits<unsigned long>::max();
                    dist = 0;
                }
                if((k.second < min ) && (k.first != it) && (check(done, k.first)))
                {
                    tempLabel = k.first;
                    min = k.second + dist;
                }
            }
        }
        dist = distMap[tempLabel];
        it = tempLabel;
        
    }
    std::string test =route[endLabel];
    while (test != startLabel) //This is the loop that puts the right path into the path parameter that is passed through
    {
        path.insert(path.begin(), test);
        test = route[test];
    }
    path.insert(path.begin(),startLabel);
    path.insert(path.end(), endLabel);
    done.clear();
    return distMap[endLabel];
}



