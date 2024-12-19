#include <iostream>
using namespace std;
#include <unordered_map>
#include <queue>
#include <string>



/** 
 * Linked List to create 
 * the Huffman Tree
**/
struct Node
{
    /* data*/
    char textChar;      //Store the text character
    int charFreq;       //Store the frequency character
    Node *left, *right; 
    Node(char ch, int cf) : textChar(ch), charFreq(cf), left(nullptr), right(nullptr){}
};
/**
 * Compare the value when pushing the value to the queue
 * and store data in min heap way.
**/
struct Comparator{
    bool operator()(Node* l, Node* r ){
        return l->charFreq > r->charFreq;
    }

};

void Huffman_Encoding(const string& text);
void Generate_Codes(Node *root, const string& str, unordered_map<char, string>& huffmanCode);

int main(){
   const string text = "abacdbabdbbaccd";
    Huffman_Encoding(text);
    
}
/**
 * @function Name   Huffman_Encoding
 * @parameters      string
 * @description     Take the string and convert to huffmann Tree
*/
void Huffman_Encoding(const string& text){
    std::unordered_map<char, int> freq;
    //Get the frequebncy of each character
    for(char character:text){
        freq[character]++;
    }
    // for (const auto& pair : freq) {
//     std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
// }
    // Now sort the data from smallest frequency to high.
    priority_queue<Node*, vector<Node*>, Comparator> pq;
    for(auto& pair: freq){
    pq.push(new Node(pair.first, pair.second));
    }
    // while(!pq.empty()){
    //     Node *node = pq.top();
    //     pq.pop();
    //     cout<<"Charater: "<<node->textChar<<" Frequency: "<<node->charFreq<<endl;
    // }

    // Creating ther huffman tree
    while(pq.size()>1){
    Node *left = pq.top();
    pq.pop();
    Node *right= pq.top();
    pq.pop();
    Node* newNode = new Node('\0', left->charFreq + right->charFreq);
    newNode->left = left;
    newNode->right = right;
    pq.push(newNode);
    }
    Node *root = pq.top();
    unordered_map<char, string> huffmanCode;
    Generate_Codes(root, "", huffmanCode);

    // Print encoded text
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << '\n';
    }
    string encodedText = "";
    for (char ch : text) {
        encodedText += huffmanCode[ch];
    }
    cout << "\nEncoded text:\n" << encodedText << '\n';
}
/**
 * @function Name   Generate_Codes
 * @parameters      Hufmann tree root Node, String, Map
 * @description     Take the tree and convert to huffman codes
*/
void Generate_Codes(Node *root, const string& str, unordered_map<char, string>& huffmanCode){
    if(root == nullptr){
        return;
    }
    if(!root->left && !root->right){
        huffmanCode[root->textChar]= str;
    }
    Generate_Codes(root->left, str + "0", huffmanCode );
    Generate_Codes(root->right, str + "1", huffmanCode );
}

