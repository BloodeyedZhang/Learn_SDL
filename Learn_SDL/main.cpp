//
//  main.cpp
//  Learn_SDL
//
//  Created by 张佳俊 on 2019/6/9.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* mWindow = nullptr;
SDL_Renderer* mRenderer = nullptr;

SDL_Texture* LoadImage(std::string filename, SDL_Renderer *mRenderer) {
    SDL_Texture* mTexture = nullptr;
    mTexture = IMG_LoadTexture(mRenderer, filename.c_str());
    if (mTexture == nullptr)
        throw std::runtime_error("Fail to load image: " + filename + SDL_GetError());
    return mTexture;
}

void ApplySurface(int x, int y, SDL_Texture *mTexture, SDL_Renderer *mRenderer, SDL_Rect *clip = NULL) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    //Detect if we should use clip width settings or texture width
    if (clip != NULL) {
        pos.w = clip->w;
        pos.h = clip->h;
    }
    else
        SDL_QueryTexture(mTexture, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(mRenderer, mTexture, clip, &pos);
}

int main(int argc, const char * argv[]) {
    bool quit = false;
    SDL_Event event;
    // 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    // 额外使用了图片库,需要单独初始化
    IMG_Init(IMG_INIT_JPG);
    // 创建窗口
    mWindow = SDL_CreateWindow("lesson 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }
    // 创建渲染器
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }
    
    // 加载bmp格式图片
    SDL_Texture *mBackground = nullptr, *mSmile = nullptr;
    std::string resRoot = "/Users/zhangjiajun/work/MyLearning/Learn_SDL/Resources/lesson5/";
    try {
//        mBackground = LoadImage((resRoot + "background.png").c_str(), mRenderer);
        mSmile = LoadImage((resRoot + "image.png").c_str(), mRenderer);
    }
    catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return 4;
    }
    int iW = 100, iH = 100, column = 0;
    SDL_Rect clips[4];
    for (int i = 0; i < 4; i++) {
        if (i != 0 && i % 2 == 0)
            column++;
        clips[i].x = column * iW;
        clips[i].y = (i % 2) * iH;
        clips[i].w = iW;
        clips[i].h = iH;
    }
    int useClip = 0;
    // 绘制图像
    SDL_RenderClear(mRenderer);  //清空渲染器
    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                    // 用户从菜单要求退出程序
    //            case SDL_QUIT:
    //                quit = true;
    //                break;
                case SDLK_1:
                    useClip = 0;
                    break;
                case SDLK_2:
                    useClip = 1;
                    break;
                case SDLK_3:
                    useClip = 2;
                    break;
                case SDLK_4:
                    useClip = 3;
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                default:
                    break;
            }
            // 绘制图像
            SDL_RenderClear(mRenderer);  //清空渲染器
            // 把贴图材质复制到渲染器上
            ApplySurface(clips[useClip].x, clips[useClip].y, mSmile, mRenderer, &clips[useClip]);
        }

        
        // 显示出来
        SDL_RenderPresent(mRenderer);
    }
    
    
    // 释放内存
    SDL_DestroyTexture(mBackground);
    SDL_DestroyTexture(mSmile);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    
    
    IMG_Quit();
    SDL_Quit();

    return 0;
}
