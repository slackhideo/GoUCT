/* Node.h */

#ifndef __NODE_H__
#define __NODE_H__

class Node {
    public:
        int wins;
        int visits;

        int x, y; /* Position of move */

        Node *child;
        Node *sibling;

        Node(int x, int y);
        void update(int val);
        double getWinRate();
};

#endif /* __NODE_H__ */
