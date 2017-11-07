#pragma once

// - - - - - -
// Autodesk FBX importer - imports vertices as Model-friendly ModelData
// - - - - - -

#include <fbxsdk.h>
#include "Video.hpp"

namespace Video
{
	class FBXImporter
	{
		public:
			FBXImporter();
			~FBXImporter();
			
			ModelData *ImportModel(char const * const filePath);
			
		private:
			FbxManager *fbxMan;
			FbxImporter *importer;
			
			FbxMesh *FindMesh(FbxNode * const rootNode);
			float *GetPositions(const FbxMesh * const mesh, int vertexCount, const FbxAMatrix& transform);
			uint16 *GetIndices(const FbxMesh * const mesh, int indexCount);
			float *GetColors(const FbxMesh * const mesh, uint16 *indices, int indexCount, int vertexCount);
	};
}