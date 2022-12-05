#ifndef _TEXTURE_STYLE_H
#define _TEXTURE_STYLE_H

#include <vector>
#include <map>
using namespace std;

class node_state;
class texture_style
{
	friend class node_state;

	struct wrap_style
	{
		wrap_style(unsigned int axis, unsigned int style);
		unsigned int m_axis; //�����ᣨX��Y�ᣩ
		unsigned int m_style; //���Ʒ�ʽ
	};

	struct filter_style
	{
		filter_style(unsigned int type, unsigned int style);
		unsigned int m_type; // GL_TEXTURE_MIN_FILTER GL_TEXTURE_MAG_FILTER
		unsigned int m_style; //���˷�ʽ
	};

	struct wrap_filter
	{
		unsigned int m_texture_type; //�������� 2D��3D
		vector<wrap_style> m_wrap_styles;
		vector<filter_style> m_filter_styles;
	};

public:
	texture_style();
	~texture_style();
	void set_wrap(unsigned int texture_id, unsigned int texture_type, unsigned int axis, unsigned int style);
	void set_filter(unsigned int texture_id, unsigned int texture_type, unsigned int filter_type, unsigned int style);

protected:
	void do_set_texture_style();
private:
	void do_set_wrap_style();
	void do_set_filter_style();
private:
	map<unsigned int, wrap_filter*> m_texture_styles;
};
#endif //_TEXTURE_STYLE_H
