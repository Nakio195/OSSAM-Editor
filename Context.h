#ifndef CONTEXT_H
#define CONTEXT_H

#include "AssetModel.h"
#include "AnimationManager/AnimationModel.h"
#include "FileManager/FileModel.h"
#include "ParticleManager/ParticleModel.h"

class Context
{
    public:
        Context();

        AssetModel* assets();
        FileModel* files();
        AnimationModel* animations();
        ParticleModel* particles();

    private:
        AssetModel mAssets;
        FileModel mFiles;
        AnimationModel mAnimations;
        ParticleModel mParticles;

};

#endif // CONTEXT_H
