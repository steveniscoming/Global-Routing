#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include <climits>
#include <algorithm>
#include<cmath>
#include <fstream> 
using namespace std;

struct edge{
    int des_id;
    double weight;
    double demand;
};


struct node {
    double distance;
    int node_id;
    int parent;
    //operator overload for the use of priority queue
    bool operator>(const node &object) const {
        if (this->distance == object.distance) {
            return this->node_id < object.node_id;
        } else {
            return this->distance > object.distance;
        }
    }
};

bool compareNodes(const node& a, const node& b) {
    return a.node_id < b.node_id;
}

class graph{
    public:
    int v_number;
    int capacity;
    int net; 
    vector<vector<edge>> edges;
    //member function add the edge
    void add_edge(int source,int destination){
        edges[source].push_back({destination,1,0});
    };
    //member function print all edges
    void print_graph(){
        for(int i=0;i<edges.size();i++){
        cout<<"the node is "<<i<<" having the connected node"<<endl;
        for(int j=0;j<edges[i].size();j++){
            cout<<"node :"<<edges[i][j].des_id<<" weight : "<<edges[i][j].weight<<endl;
        }
        cout<<endl;
        }
    };
    //constructor
    graph (int size,int cap, int n){
        v_number=size*size;
        capacity=cap;
        net=n;
        edges.resize(size*size);
        for(int i=0;i<size*size;i++){
            if((i+1)%size!=0){
                add_edge(i,i+1);
            }
            if(i+size<size*size){
                add_edge(i,i+size);
            }
            if(i-size>=0){
                add_edge(i,i-size);
            }
            if(i%size!=0){
                add_edge(i,i-1);
            }
        }
    };
    //member function
    void Dijkstra(vector<node> &path, int source){
        priority_queue<node,vector<node>,greater<node>> pq;
        unordered_map<int,bool> visited;
        //to record the current relaxed distance
        vector<double> record;
        for(int i=0;i<v_number;i++){
            record.push_back(INT_MAX);
        }

        //put source the nodes int to the priority queue
        pq.push({0,source,-1});
        while(!pq.empty()){
            //pop the top node to A
            node A = pq.top();
            pq.pop();
            //check if it has been visited
            if(visited[A.node_id]==true){
                continue;
            }
            visited[A.node_id]=true;
            path.push_back(A);
            //relax the edge
            for(auto x:edges[A.node_id]){
                if(A.distance+x.weight<record[x.des_id]){
                    record[x.des_id]=A.distance+x.weight;
                    pq.push({A.distance+x.weight,x.des_id,A.node_id});
                }
            }
        }
            
    };
    //use recursive helper for find the net
    void find_the_Net_helper(const vector<node> &path, node iter,vector<int> &net){
        if(iter.parent==-1){
            net.push_back(iter.node_id);
        }
        else{
            net.push_back(iter.node_id);
            iter=path[iter.parent];
            find_the_Net_helper(path,iter,net);
        }

    };
    //member function find the Net and add the weight
    vector<pair<int,int>> find_the_net( pair<int,int> src, pair<int,int> dest){
        //convert (x,y) into node_id 
        int source=src.first+src.second*sqrt(v_number);
        int destination=dest.first+dest.second*sqrt(v_number);
        //perform Dijksra
        vector<node> path;
        Dijkstra(path,destination);
        //sort the path 
        sort(path.begin(), path.end(), compareNodes);
        //find the source node
        node source_node=path[source];
        //use the helper to find the Net sequential
        vector<int> net;
        find_the_Net_helper(path,source_node,net);
        //convert to net to net_xy and addthe weight
        int step =net.size();
        vector<pair<int,int>> net_xy;
        for(int i=0;i<step;i++){
            int x=net[i]%int(sqrt(v_number));
            int y=net[i]/sqrt(v_number);

            if(i+1<step){
                for(int k=0;k<edges[net[i]].size();k++){
                    if(edges[net[i]][k].des_id==net[i+1]){
                        edges[net[i]][k].demand++;
                        edges[net[i]][k].weight=static_cast<double>(pow(2,(edges[net[i]][k].demand/capacity)));                     
                        break;
                    }
                }
                for(int k=0;k<edges[net[i+1]].size();k++){
                    if(edges[net[i+1]][k].des_id==net[i]){
                        edges[net[i+1]][k].demand++;
                        edges[net[i+1]][k].weight=static_cast<double>(pow(2,(edges[net[i+1]][k].demand/capacity)));                           
                        break;
                    }
                }
            }
            net_xy.push_back({x,y});
        }
        return net_xy;

    }

};
int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Unable to open input file: " << argv[1] << std::endl;
        return 1;
    }


    std::ofstream outputFile(argv[2]);
    if (!outputFile) {
        std::cerr << "Unable to open output file: " << argv[2] << std::endl;
        inputFile.close();
        return 1;
    }

    string temp;
    int size;
    int net;
    int cap;
    inputFile >> temp; 
    inputFile >> size;  
    inputFile >> temp; 
    inputFile >> temp; 
    inputFile >> cap;  
    inputFile >> temp; 
    inputFile >> temp; 
    inputFile >> net;  

    graph g(size,cap,net);
    for(int i=0;i<net;i++){
        int id;
        pair<int,int> s;
        pair<int,int> d;
        inputFile>>id>>s.first>>s.second>>d.first>>d.second;
        vector<pair<int,int>> steven=g.find_the_net(s,d);

        outputFile<<id<<" "<<steven.size()-1<<endl;
        for(int j=0;j<steven.size()-1;j++){
            outputFile<<steven[j].first<<" "<<steven[j].second<<" ";
            outputFile<<steven[j+1].first<<" "<<steven[j+1].second<<endl;
        }
    }
    inputFile.close(); 
    outputFile.close();
}

