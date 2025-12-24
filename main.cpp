#include <ctime>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// A struct containing Transaction data 

struct TransactionData { // Alice to Bob --> 
	double amount; // amount that is being transacted 
	string senderKey; // key of the sender 
	string receiverKey; // key of the reciever
	time_t timestamp; // timestamp of the transaction 
};

// - - --- -- - -- - -- - - - - -- - -- -- - --- - -- - -- -- - -- -- - - -- - - - - -- - --- - -- -- //

// Block Class - has its index, hash, previous hash and data


// Understanding the blocks
// 1. In private: store hash, store prev hash, index, also generate hash with func
// 2. In public: constructor function with 

// -- -- -- -- -- -- -- -- -- -- - - - - - - - - -- - - - --  -- - - - - - - -- - - - - - - - - - -- //

class Block
{
private:
	int index;
	size_t blockHash;
	size_t previousHash;
	size_t generateHash();


public: 
	// Constructor 
	Block(int idx, TransactionData d, size_t prevHash); // Block here is a function which takes 
	// 3 parameters here rn, index, data about transaction and prev hash?

	// Get Original Hash
	size_t getHash(); // an unsigned integer type used to represent the size of objects in bytes and
	// for array indexing and loop counting

	//Get Previous Hash 
	size_t  getPreviousHash();

	//Transaction Data
	TransactionData d;

	// Validate The Hash 
	bool isHashValid();
	

};

// Constructor with some params
Block::Block(int idx, TransactionData data, size_t prevHash) {
	index = idx;
	d = data;
	previousHash = prevHash;
	blockHash = generateHash();
}

// Private Functions 

size_t Block::generateHash()
{
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalHash;

	string toHash = to_string(d.amount) + d.receiverKey + d.senderKey + to_string(d.timestamp);

	return finalHash(hash1(toHash) + hash2(previousHash));


}

// Public Functions
size_t Block::getHash()
{
	return blockHash;
}

size_t Block::getPreviousHash()
{
	return previousHash;
}

bool Block::isHashValid() {
	return generateHash() == blockHash;
}

//											Blockchain 
// 1. This class contains a vector of blocks 
// 2. calls the Blockchain constructor function - creates the genesis block
// 3. has an add block function which adds new blocks to the chain 
// 4. has a function to check if the chain is valid after every new block is added


class Blockchain

{
private:
	Block createGenesisBlock();
public:
	/// we need a chain PUBLIC
	vector<Block> chain; // this is a vector of type Block ( chain of blocks in vector) 

	// constructor 
	Blockchain();
		
	// Public 
	void addBlock(TransactionData data);
	bool isChainValid();

	// Contrieved Example for Demo only
	Block* getLatestBlock();


};


// Blockchain Constructor 
		
Blockchain::Blockchain() // from the class blockchain you created a constructor
{
	Block genesis = createGenesisBlock(); // created the genesis block, this is the first block to run 
	chain.push_back(genesis);			  // push back to add elements to the end of this chain.
}

// what you have to do is define a function called createGenesisBlock that belongs to the Blockchain class and returns a BLOCK
Block Blockchain::createGenesisBlock()	  // this means that the function will return an object type of BLOCK. Block is the return type
{
	time_t current;						// all this is 0 and empty because this is the genesis block
	TransactionData d;
	d.amount = 0;
	d.receiverKey = "None";
	d.senderKey = "None";
	d.timestamp = time(&current);

	std::hash<int> hash1; // Converts data into a fixed-size number (called a hash value) --- Data -> Blender -> Number 
	Block genesis(0, d, hash1(0));
	return genesis;
}



Block* Blockchain::getLatestBlock()
{
	return &chain.back();

}

void Blockchain::addBlock(TransactionData d)
{
	int index = (int)chain.size();
	Block newBlock(index, d, getLatestBlock()->getHash());
	chain.push_back(newBlock); // you create the newBlock but you also have to push it to the chain

}

bool Blockchain::isChainValid()                       // return a bool about if Chain is Valid
{
	vector<Block>::iterator it;						// iterates over a vector type block
	int chainLen = (int)chain.size();	// c++ size of a vector it returns something other than an INT so we cast it  
	
	for (it = chain.begin(); it != chain.end(); ++it) // -iterating the vector
	{	
		Block currentBlock = *it;
		if (!currentBlock.isHashValid()) // if the current block doesnt have a valid hash
		{
			// !!! INVALID !!!
			return false;
		}

		if (chainLen > 1)
		{
			Block previousBlock = *(it - 1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash())
			{
				return false;
			}
		}

	}
    return true;
}


int main()
{
	/// Start Blockchain!!!
	Blockchain KenCoin;

	/// Data for first added block
	TransactionData data1;
	time_t data1Time; // trasanction data needs a time stamp 
	data1.amount = 1.5;
	data1.receiverKey = "Brad";
	data1.senderKey = "Alex";
	data1.timestamp = time(&data1Time);


	KenCoin.addBlock(data1);

	cout << "Is chain valid?" << endl
		<< KenCoin.isChainValid() << endl;
	

}



/// We have run this but the output seems to be 54. whys that


// 1. You never add the new block to the chain.
