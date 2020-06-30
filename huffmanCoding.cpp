#include <bits/stdc++.h>
#include <iomanip>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
#define endl '\n'
#define MOD (1000000007)
#define INF 10000000000000000
// find_by_order(), order_of_key()
#define oset tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define FORI(i,j,n) for(int i=j; i<n; i++)
#define FOR(i, n) FORI(i, 0, n)
#define all(a) a.begin(),a.end()
#define mp make_pair
#define vi vector<int>
#define ss second
#define pb push_back
#define ff first
#define pii pair<int,int>
#define vii vector<pii>
#define pq priority_queue<int>
#define pdq priority_queue<int, vi, greater<int> >
#define gethash(l, r) (MOD-(h[r+1]*p_pow[r-l+1])%MOD+h[l])%MOD;

using namespace __gnu_pbds;
using namespace std;

///Node class for making a tree
struct Node{
    char c;
    int freq;
    Node *left, *right;
};

///Function to make a new tree node
Node* getNode(char c, int freq, Node* left, Node* right){
    Node* t = new Node();
    t->c = c;
    t->freq = freq;
    t->left = left;
    t->right = right;
    return t;
}

///Comparison object so as to order the heap
struct comp{
    bool operator()(Node* left, Node* right){
        ///Highest priority or top most item in pq must have highest freq
        return left->freq > right->freq;
    }
};

///Traverse huffman and store strings in the map for huffman codes;
void encode(Node* root, string str, map<char, string> &huffmanCode){
    ///If root is NULL nothing can be done!
    if(!root) return;

    ///Found a leaf
    if(!root->left && !root->right) huffmanCode[root->c] = str;

    encode(root->left, str+"0", huffmanCode);
    encode(root->right, str+"1", huffmanCode);
}

///Traverse huffman and decode the string given
void decode(Node* root, int &ind, string str){
    ///If root is NULL nothing can be done!
    if(!root) return;

    ///Found a leaf
    if(!root->left && !root->right) {
        cout<<root->c;
        return;
    }

    ind++;
    if(str[ind]=='0') decode(root->left, ind, str);
    else decode(root->right, ind, str);
}

///Building huffman and finally, decoding it!
void buildHuffman(string text){
    ///Counts and stores frequency of every occuring character
    map<char, int> freq;
    for(auto c:text){
        ///Updating frequency
        freq[c]++;
    }

    ///Creating priority queue for storing leaves of the huffman tree
    priority_queue<Node*, vector<Node*>, comp> tree;

    ///Creating leaf node of each character stored in the map and insert in root;
    for(auto p: freq){
        tree.push(getNode(p.ff, p.ss, NULL, NULL));
    }

    ///Creating tree
    while(tree.size()!=1){
        ///Remove two nodes with highest priority ie lowest frequency from tree
        Node* left = tree.top(); tree.pop();
        Node* right = tree.top(); tree.pop();

        ///Create new node with these two as its children and push a new node with freq = sum of both children
        int sum = left->freq + right->freq;
        tree.push(getNode(NULL, sum, left, right));
    }

    ///Root stores pointer to root of huffman tree
    Node* root = tree.top();

    ///CREATED!

    ///Traverse the whole huffman tree and store huffman codes in map
    map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout<<"HUFFMAN CODES ARE: \n"<<endl;

    ///Printing codes for each character
    for(auto p: huffmanCode){
        cout<<p.ff<<" : "<<p.ss<<endl;
    }
    cout<<endl;

    cout<<"Original string was: \n"<<text<<endl;
    cout<<endl;

    ///Appending code
    string res = "";
    for(char c:text) res+=huffmanCode[c];

    ///Printing huffman coded string for the given text;
    cout<<"Encoded string is: \n"<<res<<endl;

    ///Traversing the huffman tree again so as to decode the string res
    int index = -1;
    cout<<"\nDecoded string is: \n";
    while(index<res.size()-2){
        decode(root, index, res);
    }
    cout<<endl<<endl;

    ///Finding compression ratio
    int org = 8*text.length();
    int conv = ceil(res.length()/8);
    double compressionRate = (double)conv/org;
    cout<<"String is compressed to "<<compressionRate*100<<"% of the total size."<<endl;
}

///Huffman coding begins
signed main()
{
    fastIO
    string str;
    getline(cin, str);

    buildHuffman(str);

    return 0;
}
