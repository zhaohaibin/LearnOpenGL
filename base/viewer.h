#ifndef _VIEWER_H
#define _VIEWER_H

class node;
class viewer
{
public:
	void set_scene(node* root);

	int run();

private:
	node* m_root;
};
#endif //_VIEWER_H
