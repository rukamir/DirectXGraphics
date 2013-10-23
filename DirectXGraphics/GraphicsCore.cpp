#include "GraphicsCore.h"

GraphicsCore::GraphicsCore(){
	m_camera		=	new Camera();
	//gStats			=	new GfxStats();

	//D3DXFONT_DESC fpsDesc;
	//fpsDesc.Height          = 20;
 //   fpsDesc.Width           = 5;
 //   fpsDesc.Weight          = FW_BOLD;
 //   fpsDesc.MipLevels       = 0;
 //   fpsDesc.Italic          = false;
 //   fpsDesc.CharSet         = DEFAULT_CHARSET;
 //   fpsDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
 //   fpsDesc.Quality         = DEFAULT_QUALITY;
 //   fpsDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	////fpsDesc.FaceName		=	L"Arial";
 //   //strcpy_s(fpsDesc.FaceName, ("Comic Sans MS"));

	//D3DXCreateFontIndirect(m_Device, &fpsDesc, &statFont);
}

GraphicsCore::~GraphicsCore(){
	delete m_camera;

	if (statFont)
		statFont->Release();
}

void GraphicsCore::Initialize(LPDIRECT3DDEVICE9 device){
	m_Device = device;

	D3DXFONT_DESC fontDesc;
	fontDesc.Height          = 18;
    fontDesc.Width           = 0;
    fontDesc.Weight          = 0;
    fontDesc.MipLevels       = 1;
    fontDesc.Italic          = false;
    fontDesc.CharSet         = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality         = DEFAULT_QUALITY;
    fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    //_tcscpy(fontDesc.FaceName, _T("Times New Roman"));
	strcpy_s(fontDesc.FaceName, "Times New Roman");


	D3DXCreateFontIndirect(m_Device, &fontDesc, &statFont);

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
	calculateFPS(dt);
	//gStats->update(dt);
}

void GraphicsCore::Render(){
	m_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,  D3DCOLOR_XRGB(200,0,0), 1.0f, 0);
	m_Device->BeginScene();

	m_ShaderManager.Render();

	//m_Stats->display();


	////m_FX->SetValue(m_Light, &m_GlobalLight, sizeof(DirectionalLight));
	////m_FX->SetValue(m_EyePos, &camera->m_Position, sizeof(D3DXVECTOR3));

	//UINT numPasses = 0;
	//m_FX->Begin(&numPasses, 0);
	//m_FX->BeginPass(0);

	////D3DXMATRIX CameraVP = m_camera->GetViewMatrix();

	//////iterate throuh mesh components and render
	////for(auto object : GraphicObjects)
	////{
	////}

	//m_FX->EndPass();
	//m_FX->End();


	// Display stats
	DisplayStats();

	m_Device->EndScene();
	m_Device->Present(0, 0, 0, 0);
}

void GraphicsCore::loadMesh(std::string meshName, std::string meshFile){

}

void GraphicsCore::calculateFPS(float dt)
{
      // Make static so that their values persist across
      // function calls.
      static float numFrames   = 0.0f;
      static float timeElapsed = 0.0f;

      // Increment the frame count.
      numFrames += 1.0f;

      // Accumulate how much time has passed.
      timeElapsed += dt;

      if( timeElapsed >= 1.0f )
      {
            // Frames Per Second = numFrames / timeElapsed,
            // but timeElapsed approx. equals 1.0, so
            // frames per second = numFrames.

            mFPS = numFrames;

            // Average time, in milliseconds, it took to render a
            // single frame.
            mMilliSecPerFrame = 1000.0f / mFPS;

            // Reset time counter and frame count to prepare
            // for computing the average stats over the next second.
            timeElapsed = 0.0f;
            numFrames   = 0.0f;
      }
}

void GraphicsCore::DisplayStats()
{

	if (true)
	{
		// Make static so memory is not allocated every frame.
		static char buffer[256];


		sprintf_s(buffer, "FPS %.2f" , mFPS);
 
		RECT R = {50, 50, 0, 0};
		if (statFont)
			statFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(255,255,255));
	}
}
