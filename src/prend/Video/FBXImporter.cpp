#include "Video.hpp"

namespace Video
{
	FBXImporter::FBXImporter()
	{
		fbxMan = FbxManager::Create();
		
		FbxIOSettings *ioSettings = FbxIOSettings::Create(fbxMan, IOSROOT);
		fbxMan->SetIOSettings(ioSettings);
		
		importer = FbxImporter::Create(fbxMan, "");
	}
	
	FBXImporter::~FBXImporter()
	{
		fbxMan->Destroy();
	}
	
	ModelData *FBXImporter::ImportModel(const char * const filePath)
	{
		AssertPtr(filePath);
		AssertPtr(fbxMan);
		AssertPtr(importer);
		
		ModelData *data = NULL;
		
		if(importer->Initialize(filePath, -1, fbxMan->GetIOSettings()))
		{
			FbxScene *scene = FbxScene::Create(fbxMan, "scene");
			importer->Import(scene);
			
			FbxMesh *mesh = FindMesh(scene->GetRootNode());
			if(mesh)
			{
				int posCount;
				int colCount;
				int idxCount;
				
				float *pos = GetPositions(mesh, &posCount);
				float *col = GetColors(mesh, &colCount);
				uint16 *idx = GetIndices(mesh, &idxCount);
				
				// make sure we didn't get more color data than position data
				if(posCount != colCount)
				{
					LogWarning("vertex position count (%i) does not match vertex color count (%i)", posCount, colCount);
					posCount = min(posCount, colCount);
				}
				
				data = new ModelData(pos, col, colCount, idx, idxCount);
			}
			else
			{ LogError("failed to import FBX file\n\tno meshes found"); }
		}
		else
		{ LogError("failed to import FBX file\n\t%s", importer->GetStatus().GetErrorString()); }
		
		importer->Destroy();
		return data;
	}
	
	FbxMesh *FBXImporter::FindMesh(FbxNode * const node)
	{
		AssertPtr(node);
		
		// see if we found a mesh on this node
		FbxMesh *m = node->GetMesh();
		if(m)
		{ return m; }
		
		// if not, recurse until we do
		int childCount = node->GetChildCount();
		if(childCount > 0)
		{
			for(int i = 0; i < childCount; i++)
			{
				m = FindMesh(node->GetChild(i));
				if(m)
				{ return m; }
			}
		}
		
		return NULL;
	}
	
	float *FBXImporter::GetPositions(const FbxMesh * const mesh, int *count)
	{
		int posCount = mesh->GetControlPointsCount();		// position count
		FbxVector4 *fbxPoints = mesh->GetControlPoints();	// position vectors
		float *positions = new float[posCount * 3];			// we'll pack them into a GL-friendly float array
		
		for(int i = 0; i < posCount; i++)
		{
			// pack 3d vector data into the float array
			// (we don't care about the w coordinate in this case)
			FbxVector4 fbxPoint = fbxPoints[i];
			int baseIndex = i * 3;
			positions[baseIndex] = (float)(fbxPoint[0]);
			positions[baseIndex + 1] = (float)(fbxPoint[1]);
			positions[baseIndex + 2] = (float)(fbxPoint[2]);
		}
		
		*count = posCount;
		return positions;
	}
	
	float *FBXImporter::GetColors(FbxMesh * const mesh, int *count)
	{
		FbxGeometryElementVertexColor *vertexColor = mesh->GetElementVertexColor();
		
		// try to remap any vertex color setup beyond 1 color per vertex
		int result = vertexColor->RemapIndexTo(FbxLayerElement::eByControlPoint);
		switch(result)
		{
			case 1:
				LogNote("successfully remapped vertex colors");
				break;
			case 0:
				LogError("error remapping vertex colors");
				break;
			case -1:
				LogError("impossible to remap vertex colors");	// we really should figure out multi-color vertices, though
				break;
		}

		FbxLayerElementArrayTemplate<int>& indices = vertexColor->GetIndexArray();		// color array indices
		FbxLayerElementArrayTemplate<FbxColor>& array = vertexColor->GetDirectArray();	// color array
		int colorCount = indices.GetCount();		// color count
		float *colors = new float[colorCount * 4];	// we'll pack them into a GL-friendly float array
		
		for(int i = 0; i < colorCount; i++)
		{
			// get the color corresponding to this color index
			int index = indices[i];
			FbxColor color = array[index];
			int baseIndex = i * 4;
			
			// pack it
			colors[baseIndex] = (float)(color.mRed);
			colors[baseIndex + 1] = (float)(color.mGreen);
			colors[baseIndex + 2] = (float)(color.mBlue);
			colors[baseIndex + 3] = (float)(color.mAlpha);
		}
		
		*count = colorCount;
		return colors;
	}
	
	uint16 *FBXImporter::GetIndices(const FbxMesh * const mesh, int *count)
	{
		int indexCount = mesh->GetPolygonVertexCount();
		int *indices = mesh->GetPolygonVertices();
		
		uint16 *outIndices = new uint16[indexCount];
		for(int i = 0; i < indexCount; i++)
		{ outIndices[i] = (uint16)(indices[i]); }
		
		*count = indexCount;
		return outIndices;
	}
}