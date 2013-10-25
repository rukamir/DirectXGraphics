#include "ShaderManager.h"

ShaderManager::ShaderManager(){
}

ShaderManager::~ShaderManager(){
}

void ShaderManager::Initialize(LPDIRECT3DDEVICE9 device){
	m_Device = device;

	// Call Funcs to set up shaders
	SetUpBasic();
}

bool ShaderManager::Register(DWORD flags, GraphicsComponent *ent){
	// Create graphics component


	// If this flag is on push back
	if (flags && BASIC)
		m_mRegistry.find(flags && BASIC)->second->push_back(ent);
	else
		return false;

	// All flags good
	return true;
}

void ShaderManager::Render(D3DXMATRIX view, D3DXMATRIX proj){
	D3DXMATRIX Translation, Rotation, Scale;

	// Begin passes.
	UINT numPasses = 0;

	//for (const auto &ent : *m_mRegistry.find(BASIC)->second)
	//{
	//	(mFX->Begin(&numPasses, 0));
	//	for(UINT i = 0; i < numPasses; ++i)
	//	{
	//		(mFX->BeginPass(i));

	//		D3DXMatrixScaling(&Scale, 1, 1, 1);
	//		//D3DXMatrixRotationQuaternion(&Rotation, &m_qHeading);
	//		D3DXMatrixIdentity(&Rotation);
	//		D3DXMatrixTranslation(&Translation, 
	//							  ent->GetPosition().x, 
	//							  ent->GetPosition().y, 
	//							  ent->GetPosition().z );

	//		(mFX->SetVector(mhColor, 
	//						&D3DXVECTOR4(ent->GetColor().r, ent->GetColor().g, ent->GetColor().b, 0.0f)));
	//		(mFX->SetMatrix(mhWVP, &(Scale*Rotation*Translation*view*proj)));
	//		(mFX->CommitChanges());
	//		(ent->m_mesh->DrawSubset(0));

	//		(mFX->EndPass());
	//	}
	//	(mFX->End());
	//}
}

void ShaderManager::SetUpBasic(){
	// Create FX
	ID3DXBuffer* errors = 0;
	D3DXCreateEffectFromFile(m_Device, 
							 "Shaders/color.fx", 
							 0, 0, 0, 0, 
							 &mFX, 
							 &errors);
	if( errors )
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	// Get handles
	mhTech		= mFX->GetTechniqueByName("ColorTech");
	mhWVP		= mFX->GetParameterByName(0, "gWVP");
	mhColor		= mFX->GetParameterByName(0, "CustCol");

	mFX->SetVector(mhColor, &D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f));
	mFX->SetTechnique(mhTech);

	// add to map
	m_mRegistry.insert( make_pair(BASIC, new vector<GraphicsComponent*>) );
}