freetext: linkedlist trie
	g++ main.cpp -o freetext

trie: trienode
	g++ trie.h -o trie

trienode: avltreedict linkedlist
	g++ trienode.h -o trienode

avltreedict: avltree kvpair linkedlist
	g++ avltreedictionary.h -o avltreedictionary

avltree: linkedlist bstnode
	g++ avltree.h -o avltree

bstnode:
	g++ bstnode.h -o bstnode

kvpair:
	g++ KVPair.h -o kvpair

linkedlist: node
	g++ LinkedList.h -o linkedlist

node:
	g++ node.h -o node