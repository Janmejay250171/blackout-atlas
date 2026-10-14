#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int u;
    int v;
    int cost;
};

const int n = 6;
const int m = 8;
const int INF = 1e9;

string names[n] = {
    "Main Block",
    "Library",
    "Computer Lab",
    "Hostel",
    "Administration",
    "Medical Centre"
};

Edge edges[m] = {
    {0, 1, 4},
    {0, 4, 3},
    {1, 2, 2},
    {1, 4, 5},
    {2, 3, 4},
    {3, 5, 3},
    {4, 5, 6},
    {2, 4, 2}
};

int costMat[n][n];
int statusMat[n][n];

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            costMat[i][j] = -1;
            statusMat[i][j] = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int c = edges[i].cost;
        costMat[u][v] = c;
        costMat[v][u] = c;
        statusMat[u][v] = 0;
        statusMat[v][u] = 0;
    }
}

void show() {
    cout << "\n--- Campus Buildings ---\n";
    for (int i = 0; i < n; i++) {
        cout << i << ". " << names[i] << "\n";
    }
    cout << "\n--- Campus Connections ---\n";
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int st = statusMat[u][v];
        cout << "[" << (i + 1) << "] " << names[u] << " -- " << names[v]
             << " | Repair Cost: " << costMat[u][v] << " | Status: ";
        if (st == 0) {
            cout << "Working\n";
        } else if (st == 1) {
            cout << "Failed (repairable)\n";
        } else {
            cout << "Unavailable\n";
        }
    }
    cout << "\n";
}

void failEdge() {
    cout << "Enter connection number (1-" << m << "): ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "Invalid input.\n\n";
        return;
    }
    if (id < 1 || id > m) {
        cout << "Invalid connection number.\n\n";
        return;
    }

    int idx = id - 1;
    int u = edges[idx].u;
    int v = edges[idx].v;

    if (statusMat[u][v] == 2) {
        cout << "Connection is already unavailable. Restore it first.\n\n";
        return;
    }

    if (statusMat[u][v] == 1) {
        cout << "Connection is already failed (repairable).\n";
        cout << "Mark it as Unavailable? (1 = Yes, 2 = No): ";
        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "Invalid input.\n\n";
            return;
        }
        if (opt == 1) {
            statusMat[u][v] = 2;
            statusMat[v][u] = 2;
            cout << "Connection [" << id << "] " << names[u] << " -- " << names[v]
                 << " updated to Unavailable.\n\n";
        } else {
            cout << "Connection is already down. No changes made.\n\n";
        }
        return;
    }

    cout << "Select failure mode:\n";
    cout << "1. Failed but repairable\n";
    cout << "2. Unavailable and not repairable\n";
    cout << "Enter choice (1-2): ";
    int mode;
    if (!(cin >> mode)) {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "Invalid input.\n\n";
        return;
    }

    if (mode == 1) {
        statusMat[u][v] = 1;
        statusMat[v][u] = 1;
        cout << "Connection [" << id << "] " << names[u] << " -- " << names[v]
             << " marked as Failed (repairable).\n\n";
    } else if (mode == 2) {
        statusMat[u][v] = 2;
        statusMat[v][u] = 2;
        cout << "Connection [" << id << "] " << names[u] << " -- " << names[v]
             << " marked as Unavailable.\n\n";
    } else {
        cout << "Invalid failure mode selected.\n\n";
    }
}

void restoreEdge() {
    cout << "Enter connection number to restore (1-" << m << "): ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "Invalid input.\n\n";
        return;
    }
    if (id < 1 || id > m) {
        cout << "Invalid connection number.\n\n";
        return;
    }

    int idx = id - 1;
    int u = edges[idx].u;
    int v = edges[idx].v;

    if (statusMat[u][v] == 0) {
        cout << "Connection is already working. No change needed.\n\n";
        return;
    }

    statusMat[u][v] = 0;
    statusMat[v][u] = 0;
    cout << "Connection [" << id << "] " << names[u] << " -- " << names[v]
         << " restored to working state.\n\n";
}

void reset() {
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        statusMat[u][v] = 0;
        statusMat[v][u] = 0;
    }
    cout << "Network reset: all connections are restored to working state.\n\n";
}

