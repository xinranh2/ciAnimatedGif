#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"

using ciAnimatedGifRef = std::shared_ptr<class ciAnimatedGif>;

class ciAnimatedGif {
  public:
    ciAnimatedGif() = delete;
    ciAnimatedGif(ci::DataSourceRef data);
    
    static ciAnimatedGifRef create(ci::DataSourceRef data){ return std::make_shared<ciAnimatedGif>(data); }
    
    void update();
    void draw();
    void play();
    void seek( float pct );
    
    const std::vector<ci::Color> getPalette(){ return mColorList; };
    
  protected:
    
    void parseMetadata(ci::DataSourceRef data);
    void printBit(uint8_t byte);
    
    std::vector<ci::SurfaceRef>     mFrameList;
    std::vector<float>              mFrameTimes;
    
    double                          mNextFrameTime = -1;
    int                             mCurFrame = -1;
    ci::gl::TextureRef              mCurTex = nullptr;
    
    std::string                     mHeader;
    
    uint16_t                        canvasWidth, canvasHeight;
    bool                            hasGlobalColorTable = false;
    std::vector<ci::Color>          mColorList;
};