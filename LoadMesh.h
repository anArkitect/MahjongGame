#ifndef __LOADMESH_H__
#define __LOADMESH_H__


#include <string>
#include <GL/glew.h>
#include "assimp/Scene.h"

struct MeshData
{
   unsigned int mVao;
   unsigned int mVboVerts;
   unsigned int mVboNormals;
   unsigned int mVboTexCoords;
   unsigned int mIndexBuffer;
   float mScaleFactor; //TODO replace with bounding box
   unsigned int mNumIndices;
   const aiScene* mScene;
   aiVector3D mBbMin, mBbMax;
   MeshData::MeshData(): mVao(-1), mVboVerts(-1), mVboNormals(-1), mVboTexCoords(-1), mIndexBuffer(-1),
						 mScaleFactor(0.0f), mNumIndices(0), mScene(NULL), drawEnabled(true), 
						 holdStatus(false), explosionStatus(false), exploStartTimeAllowed(false), 
						 hoverOver(false), exploStartTime(0){}
      
   // Zhiwen
   std::string tileContent;
   float exploStartTime;
   bool drawEnabled;
   bool holdStatus;
   bool hoverOver;
   bool explosionStatus;
   bool exploStartTimeAllowed;
   
   
};


void BufferIndexedVerts(MeshData& meshdata);
MeshData LoadMesh( const std::string& pFile);
void GetBoundingBox (const aiScene* scene, aiVector3D* min, aiVector3D* max);
void GetBoundingBox (const aiMesh* mesh, aiVector3D* min, aiVector3D* max);

#endif