void bfs() {
    bool vis[n];
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    queue<int> q;
    vector<int> order;

    q.push(0);
    vis[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v = 0; v < n; v++) {
            if (costMat[u][v] > 0 && statusMat[u][v] == 0 && !vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    cout << "\n--- BFS Network Diagnosis ---\n";
    cout << "Starting Building: " << names[0] << " (0)\n";
    cout << "Traversal Order: ";
    for (size_t i = 0; i < order.size(); i++) {
        cout << names[order[i]];
        if (i + 1 < order.size()) {
            cout << " -> ";
        }
    }
    cout << "\n\n";

    cout << "Reachable Buildings (" << order.size() << "):\n";
    for (size_t i = 0; i < order.size(); i++) {
        cout << "  - " << names[order[i]] << "\n";
    }

    int discCount = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            discCount++;
        }
    }

    if (discCount == 0) {
        cout << "\nDiagnosis: All buildings are reachable. No building is currently disconnected.\n\n";
    } else {
        cout << "\nDisconnected Buildings (" << discCount << "):\n";
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                cout << "  - " << names[i] << " (Building " << i << ")\n";
            }
        }
        cout << "\nDiagnosis: Network partition detected!\n\n";
    }
}

void prim() {
    int key[n];
    int par[n];
    bool st[n];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        par[i] = -1;
        st[i] = false;
    }

    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        int minKey = INF;

        for (int i = 0; i < n; i++) {
            if (!st[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }
        }

        if (u == -1) {
            cout << "\nRecovery Plan Failed: Complete recovery is impossible.\n";
            cout << "Remaining available connections cannot connect every building.\n\n";
            return;
        }

        st[u] = true;

        for (int v = 0; v < n; v++) {
            if (costMat[u][v] > 0 && !st[v]) {
                int w = INF;
                if (statusMat[u][v] == 0) {
                    w = 0;
                } else if (statusMat[u][v] == 1) {
                    w = costMat[u][v];
                }

                if (w < INF && w < key[v]) {
                    key[v] = w;
                    par[v] = u;
                }
            }
        }
    }

    cout << "\n--- Minimum-Cost Recovery Plan (Prim's MST) ---\n";
    int totalCost = 0;
    int repairCount = 0;

    for (int i = 1; i < n; i++) {
        int u = par[i];
        int v = i;
        int edgeStatus = statusMat[u][v];
        cout << names[u] << " -- " << names[v] << " | ";
        if (edgeStatus == 0) {
            cout << "Status: Working | Additional Repair Cost: 0\n";
        } else {
            cout << "Status: Needs Repair | Additional Repair Cost: " << costMat[u][v] << "\n";
            totalCost += costMat[u][v];
            repairCount++;
        }
    }

    cout << "------------------------------------------------\n";
    if (repairCount == 0) {
        cout << "All buildings are already connected through working connections.\n";
        cout << "No repairs are required.\n";
    } else {
        cout << "Repairs required: " << repairCount << " connection(s).\n";
    }
    cout << "Total Recovery Cost: " << totalCost << "\n\n";
}

int main() {
    init();
    int choice;
    while (true) {
        cout << "=================================\n";
        cout << " Blackout Atlas - Campus Network\n";
        cout << "=================================\n";
        cout << "1. Show campus network\n";
        cout << "2. Simulate connection failure\n";
        cout << "3. Diagnose network using BFS\n";
        cout << "4. Calculate recovery plan using Prim\n";
        cout << "5. Restore a connection\n";
        cout << "6. Reset campus network\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "Invalid input. Please enter a valid number.\n\n";
            continue;
        }

        if (choice == 0) {
            cout << "Exiting Blackout Atlas. Goodbye.\n";
            break;
        } else if (choice == 1) {
            show();
        } else if (choice == 2) {
            failEdge();
        } else if (choice == 3) {
            bfs();
        } else if (choice == 4) {
            prim();
        } else if (choice == 5) {
            restoreEdge();
        } else if (choice == 6) {
            reset();
        } else {
            cout << "Invalid choice. Please select from 0 to 6.\n\n";
        }
    }
    return 0;
}
