#include "../base/viewer.h"
#include "../base/node.h"
#include "stencil_test.h"


/*
当片段着色器处理完一个片段之后，模板测试(Stencil Test)会开始执行，
和深度测试一样，它也可能会丢弃片段。接下来，被保留的片段会进入深度测试

一个模板缓冲中，（通常）每个模板值(Stencil Value)是8位的。所以每个像素/片段一共能有256种不同的模板值。
我们可以将这些模板值设置为我们想要的值，然后当某一个片段有某一个模板值的时候，
我们就可以选择丢弃或是保留这个片段了

使用模板缓冲的时候你可以尽情发挥，但大体的步骤如下:
启用模板缓冲的写入。
渲染物体，更新模板缓冲的内容。
禁用模板缓冲的写入。
渲染（其它）物体，这次根据模板缓冲的内容丢弃特定的片段。

*/

int main()
{
	node* root = new node;
	root->add_child(new stencil_test());
	viewer* _viewer = new viewer;
	_viewer->set_scene(root);
	_viewer->run();
	return 0;
}