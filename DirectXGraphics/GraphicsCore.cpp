#include "GraphicsCore.h"

GraphicsCore::GraphicsCore(){
	m_camera		=	new Camera();
	//gStats			=	new GfxStats();
}

GraphicsCore::~GraphicsCore(){
	delete m_camera;
}

void GraphicsCore::Initialize(LPDIRECT3DDEVICE9 device){
}

void GraphicsCore::Shutdown(){
}

void GraphicsCore::OnResetDevice(){
	D3DVIEWPORT9 viewport;
	m_Device->GetViewport(&viewport);

	//camera->OnResetDevice(viewport.Width, viewport.Height);
}

void GraphicsCore::OnLostDevice(){
	// handle->OnLostDevice()
}

void GraphicsCore::Update(float dt){
	m_camera->Update();
	//gStats->update(dt);
}

void GraphicsCore::Render(){
	m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,  D3DCOLOR_XRGB(200,200,200), 1.0f, 0);
	m_Device->BeginScene();

	//m_FX->SetValue(m_Light, &m_GlobalLight, sizeof(DirectionalLight));
	//m_FX->SetValue(m_EyePos, &camera->m_Position, sizeof(D3DXVECTOR3));

	UINT numPasses = 0;
	m_FX->Begin(&numPasses, 0);
	m_FX->BeginPass(0);

	D3DXMATRIX CameraVP = m_camera->GetViewMatrix();

	////iterate throuh mesh components and render
	//for(auto object : GraphicObjects)
	//{
	//}

	m_FX->EndPass();
	m_FX->End();

	//m_Stats->display();

	m_Device->EndScene();
	m_Device->Present(0, 0, 0, 0);
}

void GraphicsCore::loadMesh(std::string meshName, std::string meshFile){

}