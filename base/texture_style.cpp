#include "texture_style.h"

texture_style::wrap_style::wrap_style(unsigned int axis, unsigned int style) : m_axis(axis)
, m_style(style)
{

}

texture_style::filter_style::filter_style(unsigned int type, unsigned int style) : m_type(type)
, m_style(style)
{

}

texture_style::texture_style()
{

}

texture_style::~texture_style()
{

}

void texture_style::set_wrap(unsigned int texture_id, unsigned int texture_type, unsigned int axis, unsigned int style)
{
	map<unsigned int, wrap_filter*>::iterator it = m_texture_styles.find(texture_id);
	if ( it == m_texture_styles.end() )
	{
		wrap_filter* _wrap_filter = new wrap_filter();
		_wrap_filter->m_texture_type = texture_type;
		_wrap_filter->m_wrap_styles.push_back(wrap_style(axis, style));
		m_texture_styles.insert(std::make_pair(texture_id, _wrap_filter));
	}
	else
	{
		wrap_filter* _wrap_filter = it->second;
		for (int i = 0; i < _wrap_filter->m_wrap_styles.size(); ++i)
		{
			if (_wrap_filter->m_wrap_styles[i].m_axis == axis)
			{
				_wrap_filter->m_wrap_styles[i].m_style = style;
				return;
			}
		}
		_wrap_filter->m_wrap_styles.push_back(wrap_style(axis, style));
	}
}

void texture_style::set_filter(unsigned int texture_id, unsigned int texture_type, unsigned int filter_type, unsigned int style)
{
	map<unsigned int, wrap_filter*>::iterator it = m_texture_styles.find(texture_id);
	if (it == m_texture_styles.end())
	{
		wrap_filter* _wrap_filter = new wrap_filter();
		_wrap_filter->m_texture_type = texture_type;
		_wrap_filter->m_filter_styles.push_back(filter_style(filter_type, style));
		m_texture_styles.insert(std::make_pair(texture_id, _wrap_filter));
	}
	else
	{
		wrap_filter* _wrap_filter = it->second;
		for (int i = 0; i < _wrap_filter->m_filter_styles.size(); ++i)
		{
			if (_wrap_filter->m_filter_styles[i].m_type == filter_type)
			{
				_wrap_filter->m_filter_styles[i].m_style = style;
				return;
			}
		}
		_wrap_filter->m_filter_styles.push_back(filter_style(filter_type, style));
	}
}

void texture_style::do_set_texture_style()
{
	map<unsigned int, wrap_filter*>::iterator it = m_texture_styles.begin();
	for (; it != m_texture_styles.end(); ++it)
	{
		do_set_wrap_style();
		do_set_filter_style();
	}
}

void texture_style::do_set_wrap_style()
{

}

void texture_style::do_set_filter_style()
{

}

