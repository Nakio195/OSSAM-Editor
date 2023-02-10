#include "Context.h"

Context::Context() : mAssets(), mFiles(&mAssets), mAnimations(&mAssets), mParticles(&mAssets)
{

}

AssetModel* Context::assets()
{
    return &mAssets;
}

FileModel* Context::files()
{
    return &mFiles;
}

AnimationModel* Context::animations()
{
    return &mAnimations;
}

ParticleModel* Context::particles()
{
    return &mParticles;
}
