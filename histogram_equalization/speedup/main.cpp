#include <iostream>
#include <fstream>
#include <array>
#include <vector>
using namespace std;

// A simple algorithm to calculate speedup for sequential/parallel time comparison. Use with resized images time values, from 1000x1000 to 10000x10000
int  main()
{
    //sequential
    fstream myfile1("../sequential_times_for_speedup_forest.txt", ios_base::in);
    
    //parallel
    fstream myfile2("../parallel_times_for_speedup_forest.txt", ios_base::in);

    double a, b, c, d, e, f, g, h, i, l, m, n, o, p, q, r, s, t, u, v, y, z;
    //float n, o, p, q, r, s, t, u, v, y, z;
    myfile1 >> a >> b >> c >> d >> e >> f >> g >> h >> i >> l;
    myfile2 >> n >> o >> p >> q >> r >> s >> t >> u >> v >> y;
    vector<double> speedup_vector;
    speedup_vector.push_back(a/n);
    speedup_vector.push_back(b/o);
    speedup_vector.push_back(c/p);
    speedup_vector.push_back(d/q);
    speedup_vector.push_back(e/r);
    speedup_vector.push_back(f/s);
    speedup_vector.push_back(g/t);
    speedup_vector.push_back(h/u);
    speedup_vector.push_back(i/v);
    speedup_vector.push_back(l/y);
    //speedup_vector.push_back(m/z);
    size_t count = speedup_vector.size();
    
    //saving result
    ofstream out("../speedup_times.txt");
    for(int i = 0; i < count; i++){
        string x = to_string(speedup_vector[i]);
        cout << x << endl;
        out << x << endl;
    }

    return 0;
}


