struct Edge {
    int u, v;
};

bool cut[N];
int pre[N], bccno[N], dfs_clock, bcc_cnt;
vector<int> G[N], bcc[N];
stack<Edge> S;

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        Edge e = (Edge) {u, v};
        if (!pre[v]) {
            S.push(e);
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= pre[u]) {
                cut[u] = true;
                bcc_cnt++;
                bcc[bcc_cnt].clear();
                for (;;) {
                    Edge x = S.top();
                    S.pop();
                    if (bccno[x.u] != bcc_cnt) { bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt; }
                    if (bccno[x.v] != bcc_cnt) { bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt; }
                    if (x.u == u && x.v == v) break;
                }
            }
        } else if (pre[v] < pre[u] && v != fa) {
            S.push(e);
            lowu = min(lowu, pre[v]);
        }
    }
    if (fa < 0 && child == 1) cut[u] = false;
    return lowu;
}

void find_bcc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(cut, 0, sizeof(cut));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for (int i = 0; i < n; i++)
        if (!pre[i]) dfs(i, -1);
}
