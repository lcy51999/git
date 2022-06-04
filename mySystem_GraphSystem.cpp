//********************************************
// Student Name			:junkai-liu
// Student ID			:110654047
// Student Email Address:chengyu.sc10@nycu.edu.tw
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>
#include<cmath>
#include<vector>
using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 1000;
int Param::GRAPH_MAX_NUM_EDGES = 1000;

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    mFlgAutoNodeDeletion = false;
    initMemoryPool(); 
    reset();
    createDefaultGraph();
    //
    // Implement your own stuff
    //
}
void GRAPH_SYSTEM::initMemoryPool()
{
    mNodeArr_Pool = new GRAPH_NODE[Param::GRAPH_MAX_NUM_NODES];
    mEdgeArr_Pool = new GRAPH_EDGE[Param::GRAPH_MAX_NUM_EDGES];
    
    mActiveNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
    mActiveEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];

    mFreeNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
    mFreeEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];

    reset();
   
}
void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
    mCurNumOfFreeNodes = Param::GRAPH_MAX_NUM_NODES;
    mCurNumOfFreeEdges = Param::GRAPH_MAX_NUM_EDGES;

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;

    for (int i = 0; i < mCurNumOfFreeNodes; ++i)
        mFreeNodeArr[i] = i;
    for (int i = 0; i < mCurNumOfFreeEdges; ++i)
        mFreeEdgeArr[i] = i;


}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    reset( );
    //
    // Implement your own stuff
    //
    GRAPH_NODE node[3];
    node[0].id = addNode(0.0, 0.0, 0.0);
    node[1].id = addNode(0.0, 0.0, 5.0);
    node[2].id = addNode(5.0, 0.0, 0.0);


    addEdge(node[1].id, node[2].id);
    addEdge(node[2].id, node[0].id);
    /*GRAPH_EDGE edge[2];
    edge[0].id = addEdge(node[1].id, node[2].id);
    edge[1].id = addEdge(node[2].id, node[0].id);
    /*node[1].edgeID.push_back(edge[0].id);
    node[2].edgeID.push_back(edge[0].id);
    node[2].edgeID.push_back(edge[1].id);
    node[0].edgeID.push_back(edge[1].id);*/
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    vector<vector<GRAPH_NODE>> node;
    node.resize(n);
    for (int i = 0; i < n; i++)
        node[i].resize(2);

    const double pi = acos(-1);
    double angle = 0;
    for (double i = 0; i < n; i++) {
        for (int j = 0; j <2; j++) {
            node[i][j].id = addNode((r + d * j) * cos(angle), 0.0, (r + d * j) * sin(angle));
        }
        angle += 2 * pi / n;
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset();

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
        vector<vector<GRAPH_NODE>> node;
    node.resize(n);
    for (int i = 0; i < n; i++)
        node[i].resize(num_layers+1);

    const double pi = acos(-1);
    double angle = 0;
    for (double i = 0; i <n; i ++) {
        for (int j = 0; j <=num_layers; j++) {
            node[i][j].id= addNode(r * cos(angle) * (j+1), 0.0, r * sin(angle) *(j+1) );
        }
        angle += 2 * pi / n;
    }

}
void GRAPH_SYSTEM::createNet_Square(int n, int num_layers)
{
    reset();

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
    vector<vector<GRAPH_NODE>> node;
    node.resize(num_layers);
    for (int i = 0; i < num_layers; i++)
        node[i].resize(num_layers);

    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < num_layers; j++) {
            if ((i > n && i <= 2 * n) && (j > n && j <= 2 * n)) continue;
            
            node[i][j].id = addNode(d * (i - num_layers / 2), 0.0, d * (j - num_layers));
        }
    }
    
    /*for (int i = 0; i < num_layers - 1; i++) {
        for (int j = 0; j < num_layers; j++) {
            if ((i >= n && i <= 2 * n) && (j > n && j <= 2 * n)) continue;

            

        }
    }
    /*for (int i = 0; i < num_layers ; i++) {
        for (int j = 0; j < num_layers-1; j++) {
            if ((i > n && i <= 2 * n) && (j > n && j <= 2 * n)) continue;

            addEdge(node[i][j], node[i][j+1]);

        }
    }*/
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset();

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //    
    vector<GRAPH_NODE> node;
    node.resize(n+1);
    node[0].id = addNode(0.0, 0.0, 0.0);
    const double pi = acos(-1);
    double angle = 0;
    for (int i = 1; i <= n; i++) {
        node[i].id = addNode(r * cos(angle), 0.0, r * sin(angle));
        angle += 2 * pi / n;
    }

}
GRAPH_NODE* GRAPH_SYSTEM::getFreeNode() {
    if (mCurNumOfFreeNodes == 0) return 0;
    --mCurNumOfFreeNodes;
    int id = mFreeNodeArr[mCurNumOfFreeNodes];
    GRAPH_NODE* n = &mNodeArr_Pool[id];
    mActiveNodeArr[mCurNumOfActiveNodes] = id;
    n->dynamicID = mCurNumOfActiveNodes;
    ++mCurNumOfActiveNodes;
    return n;


}
GRAPH_EDGE* GRAPH_SYSTEM::getFreeEdge() {
    if (mCurNumOfFreeEdges == 0) return 0;
    --mCurNumOfFreeEdges;
    int id = mFreeEdgeArr[mCurNumOfFreeEdges]; 
    GRAPH_EDGE* e = &mEdgeArr_Pool[id];
    mActiveEdgeArr[mCurNumOfActiveEdges] = id; 
    e->dynamicID = mCurNumOfActiveEdges;
    ++mCurNumOfActiveEdges;
    return e;

}

// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    //
    // Implement your own stuff
    //  
    GRAPH_NODE* g;
    g = getFreeNode();
    if (g == 0) return -1; // invalid id.
    g->p = vector3(x, y, z);
    g->r = r;
    g->edgeID.clear();
    return g->id;


}


// return edge id
int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    //
    // Implement your own stuff
    //  
    GRAPH_EDGE* e;
    e = getFreeEdge();
    if (e == 0) return -1;
    e->nodeID[0] = nodeID_0;
    e->nodeID[1] = nodeID_1;
    mNodeArr_Pool[nodeID_0].edgeID.push_back(e->id);
    mNodeArr_Pool[nodeID_1].edgeID.push_back(e->id);
    return e->id;


}


void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    //
    cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
    cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
    cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
    cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << " " << endl;
    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << " " << endl;
    cout << "A selected node is highlighted as red." << endl;

}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE *n = 0;
    //
    // Implement your own stuff
    // 
    return n;
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
    //
    // Implement your own stuff
    // 
    // mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    // 

}
void GRAPH_SYSTEM::deletEdge(int edgeID) {
 
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    //
    // Implement your own stuff
    // 
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    //
    //
    // Implement your own stuff
    // 
    //if(isSelectedNode)
        //return true;

    return false;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    // r = mSelectedNode->r;
    // p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 
}



void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(24);
        mSelectedNode = 0;

        break;

    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'g':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    //
    int id = mActiveNodeArr[nodeIndex];
    GRAPH_NODE* node = &mNodeArr_Pool[id];
    r = node->r;
    p = node->p;
 
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfActiveEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    vector3 position;
    //
    // Implement your own stuff
    //
    int id = mActiveEdgeArr[edgeIndex];
    const GRAPH_EDGE* edge = &mEdgeArr_Pool[id];
    
    int node_id = edge->nodeID[nodeIndex];
    const GRAPH_NODE* node = &mNodeArr_Pool[node_id];
    
    position = node->p;
    return position;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;

    Sleep(250);
    //
    //
    // Implement your own stuff
    // 

}


