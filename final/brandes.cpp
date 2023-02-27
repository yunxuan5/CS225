#include "brandes.h"

vector<double> brandes(const Graph & g) {
    int size = g.getSize();

    vector<double> BC(size, 0); // Betweenness centrality

    int progress = 0; // record progress

    // iterate through each vertex
    for (int s = 0; s < size; s++) {
        progress++;
        printProgress2((double)progress / 21048.0);
        vector<vector<int>> pred(size); // predecessor
        vector<double> delta(size, 0); // one-sided dependency
        vector<double> d(size, INF); // shortest distance, initialized to INF
        vector<int> sigma(size, 0);  // number of shortest distance

        sigma[s] = 1; // number of shortest path from s to s is 1
        d[s] = 0; // distance from s to s is 0

        std::set<std::pair<double, int>> q; // priority queue for Dijkstra
        std::stack<int> st; // for calculating delta
        q.insert(std::make_pair(0, s)); // enqueue the starting point

        /* Dijkstra SSSP algorithm */
        while (!q.empty()) {
            auto front = q.begin();
            int v = front->second; // current vertex
            q.erase(front); // pop
            st.push(v);
            for (int w : g.adjacentVertices(v)) {
                double weight = g.getWeight(v, w);
                if (d[w] > d[v] + weight) {
                    // change following 3 lines to 'q.erase(std::make_pair(d[w], w));' after test
                    q.erase(std::make_pair(d[w], w));
                    q.insert(std::make_pair(d[v] + weight, w));
                    d[w] = d[v] + weight;
                    pred[w].clear();
                    sigma[w] = 0;
                }
                // update sigma if d[w] is equal to d[v] + weight(v, w)
                if (d[w] == d[v] + weight) {
                    sigma[w] = sigma[w] + sigma[v];
                    pred[w].push_back(v);
                }
            }
        }
        /* End of Dijkstra SSSP algorithm */

        while (!st.empty()) {
            int w = st.top();            
            st.pop();
            for (int v : pred[w]) {
                delta[v] = delta[v] + (double)sigma[v] / (double)sigma[w] * (1.0 + delta[w]);
                
            }
            if (w != s) {
                BC[w] = BC[w] + delta[w];
            }
        }
    }

    // Normalize final result
    double BC_max = *std::max_element(BC.begin(), BC.end());
    double BC_min = *std::min_element(BC.begin(), BC.end());

    for (unsigned i = 0; i < BC.size(); i++) {
        BC[i] = (BC[i] - BC_min) / (BC_max - BC_min);
    }

    std::cout << std::endl;

    return BC;
}
