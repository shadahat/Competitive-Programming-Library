#include <bits/stdc++.h>

using namespace std;

const int MAX = 100010;
const int MAXC = 256;

struct SuffixTreeNode {
	struct SuffixTreeNode *children[MAXC];
	struct SuffixTreeNode *suffixLink;
	// (start,end) of node X contains the info of the edge between X
	// and it's parent P
	int start;
	int *end;
	int suffixIndex; // for leaf nodes
};

typedef struct SuffixTreeNode Node;

char text[MAX]; //Input string
Node *root = NULL; //Pointer to root node

Node *lastNewNode = NULL;
Node *activeNode = NULL;

int activeEdge = -1;
int activeLength = 0;

int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
int size = -1; //Length of input string

Node *newNode(int start, int *end) {
	Node *node =(Node*) malloc(sizeof(Node));
	for (int i = 0; i < MAXC; i++) node->children[i] = NULL;

	/*For root node, suffixLink will be set to NULL
	For internal nodes, suffixLink will be set to root
	by default in current extension and may change in
	next extension*/
	node->suffixLink = root;
	node->start = start;
	node->end = end;

	/*suffixIndex will be set to -1 by default and
	actual suffix index will be set later for leaves
	at the end of all phases*/
	node->suffixIndex = -1;
	return node;
}

int edgeLength(Node *n) {
	return *(n->end) - (n->start) + 1;
}

int walkDown(Node *currNode) {
	if (activeLength >= edgeLength(currNode)) {
		activeEdge += edgeLength(currNode);
		activeLength -= edgeLength(currNode);
		activeNode = currNode;
		return 1;
	}
	return 0;
}

void extendSuffixTree(int pos) {
	leafEnd = pos;
	remainingSuffixCount++;
	lastNewNode = NULL;

	//Add all suffixes (yet to be added) one by one in tree
	while(remainingSuffixCount > 0) {
		if (activeLength == 0) activeEdge = pos; //APCFALZ

		if (activeNode->children[text[activeEdge]] == NULL) {
			activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);
			if (lastNewNode != NULL) {
				lastNewNode->suffixLink = activeNode;
				lastNewNode = NULL;
			}
		}
		else {
			Node *next = activeNode->children[text[activeEdge]];
			if (walkDown(next)) {//Do walkdown
				//Start from next node (the new activeNode)
				continue;
			}
			if (text[next->start + activeLength] == text[pos]) {
				if(lastNewNode != NULL && activeNode != root) {
					lastNewNode->suffixLink = activeNode;
					lastNewNode = NULL;
				}
				activeLength++;
				break;
			}
			splitEnd = (int*) malloc(sizeof(int));
			*splitEnd = next->start + activeLength - 1;
			Node *split = newNode(next->start, splitEnd);
			activeNode->children[text[activeEdge]] = split;
			split->children[text[pos]] = newNode(pos, &leafEnd);
			next->start += activeLength;
			split->children[text[next->start]] = next;

			if (lastNewNode != NULL) lastNewNode->suffixLink = split;

			lastNewNode = split;
		}

		remainingSuffixCount--;
		if (activeNode == root && activeLength > 0) {//APCFER2C1
			activeLength--;
			activeEdge = pos - remainingSuffixCount + 1;
		}
		else if (activeNode != root) //APCFER2C2
			activeNode = activeNode->suffixLink;
	}
}

void print(int i, int j){
	for (int k=i; k<=j; k++) printf("%c", text[k]);
}

//Print the suffix tree as well along with setting suffix index
//So tree will be printed in DFS manner
//Each edge along with it's suffix index will be printed
void setSuffixIndexByDFS(Node *n, int labelHeight){
	if (n == NULL) return;
	if (n->start != -1) { //A non-root node
		//Print the label on edge from parent to current node
		print(n->start, *(n->end));
	}
	int leaf = 1;
	for (int i = 0; i < MAXC; i++) {
		if (n->children[i] != NULL) {
			if (leaf == 1 && n->start != -1) printf(" [%d]\n", n->suffixIndex);
			//Current node is not a leaf as it has outgoing edges from it.
			leaf = 0;
			setSuffixIndexByDFS(n->children[i], labelHeight + edgeLength(n->children[i]));
		}
	}
	if (leaf == 1) {
		n->suffixIndex = size - labelHeight;
		printf(" [%d]\n", n->suffixIndex);
	}
}

void freeSuffixTreeByPostOrder(Node *n) {
	if (n == NULL) return;
	for (int i = 0; i < MAXC; i++) {
		if (n->children[i] != NULL) freeSuffixTreeByPostOrder(n->children[i]);
	}
	if (n->suffixIndex == -1) free(n->end);
	free(n);
}

/*Build the suffix tree and print the edge labels along with
suffixIndex. suffixIndex for leaf edges will be >= 0 and
for non-leaf edges will be -1*/
void buildSuffixTree() {
	size = strlen(text);
	int i;
	rootEnd = (int*) malloc(sizeof(int));
	*rootEnd = - 1;

	/*Root is a special node with start and end indices as -1,
	as it has no parent from where an edge comes to root*/
	root = newNode(-1, rootEnd);

	activeNode = root; //First activeNode will be root
	for (i=0; i<size; i++)
		extendSuffixTree(i);
	int labelHeight = 0;
	setSuffixIndexByDFS(root, labelHeight);

	//Free the dynamically allocated memory
	freeSuffixTreeByPostOrder(root);
}

int main() {
	strcpy(text, "abcabxabcd$"); buildSuffixTree();
	return 0;
}
