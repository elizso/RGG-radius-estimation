#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <random>
#include <fstream>

using namespace std;

struct Point{
    double x, y;
    Point(double x, double y) : x(x), y(y) {};
};



struct Graph{
    vector<Point> points;
    vector<vector<int>> adj;
    void addPoint(Point p){
        points.push_back(p);  
    };

    Graph(const vector<Point>& points) : points(points), adj(points.size()) {}
};

double r_n(int n, double r){
    return r / sqrt(n);
}

bool equal_points(Point p1, Point p2){
    return (p1.x == p2.x) && (p1.y == p2.y);
}

int find_index(vector<Point> points, Point p){
    for (int i = 0; i < (int) points.size(); i++){
        if (equal_points(points[i], p)) return i;
    }
    return -1;
}



Graph construct_RGG(int n, double R){

    vector<Point> points = {};
    for (int i = 0; i < n; i++){
        double x = (double) rand() / RAND_MAX;
        double y = (double) rand() / RAND_MAX;
        points.push_back(Point(x, y));
    }

    Graph g(points);

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            double distance = sqrt(dx * dx + dy * dy);
            if (distance <= R){
                g.adj[i].push_back(j);
                g.adj[j].push_back(i);
            }
        }
    }

    return g;
}

int visited_BFS(Graph g){
    if (g.points.empty()) return 0;

    vector<bool> visited(g.points.size(), false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int count = 1;

    while (!q.empty()){
        int current = q.front();
        q.pop();
        
        for (int neighbour : g.adj[current]){
            if (!visited[neighbour]){
                visited[neighbour] = true;
                q.push(neighbour);
                count++;
            }
        }
    }
    return count;
}

double rc_estimate(int n, double preq, double epsilon_p, double epsilon_r){

    double r_min = 0;
    double r_max = sqrt(2) * sqrt(n); // max radius in unit square (diagonal length)
    const int trials = 300;

    while (true){

        double r_mid = (r_min + r_max) / 2;
        double p = 0;

        for (int i = 0; i < trials; i++){
            Graph g = construct_RGG(n, r_n(n, r_mid));
            int n_visited = visited_BFS(g);
            if (n_visited == n) p += 1;
        }

        p /= trials;
        if (abs(p - preq) <= epsilon_p || abs(r_max - r_min) <= epsilon_r)
            return r_mid;
        else if (p < preq)
            r_min = r_mid;
        else
            r_max = r_mid;
        
    }

    return -1;
}

int main(){

    // Defining epsilon for probability and radius
    double epsilon_p = 0.01;
    double epsilon_r = 0.001;

    ofstream file("output/rc_estimate_results.csv");
    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return 1;
    }

    file << "n,probability, r\n";
    double preq = 0.5;

    for (int n = 25; n <= 600; n += 25){
        double r_estimate = rc_estimate(n, preq, epsilon_p, epsilon_r);
        cout << "Estimated r for n = " << n << " when preq = " << preq << ": " << r_estimate << endl;
        file << n << "," << preq << "," << r_estimate << "\n";

    }
    file.close();

    return 0; 
}