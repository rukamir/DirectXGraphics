#pragma once

#include <D3dx9math.h>

class BaseComponent{
protected:
	D3DXVECTOR3				*m_pos;
	unsigned int			m_id;
public:
	BaseComponent(){}
	~BaseComponent(){}
	D3DXVECTOR3 GetPosition()
		{return *m_pos;}
	void AssignPosition(D3DXVECTOR3 *pos)
		{m_pos = pos;}
	unsigned int GetID(){return m_id;}
};

class GraphicsComponent
	: public BaseComponent
{
private:
	D3DXVECTOR3				m_scale;
	D3DXQUATERNION			m_heading;
	D3DXCOLOR				m_color;

	DWORD					numMaterials;
	LPD3DXBUFFER			bufMeshMaterial;
	D3DMATERIAL9			*material;    // a pointer to a material buffer
	LPDIRECT3DTEXTURE9		*texture;    // a pointer to a texture
public:
	LPD3DXMESH				m_mesh;
	DWORD					m_shaderFlags;
	GraphicsComponent(){}
	~GraphicsComponent(){}

	D3DXCOLOR			GetColor()
		{return m_color;}
	void				SetColor(float r, float g, float b)
		{m_color = D3DXCOLOR(r, g, b, 0);}

	D3DXVECTOR3			GetScale()
		{return m_scale;}
	void				SetScale(float x, float y, float z)
		{m_scale = D3DXVECTOR3(x, y, z);}
};