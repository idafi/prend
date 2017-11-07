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
			// import the scene
			FbxScene *scene = FbxScene::Create(fbxMan, "scene");
			importer->Import(scene);

			// don't do anything else until a mesh is located
			FbxMesh *mesh = FindMesh(scene->GetRootNode());
			if(mesh)
			{
				// convert to y-up/z-forward/right-hand axis system
				FbxAxisSystem sys(FbxAxisSystem::OpenGL);
				sys.ConvertScene(scene);

				// convert to meter-based unit system
				FbxSystemUnit::m.ConvertScene(scene);

				// get transform to apply to mesh vertex positions
				FbxNode *node = mesh->GetNode();
				FbxAMatrix mat = node->EvaluateGlobalTransform();

				// get counts
				int vertexCount = mesh->GetControlPointsCount();
				int indexCount = mesh->GetPolygonVertexCount();
				
				// get vertex data
				float *positions = GetPositions(mesh, vertexCount, mat);
				uint16 *indices = GetIndices(mesh, indexCount);
				float *colors = GetColors(mesh, indices, indexCount, vertexCount);

				// done
				data = new ModelData(positions, colors, vertexCount, indices, indexCount);
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
	
	float *FBXImporter::GetPositions(const FbxMesh * const mesh, int vertexCount, const FbxAMatrix& transform)
	{
		FbxVector4 *fbxPositions = mesh->GetControlPoints();	// source positions
		float *positions = new float[vertexCount * 3];			// we convert to float array and discard the w component

		// convert
		for(int i = 0; i < vertexCount; i++)
		{
			// apply node transform
			FbxVector4 fbxPoint = fbxPositions[i];
			fbxPoint = transform.MultT(fbxPoint);

			int baseIndex = i * 3;
			positions[baseIndex] = (float)(fbxPoint[0]);
			positions[baseIndex + 1] = (float)(fbxPoint[1]);
			positions[baseIndex + 2] = (float)(fbxPoint[2]);
		}

		return positions;
	}
	
	uint16 *FBXImporter::GetIndices(const FbxMesh * const mesh, int indexCount)
	{
		int *fbxIndices = mesh->GetPolygonVertices();	// source indices
		uint16 *indices = new uint16[indexCount];		// we can just copy these directly

		// copy
		for(int v = 0; v < indexCount; v++)
		{ indices[v] = fbxIndices[v]; }

		return indices;
	}

	float *FBXImporter::GetColors(const FbxMesh * const mesh, uint16 *indices, int indexCount, int vertexCount)
	{
		const FbxGeometryElementVertexColor *colorElement = mesh->GetElementVertexColor();
		float *colors = new float[vertexCount * 4];

		for(int i = 0; i < indexCount; i++)
		{
			int index = indices[i];

			// the source color is grabbed directly from each source vertex...
			int colorIndex = colorElement->GetIndexArray().GetAt(i);
			FbxColor fbxCol = colorElement->GetDirectArray().GetAt(colorIndex);

			// ...but it's mapped to a specific destination vertex via the vertex's array index
			int baseI = index * 4;
			colors[baseI] = (float)(fbxCol.mRed);
			colors[baseI + 1] = (float)(fbxCol.mGreen);
			colors[baseI + 2] = (float)(fbxCol.mBlue);
			colors[baseI + 3] = (float)(fbxCol.mAlpha);
		}

		return colors;
	}
}