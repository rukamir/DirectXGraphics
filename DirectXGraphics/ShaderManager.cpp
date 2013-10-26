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
	if ((flags & BASIC) == BASIC)
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

	for (const auto &ent : *m_mRegistry.find(BASIC)->second)
	{
		(mFX->Begin(&numPasses, 0));
		for(UINT i = 0; i < numPasses; ++i)
		{
			(mFX->BeginPass(i));

			D3DXMatrixScaling(&Scale, 1, 1, 1);
			D3DXMatrixIdentity(&Rotation);
			D3DXMatrixTranslation(&Translation, 
								  ent->GetPosition().x, 
								  ent->GetPosition().y, 
								  ent->GetPosition().z );

			(mFX->SetMatrix(mhWVP, &(Scale*Rotation*Translation*view*proj)));

			for(DWORD i = 0; i < ent->GetMeshComponents()->numMaterials; i++)    // loop through each subset
			{
				if (ent->GetMeshComponents()->texture)
					mFX->SetTexture(mhTexture, ent->GetMeshComponents()->texture[i]);
				mFX->CommitChanges();
				//gD3DDev->SetMaterial(&material[i]);    // set the appropriate material for the subset
				//if(texture[i] != NULL)    // if the subset has a texture (if texture is not NULL)
				//	gD3DDev->SetTexture(0, texture[i]);    // ...then set the texture
				ent->GetMeshComponents()->mesh->DrawSubset(i);    // draw the subset
			}
			//(ent->GetMeshComponents()->mesh->DrawSubset(0));

			(mFX->EndPass());
		}
		(mFX->End());
	}
}

void ShaderManager::SetUpBasic(){
	// Create FX
	ID3DXBuffer* errors = 0;
	D3DXCreateEffectFromFile(m_Device, 
							 "Shaders/Transform.fx", 
							 0, 0, 0, 0, 
							 &mFX, 
							 &errors);
	if( errors )
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	//// Get handles
	//mhTech		= mFX->GetTechniqueByName("ColorTech");
	//mhWVP		= mFX->GetParameterByName(0, "gWVP");
	//mhColor		= mFX->GetParameterByName(0, "CustCol");
	//mhTexture	= mFX->GetParameterByName(0, "gTexture");
	// Get handles
	mhTech		= mFX->GetTechniqueByName("TransformTech");
	mhWVP		= mFX->GetParameterByName(0, "gWVP");
	mhTexture	= mFX->GetParameterByName(0, "gTexture");


	//mFX->SetVector(mhColor, &D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f));
	mFX->SetTechnique(mhTech);

	// add to map
	m_mRegistry.insert( make_pair(BASIC, new vector<GraphicsComponent*>) );
}