//
// Prof. Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_ImageEditor.h"

#define IMAGE_FILE_NAME "3d-flower-desktop.jpg"

#define IMAGE_MAX_HIERARCHY_DEPTH 8
using namespace std;
IMAGE_SYSTEM::IMAGE_SYSTEM()
{
    m_ImageHierarchy = 0;
    m_Image = new ns_opengl::Image;
    m_Image->readFile(IMAGE_FILE_NAME);

    int wImage, hImage;
        m_Image->getInfo(wImage, hImage);

    int cur_depth = 0;
     int start_x = 0;
    int start_y = 0;

        int w = wImage;
        int h = hImage;
        float sx = 2; 
        float sy = 2;

        float radius = wImage/2.0*(sx+sy)*0.5;

    m_ImageHierarchy = new IMAGE_NODE(
        cur_depth, 
        start_x,
        start_y,
        w,
        h,
        sx,
        sy,
        radius
        ); 
    float r, g, b;
    computeAverageColor(start_x, start_y, w, h, r, g, b);

    m_ImageHierarchy->setColor(r,g,b);
    m_ImageHierarchy->computeDrawPosition( 
        wImage, hImage
        );
    //
}

void IMAGE_SYSTEM::reset()
{
    int wImage, hImage;
    m_Image->getInfo(wImage, hImage);

    int cur_depth = 0;
    int start_x = 0;
    int start_y = 0;

    int w = wImage;
    int h = hImage;
    float sx = 2;
    float sy = 2;

    float radius = wImage / 2.0 * (sx + sy) * 0.5;

    m_ImageHierarchy = new IMAGE_NODE(
        cur_depth,
        start_x,
        start_y,
        w,
        h,
        sx,
        sy,
        radius
    );
    float r, g, b;
    computeAverageColor(start_x, start_y, w, h, r, g, b);
    m_ImageHierarchy->setColor(r, g, b);
    m_ImageHierarchy->computeDrawPosition(
        wImage, hImage
    );
}

void IMAGE_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    switch(key) {
    case ' ':
        break;
    case '.':
    case '<':
        break;
    case ',':
    case '>': 
        break;
    case 'r':
        reset();
        break;
    
    case 'k':
    case 'K':
        break;
    case 'l':
    case 'L':
        break;
    }
}

//
// Compute the node color.
// That is compute the average color of the block of the node
//
void IMAGE_SYSTEM::computeNodeColor(IMAGE_NODE *node)
{
    
    computeAverageColor(node->start_x, 
        node->start_y, 
        node->w, 
        node->h, 
        node->r, 
        node->g, 
        node->b);

    //node->setColor(r, g, b);
}

//
// Explore a node if it is not explored.
// Go down the children if the node is explored.
//
void IMAGE_SYSTEM::exploreImageNode(IMAGE_NODE *node, double x, double y)
{
    if (!node) return;

    if (node->flg_explored) {
        // If the node has been explored, 
        // go to check its children
        for (int i = 0; i < 4; i++) {
            exploreImageNode(node->children[i], x, y);
        }
    } 
    else {
        // The node is not explored yet.
        // Now, explored it.
        // Do the following steps:
        // Can we explore it? If the dimension is less than 1x1, return.
        // If the dimension is at least 2x2
        //
        // Divide the image block into four children
        // Compute the draw positions of each child.
        //

        if (node->w <2 || node->h < 2) return;
        //

        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);

        float dx = x - node->draw_x;
        float dy = y - node->draw_y;
        float d2 = dx * dx + dy * dy;
        float r2 = node->radius * node->radius;
        if (d2 > r2) return;
        node->flg_explored = true;
        IMAGE_NODE* children[4] = {nullptr};

        children[0] = new IMAGE_NODE;
        children[0]->radius = node->radius / 2;
        children[0]->start_x = node->start_x;
        children[0]->start_y = node->start_y;
        children[0]->w = node->w / 2;
        children[0]->h = node->h / 2;
        children[0]->sx = node->sx;
        children[0]->sy = node->sy;

        children[1] = new IMAGE_NODE;
        children[1]->radius = node->radius / 2;
        children[1]->start_x = node->start_x ;
        children[1]->start_y = node->start_y + (node->h) / 2;
        children[1]->w = node->w / 2;
        children[1]->h = node->h / 2;
        children[1]->sx = node->sx;
        children[1]->sy = node->sy;

        children[2] = new IMAGE_NODE;
        children[2]->radius = node->radius / 2;
        children[2]->start_x = node->start_x+(node->w) / 2;
        children[2]->start_y = node->start_y + (node->h) / 2;
        children[2]->w = node->w / 2;
        children[2]->h = node->h / 2;
        children[2]->sx = node->sx;
        children[2]->sy = node->sy;

        children[3] = new IMAGE_NODE;
        children[3]->radius = node->radius / 2;
        children[3]->start_x = node->start_x +(node->w)/2;
        children[3]->start_y = node->start_y ;
        children[3]->w = node->w / 2;
        children[3]->h = node->h / 2;
        children[3]->sx = node->sx;
        children[3]->sy = node->sy;

        for (int i = 0; i < 4; ++i) {
            if (children[i] == nullptr) continue;
            computeNodeColor(children[i]);
            children[i]->computeDrawPosition(children[i]->w, children[i]->h);
            node->children[i] = children[i]; // set children
            cout << children[i]->start_x << " " << children[i]->start_y << " "
                << children[i]->draw_x << " " << children[i]->draw_y << " "
                << (children[i]->start_x + children[i]->w / 2) * children[i]->sx << " " << hImage * children[i]->sy - (children[i]->start_y + children[i]-> h / 2) * children[i]->sy << endl;

        }
    }
}

//
// call exploreImageNode(root, mouse_x, mouse_y)
//
void IMAGE_SYSTEM::handlePassiveMouseEvent( double x, double y )
{
    //std::cout << "IMAGE_SYSTEM Mouse:" << x << "\t" << y << std::endl;
    
    exploreImageNode(m_ImageHierarchy,x,y);
}


